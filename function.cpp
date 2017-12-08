#include "Function.h"
#include <cmath>

double F1::f(vector<double>const& x) {
    return ((x[1] - x[0] * x[0])*(x[1] - x[0] * x[0]) +
        100 * (1 - x[0])*(1 - x[0]));
}
double F2::f(vector<double>const& x) {
    return (x[0]-2) * (x[0]-2) + (x[1]+1) * (x[1]+1);
}
double F3::f(vector<double>const& x) {
    return (x[0]*x[0]+x[1]-11)*(x[0]*x[0]+x[1]-11)+
            (x[0]+x[1]*x[1]-7)*(x[0]+x[1]*x[1]-7);
}
//(3,2), (-2,8;-3,13), (-3,7;-3,2)
Function:: Function(int d) { dim = d; }
int const Function:: GetDim() const { return dim; }
Function:: ~Function() {}

vector<double> Function::gradient(vector<double> const& x, Constant& par) {
    vector<double> grad(x.size());
    double delta = par.GetDelta();
    for (int i = 0; i < x.size(); i++) {
        std::vector<double> delt(x.size());
        delt.at(i) = delta;
        grad[i] = (f(x + delt) - f(x - delt)) / (2 * delta);
    }
    return grad;
}

double Function::df(vector<double> x, vector<double> p, Constant& par) {
    double delta = par.GetDelta();
    return((f(x + (p*(1 / norm(p)))* delta) -
        f(x + (p*(1 / norm(p)))* (-1)* delta)) / (2 * delta));
}

vector<double> operator+(vector<double> const& x, vector<double> const& y) {
    std::vector<double> res;
    for (int i = 0; i < x.size(); i++) {
        res.push_back(x.at(i) + y.at(i));
    }
    return res;
}

vector<double> operator-(vector<double> const& x, vector<double> const& y) {
    std::vector<double> res;
    for (int i = 0; i < x.size(); i++) {
        res.push_back(x.at(i) - y.at(i));
    }
    return res;
}
vector<double> operator*(vector<double> const& x, const double c) {
    vector<double> res;
    for (int i = 0; i < x.size(); i++) {
        res.push_back(c* x.at(i));
    }
    return res;
}

double norm(vector<double> const& x) {
    double accum = 0.;
    for (int i = 0; i < x.size(); ++i) {
        if (abs(x[i]) > accum) accum = abs(x[i]);
    }
    return accum;
}

double scalpr(vector<double> const& x, vector<double> const& y) {
    double prod = 0;
    for (int i = 0; i < x.size(); i++) {
        prod += x.at(i)*y.at(i);
    }
    return prod;
}

void vprint(vector<double> x) {
    for (int i = 0; i < x.size(); ++i)
        cout << x[i] << "   ";
    cout << endl;
}

void vread(vector<double>& x) {
    for (int i = 0; i < x.size(); ++i)
        cin >> x[i];
}
