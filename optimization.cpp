#include"Optimization.h"
#include <vector>
#include <cstdio>
#include <iostream>
#include <random>
#include <time.h>
using namespace std;

const char* PolakRibiere:: name() const {
    return "Polak-Ribiere Method"; };
double PolakRibiere::right_value(vector<double> x,
    vector<double> l, vector<double> r, vector<double> p) {
    double bord, t;
    if (p[0] > 0) bord = (r[0] - x[0]) / p[0];
    else bord = (l[0] - x[0]) / p[0];
    for (int i = 0; i < x.size(); ++i) {
        if (p[i] > 0) t = (r[i] - x[i]) / p[i];
        else t = (l[i] - x[i]) / p[i];
        if (abs(t) < bord) bord = abs(t);
    }
    return bord;
};
double PolakRibiere::argmin(vector<double> const& x,
    vector<double> const& p, Function* f, Area* area, Constant& par) {
    double l = 0, r = right_value(x, area->GetL(), area->GetR(), p);
    double m = (l + r) / 2;
    while (abs(f->df(x + p*m, p,par)) >= par.GetEps()) {
        if (f->df(x + p*m, p,par) > 0)
            r = m;
        else l = m;
        m = (l + r) / 2;
    }
    // // //

    return m;
};
vector<double> PolakRibiere:: minimize(Function* f, Area* area,
    StopCriterion* crit1,  vector<double> x, Constant& par) {
    double beta = 0; double alpha = 1;
    vector<double> oldGrad(f->gradient(x,par));
    vector<double> newGrad(x.size());
    vector<double> p(oldGrad*(-1));
    points.clear();
    points.push_back(x);
    int k = 1;
    while (crit1->StopCheck(f, x, k,k,par)) {
        alpha = argmin(x, p, f, area, par);
        x = x + p*alpha;
        newGrad = f->gradient(x,par);
        beta = scalpr(newGrad, newGrad - oldGrad) /
            scalpr(oldGrad, oldGrad);
        p = newGrad*(-1) + p*beta;
        oldGrad = newGrad;
        k++;
        points.push_back(x);
        ++iter;
    }
    return x;
};

RandomSearch::RandomSearch(double prob) : p(prob) {
    std::random_device rd;
    //std::mt19937 mt(rd());
   // std::mt19937 mt(time(0));
  //  std::uniform_real_distribution<> d(0, 1);
  //  u = d;
    iter = 0;
}
mt19937 mt_rand(time(0));
uniform_real_distribution<>u(0, 1);

const char* RandomSearch::name() const {
    return "Random Search Method"; };
vector<double> RandomSearch::RandInArea(Area* D) {
    int dim = D->GetL().size();
    vector<double> res;
    for (int k = 0; k < dim; ++k) {
    res.push_back(D->GetL()[k] + (D->GetR()[k] - D->GetL()[k])*u(mt_rand));
    }
    return res;
}
vector<double>RandomSearch::minimize(Function* f, Area* area,
    StopCriterion* crit1, vector<double> x, Constant& par) {
    int count = 0;
    points.clear();
    points.push_back(x);
    double ksi; double eps1 = par.GetEps();
    std::vector<double> xi(area->GetL().size());
    std::vector<double> yi(area->GetL().size());
    std::vector<double> br(area->GetL().size());
    std::vector<double> bl(area->GetL().size());
    yi = RandInArea(area);
    points.push_back(yi);
    //for (int i = 0; count<STOP_RAND; i++) {
    for (int i = 0; crit1->StopCheck(f,yi,iter,count,par); i++) {
        ++iter;
        ksi = u(mt_rand);
        if (ksi <= p) {
            xi = RandInArea(area);
        }
        else {
            for (int k = 0; k < area->GetL().size(); k++) {
                if (abs(area->GetR()[k] - yi[k]) > eps1) {
                    br[k] = yi[k] + eps1;
                }
                else br[k] = area->GetR()[k];
                if (abs(area->GetL()[k] - yi[k]) > eps1) {
                    bl[k] = yi[k] - eps1;
                }
                else bl[k] = area->GetL()[k];
            }
            Area NewRectangle(bl, br);
            xi = RandInArea(&NewRectangle);
            eps1 *= c;
        }
        if (f->f(yi) > f->f(xi)) {
            yi = xi, count = 0;
        }
        else count++;
        points.push_back(yi);
    }
    return yi;
}

int Optimization::GetIter() const { return iter; };
vector<vector<double>> Optimization:: GetPoints() {return points; };
Optimization:: ~Optimization() {};
