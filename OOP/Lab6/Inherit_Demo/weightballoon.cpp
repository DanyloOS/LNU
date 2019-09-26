#include "weightballoon.h"

WeightBalloon::WeightBalloon() : Balloon()
{
}

WeightBalloon::WeightBalloon(double initialRadius, std::string initialName, Color initialColor,
                             Gas initialGas) : Balloon (initialRadius, initialName, initialColor, initialGas)
{
}

double WeightBalloon::getDensity()
{
    double theDensity = 0;
    switch(getGas())
    {
    case N2O2: {
        theDensity = 1.225;
        break;
    }
    case H2: {
        theDensity = 0.09;
        break;
    }
    case He: {
        theDensity = 0.178;
        break;
    }
    case Ne: {
        theDensity = 0.901;
        break;
    }
    }
    return theDensity;
}

double WeightBalloon::getWeight()
{
    WeightBall::setDensity(getDensity());
    return WeightBall::getWeight();
}

void WeightBalloon:: resetWeightBalloon(double newRadius, std::string newName, Color newColor, Gas newGas)
{
    resetBallon(newRadius, newName, newColor, newGas);
}

void WeightBalloon::displayStatistics()
{
    Balloon::displayStatistics();
    std::cout << "Density = " << getDensity()
              << "\nWeight = " << WeightBalloon::getWeight() << std::endl;
}
