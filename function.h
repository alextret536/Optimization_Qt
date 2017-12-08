#ifndef FUNCTION_H
#define FUNCTION_H
//#pragma once
#include <iostream>
#include<vector>
#include "Const.h"
using namespace std;
/*!
\file
\author Aleksandra Tretyakova
\version 1.0

\section DESCRIPTION

Function class with an integer dim (dimension of the function)
*/
class Function {
    int dim;
public:
    /*!
    Constructor that sets the dimension of the function
    \param d The dimension
    */
    Function(int d);
    /*!
    Abstract method that returns value of the function
    \param x Vector of double
    */
    virtual double f(vector<double> const& x) = 0;
    /*!
    Method that returns the dimension of the function
    */
    int const GetDim() const;
    /*!
    Returns gradient of function in point x
    \param x Vector of double
    */
    vector<double> gradient(vector<double> const& x, Constant& par);
    /*!
    Method that returns directional derivative
    \param x Vector of double
    \param p Direction
    */
    double df(vector<double> x, vector<double> p, Constant& par);
    /*!
    Destructor
    */
    virtual ~Function();
    /*!
    Operator+ for std::vector<double>
    \param x Vector of double
    \param y Vector of double
    \return x+y
    */
};

/*!
The class F1 derives from the Function class
*/
class F1 : public Function {
public:
    /*!
    Constructor that sets dim = 2
    */
    F1() : Function(2) {}
    /*!
    Returns function value
    */
    double f(vector<double>const& x) override;
};

class F2 : public Function {
public:
    /*!
    Constructor that sets dim = 2
    */
    F2() : Function(2) {}
    /*!
    Returns function value
    */
    double f(vector<double>const& x) override;
};

class F3 : public Function {
public:
    /*!
    Constructor that sets dim = 4
    */
    F3() : Function(2) {}
    /*!
    Returns function value
    */
    double f(vector<double>const& x) override;
};
/*!
Void for printing vector
*/
void vprint(vector<double> x);
void vread(vector<double>& x);

vector<double> operator+(vector<double> const& x, vector<double> const& y);
/*!
Operator- for std::vector<double>
\param x Vector of double
\param y Vector of double
\return x-y
*/
vector<double> operator-(vector<double> const& x, vector<double> const& y);
/*!
Operator* for const and std::vector<double>
\param x Vector of double
\param c const
\return c*x
*/
vector<double> operator*(vector<double> const& x, const double c);
/*!
Returns the norm of vector
\param x Vector of double
*/
 double norm(vector<double> const& x);
/*!
Returns the scalar product of two vectors
\param x Vector of double
\param y Vector of double
*/
 double scalpr(vector<double> const& x, vector<double> const& y);
#endif // FUNCTION_H
