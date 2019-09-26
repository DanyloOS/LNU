#ifndef BALL_H
#define BALL_H

#include "sphere.h"
#include <iostream>

enum Color {RED, GREEN, BLUE, YELLOW, WHITE, BLACK};
class Ball : public Sphere
{
public:
    Ball();
    Ball(double initialRadiuse, std::string initialName, Color initialColor);
    void setName (std::string newName);
    std::string getName();
    void setColor(Color newColor);
    Color getColor();
    std::string getColorName();
    void resetBall(double newRadius, std::string newName, Color newColor);
    void displayStatistics();
private:
    std::string theName;
    Color theColor;
};

#endif // BALL_H
