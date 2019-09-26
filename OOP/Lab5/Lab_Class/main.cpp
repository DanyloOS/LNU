#include <iostream>
#include "sphere.h"

using namespace std;

int main()
{
    Sphere unitSphere;
    Sphere mySphere(5.1);
    unitSphere.displayStatistics();
    mySphere.setRadius(4.2);
    mySphere.displayStatistics();
    std::cout << "\nD = " << mySphere.getDiameter() << std::endl;
    return 0;
}
