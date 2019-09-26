#include <QCoreApplication>
#include <vector>
#include <iostream>
#include <iomanip>
#include "libSlvEqu/slvequ.h"

double func(double x)
{
    return cos(4*PI*x) + sin(8*PI*x);
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    std::vector<double> x;
    std::vector<int> L;

    double a, b, eps;
    int N, Kmax;

    std::cout << "Input a, b, eps and others\na\tb\teps\tN\tKmax\n";
    std::cin >> a >> b >> eps >> N >> Kmax;



    slvequ newObject(1e-7,100);

    newObject.Solve(a, b, func, x, L);

    std::cout << "\n" << std::setw(10) << "X" << std::setw(6) << "L" << std::endl;
    for (unsigned int i = 0; i < x.size(); i++)
        std::cout << std::setw(10) << x[i] << std::setw(6) << L[i] << std::endl;


    return app.exec();
}
