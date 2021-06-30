#include "Experiment.hpp"

#include "priv/Experiment.hpp"
#include "priv/TrackingSolver.hpp"
#include "priv/AntShapeType.hpp"
#include "priv/Identifier.hpp"
#include "priv/Measurement.hpp"
#include "priv/TrackingDataDirectory.hpp"

#include "utils/ConstClassHelper.hpp"

namespace fort {
namespace myrmidon {


Experiment::Ptr Experiment::Open(const std::string & filepath) {
	return Experiment::Ptr(new Experiment(priv::Experiment::Open(filepath)));
}

Experiment::Ptr Experiment::OpenDataLess(const std::string & filepath) {
	// its ok to const cast as we cast back as a const
	return Experiment::Ptr(new Experiment(priv::Experiment::OpenDataLess(filepath)));
}

Experiment::Ptr Experiment::Create(const std::string & filepath) {
	return Experiment::Ptr(new Experiment(priv::Experiment::Create(filepath)));
}

void Experiment::Save(const std::string & filepath) {
	d_p->Save(filepath);
}

std::string Experiment::AbsoluteFilePath() const {
	return d_p->AbsoluteFilePath().string();
}

Space & Experiment::CreateSpace(const std::string & name) {
	return d_p->PublicCreateSpace(name);
}

void Experiment::DeleteSpace(SpaceID spaceID) {
	d_p->DeleteSpace(spaceID);
}

const Space::ByID & Experiment::Spaces() const {
	return d_p->PublicSpaces();
}

std::string Experiment::AddTrackingDataDirectory(SpaceID spaceID,
                                                 const std::string & filepath) {
	auto fi  = d_p->Spaces().find(spaceID);
	if ( fi == d_p->Spaces().end() ) {
		throw std::invalid_argument("Unknown Space::ID " + std::to_string(spaceID));
	}
	auto tdd = priv::TrackingDataDirectory::Open(filepath,d_p->Basedir());
	d_p->AddTrackingDataDirectory(fi->second,tdd);
	return tdd->URI();
}

void Experiment::RemoveTrackingDataDirectory(const std::string & URI) {
	d_p->DeleteTrackingDataDirectory(URI);
}


const Ant::Ptr & Experiment::CreateAnt() {
	return d_p->PublicCreateAnt();
}

const std::map<AntID,const Ant::Ptr> & Experiment::Ants() const {
	return d_p->Identifier()->PublicAnts();
}

Identification::Ptr Experiment::AddIdentification(AntID antID,
                                                  TagID tagID,
                                                  const Time & start,
                                                  const Time & end) {
	auto i = priv::Identifier::AddIdentification(d_p->Identifier(),
	                                             antID,
	                                             tagID,
	                                             start,
	                                             end);
	return Identification::Ptr(new Identification(i));
}

void Experiment::DeleteIdentification(const Identification::Ptr & identification) {
	d_p->Identifier()->DeleteIdentification(identification->d_p);
}


std::tuple<fort::Time,fort::Time>
Experiment::FreeIdentificationRangeAt(TagID tagID, const Time & time) const {
	fort::Time start,end;
	if ( d_p->Identifier()->FreeRangeContaining(start,end,tagID,time) == false ) {
		std::ostringstream oss;
		oss << fort::myrmidon::FormatTagID(tagID) << " identifies an Ant at " << time;
		throw std::runtime_error(oss.str());
	}
	return {start,end};
}



const std::string & Experiment::Name() const {
	return d_p->Name();
}

void Experiment::SetName(const std::string & name) {
	d_p->SetName(name);
}

const std::string & Experiment::Author() const {
	return d_p->Author();
}

void Experiment::SetAuthor(const std::string & author) {
	d_p->SetAuthor(author);
}

const std::string & Experiment::Comment() const {
	return d_p->Comment();
}

void Experiment::SetComment(const std::string & comment) {
	d_p->SetComment(comment);
}

fort::tags::Family Experiment::Family() const {
	return d_p->Family();
}

double Experiment::DefaultTagSize() const {
	return d_p->DefaultTagSize();
}

void Experiment::SetDefaultTagSize(double defaultTagSize) {
	d_p->SetDefaultTagSize(defaultTagSize);
}

MeasurementTypeID Experiment::CreateMeasurementType(const std::string & name) {
	return d_p->CreateMeasurementType(name)->MTID();
}

void Experiment::DeleteMeasurementType(MeasurementTypeID mTypeID) {
	d_p->DeleteMeasurementType(mTypeID);
}

void Experiment::SetMeasurementTypeName(MeasurementTypeID mTypeID,
                                        const std::string & name) {
	auto fi = d_p->MeasurementTypes().find(mTypeID);
	if ( fi == d_p->MeasurementTypes().end() ) {
		throw std::invalid_argument("Unknwon measurement type " + std::to_string(mTypeID));
	}
	fi->second->SetName(name);
}


std::map<MeasurementTypeID,std::string> Experiment::MeasurementTypeNames() const {
	std::map<MeasurementTypeID,std::string> res;
	for ( const auto & [mtID,mt] : d_p->MeasurementTypes() ) {
		res.insert(std::make_pair(mtID,mt->Name()));
	}
	return res;
}

AntShapeTypeID Experiment::CreateAntShapeType(const std::string & name) {
	return d_p->CreateAntShapeType(name)->TypeID();
}

std::map<AntShapeTypeID,std::string> Experiment::AntShapeTypeNames() const {
	std::map<AntShapeTypeID,std::string> res;
	for ( const auto & [shapeTypeID,shapeType] : d_p->AntShapeTypes() ) {
		res.insert(std::make_pair(shapeTypeID,shapeType->Name()));
	}
	return res;
}

void Experiment::SetAntShapeTypeName(AntShapeTypeID antShapeTypeID,
                                     const std::string & name) {
	auto fi = d_p->AntShapeTypes().find(antShapeTypeID);
	if ( fi == d_p->AntShapeTypes().end() ) {
		throw std::invalid_argument("unknow AntShapeTypeID " + std::to_string(antShapeTypeID));
	}
	fi->second->SetName(name);
}

void Experiment::DeleteAntShapeType(AntShapeTypeID antShapeTypeID) {
	d_p->DeleteAntShapeType(antShapeTypeID);
}


void Experiment::SetMetaDataKey(const std::string & name,
                                AntStaticValue defaultValue) {
	d_p->SetMetaDataKey(name,defaultValue);
}

void Experiment::DeleteMetaDataKey(const std::string & key) {
	d_p->DeleteMetaDataKey(key);
}


std::map<std::string,std::pair<AntMetaDataType,AntStaticValue>>
Experiment::MetaDataKeys() const {
	std::map<std::string,std::pair<AntMetaDataType,AntStaticValue>> res;
	for ( const auto & [name,key] : d_p->AntMetadataPtr()->Keys() ) {
		res.insert(std::make_pair(name,std::make_pair(key->Type(),key->DefaultValue())));
	}
	return res;
}


void Experiment::RenameMetaDataKey(const std::string & oldName,
                                   const std::string & newName) {
	d_p->RenameMetaDataKey(oldName,newName);

}

Experiment::Experiment(const PPtr & pExperiment)
	: d_p(pExperiment) {
}


TrackingDataDirectoryInfo buildTddInfos(const priv::TrackingDataDirectory::Ptr & tdd) {
	return {
	        .URI = tdd->URI(),
	        .AbsoluteFilePath = tdd->AbsoluteFilePath().string(),
	        .Frames = tdd->EndFrame() - tdd->StartFrame() + 1,
	        .Start  = tdd->Start(),
	        .End = tdd->End(),
	};
}


SpaceDataInfo 	buildSpaceInfos( const priv::Space::ConstPtr & space ) {
	SpaceDataInfo res = {.URI = space->URI(),.Name = space->Name(), .Frames = 0 , .Start = Time(), .End = Time()};
	const auto & tdds = space->TrackingDataDirectories();
	if ( tdds.empty() == true ) {
		return res;
	}
	res.Start = tdds.front()->Start();
	res.End = tdds.back()->End();
	res.TrackingDataDirectories.reserve(tdds.size());
	for ( const auto & tdd : tdds ) {
		res.TrackingDataDirectories.push_back(buildTddInfos(tdd));
		res.Frames += res.TrackingDataDirectories.back().Frames;
	}
	return res;
}


ExperimentDataInfo Experiment::GetDataInformations() const {
	ExperimentDataInfo res = { .Frames = 0, .Start = Time::Forever(), .End = Time::SinceEver() };
	const auto & spaces = d_p->Spaces();
	for ( const auto & [spaceID,space] : spaces ) {
		auto sInfo = buildSpaceInfos(space);
		res.Start = std::min(res.Start,sInfo.Start);
		res.End = std::max(res.End,sInfo.End);
		res.Frames += sInfo.Frames;
		res.Spaces[spaceID] = sInfo;
	}

	return res;
}

std::map<AntID,TagID> Experiment::IdentificationsAt(const Time & time,
                                                    bool removeUnidentifiedAnt) const {
	return d_p->Identifier()->IdentificationsAt(time,removeUnidentifiedAnt);
}

TrackingSolver Experiment::CompileTrackingSolver() const {
	return TrackingSolver(std::make_shared<priv::TrackingSolver>(d_p->Identifier(),
	                                                             d_p->CompileCollisionSolver()));
}



} // namespace mrymidon
} // namespace fort
