#include"StopCriterion.h"

bool const NumberOfIterations:: StopCheck(Function* f,
    vector<double> const& x, int iter, int iter_s, Constant& par) const {
    return (iter_s < par.GetMaxiterSuccess())
        && (iter < par.GetMaxiter());
};
bool const GradientNorm:: StopCheck(Function* f,
    vector<double> const& x, int iter, int iter_s, Constant& par) const {
    return (norm(f->gradient(x,par)) >= par.GetEps())
        &&(iter< par.GetMaxiter());
};
StopCriterion:: ~StopCriterion() {};
