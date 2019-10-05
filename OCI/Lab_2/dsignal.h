#ifndef DSIGNAL_H
#define DSIGNAL_H

#include <vector>

class dSignal
{
public:
    dSignal(std::vector<float> signal);
    ~dSignal();

private:
    std::vector<float> signal;

public:
    void setSignal(std::vector<float> signal);
    std::vector<float> getSignal();

    void Scale(float a);
    void Reverse();
    void Time_shift(float N);
    void Expand(unsigned int a);

};

#endif // DSIGNAL_H
