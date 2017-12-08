#ifndef OPTIMIZATION_H
#define OPTIMIZATION_H
#include <random>
#include <time.h>
#include "Const.h"
#include "Function.h"
#include "Area.h"
#include"StopCriterion.h"

/*!
\file
\section DESCRIPTION
Optimization class for searching for a minimum of the function
*/
class Optimization {
protected:
    int iter=0;
    vector<vector<double>> points;
public:
    /*!
    Abstract method for searching for a minimum
    \param f Function
    \param area Area
    \param crit1 Stop Criterion
    \param x Vector
    \return Argmin of the function
    */
    virtual vector<double> minimize(Function* f, Area* area,
        StopCriterion* crit1, vector<double> x, Constant& par) = 0;
    /*!
    Returns the method name
    \return const char* string with the method name
    */
    virtual const char* name() const = 0;
    int GetIter() const;
    vector<vector<double>> GetPoints();
    virtual ~Optimization();
};

/*!
PolakRibiere class is for searching for local minimum using Polak-Ribiere Method
*/
class PolakRibiere : public Optimization {
public:
    /*!
    Returns the method name
    */
    const char* name() const override;
    PolakRibiere() { iter = 0; };
    /*!
    Method for searching for a right bound of alpha
    \param x Vector
    \param l Left bound of area
    \param r Right bound of area
    \param p Vector
    \return Right bound for alpha
    */
    double right_value(vector<double> x, vector<double> l,
        vector<double> r, vector<double> p);
    /*!
    Method for searching for argmin f(x_k + alpha_k * p_k) using Dichotomy Method
    \param x Vector
    \param p Vector
    \param f Function
    \param area Area
    \return Argmin of the function
    */
    double argmin(vector<double> const& x, vector<double> const& p,
        Function* f, Area* area, Constant& par);
    /*!
    Abstract method for searching for a local minimum of the function using Polak-Ribiere Method
    \param f Function
    \param area Area
    \param crit1 Stop Criterion
    \param x Vector
    \return Argmin of the function
    */
    vector<double> minimize(Function* f, Area* area,
        StopCriterion* crit1, vector<double> x, Constant& par);

};

/*!
RandomSearch class is for searching for global minimum using Random Search Method
*/
class RandomSearch : public Optimization {
   // std::mt19937 mt_rand;
  //  std::uniform_real_distribution<> u;
    double p;
public:
    /*!
    Default constructor
    */
    RandomSearch() = default;
    /*!
    Constructor that sets the probability for Random Search Method
    */
    RandomSearch(double prob);
    /*!
    Returns the method name
    */
    const char* name() const override;
    /*!
    Method for getting a random point in the area
    \param D Area
    */
    vector<double> RandInArea(Area* D);
    /*!
    Abstract method for searching for a global minimum of the function using Random Search
    \param f Function
    \param area Area
    \param crit1 Stop Criterion 1
    \param x Vector
    \return Argmin of the function
    */
    vector<double> minimize(Function* f, Area* area,
        StopCriterion* crit1, vector<double> x, Constant& par);
};
#endif // OPTIMIZATION_H
