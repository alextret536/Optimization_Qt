#ifndef STOPCRITERION_H
#define STOPCRITERION_H
#include "Const.h"
#include "Function.h"
#include<vector>
using namespace std;

/*!
\file
\section DESCRIPTION
StopCriterion class for checking when method should stop
*/
class StopCriterion {
public:
    /*!
    Abstract method for checking if criterion is true or false
    \param f Function
    \param x Vector
    \param iter Number of iterations
    */
    virtual const bool StopCheck(Function* f, vector<double> const& x,
        int iter, int iter_s, Constant& par) const = 0;
    /*!
    Destructor
    */
    virtual ~StopCriterion();
};

/*!
NumberOfIterations class derives from the StopCriterion class and represents Number of iterations Criterion: (iter <= STOP_CRIT)
*/
class NumberOfIterations : public StopCriterion {
public:
    /*!
    Abstract method for checking if NumberOfIterations criterion is true or false
    \param f Function
    \param x Vector
    \param iter Number of iterations
    */
    bool const StopCheck(Function* f, vector<double> const& x,
        int iter, int iter_s, Constant& par) const override;
};

/*!
GradientNorm class derives from the StopCriterion class and represents Gradient norm Criterion: (norm(gradient)>=eps)
*/
class GradientNorm : public StopCriterion {
public:
    /*!
    Abstract method for checking if GradientNorm  criterion is true or false
    \param f Function
    \param x Vector
    \param iter Number of iterations
    */
    bool const StopCheck(Function* f, vector<double> const& x,
        int iter, int iter_s, Constant& par) const override;
};
#endif // STOPCRITERION_H
