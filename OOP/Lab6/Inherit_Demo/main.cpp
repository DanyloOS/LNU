#include <iostream>
#include "weightball.h"
#include "weightballoon.h"

using namespace std;

int main()
{
    Ball newBall;
    newBall.resetBall(2.3,"Ball",GREEN);
    newBall.displayStatistics();

    Balloon newBalloon(4, "Sharik", BLUE, He);
    newBalloon.displayStatistics();

    WeightBall newWeightBall(1, "wagaSharika", BLACK, 1000);
    newWeightBall.displayStatistics();

    WeightBalloon newWeightBallon;
    newWeightBallon.displayStatistics();

    return 0;
}
