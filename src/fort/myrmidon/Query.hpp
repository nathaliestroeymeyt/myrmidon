#pragma once

#include "Types.hpp"

#include "Experiment.hpp"
#include "Matchers.hpp"

namespace fort {
namespace myrmidon {


// Wrapper for Queries on Experiment
//
// This class is a wrapper for all data queries that can be made on an
// Experiment. They takes advantages of multithreading to have
// efficient computation time.
class Query {
public:

	// Data returned by <CollideFrame>.
	typedef std::pair<IdentifiedFrame::ConstPtr,CollisionFrame::ConstPtr> CollisionData;

	// Computes all measurement for an Ant
	// @experiment the <Experiment> to query for
	// @antID the desired <Ant>
	// @mTypeID the desired measurement type
	//
	// @return a <ComputedMeasurement::List> of the Measurement for the <Ant>
	static ComputedMeasurement::List ComputeMeasurementFor(const Experiment::ConstPtr & experiment,
	                                                       Ant::ID antID,
	                                                       MeasurementTypeID mTypeID);

	// Computes <TagStatistics> for an experiment
	// @experiment the <Experiment> to query for
	//
	// @return the tag statistics index by <TagID>
	static TagStatistics::ByTagID ComputeTagStatistics(const Experiment::ConstPtr & experiment);

	// Identifies ants in frames
	// @experiment the <Experiment> to query for
	// @result the resulting <IdentifiedFrame>
	// @start the start time for the query use nullptr for the starts
	//        of the experiment.
	// @end the end time for the query, use nullptr for the end of the
	//      experiment
	//
	// Identifies Ants in frames, data will be reported squencially,
	// space by space.

	static void IdentifyFrames(const Experiment::ConstPtr & experiment,
	                           std::vector<IdentifiedFrame::ConstPtr> & result,
	                           const Time::ConstPtr & start,
	                           const Time::ConstPtr & end);

	// Finds <Collision> in data frame
	// @experiment the <Experiment> to query for
	// @result the resulting <IdentifiedFrame> and <CollisionFrame>
	// @start the start time for the query use nullptr for the starts
	//        of the experiment.
	// @end the end time for the query, use nullptr for the end of the
	//      experiment
	//
	// Finds <Collision> between ants in frames, data will be reported
	// sequencially, space by space.

	static void CollideFrames(const Experiment::ConstPtr & experiment,
	                          std::vector<CollisionData> & result,
	                          const Time::ConstPtr & start,
	                          const Time::ConstPtr & end);

	// Computes trajectories for ants
	// @experiment the <Experiment> to query for
	// @trajectories the resulting <IdentifiedFrame> and <CollisionFrame>
	// @start the start time for the query use nullptr for the starts
	//        of the experiment.
	// @end the end time for the query, use nullptr for the end of the
	//      experiment
	// @maximumGap the maximal undetected duration before cutting the
	//             trajectory in two
	// @matcher a <Matcher> to specify more precise, less memory
	//          intensive queries.
	//
	// Computes trajectories for <Ant>. Those will be reported ordered
	// in time, ant by ant.
	static void ComputeTrajectories(const Experiment::ConstPtr & experiment,
	                                std::vector<AntTrajectory::ConstPtr> & trajectories,
	                                const Time::ConstPtr & start,
	                                const Time::ConstPtr & end,
	                                Duration maximumGap,
	                                Matcher::Ptr matcher = Matcher::Ptr());

	// Computes interactions for ants
	// @experiment the <Experiment> to query for
	// @trajectories the resulting <IdentifiedFrame> and <CollisionFrame>
	// @start the start time for the query use nullptr for the starts
	//        of the experiment.
	// @end the end time for the query, use nullptr for the end of the
	//      experiment
	// @maximumGap the maximal undetected duration before cutting the
	//             trajectory in two
	// @matcher a <Matcher> to specify more precise, less memory
	//          intensive queries.
	//
	// Computes interactions for <Ant>. Those will be reported ordered
	// in time, first interacting Ant by firs interacting Ant.
	static void ComputeAntInteractions(const Experiment::ConstPtr & experiment,
	                                   std::vector<AntTrajectory::ConstPtr> & trajectories,
	                                   std::vector<AntInteraction::ConstPtr> & interactions,
	                                   const Time::ConstPtr & start,
	                                   const Time::ConstPtr & end,
	                                   Duration maximumGap,
	                                   Matcher::Ptr matcher = Matcher::Ptr());


};


} // namespace myrmidon
} // namespace fort
