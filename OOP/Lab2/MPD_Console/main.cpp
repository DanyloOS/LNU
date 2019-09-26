#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

#define PI 3.14159265359

using namespace std;

double f (double x)
{
    return cos(4*x*PI)+sin(8*x*PI);
}
void MPN(double a, double b, vector<double> &x, vector<int> &L, double eps);
void Solve(double a0, double b0, int N, vector <double> &x, vector <int> &L, double eps = 1e-3);

int main()
{
    double a0, b0, eps;
    int N;
    vector <double> x;
    vector <int> L;

    cout << "Input [a, b], N and eps: " ;
    cin >> a0 >> b0 >> N >> eps;
    if (b0 < a0) swap (a0, b0);
    Solve(a0, b0, N, x, L, eps);

    if (x.empty()){
        cout << "I couldn't find any root... sorry :(\nTry to input larger N";
        return 0;
    }
    // доробити cout.precision(1/eps) + setw(1/eps+2);

    cout << "I have found some roots!\n\n" <<
            setw(3) << "i" << setw(10) << "x" << setw(3) << "L" << setw(15) << "f(x)" << fixed << endl;
    cout.precision(4);
    for(unsigned long long i = 0; i < x.size(); i++)
    {
        cout << setw(3) << i + 1 << ". " << setw(8) << x[i] << setw(3) << L[i] << setw(15) << f(x[i]) << endl;
    }
    return 0;
}

void MPN(double a, double b, vector <double> &x, vector <int> &L, double eps)
{
    L.push_back(0);
    double c = 0;
    if (fabs(a) <= eps){
        x.push_back(a);
        return;
    }
    else if(fabs(b) < eps){
        x.push_back(b);
        return;
    }

    if (f(a)*f(b) < 0) {
        while (fabs(a - b) > eps ) {
            L[L.size()-1]++;
            c = a + 0.5*(b - a);

            if (fabs(f(c)) < eps) {
                x.push_back(c);
                return;

            }
            if (f(a)*f(c) < 0)
                b = c;
            else
                a = c;
        }
    }
    x.push_back(c);
}

void Solve(double a0, double b0, int N, vector <double> &x, vector <int> &L, double eps)
{
    double step = fabs(a0 - b0)/N;
    double a, b, a0prev;
    if (fabs(f(a0)) < eps){
        x.push_back(a0);
        L.push_back(0);
        a0 += step;
    }
    if (fabs(f(b0)) < eps){
        x.push_back(b0);
        L.push_back(0);
        b0 -= step;
    }

    a0 += step;

    while (a0 < b0) {
        a0prev = a0 - step;
        if (fabs(f(a0)) < eps)
                {
                    x.push_back(a0);
                    L.push_back(0);
                    a0 += step;
                }
        else if (f(a0prev) > 0 && f(a0) < 0) {
            if ( ( f(a0prev) > f(a0prev + eps) ) &&  ( f(a0 - eps) > f(a0) ) ){
                a = (a0prev);
                b = (a0);
                MPN(a, b, x, L, eps);
            }
        }
        else if (f(a0prev) < 0 && f(a0) > 0) {
            if ( ( f(a0prev) < f(a0prev + eps) ) &&  ( f(a0 - eps) < f(a0) ) ){
                a = a0prev;
                b = a0;
                MPN(a, b, x, L, eps);
            }
        } 
        a0 += step;
    }
}
