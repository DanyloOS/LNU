#ifndef SLVEQU_H
#define SLVEQU_H

#include "solvingequations_global.h"
#include <vector>
#include <cmath>

static const double PI = 3.14159265359;

enum MethodOfSolving {MthPD, MthN};

class SOLVINGEQUATIONSSHARED_EXPORT slvequ
{

public:
    slvequ(const double eps = 1e-7, const int N = 100, const int Kmax = 100) : eps(eps), N(N), Kmax(Kmax){}
    void Solve(double a0, double b0, double function(double), std::vector<double> &x,
               std::vector<int> &L, const int N, const int Kmax, const double eps, const MethodOfSolving method = MthN);

    void Solve(double a0, double b0, double function(double), std::vector<double> &x,
               std::vector<int> &L, const MethodOfSolving method = MthN);

    void setEps(double eps);
    void setN(int N);
    void setKmax(int Kmax);

private:
    double (*f)(double);
    double fp(double x, double D);
    double f2p(double x, double D);
    void MPN(double a, double b, std::vector<double> &x, std::vector<int> &L);
    void MN(double a, double b, std::vector<double> &x, std::vector<int> &L);

private:
    double eps;
    int N;
    int Kmax;
};

#endif // SLVEQU_H
