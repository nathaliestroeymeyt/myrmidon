// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include "../inst/include/FortMyrmidon_types.hpp"
#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// fmVector2dListCreate
fort::myrmidon::Vector2dList fmVector2dListCreate(SEXP points);
RcppExport SEXP _FortMyrmidon_fmVector2dListCreate(SEXP pointsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type points(pointsSEXP);
    rcpp_result_gen = Rcpp::wrap(fmVector2dListCreate(points));
    return rcpp_result_gen;
END_RCPP
}
// pfmIWantAVector2dList
void pfmIWantAVector2dList(const fort::myrmidon::Vector2dList& l);
RcppExport SEXP _FortMyrmidon_pfmIWantAVector2dList(SEXP lSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const fort::myrmidon::Vector2dList& >::type l(lSEXP);
    pfmIWantAVector2dList(l);
    return R_NilValue;
END_RCPP
}
// fmExperimentCreate
ExperimentPtr fmExperimentCreate(const std::string& filepath);
RcppExport SEXP _FortMyrmidon_fmExperimentCreate(SEXP filepathSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type filepath(filepathSEXP);
    rcpp_result_gen = Rcpp::wrap(fmExperimentCreate(filepath));
    return rcpp_result_gen;
END_RCPP
}
// fmShapeListCreate
fort::myrmidon::Shape::List fmShapeListCreate(SEXP shapes);
RcppExport SEXP _FortMyrmidon_fmShapeListCreate(SEXP shapesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type shapes(shapesSEXP);
    rcpp_result_gen = Rcpp::wrap(fmShapeListCreate(shapes));
    return rcpp_result_gen;
END_RCPP
}
// pfmIWantAShapeList
void pfmIWantAShapeList(const fort::myrmidon::Shape::List& l);
RcppExport SEXP _FortMyrmidon_pfmIWantAShapeList(SEXP lSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const fort::myrmidon::Shape::List& >::type l(lSEXP);
    pfmIWantAShapeList(l);
    return R_NilValue;
END_RCPP
}
// fmTimeCreate
fort::Time fmTimeCreate(double offset);
RcppExport SEXP _FortMyrmidon_fmTimeCreate(SEXP offsetSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type offset(offsetSEXP);
    rcpp_result_gen = Rcpp::wrap(fmTimeCreate(offset));
    return rcpp_result_gen;
END_RCPP
}
// fmTimeNow
fort::Time fmTimeNow();
RcppExport SEXP _FortMyrmidon_fmTimeNow() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(fmTimeNow());
    return rcpp_result_gen;
END_RCPP
}
// fmTimeForever
fort::Time fmTimeForever();
RcppExport SEXP _FortMyrmidon_fmTimeForever() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(fmTimeForever());
    return rcpp_result_gen;
END_RCPP
}
// fmTimeSinceEver
fort::Time fmTimeSinceEver();
RcppExport SEXP _FortMyrmidon_fmTimeSinceEver() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(fmTimeSinceEver());
    return rcpp_result_gen;
END_RCPP
}
// fmTimeParse
fort::Time fmTimeParse(const std::string& input);
RcppExport SEXP _FortMyrmidon_fmTimeParse(SEXP inputSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type input(inputSEXP);
    rcpp_result_gen = Rcpp::wrap(fmTimeParse(input));
    return rcpp_result_gen;
END_RCPP
}
// fmDurationParse
fort::Duration fmDurationParse(const std::string& input);
RcppExport SEXP _FortMyrmidon_fmDurationParse(SEXP inputSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type input(inputSEXP);
    rcpp_result_gen = Rcpp::wrap(fmDurationParse(input));
    return rcpp_result_gen;
END_RCPP
}
// fmHour
fort::Duration fmHour(double h);
RcppExport SEXP _FortMyrmidon_fmHour(SEXP hSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type h(hSEXP);
    rcpp_result_gen = Rcpp::wrap(fmHour(h));
    return rcpp_result_gen;
END_RCPP
}
// fmMinute
fort::Duration fmMinute(double m);
RcppExport SEXP _FortMyrmidon_fmMinute(SEXP mSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type m(mSEXP);
    rcpp_result_gen = Rcpp::wrap(fmMinute(m));
    return rcpp_result_gen;
END_RCPP
}
// fmSecond
fort::Duration fmSecond(double s);
RcppExport SEXP _FortMyrmidon_fmSecond(SEXP sSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type s(sSEXP);
    rcpp_result_gen = Rcpp::wrap(fmSecond(s));
    return rcpp_result_gen;
END_RCPP
}
// fmMillisecond
fort::Duration fmMillisecond(double ms);
RcppExport SEXP _FortMyrmidon_fmMillisecond(SEXP msSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type ms(msSEXP);
    rcpp_result_gen = Rcpp::wrap(fmMillisecond(ms));
    return rcpp_result_gen;
END_RCPP
}
// fmMicrosecond
fort::Duration fmMicrosecond(double us);
RcppExport SEXP _FortMyrmidon_fmMicrosecond(SEXP usSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type us(usSEXP);
    rcpp_result_gen = Rcpp::wrap(fmMicrosecond(us));
    return rcpp_result_gen;
END_RCPP
}
// fmNanosecond
fort::Duration fmNanosecond(int64_t ns);
RcppExport SEXP _FortMyrmidon_fmNanosecond(SEXP nsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int64_t >::type ns(nsSEXP);
    rcpp_result_gen = Rcpp::wrap(fmNanosecond(ns));
    return rcpp_result_gen;
END_RCPP
}
// fmUTestDataCreate
Rcpp::List fmUTestDataCreate();
RcppExport SEXP _FortMyrmidon_fmUTestDataCreate() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(fmUTestDataCreate());
    return rcpp_result_gen;
