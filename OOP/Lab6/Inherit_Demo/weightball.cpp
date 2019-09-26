#include "weightball.h"

WeightBall::WeightBall() : Ball()
{
    setDensity(1000);
}

WeightBall::WeightBall(double initialRadius, std::string initialName, Color initialColor,
                       double initialDensity) : Ball(initialRadius, initialName, initialColor)
{
    setDensity(initialDensity);
}

void WeightBall::setDensity(double newDensity)
{
    theDensity = newDensity;
}

double WeightBall::getDensity()
{
    return theDensity;
}

double WeightBall::getWeight()
{
    return theDensity*getVolume();
}

void WeightBall::resetWeightBall(double newRadius, std::string newName, Color newColor, double newDensity)
{
    resetBall(newRadius, newName, newColor);
    setDensity(newDensity);
}

void WeightBall::displayStatistics()
{
    Ball::displayStatistics();
    std::cout << "Density = " << getDensity()
              << "\nWeight = " << getWeight() << std::endl;
}
