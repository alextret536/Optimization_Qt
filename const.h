#ifndef CONST_H
#define CONST_H
class Constant {
double eps;
double delta;
int maxiter;
int maxiter_success;
public:
Constant(double _eps, double _delta,
    int _maxiter,int _maxiter_success);
//Constant();
Constant() = default;
double GetEps() const;
double GetDelta() const;
double GetMaxiter() const;
double GetMaxiterSuccess() const;

};
const  double c = 0.6; ///<For making epsilon in Random Search smaller
#endif // CONST_H
