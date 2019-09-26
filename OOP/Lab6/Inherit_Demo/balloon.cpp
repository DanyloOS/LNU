#include "balloon.h"

Balloon::Balloon() : Ball()
{
   setGas(N2O2);
}

Balloon::Balloon(double initialRadius, std::string initialName, Color initialColor,
                 Gas initialGas) : Ball(initialRadius, initialName, initialColor)
{
    setGas(initialGas);
}

void Balloon::setGas(Gas newGas)
{
    theGas = newGas;
}

Gas Balloon::getGas()
{
    return theGas;
}

std::string Balloon::getGasName()
{
    std::string theGasName = "";

    switch(theGas){
    case N2O2: {
        theGasName = "N2O2";
        break;
    }
    case H2: {
        theGasName = "H2";
        break;
    }
    case He: {
        theGasName = "He";
        break;
    }
    case Ne: {
        theGasName = "Ne";
    }
    }
    return theGasName;
}

void Balloon::resetBallon(double newRadius, std::string newName,
                          Color newColor, Gas newGas)
{
    resetBall(newRadius, newName, newColor);
    setGas(newGas);
}

void Balloon::displayStatistics()
{
    Ball::displayStatistics();
    std::cout << "Gas = " << getGasName() << std::endl;
}
