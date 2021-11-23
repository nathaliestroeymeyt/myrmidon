#include <gtest/gtest.h>

#include "Experiment.hpp"
#include "Query.hpp"

#include "MovieSegmentData.hpp"

#include "UtilsUTest.hpp"
#include "TestSetup.hpp"

#include <opencv2/core.hpp>

#define failure_helper(aExpr,bExpr,a,b,field) \
	::testing::AssertionFailure() \
	<< "Value of: " << aExpr << "." << #field << std::endl \
	<< "  Actual: " << a.field << std::endl \
	<< "Expected: " << bExpr << "." << #field << std::endl \
	<< "Which is: " << b.field


#define check(aExpr,bExpr,a,b,field) do {	  \
		if ( a.field != b.field ) { \
			return failure_helper(aExpr,bExpr,a,b,field); \
		} \
	} while(0)

#define check_presence(aExpr,bExpr,a,b,field) do { \
		if ( (!b.field) != (!a.field) ) { \
			return ::testing::AssertionFailure() \
				<< "Value of: " << aExpr << "." << #field << " != nullptr " << std::endl \
				<< "  Actual: " << std::boolalpha << bool(a.field) << std::endl \
				<< "Expected: " << bool(b.field); \
		} \
	}while(0)



::testing::AssertionResult AssertMatchedDataEqual(const char * aExpr,
                                                  const char * bExpr,
                                                  const fort::myrmidon::MovieSegmentData::MatchedData & a,
                                                  const fort::myrmidon::MovieSegmentData::MatchedData & b) {
	auto tmp = AssertTimeEqual((std::string(aExpr) + ".Time").c_str(),
	                           (std::string(bExpr) + ".Time").c_str(),
	                           a.Time,
	                           b.Time);
	if ( !tmp ) {
		return tmp;
	}
	check_presence(aExpr,bExpr,a,b,Identified);
	if ( b.Identified ) {
		tmp = AssertIdentifiedFrameEqual(("*" + std::string(aExpr) + ".Identified").c_str(),
		                                  ("*" + std::string(bExpr) + ".Identified").c_str(),
		                                 *a.Identified,
		                                 *b.Identified);
		if (!tmp) {
			return tmp;
		}
	}
	check_presence(aExpr,bExpr,a,b,Collided);
	if ( b.Collided ) {
		tmp = AssertCollisionFrameEqual(("*" + std::string(aExpr) + ".Collided").c_str(),
		                                ("*" + std::string(bExpr) + ".Collided").c_str(),
		                                *a.Collided,
		                                *b.Collided);
		if (!tmp) {
			return tmp;
		}
	}

	check(aExpr,bExpr,a,b,Trajectories.size());
	for ( size_t i = 0; i < b.Trajectories.size(); ++i) {
		tmp == AssertAntTrajectoryEqual(("*" + std::string(aExpr) + ".Trajectories[" + std::to_string(i) + "]").c_str(),
		                                ("*" + std::string(bExpr) + ".Trajectories[" + std::to_string(i) + "]").c_str(),
		                                *a.Trajectories[i],
		                                *b.Trajectories[i]);
		if (!tmp) {
			return tmp;
		}
	}

	check(aExpr,bExpr,a,b,Interactions.size());

	for ( size_t i = 0; i < b.Interactions.size(); ++i) {
		tmp == AssertAntInteractionEqual(("*" + std::string(aExpr) + ".Interactions[" + std::to_string(i) + "]").c_str(),
		                                 ("*" + std::string(bExpr) + ".Interactions[" + std::to_string(i) + "]").c_str(),
		                                *a.Interactions[i],
		                                *b.Interactions[i]);
		if (!tmp) {
			return tmp;
		}
	}

	check(aExpr,bExpr,a,b,UserData.size());
	return ::testing::AssertionSuccess();

}


::testing::AssertionResult AssertMovieSegmentDataEqual(const char * aExpr,
                                                       const char * bExpr,
                                                       const fort::myrmidon::MovieSegmentData & a,
                                                       const fort::myrmidon::MovieSegmentData & b) {
	check(aExpr,bExpr,a,b,Space);
	check(aExpr,bExpr,a,b,AbsoluteFilePath);
	check(aExpr,bExpr,a,b,Begin);
	check(aExpr,bExpr,a,b,End);
	check(aExpr,bExpr,a,b,Data.size());
	for ( size_t i = 0; i < a.Data.size(); ++i ) {
		auto tmp = AssertMatchedDataEqual((std::string(aExpr) + ".Data[" + std::to_string(i) + "]").c_str(),
		                                  (std::string(bExpr) + ".Data[" + std::to_string(i) + "]").c_str(),
		                                  a.Data[i],
		                                  b.Data[i]);
		if ( !tmp ) {
			return tmp;
		}
	}
	return ::testing::AssertionSuccess();
}

