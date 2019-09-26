#ifndef WEIGHTBALLOON_H
#define WEIGHTBALLOON_H

#include "weightball.h"
#include "balloon.h"

class WeightBalloon : public WeightBall, public Balloon
{
public:
    WeightBalloon();
    WeightBalloon(double initialRadius, std::string initialName,
                  Color initialColor, Gas initialGas);
    double getDensity();
    virtual double getWeight();
    void resetWeightBalloon(double newRadius, std::string newName,
                            Color newColor, Gas newGas);
    virtual void displayStatistics();
};

#endif // WEIGHTBALLOON_H
