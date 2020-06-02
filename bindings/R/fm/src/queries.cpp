#include "queries.h"

#include "time.h"
#include "experiment.h"
#include "matchers.h"
#include "duration.h"


#include <iostream>

#include <Rcpp.h>

using namespace fort::myrmidon;

SEXP fmIdentifiedFrame_asR(const IdentifiedFrame::ConstPtr & frame) {
	size_t n = frame->Positions.size();
	Rcpp::IntegerVector IDs(n);
	Rcpp::NumericVector X(n),Y(n),Angle(n);
	size_t i = 0;
	for ( const auto & ant : frame->Positions ) {
		IDs[i] = ant.ID;
		X[i] = ant.Position.x();
		Y[i] = ant.Position.y();
		Angle[i] = ant.Angle;
		++i;
	}


	Rcpp::List Data;
	Rcpp::CharacterVector colNames({"AntID","X","Y","Angle"}); \
	Data = Rcpp::List({IDs,X,Y,Angle});
	if ( frame->Zones.empty() == false ) {
		Data.push_back(Rcpp::IntegerVector(frame->Zones.begin(),frame->Zones.end()));
		colNames.push_back("ZoneID");
	}


	Data.attr("names") = colNames;
	Data.attr("class") = "data.frame";
	Rcpp::S4 res("fmIdentifiedFrame");

	res.slot("frameTime") = fmTime_asR(frame->FrameTime);
	res.slot("width") = frame->Width;
	res.slot("height") = frame->Height;
	res.slot("space") = frame->Space;
	res.slot("data") = Data;
	return res;
}



IdentifiedFrame::ConstPtr IdentifiedFrame_debug() {
	auto f = std::make_shared<IdentifiedFrame>();
	f->FrameTime = Time::Now();
	f->Space = 42;
	f->Width = 1920;
	f->Height = 1080;
	f->Positions.push_back(PositionedAnt{Eigen::Vector2d(0,0),0,1});
	f->Positions.push_back(PositionedAnt{Eigen::Vector2d(1,1),-0.1,2});
	f->Zones.push_back(0);
	f->Zones.push_back(2);

	return f;
}

SEXP fmIdentifiedFrame_debug() {
	return fmIdentifiedFrame_asR(IdentifiedFrame_debug());
}

struct fmCollision {
	AntID  Ant1;
	AntID  Ant2;
	ZoneID Zone;
	Rcpp::List             InteractionTypes;
	void Show() const {
		Rcpp::Rcout << "fmCollision (\n"
		            << "  ant1 = " << Ant1 << "\n"
		            << "  ant2 = " << Ant2 << "\n"
		            << "  zone = " << Zone << "\n"
		            << "  interactionTypes = ";
		Rcpp::Function("str")(InteractionTypes);
		Rcpp::Rcout << ")\n";
	}

	fmCollision(const Collision & c)
		: Ant1(c.IDs.first)
		, Ant2(c.IDs.second)
		, Zone(c.Zone)
		, InteractionTypes(c.InteractionTypes.size()) {
		for ( size_t i = 0 ; i < c.InteractionTypes.size(); ++i ) {
			const auto & t = c.InteractionTypes[i];
			InteractionTypes[i] = Rcpp::IntegerVector({(int)t.first,(int)t.second});
		}
	}
};


SEXP fmInteractionTypes_asR(const std::vector<InteractionType> & it ) {
	// ugly reinterpret cast, but the memory layout is right
	return Rcpp::IntegerMatrix(it.size(),
	                           2,
	                           reinterpret_cast<const std::vector<uint32_t>*>(&(it))->begin());
}


SEXP fmCollision_asR(const Collision & c) {
	Rcpp::S4 res("fmCollision");
	res.slot("ant1") = c.IDs.first;
	res.slot("ant2") = c.IDs.second;
	res.slot("zone") = c.Zone;
	res.slot("interactionTypes") = fmInteractionTypes_asR(c.InteractionTypes);
	return res;
}

Collision Collision_debug() {
	return Collision{
		.IDs = std::make_pair(3,4),.InteractionTypes = {{1,1},{2,1},{1,3}},.Zone= 51};
}

