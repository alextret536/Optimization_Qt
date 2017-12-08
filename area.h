#ifndef AREA_H
#define AREA_H
#include "Const.h"
#include <iostream>
#include<vector>
//#pragma once
using namespace std;
/*!
\file
\section DESCRIPTION
The Area class represesent an area where the function exists
*/
class Area {
    vector<double> l; ///<left bound of area
    vector<double> r; ///<right bound of area
public:
    /*!
    Constructor that sets left and right bounds of the area
    \param left Left bound
    \param right Right bound
    */
    Area(vector<double> left, vector<double> right) : l(left), r(right) {};
    /*!
    Method that returns left bound of area
    */
    const vector<double> GetL() const;
    /*!
    Method that returns right bound of area
    */
    const vector<double> GetR() const;
    /*!
    Destructor
    */
    virtual ~Area();
};

/*!
This class derives from the Area class and represents an area of dimension 2
*/
class Area1 : public Area {
public:
    /*!
    Constructor that sets left bound to a given value or {-3,-3} and right bound to a given value or {4,4} if no parameter is supplied
    \param left Left bound
    \param right Right bound
    */
    Area1(vector<double> left = { -3,-3 },
        vector<double> right = { 4,4 }) :
        Area(left, right) {};
};

/*!
This class derives from the Area class and represents an area of dimension 4
*/
class Area2 : public Area {
public:
    /*!
    Constructor that sets left bound to a given value or {-3,-3,-3,-3} and right bound to a given value or {4,4,4,4} if no parameter is supplied
    \param left Left bound
    \param right Right bound
    */
    Area2(vector<double> left = { -3,-3,-3,-3 },
        vector<double> right = { 4,4,4,4 }) :
        Area(left, right) {};
};
#endif // AREA_H
