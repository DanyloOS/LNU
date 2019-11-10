#ifndef DSIGNAL_H
#define DSIGNAL_H

#include <vector>

class dSignal
{
public:
    dSignal(std::vector<float> signal);

private:
    std::vector<float> signal;

public:
    void setSignal(std::vector<float> signal);
    std::vector<float> getSignal();

    void Scale(float a);
    void Reverse();
    void Time_shift(float N);
    void Expand(unsigned int a);
    //friend std::vector<float> Conv(std::vector<float>& A, std::vector<float>& B, bool hint);
};

#endif // DSIGNAL_H
