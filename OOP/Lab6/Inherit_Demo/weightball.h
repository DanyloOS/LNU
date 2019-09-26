#ifndef WEIGHTBALL_H
#define WEIGHTBALL_H

#include "ball.h"

class WeightBall : public Ball
{
public:
    WeightBall();
    WeightBall(double initialRadius, std::string initialName,
               Color initialColor, double initialDensity);
    void setDensity(double newDensity);
    double getDensity();
    virtual double getWeight();
    void resetWeightBall(double newRadius, std::string newName,
                         Color newColor, double newDensity);
    virtual void displayStatistics();
private:
    double theDensity;
};

#endif // WEIGHTBALL_H