SEXP fmCollision_debug() {
	return fmCollision_asR(Collision_debug());
}



SEXP fmCollisionFrame_asR(const CollisionFrame::ConstPtr & frame ) {
	Rcpp::S4 res("fmCollisionFrame");
	res.slot("frameTime") = fmTime_asR(frame->FrameTime);
	res.slot("space") = frame->Space;
	res.slot("collisions") = Rcpp::List::import_transform(frame->Collisions.cbegin(),
	                                                      frame->Collisions.cend(),
	                                                      &fmCollision_asR);
	return res;
}


CollisionFrame::ConstPtr CollisionFrame_debug() {
	auto f = std::make_shared<CollisionFrame>();
	f->FrameTime = Time::Now();
	f->Space = 42;
	for ( size_t i = 0 ; i < 3; ++i) {
		f->Collisions.push_back(Collision_debug());
	}
	return f;
}

SEXP fmCollisionFrame_debug() {
	return fmCollisionFrame_asR(CollisionFrame_debug());
}


SEXP fmAntTrajectory_asR(const AntTrajectory::ConstPtr & at) {
	size_t nPoints = at->Data.rows();
#define numericVectorFromEigen(Var,matrix,col,size) Rcpp::NumericVector Var(&((matrix)(0,col)),&((matrix)(0,col))+size)
 	numericVectorFromEigen(Times,at->Data,0,nPoints);
 	numericVectorFromEigen(Xs,at->Data,1,nPoints);
 	numericVectorFromEigen(Ys,at->Data,2,nPoints);
 	numericVectorFromEigen(Angles,at->Data,3,nPoints);
#undef numericVectorFromEigen
	Rcpp::List data({Times,Xs,Ys,Angles});
	Rcpp::CharacterVector names = {"Time (s)","X","Y","Angle"};
	if ( at->Zones.empty() == false ) {
		data.push_back(Rcpp::IntegerVector(at->Zones.cbegin(),at->Zones.cend()));
		names.push_back("Zone");
	}
	data.attr("names") = names;
	data.attr("class") = "data.frame";

	Rcpp::S4 res("fmAntTrajectory");
	res.slot("ant") = at->Ant;
	res.slot("start") = fmTime_asR(at->Start);
	res.slot("space") = at->Space;
	res.slot("positions") = data;
	return res;
}

AntTrajectory::ConstPtr AntTrajectory_debug() {
	auto res = std::make_shared<AntTrajectory>();
	res->Ant = 3;
	res->Space = 42;
	res->Start = Time::Now();
	res->Data.resize(10,4);
	for ( size_t i = 0; i < 10 ; ++i ) {
		res->Data(i,0) = i*0.1;
		res->Data(i,1) = 1.0 * i;
		res->Data(i,2) = -1.0 * i;
		res->Data(i,3) = i * 0.1;
		res->Zones.push_back(i > 4 ? 51 : 0);
	}
	return res;
}

SEXP fmAntTrajectory_debug() {
	return fmAntTrajectory_asR(AntTrajectory_debug());
}


SEXP fmAntInteraction_asR(const AntInteraction::ConstPtr & ai) {
	Rcpp::S4 res("fmAntInteraction");
	res.slot("ant1") = ai->IDs.first;
	res.slot("ant2") = ai->IDs.second;
	res.slot("ant1Trajectory") = fmAntTrajectory_asR(ai->Trajectories.first);
	res.slot("ant2Trajectory") = fmAntTrajectory_asR(ai->Trajectories.second);
	res.slot("start") = fmTime_asR(ai->Start);
	res.slot("end") = fmTime_asR(ai->End);
	res.slot("types") = fmInteractionTypes_asR(ai->Types);
	return res;
}

AntInteraction::ConstPtr AntInteraction_debug() {
	auto res = std::make_shared<AntInteraction>();
	res->IDs = {3,4};
	res->Types = { {1,2},{1,3},{2,1} };
	res->Trajectories = {AntTrajectory_debug(),AntTrajectory_debug()};
	res->Start = Time::Now();
	res->End = res->Start.Add(10 * Duration::Second);
	return res;
}

