#include "TrackingDataDirectoryUTest.hpp"


#include "TrackingDataDirectory.hpp"
#include <myrmidon/Experiment.pb.h>
#include <google/protobuf/util/time_util.h>
#include <google/protobuf/util/message_differencer.h>

#include "../TestSetup.hpp"

#include "../UtilsUTest.hpp"

#include "RawFrame.hpp"

namespace fort {
namespace myrmidon {
namespace priv {

TEST_F(TrackingDataDirectoryUTest,ExtractInfoFromTrackingDatadirectories) {

	try {
		auto tddPath = TestSetup::Basedir() / "foo.0001";
		auto startOpen = Time::Now();

		auto tdd = TrackingDataDirectory::Open(tddPath,TestSetup::Basedir());
		auto endOpen = Time::Now();
		std::cerr << "Opening " <<  tddPath << " took " << endOpen.Sub(startOpen) << std::endl;
		EXPECT_EQ(tdd->URI(),"foo.0001");
		EXPECT_EQ(tdd->StartFrame(),0);
		EXPECT_EQ(tdd->EndFrame(),999);
		EXPECT_TRUE(TimeEqual(tdd->StartDate(),TestSetup::StartTime("foo.0001/tracking.0000.hermes")));
		EXPECT_TRUE(TimeEqual(tdd->EndDate(),TestSetup::EndTime("foo.0001/tracking.0009.hermes")));

		std::vector<SegmentIndexer<std::string>::Segment> segments;

		for(size_t i = 0; i < 10; ++i ) {
			std::ostringstream os;
			os << "tracking." << std::setw(4) << std::setfill('0') << i << ".hermes";
			segments.push_back(std::make_pair(FrameReference("foo.0001",
			                                                 100*i,
			                                                 TestSetup::StartTime("foo.0001/" + os.str())),
			                                  os.str()));
		}
		ASSERT_EQ(segments.size(),tdd->TrackingSegments().Segments().size());
		for(size_t i = 0;  i < segments.size(); ++i) {
			EXPECT_EQ(segments[i].first.ID(),tdd->TrackingSegments().Segments()[i].first.ID());
			EXPECT_TRUE(TimeEqual(segments[i].first.Time(),tdd->TrackingSegments().Segments()[i].first.Time()));
			EXPECT_EQ(segments[i].second,tdd->TrackingSegments().Segments()[i].second);
		}



		uint64_t i  = tdd->StartFrame();
		auto iterStart = Time::Now();

		for ( auto it = tdd->begin(); it != tdd->end() ; ++it) {
			auto f = *it;
			EXPECT_EQ(f->ID(),i);
			ASSERT_EQ(f->Tags().size(),1);
			EXPECT_EQ(f->Tags().Get(0).id(),123);
			++i;
		}
		auto iterEnd = Time::Now();
		std::cerr << "Iterating over all frames from " <<  tddPath << " took " << iterEnd.Sub(iterStart) << std::endl;
		i = tdd->EndFrame()-3;
		for( auto it = tdd->FrameAt(tdd->EndFrame()-3); it != tdd->end(); ++it ) {
			EXPECT_EQ((*it)->ID(),i);
			ASSERT_EQ((*it)->Tags().size(),1);
			EXPECT_EQ((*it)->Tags().Get(0).id(),123);
			++i;
		}

	} catch( const std::exception & e) {
		ADD_FAILURE() << "Got unexpected exception: " << e.what();
	}

	EXPECT_THROW({
			//no tracking data
			auto tdd = TrackingDataDirectory::Open(TestSetup::Basedir() / "bar.0000",TestSetup::Basedir());
		}, std::invalid_argument);

	EXPECT_THROW({
			//directory does not exists
			auto tdd = TrackingDataDirectory::Open(TestSetup::Basedir() / "foo.1234",TestSetup::Basedir());
		}, std::invalid_argument);


	EXPECT_THROW({
			// is not a directory
			auto tdd = TrackingDataDirectory::Open(TestSetup::Basedir() / "test.myrmidon",TestSetup::Basedir());
		}, std::invalid_argument);

	EXPECT_THROW({
			//root does not exist
			auto tdd = TrackingDataDirectory::Open(TestSetup::Basedir() / "foo.0001", TestSetup::Basedir() /  "does-not-exists");
		}, std::invalid_argument);


}


TEST_F(TrackingDataDirectoryUTest,HasUIDBasedOnPath) {
	struct TestData {
		fs::path A,B;
		bool Expected;
	};

	std::vector<TestData> data
		= {
		   {
		    "bar/foo",
		    "bar/foo",
		    true,
		   },
		   {
		    "bar/foo",
		    "bar////foo",
		    true,
		   },
		   {
		    "bar/foo",
		    "baz/foo",
		    false,
		   },
		   {
		    "bar/../foo",
		    "baz/../foo",
		    true,
		   },
	};

	for(const auto & d : data ) {
		auto aUID = TrackingDataDirectory::GetUID(d.A);
		auto bUID = TrackingDataDirectory::GetUID(d.B);
		EXPECT_EQ(aUID == bUID,d.Expected);
	}
}


TEST_F(TrackingDataDirectoryUTest,HaveConstructorChecks) {
	uint64_t startFrame = 10;
	uint64_t endFrame = 20;
	auto startTime = Time::Parse("2019-11-02T22:02:24.674+01:00");
	auto endTime = Time::Parse("2019-11-02T22:02:25.783+01:00");
	auto segments = std::make_shared<TrackingDataDirectory::TrackingIndex>();
	auto movies = std::make_shared<TrackingDataDirectory::MovieIndex>();
	auto cache = std::make_shared<TrackingDataDirectory::FrameReferenceCache>();
	EXPECT_NO_THROW({
			TrackingDataDirectory::Create("foo","bar",startFrame,endFrame,startTime,endTime,segments,movies,cache);
		});

	EXPECT_THROW({
			TrackingDataDirectory::Create("foo","bar",endFrame,startFrame,startTime,endTime,segments,movies,cache);
		},std::invalid_argument);

	EXPECT_THROW({
			TrackingDataDirectory::Create("foo","bar",startFrame,endFrame,endTime,startTime,segments,movies,cache);
		},std::invalid_argument);



}

} // namespace fort
} // namespace myrmidon
} // namespace priv
