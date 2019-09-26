#include "sphere.h"
#include <iostream>

Sphere::Sphere() : theRadius(1.0)
{ }

Sphere::Sphere(double initialRadius)
{
    if (initialRadius > 0 )
        theRadius = initialRadius;
    else
        theRadius = 1.0;
}

void Sphere::setRadius(double newRadius)
{
    if (newRadius > 0)
        theRadius = newRadius;
    else
        theRadius = 1.0;
}

double Sphere::getRadius() const
{
    return theRadius;
}

double Sphere::getDiameter() const
{
    return 2 * theRadius;
}

double Sphere::getCircumference() const
{
    return PI * getDiameter();
}

double Sphere::getArea() const
{
    return 4 * PI * theRadius * theRadius;
}

double Sphere::getVolume() const
{
    return (4 * PI * theRadius * theRadius * theRadius) / 3;
}
void Sphere::displayStatistics() const
{
    std::cout << "\nRadius = " << getRadius()
              << "\nDiameter = " << getDiameter()
              << "\nCircumference = " << getCircumference()
              << "\nArea = " << getArea()
              << "\nVolume = " << getVolume() << std::endl;
}