SEXP fmAntInteraction_debug() {
	return fmAntInteraction_asR(AntInteraction_debug());
}

Rcpp::DataFrame fmQuery_computeMeasurementFor(const CExperiment & experiment,
                                              AntID antID,
                                              MeasurementTypeID mTypeID) {
	auto cMeasurements = Query::ComputeMeasurementFor(experiment,antID, mTypeID);

	Rcpp::DatetimeVector times(cMeasurements.size());
	Rcpp::NumericVector lengths(cMeasurements.size());
	for( size_t i = 0; i < cMeasurements.size(); ++i ) {
		times[i] = fmTime_asR(cMeasurements[i].MTime);
		lengths[i] = cMeasurements[i].LengthMM;
	}

	return Rcpp::DataFrame::create(Rcpp::_["date"] = times,
	                               Rcpp::_["length (mm)"] = lengths);
}


SEXP fmTagStatistics_asR(const TagStatistics::ByTagID & tagStats ) {
	size_t nTags  = tagStats.size();
	Rcpp::IntegerVector TagID(nTags),Count(nTags),Multiple(nTags),Gap500(nTags),Gap1s(nTags),Gap10s(nTags),Gap1m(nTags),Gap10m(nTags),Gap1h(nTags),Gap10h(nTags),GapMore(nTags);
	Rcpp::DatetimeVector FirstSeen(nTags),LastSeen(nTags);
	size_t i = 0;
	for(const auto & [tagID,stat] : tagStats) {
		TagID[i] = stat.ID;
		FirstSeen[i] = stat.FirstSeen.ToTimeT();
		LastSeen[i] = stat.LastSeen.ToTimeT();
		Count[i] = stat.Counts(TagStatistics::TOTAL_SEEN);
		Multiple[i] = stat.Counts(TagStatistics::MULTIPLE_SEEN);
		Gap500[i] = stat.Counts(TagStatistics::GAP_500MS);
		Gap1s[i] = stat.Counts(TagStatistics::GAP_1S);
		Gap10s[i] = stat.Counts(TagStatistics::GAP_10S);
		Gap1m[i] = stat.Counts(TagStatistics::GAP_1M);
		Gap10m[i] = stat.Counts(TagStatistics::GAP_10M);
		Gap1h[i] = stat.Counts(TagStatistics::GAP_1H);
		Gap10h[i] = stat.Counts(TagStatistics::GAP_10H);
		GapMore[i] = stat.Counts(TagStatistics::GAP_MORE);
		++i;
	}

	return Rcpp::DataFrame::create(Rcpp::_["TagID"] = TagID,
	                               Rcpp::_["First Seen"] = FirstSeen,
	                               Rcpp::_["Last Seen"] = LastSeen,
	                               Rcpp::_["Count"] = Count,
	                               Rcpp::_["Multiple Seen"] = Multiple,
	                               Rcpp::_["Gap < 500ms"] = Gap500,
	                               Rcpp::_["Gap < 1s"] = Gap1s,
	                               Rcpp::_["Gap < 10s"] = Gap10s,
	                               Rcpp::_["Gap < 1m"] = Gap1m,
	                               Rcpp::_["Gap < 10m"] = Gap10m,
	                               Rcpp::_["Gap < 1h"] = Gap1h,
	                               Rcpp::_["Gap < 10h"] = Gap10h,
	                               Rcpp::_["Gap >= 10h"] = GapMore);

}


SEXP fmQuery_computeTagStatistics(const CExperiment & experiment) {
	return fmTagStatistics_asR(Query::ComputeTagStatistics(experiment));
}


class ProgressDisplayerIF {
public :
	virtual ~ProgressDisplayerIF(){}
	virtual void ShowProgress(const Time & t) {}

};

