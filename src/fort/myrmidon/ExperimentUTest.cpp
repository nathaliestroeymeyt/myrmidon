#include <gtest/gtest.h>

#include "Experiment.hpp"
#include "Query.hpp"
#include "UtilsUTest.hpp"
#include "TestSetup.hpp"

namespace fort {
namespace myrmidon {

class PublicExperimentUTest : public ::testing::Test {
protected:
	void SetUp();
	void TearDown();

	Experiment::Ptr experiment;
};


void PublicExperimentUTest::SetUp() {
	experiment = Experiment::Create(TestSetup::UTestData().Basedir() / "public-experiment.myrmidon");
}
void PublicExperimentUTest::TearDown() {
	experiment.reset();
}



TEST_F(PublicExperimentUTest,OpeningDataLess) {
	Experiment::Ptr dataless;
	ASSERT_NO_THROW({experiment = Experiment::Open(TestSetup::UTestData().CurrentVersionFile().AbsoluteFilePath);});
	ASSERT_TRUE(experiment);
	ExperimentDataInfo dataInformation;
	ASSERT_NO_THROW({dataInformation = Query::GetDataInformations(*experiment);});

	EXPECT_EQ(dataInformation.Spaces.size(),2);
	ASSERT_EQ(dataInformation.Spaces[1].TrackingDataDirectories.size(),
	          TestSetup::UTestData().NestDataDirs().size());
	size_t i = -1;
	for( const auto & tddInfo : TestSetup::UTestData().NestDataDirs() ) {
		EXPECT_EQ(dataInformation.Spaces[1].TrackingDataDirectories[++i].URI,
		          tddInfo.AbsoluteFilePath.filename());
	}
	ASSERT_EQ(dataInformation.Spaces[2].TrackingDataDirectories.size(),
	          TestSetup::UTestData().ForagingDataDirs().size());
	i = -1;
	for( const auto & tddInfo : TestSetup::UTestData().ForagingDataDirs() ) {
		EXPECT_EQ(dataInformation.Spaces[2].TrackingDataDirectories[++i].URI,
		          tddInfo.AbsoluteFilePath.filename());
	}


	ASSERT_NO_THROW({dataless = Experiment::OpenDataLess(TestSetup::UTestData().CurrentVersionFile().AbsoluteFilePath);});
	ASSERT_NO_THROW({dataInformation = Query::GetDataInformations(*dataless);});
	ASSERT_EQ(dataInformation.Spaces.size(),2);
	EXPECT_TRUE(dataInformation.Spaces[1].TrackingDataDirectories.empty());
	EXPECT_TRUE(dataInformation.Spaces[2].TrackingDataDirectories.empty());

	// Ant information is conserved
	EXPECT_EQ(experiment->Ants().size(),3);
	EXPECT_EQ(dataless->Ants().size(),3);
	for ( const auto & [antID,expected] : experiment->Ants() ) {
		ASSERT_EQ(dataless->Ants().count(antID),1) << "   AntID: " << FormatAntID(antID);
		const auto & ant = dataless->Ants().at(antID);
		ASSERT_EQ(ant->Capsules().size(),expected->Capsules().size());
		i = -1;
		for ( const auto & [eShapeType,eCapsule] : expected->Capsules() ) {
			const auto & [shapeType,capsule] = ant->Capsules()[++i];
			EXPECT_EQ(shapeType,eShapeType)
				<< "  With i: " << i << std::endl
				<< "   AntID: " << FormatAntID(antID);
			EXPECT_CAPSULE_EQ(*capsule,*eCapsule)
				<< "  With i: " << i << std::endl
				<< "   AntID: " << FormatAntID(antID);
		}
		ASSERT_EQ(ant->Identifications().size(),expected->Identifications().size());
		i = -1;
		for ( const auto & eIdentification : expected->Identifications() ) {
			const auto & identification = ant->Identifications()[++i];
			EXPECT_EQ(identification->TagValue(),eIdentification->TagValue())
				<< "  With i: " << i << std::endl
				<< "   AntID: " << FormatAntID(antID);
			EXPECT_TIME_EQ(identification->Start(),eIdentification->Start())
				<< "  With i: " << i << std::endl
				<< "   AntID: " << FormatAntID(antID);
			EXPECT_TIME_EQ(identification->End(),eIdentification->End())
				<< "  With i: " << i << std::endl
				<< "   AntID: " << FormatAntID(antID);
		}

	}

	// They point to the same file
	EXPECT_EQ(experiment->AbsoluteFilePath(),
	          TestSetup::UTestData().CurrentVersionFile().AbsoluteFilePath);
	EXPECT_EQ(dataless->AbsoluteFilePath(),
	          TestSetup::UTestData().CurrentVersionFile().AbsoluteFilePath);


	EXPECT_THROW(Experiment::Open(TestSetup::UTestData().Basedir() / "does-not-exists.myrmidon"),
	             std::runtime_error);
	EXPECT_THROW(Experiment::OpenDataLess(TestSetup::UTestData().Basedir() / "does-not-exists.myrmidon"),
	             std::runtime_error);

}


TEST_F(PublicExperimentUTest,FileManipulation) {
	fs::path dirs[2] = {TestSetup::UTestData().Basedir()/ "test-manipulation",
	               TestSetup::UTestData().Basedir()/ "test-manipulation-new"};
	for ( const auto & d : dirs ) {
		ASSERT_NO_THROW(fs::create_directories(d));
	}
	auto filepath = dirs[0] / "test.myrmidon";
	auto goodNewPath = dirs[0] / "test2.myrmidon";
	auto badNewPath =  dirs[1]/ "test.myrmidon";
	auto e = Experiment::Create(filepath);
	EXPECT_NO_THROW(e->Save(filepath));
	EXPECT_NO_THROW(e->Save(goodNewPath));
	EXPECT_THROW(e->Save(badNewPath),std::invalid_argument);
}

TEST_F(PublicExperimentUTest,SpaceManipulation) {
	Space::Ptr spaces[2] =
		{
		 experiment->CreateSpace("nest"),
		 experiment->CreateSpace("foraging"),
		};

	ASSERT_EQ(experiment->Spaces().size(),2);
	// they are indeed the same objects
	EXPECT_NO_THROW({
			EXPECT_EQ(experiment->Spaces().at(spaces[0]->ID()),
			          spaces[0]);
		});
	EXPECT_NO_THROW({
			EXPECT_EQ(experiment->Spaces().at(spaces[1]->ID()),
			          spaces[1]);
		});
	EXPECT_THROW({
			experiment->DeleteSpace(42);
		},std::out_of_range);

	EXPECT_NO_THROW(experiment->DeleteSpace(spaces[0]->ID()));
	EXPECT_EQ(experiment->Spaces().size(),1);
	EXPECT_EQ(experiment->Spaces().count(spaces[0]->ID()),0);
	EXPECT_EQ(experiment->Spaces().count(spaces[1]->ID()),1);
	const auto & tdd = TestSetup::UTestData().ForagingDataDirs().front();

	experiment->AddTrackingDataDirectory(spaces[1]->ID(),
	                                     tdd.AbsoluteFilePath);
	EXPECT_THROW({
			experiment->DeleteSpace(spaces[1]->ID());
		},std::runtime_error);
}


TEST_F(PublicExperimentUTest,TDDManipulation) {
	auto foragingID = experiment->CreateSpace("foraging")->ID();
	auto nestID = experiment->CreateSpace("nest")->ID();

	fs::path foragingTDDPath = TestSetup::UTestData().ForagingDataDirs().front().AbsoluteFilePath;
	fs::path nestTDDPath = TestSetup::UTestData().NestDataDirs().front().AbsoluteFilePath;

	fs::path badTDDPath = TestSetup::UTestData().Basedir() / "does-not-exist.0000";

	std::string URI;
	EXPECT_THROW({
			experiment->AddTrackingDataDirectory(42,
			                                     foragingTDDPath);
		},std::out_of_range);

	EXPECT_THROW({
			experiment->AddTrackingDataDirectory(foragingID,
			                                     badTDDPath);
		},std::runtime_error);

	EXPECT_NO_THROW({
			URI = experiment->AddTrackingDataDirectory(foragingID,foragingTDDPath);
		});
	EXPECT_EQ(URI,foragingTDDPath.filename());

	// Note nestTDDPath and goodTDDPath overlaps in time
	EXPECT_THROW({
			experiment->AddTrackingDataDirectory(foragingID,
			                                     nestTDDPath);
		},std::domain_error);

	// Note goodTDDPath is already in use in another space
	EXPECT_THROW({
			experiment->AddTrackingDataDirectory(nestID,
			                                     foragingTDDPath);
		},std::invalid_argument);

	EXPECT_NO_THROW({
			URI = experiment->AddTrackingDataDirectory(nestID,nestTDDPath);
		});
	EXPECT_EQ(URI,nestTDDPath.filename());

	EXPECT_THROW({
			experiment->RemoveTrackingDataDirectory(badTDDPath.filename());
		},std::invalid_argument);
	EXPECT_NO_THROW({
			experiment->RemoveTrackingDataDirectory(URI);
		});

}

TEST_F(PublicExperimentUTest,AntManipulation) {
	auto a = experiment->CreateAnt();
	ASSERT_EQ(experiment->Ants().count(a->ID()),1);
	// they are the same objects
	EXPECT_EQ(experiment->Ants().at(a->ID()),a);

	EXPECT_THROW({
			experiment->DeleteAnt(42);
		},std::out_of_range);

	ASSERT_NO_THROW({
			experiment->AddIdentification(a->ID(),
			                              0,
			                              Time::SinceEver(),
			                              Time::Forever());
		});

	EXPECT_THROW({
			experiment->DeleteAnt(a->ID());
		},std::runtime_error);

	ASSERT_NO_THROW({
			experiment->DeleteIdentification(a->Identifications().front());
		});

	EXPECT_NO_THROW({
			experiment->DeleteAnt(a->ID());
		});
}

TEST_F(PublicExperimentUTest,IdentificationManipulation) {
	Ant::Ptr ants[2] =
		{
		 experiment->CreateAnt(),
		 experiment->CreateAnt(),
		};
	EXPECT_THROW({
			experiment->AddIdentification(42,
			                              0,
			                              Time::SinceEver(),
			                              Time::Forever());
		},std::out_of_range);

	EXPECT_NO_THROW(experiment->AddIdentification(ants[0]->ID(),
	                                              0,
	                                              Time::SinceEver(),
	                                              Time::Forever()));

	EXPECT_THROW({
			experiment->AddIdentification(ants[0]->ID(),
			                              1,
			                              Time(),
			                              Time::Forever());
		}, OverlappingIdentification);

	EXPECT_THROW({
			experiment->AddIdentification(ants[1]->ID(),
			                              0,
			                              Time::SinceEver(),
			                              Time::Forever());
		}, OverlappingIdentification);

	EXPECT_NO_THROW({
			experiment->AddIdentification(ants[1]->ID(),
			                              1,
			                              Time::SinceEver(),
			                              Time::Forever());
		});

	auto e2 = Experiment::Create("foo.myrmidon");
	auto a2 = e2->CreateAnt();
	auto i2 = e2->AddIdentification(a2->ID(),0,Time::SinceEver(),Time::Forever());

	// cannot delete Identification from another Experiment
	EXPECT_THROW({
			experiment->DeleteIdentification(i2);
		},std::invalid_argument);


	ants[0]->Identifications().front()->SetEnd(Time());
	EXPECT_THROW({
			experiment->FreeIdentificationRangeAt(ants[0]->Identifications().front()->TagValue(),
			                                      Time().Add(-1));
		},std::runtime_error);

	EXPECT_NO_THROW({
			auto res =
				experiment->FreeIdentificationRangeAt(ants[0]->Identifications().front()->TagValue(),
				                                      Time());
			EXPECT_TIME_EQ(std::get<0>(res),Time());
			EXPECT_TIME_EQ(std::get<1>(res),Time::Forever());
		});

	auto [low,high] = experiment->FreeIdentificationRangeAt(255,
	                                                        Time());
	EXPECT_TIME_EQ(low,Time::SinceEver());
	EXPECT_TIME_EQ(high,Time::Forever());

	auto identifications = experiment->IdentificationsAt(Time().Add(-1),true);
	EXPECT_EQ(identifications.size(),2);
	EXPECT_EQ(identifications[ants[0]->ID()],0);
	EXPECT_EQ(identifications[ants[1]->ID()],1);
	identifications = experiment->IdentificationsAt(Time(),true);
	EXPECT_EQ(identifications.size(),1);
	EXPECT_EQ(identifications[ants[1]->ID()],1);
	identifications = experiment->IdentificationsAt(Time(),false);
	EXPECT_EQ(identifications.size(),2);
	EXPECT_EQ(identifications[ants[0]->ID()],std::numeric_limits<TagID>::max());
	EXPECT_EQ(identifications[ants[1]->ID()],1);

}


TEST_F(PublicExperimentUTest,FieldsManipulation) {
	EXPECT_EQ(experiment->Name(),"");
	EXPECT_NO_THROW(experiment->SetName("foo"));
	EXPECT_EQ(experiment->Name(),"foo");

	EXPECT_EQ(experiment->Author(),"");
	EXPECT_NO_THROW(experiment->SetAuthor("bar"));
	EXPECT_EQ(experiment->Author(),"bar");

	EXPECT_EQ(experiment->Comment(),"");
	EXPECT_NO_THROW(experiment->SetComment("baz"));
	EXPECT_EQ(experiment->Comment(),"baz");

	EXPECT_EQ(experiment->Family(),fort::tags::Family::Undefined);
	const auto & tddInfo = TestSetup::UTestData().ForagingDataDirs().front();
	ASSERT_NO_THROW({
			auto spaceID = experiment->CreateSpace("foraging")->ID();
			experiment->AddTrackingDataDirectory(spaceID,
			                                     tddInfo.AbsoluteFilePath);
		});
	EXPECT_EQ(experiment->Family(),tddInfo.Family);

	EXPECT_EQ(experiment->DefaultTagSize(),1.0);
	EXPECT_NO_THROW(experiment->SetDefaultTagSize(1.6));
	EXPECT_EQ(experiment->DefaultTagSize(),1.6);
}

TEST_F(PublicExperimentUTest,MeasurementTypeManipulation) {
	auto mtID = experiment->CreateMeasurementType("antennas");
	EXPECT_EQ(experiment->MeasurementTypeNames().size(),2);
	EXPECT_EQ(experiment->MeasurementTypeNames()[mtID],"antennas");
	EXPECT_EQ(experiment->MeasurementTypeNames()[1],"head-tail");
 	EXPECT_THROW({
			experiment->SetMeasurementTypeName(42,"foo");
		},std::out_of_range);

	EXPECT_NO_THROW({
			experiment->SetMeasurementTypeName(1,"foo");
		});

	EXPECT_THROW({
			experiment->DeleteMeasurementType(42);
		},std::out_of_range);

	EXPECT_THROW({
			experiment->DeleteMeasurementType(1);
		},std::invalid_argument);

	EXPECT_NO_THROW({
			experiment->DeleteMeasurementType(mtID);
		});

}

TEST_F(PublicExperimentUTest,AntShapeTypeManipulation) {
	auto bodyID = experiment->CreateAntShapeType("body");
	auto headID = experiment->CreateAntShapeType("head");
	EXPECT_EQ(experiment->AntShapeTypeNames().size(),2);
	EXPECT_EQ(experiment->AntShapeTypeNames()[bodyID],"body");
	EXPECT_EQ(experiment->AntShapeTypeNames()[headID],"head");
 	EXPECT_THROW({
			experiment->SetAntShapeTypeName(42,"foo");
		},std::out_of_range);

	EXPECT_NO_THROW({
			experiment->SetAntShapeTypeName(bodyID,"foo");
		});

	EXPECT_THROW({
			experiment->DeleteAntShapeType(42);
		},std::out_of_range);

	ASSERT_NO_THROW({
			auto a = experiment->CreateAnt();
			a->AddCapsule(bodyID,
			              std::make_shared<Capsule>(Eigen::Vector2d(0,0),
			                                        Eigen::Vector2d(1,1),
			                                        1,1));
		});

	EXPECT_THROW({
			experiment->DeleteAntShapeType(bodyID);
		},std::runtime_error);

	EXPECT_NO_THROW({
			experiment->DeleteAntShapeType(headID);
		});

}

TEST_F(PublicExperimentUTest,MetaDataKeyManipulation) {
	experiment->SetMetaDataKey("alive",true);
	experiment->SetMetaDataKey("group",std::string("worker"));
	EXPECT_EQ(experiment->MetaDataKeys().size(),2);
	EXPECT_ANT_STATIC_VALUE_EQ(experiment->MetaDataKeys()["alive"],true);
	EXPECT_ANT_STATIC_VALUE_EQ(experiment->MetaDataKeys()["group"],std::string("worker"));

	Ant::Ptr a;
	EXPECT_NO_THROW({
			a = experiment->CreateAnt();
			a->SetValue("group",std::string("nurse"),Time::SinceEver());
		});

	EXPECT_THROW({
			experiment->DeleteMetaDataKey("foo");
		},std::out_of_range);

	EXPECT_THROW({
			experiment->DeleteMetaDataKey("group");
		},std::runtime_error);


	EXPECT_THROW({
			experiment->RenameMetaDataKey("foo","bar");
		},std::out_of_range);


	EXPECT_THROW({
			experiment->RenameMetaDataKey("alive","group");
		},std::invalid_argument);

	EXPECT_NO_THROW({
			experiment->RenameMetaDataKey("alive","death-date");
			experiment->SetMetaDataKey("death-date",Time::Forever());
			experiment->DeleteMetaDataKey("death-date");
			experiment->SetMetaDataKey("group",std::string("nurse"));
		});


	EXPECT_THROW({
			experiment->SetMetaDataKey("group",int(1));
		},std::runtime_error);

	EXPECT_NO_THROW({
			a->DeleteValue("group",Time::SinceEver());
			experiment->SetMetaDataKey("group",int(1));
		});
}


} // namespace myrmidon
} // namespace fort
