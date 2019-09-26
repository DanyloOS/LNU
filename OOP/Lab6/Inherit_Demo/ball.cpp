#include "ball.h"

Ball::Ball() : Sphere()
{
    setName("");
    setColor(BLACK);
}

Ball::Ball(double initialRadiuse, std::string initialName, Color initialColor) : Sphere(initialRadiuse)
{
    setName(initialName);
    setColor(initialColor);
}

void Ball::setName(std::string newName)
{
    theName = newName;
}

std::string Ball::getName()
{
    return theName;
}

void Ball::setColor(Color newColor)
{
    theColor = newColor;
}

Color Ball::getColor()
{
    return theColor;
}

std::string Ball::getColorName()
{
    std::string clrName = "";

    switch (theColor){
    case RED :{
        clrName = "RED";
        break;
    }
    case GREEN :{
        clrName = "GREEN";
        break;
    }
    case BLUE :{
        clrName = "BLUE";
        break;
    }
    case YELLOW :{
        clrName = "YELLOW";
        break;
    }
    case WHITE :{
        clrName = "WHITE";
        break;
    }
    case BLACK :{
        clrName = "BLACK";
        break;
    }
    }

    return clrName;
}

void Ball::resetBall(double newRadius, std::string newName, Color newColor)
{
    setRadius(newRadius);
    setName(newName);
    setColor(newColor);
}

void Ball::displayStatistics()
{
    std::cout << "\nName = " << getName()
              << "\nRadius = " << getRadius()
              << "\nDiameter = " << getDiameter()
              << "\nCircumference = " << getCircumference()
              << "\nArea = " << getArea()
              << "\nVolume = " << getVolume() << std::endl;
}