namespace fort {
namespace myrmidon {


class MovieSegmentDataUTest : public ::testing::Test {
protected:
	void SetUp() {
		experiment = Experiment::Open(TestSetup::UTestData().CurrentVersionFile().AbsoluteFilePath);
	}

	Experiment::Ptr experiment;
};

TEST_F(MovieSegmentDataUTest,MatchDataEdgeCases) {
	std::vector<IdentifiedFrame::Ptr> data;
	EXPECT_NO_THROW({
			MovieSegmentData::List segments;
			MovieSegmentData::MatchData(segments,data.begin(),data.end());
		});

	MovieSegmentData::List segments =
		{
		 {.Space = 1},
		 {.Space = 2},
		};


	EXPECT_THROW({
			MovieSegmentData::MatchData(segments,
			                            data.begin(),
			                            data.end());
		},std::invalid_argument);

};


TEST_F(MovieSegmentDataUTest,ForEachFramesEdgeCases) {
	const auto & expected = TestSetup::UTestData().ExpectedResults().front();
	const auto & frames = TestSetup::UTestData().ExpectedFrames();
	std::vector<MovieSegmentData> segments;

	Query::FindMovieSegment(*experiment,
	                        segments,
	                        1,
	                        expected.Start,
	                        expected.End);
	ASSERT_EQ(segments.size(),1);
	auto & segment = segments.front();
	segment.Data.resize(segment.Data.size()-1);
	segment.Data.push_back({.FramePosition = segment.End,
	                        .Time = Time::SinceEver()});
	segment.End += 2;

	MovieSegmentData::ForEachFrames(segments,
	                                [&](const cv::Mat & ,
	                                    const MovieSegmentData::MatchedData & d) {
		                                auto fi = std::find_if(segment.Data.begin(),
		                                                       segment.Data.end(),
		                                                       [&](const MovieSegmentData::MatchedData & it) {
			                                                       return it.FramePosition == d.FramePosition;
		                                                       });
		                                if ( fi == segment.Data.end() ) {
			                                EXPECT_PRED_FORMAT2(AssertMatchedDataEqual,
			                                                    d,
			                                                    (MovieSegmentData::MatchedData{.FramePosition = d.FramePosition,
					             .Time = Time::SinceEver()}));
		                                } else {
			                                EXPECT_PRED_FORMAT2(AssertMatchedDataEqual,
			                                                    d,
			                                                    *fi);
		                                }
	                                });

};




TEST_F(MovieSegmentDataUTest,EndToEnd) {
	const auto & expected = TestSetup::UTestData().ExpectedResults().front();
	const auto & frames = TestSetup::UTestData().ExpectedFrames();
	std::vector<MovieSegmentData> segments;

	Query::FindMovieSegment(*experiment,
	                        segments,
	                        1,
	                        expected.Start,
	                        expected.End);

	MovieSegmentData::MatchData(segments,
	                            frames.begin(),
	                            frames.end());

	MovieSegmentData::MatchData(segments,
	                            expected.Trajectories.begin(),
	                            expected.Trajectories.end());

	MovieSegmentData::MatchData(segments,
	                            expected.Interactions.begin(),
	                            expected.Interactions.end());

	ASSERT_EQ(segments.size(),
	          expected.MovieSegments.at(1).size());

	for ( size_t i = 0; i < expected.MovieSegments.at(1).size(); ++i ) {
		EXPECT_PRED_FORMAT2(AssertMovieSegmentDataEqual,
		                    segments[i],
		                    expected.MovieSegments.at(1)[i])
			<< "  With i: " << i;
	}

	ASSERT_EQ(segments.size(),1);


	auto iter = segments.front().Data.begin();

	MovieSegmentData::ForEachFrames(segments,
	                                [&](const cv::Mat & mat,
	                                    const MovieSegmentData::MatchedData & d) {
		                                ASSERT_TRUE(iter != segments.front().Data.end() );
		                                EXPECT_FALSE(mat.empty());
		                                EXPECT_PRED_FORMAT2(AssertMatchedDataEqual,
		                                                    d,
		                                                    *iter);
		                                ++iter;
	                                });

	Query::FindMovieSegment(*experiment,
	                        segments,
	                        3,
	                        expected.Start,
	                        expected.End);
	EXPECT_TRUE(segments.empty());

	Query::FindMovieSegment(*experiment,
	                        segments,
	                        2,
	                        expected.Start,
	                        expected.End);
	EXPECT_TRUE(segments.empty());

}


} // namespace myrmidon
} // namespace fort
