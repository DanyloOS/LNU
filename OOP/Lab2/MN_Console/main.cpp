#include <iostream>
#include <cmath>

using namespace std;

double f(double x){
    return x*x*x - 8;
}

double fp(double x,double D){
    return ((f(x+D)-f(x))/D);
}

double f2p(double x,double D){
    return ((fp(x+D,D)-fp(x,D))/D);
}

int main()
{
    double a, b, eps, x, Dx = 0;
    int i, Kmax;

    cout << "x*x*x - 8 = 0\n\n";
    cout << "Enter the value of the integral boundary:\n";
    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;
    cout << "Enter eps: ";
    cin >> eps;
    double D = eps/100.0;
    cout << "Enter Kmax: ";
    cin >> Kmax;
    if (a > b) swap(a,b);

    x = b;

    if((f(x)*f2p(x,D)<0))
        x = a;
    if((f(x)*f2p(x,D)<0))
        cout<<"For this equation,the convergence of Newton`s method is not guaranteed"<<endl;

    for(i = 0; i < Kmax; i++){
        Dx = f(x)/fp(x, D);
        x -= Dx;
        if (fabs(Dx) <= eps)
            break;
    }

    if (i == Kmax)
    {
        cout << "With a total number of iterations the solution is not found!";
        return 0;
    }

    cout << "x* = " << x << endl;
    cout << fixed << "Dx = " << Dx << endl;
    cout << "i = " << i << endl;

    return 0;
}