END_RCPP
}

RcppExport SEXP _rcpp_module_boot_eigen();
RcppExport SEXP _rcpp_module_boot_experiment();
RcppExport SEXP _rcpp_module_boot_shapes();
RcppExport SEXP _rcpp_module_boot_space();
RcppExport SEXP _rcpp_module_boot_time();
RcppExport SEXP _rcpp_module_boot_zone();

static const R_CallMethodDef CallEntries[] = {
    {"_FortMyrmidon_fmVector2dListCreate", (DL_FUNC) &_FortMyrmidon_fmVector2dListCreate, 1},
    {"_FortMyrmidon_pfmIWantAVector2dList", (DL_FUNC) &_FortMyrmidon_pfmIWantAVector2dList, 1},
    {"_FortMyrmidon_fmExperimentCreate", (DL_FUNC) &_FortMyrmidon_fmExperimentCreate, 1},
    {"_FortMyrmidon_fmShapeListCreate", (DL_FUNC) &_FortMyrmidon_fmShapeListCreate, 1},
    {"_FortMyrmidon_pfmIWantAShapeList", (DL_FUNC) &_FortMyrmidon_pfmIWantAShapeList, 1},
    {"_FortMyrmidon_fmTimeCreate", (DL_FUNC) &_FortMyrmidon_fmTimeCreate, 1},
    {"_FortMyrmidon_fmTimeNow", (DL_FUNC) &_FortMyrmidon_fmTimeNow, 0},
    {"_FortMyrmidon_fmTimeForever", (DL_FUNC) &_FortMyrmidon_fmTimeForever, 0},
    {"_FortMyrmidon_fmTimeSinceEver", (DL_FUNC) &_FortMyrmidon_fmTimeSinceEver, 0},
    {"_FortMyrmidon_fmTimeParse", (DL_FUNC) &_FortMyrmidon_fmTimeParse, 1},
    {"_FortMyrmidon_fmDurationParse", (DL_FUNC) &_FortMyrmidon_fmDurationParse, 1},
    {"_FortMyrmidon_fmHour", (DL_FUNC) &_FortMyrmidon_fmHour, 1},
    {"_FortMyrmidon_fmMinute", (DL_FUNC) &_FortMyrmidon_fmMinute, 1},
    {"_FortMyrmidon_fmSecond", (DL_FUNC) &_FortMyrmidon_fmSecond, 1},
    {"_FortMyrmidon_fmMillisecond", (DL_FUNC) &_FortMyrmidon_fmMillisecond, 1},
    {"_FortMyrmidon_fmMicrosecond", (DL_FUNC) &_FortMyrmidon_fmMicrosecond, 1},
    {"_FortMyrmidon_fmNanosecond", (DL_FUNC) &_FortMyrmidon_fmNanosecond, 1},
    {"_FortMyrmidon_fmUTestDataCreate", (DL_FUNC) &_FortMyrmidon_fmUTestDataCreate, 0},
    {"_rcpp_module_boot_eigen", (DL_FUNC) &_rcpp_module_boot_eigen, 0},
    {"_rcpp_module_boot_experiment", (DL_FUNC) &_rcpp_module_boot_experiment, 0},
    {"_rcpp_module_boot_shapes", (DL_FUNC) &_rcpp_module_boot_shapes, 0},
    {"_rcpp_module_boot_space", (DL_FUNC) &_rcpp_module_boot_space, 0},
    {"_rcpp_module_boot_time", (DL_FUNC) &_rcpp_module_boot_time, 0},
    {"_rcpp_module_boot_zone", (DL_FUNC) &_rcpp_module_boot_zone, 0},
    {NULL, NULL, 0}
};

RcppExport void R_init_FortMyrmidon(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
