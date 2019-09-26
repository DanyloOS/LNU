#ifndef BALLOON_H
#define BALLOON_H

#include "ball.h"

enum Gas {N2O2, H2, He, Ne};

class Balloon : public Ball
{
public:
    Balloon();
    Balloon(double initialRadius, std::string initialName, Color initialColor, Gas initialGas);
    void setGas(Gas newGas);
    Gas getGas();
    std::string getGasName();
    void resetBallon(double newRadius, std::string newName, Color newColor, Gas newGas);
    void displayStatistics();
private:
    Gas theGas;
};

#endif // BALLOON_H