class ProgressDisplayer : public ProgressDisplayerIF{
private :
	Duration d_duration;
	Time d_last,d_computeStart,d_lastShown,d_start,d_end;
	std::string d_what;
public :
	ProgressDisplayer(const CExperiment & experiment,
	                  const Time::ConstPtr & start,
	                  const Time::ConstPtr & end,
	                  const std::string & what,
	                  Duration d = Duration::Hour)
		: d_duration(d)
		, d_what(what) {
		if ( !start || !end ) {
			auto info = experiment.GetDataInformations();
			if ( !start  ) {
				d_start = info.Start;
			} else {
				d_start = *start;
			}
			if ( !end ) {
				d_end = info.End;
			} else {
				d_end = *end;
			}
		} else {
			d_start = *start;
			d_end = *end;
		}
		d_last = d_start;
		d_lastShown = Time::Now();
		d_computeStart = d_lastShown;
	}

	virtual ~ProgressDisplayer() {
		std::cerr << d_what << " took " << Time::Now().Sub(d_computeStart) << "\n";
	}

	void ShowProgress(const Time & t) override{
		auto ellapsed = t.Sub(d_last);
		if ( ellapsed < d_duration ) {
			return;
		}
		d_last = t;
		auto now = Time::Now();
		auto computationTime = now.Sub(d_lastShown);
		auto reminder = d_end.Sub(t);
		d_lastShown = now;
		std::cerr << "Processed frame at " << t
		          << ", computed "
		          << ellapsed
		          << " in "
		          << computationTime
		          << ". Remind "
		          << reminder
		          << ", ETA " << Duration((reminder.Seconds() / ellapsed.Seconds()) * computationTime.Seconds() * 1e9)
		          << "\n";
	}

};

#define DECLARE_PD() \
	auto pd = new ProgressDisplayerIF()
#define CLEAR_PD() \
	delete pd

#define SET_PD(What) \
	if ( showProgress == true ) { \
		CLEAR_PD(); \
		pd = new ProgressDisplayer(experiment,startTime,endTime,What); \
	} \


SEXP fmQueryIdentifyFrames(const fort::myrmidon::CExperiment & experiment,
                           const fort::myrmidon::Time::ConstPtr & startTime,
                           const fort::myrmidon::Time::ConstPtr & endTime,
                           bool computeZones = false,
                           bool singleThread = false,
                           bool showProgress = false) {
	std::vector<IdentifiedFrame::ConstPtr> res_;
	DECLARE_PD();
	SET_PD("Processing");
	Query::IdentifyFramesFunctor(experiment,
	                             [&res_,pd](const IdentifiedFrame::ConstPtr & frame) {
		                             res_.push_back(frame);
		                             pd->ShowProgress(frame->FrameTime);
	                             },
	                             startTime,
	                             endTime,
	                             computeZones,
	                             true);
	SET_PD("R conversion");
	Rcpp::List res(res_.size());
	while( res_.empty() == false ) {
		res[res_.size()-1] = fmIdentifiedFrame_asR(res_.back());
		res_.pop_back();
	}
	CLEAR_PD();
	return res;
}

SEXP fmQueryCollideFrames(const fort::myrmidon::CExperiment & experiment,
                          const fort::myrmidon::Time::ConstPtr & startTime,
                          const fort::myrmidon::Time::ConstPtr & endTime,
                          bool singleThread,
                          bool showProgress) {
	std::vector<Query::CollisionData> res_;
	DECLARE_PD();
	SET_PD("Processing");
	Query::CollideFramesFunctor(experiment,
	                            [&res_,pd](const Query::CollisionData & data) {
		                            res_.push_back(data);
		                            pd->ShowProgress(std::get<0>(data)->FrameTime);
	                            },
	                            startTime,
	                            endTime,
	                            true);
	SET_PD("R conversion");
	Rcpp::List resPositions(res_.size()),resCollisions(res_.size());
	while( res_.empty() == false ) {
		resPositions[res_.size()-1] = fmIdentifiedFrame_asR(std::get<0>(res_.back()));
		resCollisions[res_.size()-1] = fmCollisionFrame_asR(std::get<1>(res_.back()));
		res_.pop_back();
	}
	Rcpp::List res;
	res["positions"]  = resPositions;
	res["collisions"] = resCollisions;
	CLEAR_PD();
	return res;
}


