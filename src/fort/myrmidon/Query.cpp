#include "Query.hpp"

#include "handle/ExperimentHandle.hpp"

#include "Experiment.hpp"

#include "priv/Experiment.hpp"
#include "priv/TrackingDataDirectory.hpp"
#include "priv/Space.hpp"
#include "priv/Query.hpp"

namespace fort {
namespace myrmidon {

ComputedMeasurement::List Query::ComputeMeasurementFor(const Experiment & experiment,
                                                       AntID antID,
                                                       MeasurementTypeID mTypeID) {
	ComputedMeasurement::List res;
	experiment.d_p->Get().ComputeMeasurementsForAnt(res,antID,mTypeID);
	return res;
}

TagStatistics::ByTagID Query::ComputeTagStatistics(const Experiment & experiment) {
	TagStatistics::ByTagID res;
	priv::Query::ComputeTagStatistics(experiment.d_p->Get(),res);
	return res;
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


SpaceDataInfo buildSpaceInfos( const priv::Space::ConstPtr & space ) {
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

ExperimentDataInfo Query::GetDataInformations(const Experiment & experiment) {
	ExperimentDataInfo res = { .Frames = 0, .Start = Time::Forever(), .End = Time::SinceEver() };
	const auto & spaces = experiment.d_p->Get().Spaces();
	for ( const auto & [spaceID,space] : spaces ) {
		auto sInfo = buildSpaceInfos(space);
		res.Start = std::min(res.Start,sInfo.Start);
		res.End = std::max(res.End,sInfo.End);
		res.Frames += sInfo.Frames;
		res.Spaces[spaceID] = sInfo;
	}

	return res;
}

Query::QueryArgs::QueryArgs()
	: Start(Time::SinceEver())
	, End(Time::Forever())
	, SingleThreaded(false)
	, AllocationInCurrentThread(false) {
}

Query::IdentifyFramesArgs::IdentifyFramesArgs()
	: ComputeZones(false) {
}

void Query::IdentifyFramesFunctor(const Experiment & experiment,
                                  std::function<void (const IdentifiedFrame::Ptr &)> storeData,
                                  const IdentifyFramesArgs & args) {
	priv::Query::IdentifyFrames(experiment.d_p->Get(),storeData,args);
}


void Query::IdentifyFrames(const Experiment & experiment,
                           std::vector<IdentifiedFrame::Ptr> & result,
                           const IdentifyFramesArgs & args) {
	priv::Query::IdentifyFrames(experiment.d_p->Get(),
	                            [&result] (const IdentifiedFrame::Ptr & i) {
		                            result.push_back(i);
	                            },
	                            args);
}

Query::CollideFramesArgs::CollideFramesArgs()
	: CollisionsIgnoreZones(false) {
}

void Query::CollideFramesFunctor(const Experiment & experiment,
                                 std::function<void (const CollisionData & data)> storeData,
                                 const CollideFramesArgs & args) {
	priv::Query::CollideFrames(experiment.d_p->Get(),storeData,args);
}


void Query::CollideFrames(const Experiment & experiment,
                          std::vector<CollisionData> & result,
                          const CollideFramesArgs & args) {
	priv::Query::CollideFrames(experiment.d_p->Get(),
	                           [&result](const CollisionData & data) {
		                           result.push_back(data);
	                           },
	                           args);
}

Query::ComputeAntTrajectoriesArgs::ComputeAntTrajectoriesArgs()
	: MaximumGap(1 * Duration::Second)
	, ComputeZones(false) {
}


void Query::ComputeAntTrajectoriesFunctor(const Experiment & experiment,
                                          std::function<void (const AntTrajectory::Ptr &)> storeTrajectory,
                                          const ComputeAntTrajectoriesArgs & args) {
	priv::Query::ComputeTrajectories(experiment.d_p->Get(),
	                                 storeTrajectory,
	                                 args);
}


void Query::ComputeAntTrajectories(const Experiment & experiment,
                                   std::vector<AntTrajectory::Ptr> & trajectories,
                                   const ComputeAntTrajectoriesArgs & args) {
	priv::Query::ComputeTrajectories(experiment.d_p->Get(),
	                                 [&trajectories](const AntTrajectory::Ptr & trajectory) {
		                                 trajectories.push_back(trajectory);
	                                 },
	                                 args);
}

Query::ComputeAntInteractionsArgs::ComputeAntInteractionsArgs()
	: MaximumGap(1 * Duration::Second)
	, ReportFullTrajectories(true) {
}

void Query::ComputeAntInteractionsFunctor(const Experiment & experiment,
                                          std::function<void ( const AntTrajectory::Ptr&) > storeTrajectory,
                                          std::function<void ( const AntInteraction::Ptr&) > storeInteraction,
                                          const ComputeAntInteractionsArgs & args) {
	priv::Query::ComputeAntInteractions(experiment.d_p->Get(),
	                                    storeTrajectory,
	                                    storeInteraction,
	                                    args);
}

void Query::ComputeAntInteractions(const Experiment & experiment,
                                   std::vector<AntTrajectory::Ptr> & trajectories,
                                   std::vector<AntInteraction::Ptr> & interactions,
                                   const ComputeAntInteractionsArgs & args) {
	priv::Query::ComputeAntInteractions(experiment.d_p->Get(),
	                                    [&trajectories](const AntTrajectory::Ptr & trajectory) {
		                                    trajectories.push_back(trajectory);
	                                    },
	                                    [&interactions](const AntInteraction::Ptr & interaction) {
		                                    interactions.push_back(interaction);
	                                    },
	                                    args);
}

void Query::FindVideoSegments(const Experiment & experiment,
                              std::vector<VideoSegment> & segments,
                              SpaceID space,
                              const fort::Time & start,
                              const fort::Time & end) {
	priv::Query::FindVideoSegments(experiment.d_p->Get(),
	                               segments,
	                               space,
	                               start,
	                               end);
}

std::vector<std::tuple<AntID,Time,Time>>
Query::GetMetaDataKeyRanges(const Experiment & e,
                            const std::string & key,
                            const AntStaticValue & value) {
	std::vector<std::tuple<AntID,Time,Time>> res;
	if ( e.MetaDataKeys().count(key) == 0 ) {
		throw std::out_of_range("Invalid key '" + key + "'");
	}
	if ( e.MetaDataKeys().at(key).index() != value.index() ) {
		throw std::invalid_argument("Value is not of the right type");
	}

	for ( const auto & [antID,ant] : e.Ants() ) {
		const auto & values = ant->GetValues(key);
		for ( auto iter = values.begin();
		      iter != values.end();
		      ++iter) {
			if ( !(iter->second == value) ) {
				continue;
			}
			auto next = iter;
			while ( next != values.end() && next->second == value ) {
				++next;
			}
			if ( next == values.end() ) {
				res.push_back({antID,iter->first,Time::Forever()});
			} else {
				res.push_back({antID,iter->first,next->first});
			}
			iter = --next;
		}
	}
	return res;
}


} // namespace myrmidon
} // namespace fort