SEXP fmQueryComputeAntTrajectories(const CExperiment & experiment,
                                   const Time::ConstPtr & startTime,
                                   const Time::ConstPtr & endTime,
                                   const Duration & maximuGap,
                                   const Matcher::Ptr & matcher,
                                   bool computeZones,
                                   bool singleThreaded,
                                   bool showProgress) {
	std::vector<AntTrajectory::ConstPtr> res_;
	DECLARE_PD();
	SET_PD("Processing");
	Query::ComputeAntTrajectoriesFunctor(experiment,
	                                     [&res_,pd](const AntTrajectory::ConstPtr & at) {
		                                     res_.push_back(at);
		                                     pd->ShowProgress(at->End());
	                                     },
	                                     startTime,
	                                     endTime,
	                                     maximuGap,
	                                     matcher,
	                                     computeZones,
	                                     singleThreaded);
	SET_PD("R Conversion");
	Rcpp::List res(res_.size());
	while( res_.empty() == false ) {
		res[res_.size() - 1] = fmAntTrajectory_asR(res_.back());
		res_.pop_back();
	}
	CLEAR_PD();
	return res;
}

SEXP fmQueryComputeAntInteractions(const CExperiment & experiment,
                                   const Time::ConstPtr & startTime,
                                   const Time::ConstPtr & endTime,
                                   const Duration & maximuGap,
                                   const Matcher::Ptr & matcher,
                                   bool singleThreaded,
                                   bool showProgress) {
	std::vector<AntTrajectory::ConstPtr> resTrajectories_;
	std::vector<AntInteraction::ConstPtr>  resInteractions_;
	DECLARE_PD();
	SET_PD("Processing");
	Query::ComputeAntInteractionsFunctor(experiment,
	                                     [&resTrajectories_,pd](const AntTrajectory::ConstPtr & at) {
		                                     resTrajectories_.push_back(at);
		                                     pd->ShowProgress(at->End());
	                                     },
	                                     [&resInteractions_] ( const AntInteraction::ConstPtr & ai ) {\
		                                     resInteractions_.push_back(ai);
	                                     },
	                                     startTime,
	                                     endTime,
	                                     maximuGap,
	                                     matcher,
	                                     singleThreaded);

	Rcpp::List resTrajectories(resTrajectories_.size()),resInteractions(resInteractions_.size());
	SET_PD("R trajectory conversion");
	while(resTrajectories_.empty() == false ) {
		const auto & at = resTrajectories_.back();
		resTrajectories[resTrajectories_.size()-1] = fmAntTrajectory_asR(at);
		resTrajectories_.pop_back();
	}
	SET_PD("R interaction conversion");
	while(resInteractions_.empty() == false ) {
		const auto & ai = resInteractions_.back();
		resInteractions[resInteractions_.size()-1] = fmAntInteraction_asR(ai);
		resInteractions_.pop_back();
	}
	Rcpp::List res;
	res["trajectories"] = resTrajectories;
	res["interactions"] = resInteractions;
	CLEAR_PD();
	return res;
}



RCPP_MODULE(queries) {

	Rcpp::function("fmIdentifiedFrameDebug",&fmIdentifiedFrame_debug);
	Rcpp::function("fmCollisionDebug",&fmCollision_debug);
	Rcpp::function("fmCollisionFrameDebug",&fmCollisionFrame_debug);
	Rcpp::function("fmAntTrajectoryDebug",&fmAntTrajectory_debug);
	Rcpp::function("fmAntInteractionDebug",&fmAntInteraction_debug);


	Rcpp::function("fmQueryComputeMeasurementFor",&fmQuery_computeMeasurementFor);
	Rcpp::function("fmQueryComputeTagStatistics",&fmQuery_computeTagStatistics);
	Rcpp::function("fmQueryIdentifyFrames",&fmQueryIdentifyFrames);
	Rcpp::function("fmQueryCollideFrames",&fmQueryCollideFrames);
	Rcpp::function("fmQueryComputeAntTrajectories",&fmQueryComputeAntTrajectories);
	Rcpp::function("fmQueryComputeAntInteractions",&fmQueryComputeAntInteractions);

}
