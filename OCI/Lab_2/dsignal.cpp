#include "dsignal.h"


dSignal::dSignal(std::vector<float> signal): signal(signal) {}

void dSignal::setSignal(std::vector<float> signal)
{
    this->signal = signal;
}

std::vector<float> dSignal::getSignal()
{
    return signal;
}

void dSignal::Scale(float a)
{
    std::vector<float> temp = {};

    for(unsigned long long i = 0; i < signal.size(); i++)
    {
        temp.push_back(signal[i]*a);
    }
    signal = temp;
}

void dSignal::Reverse()
{
    std::vector<float> temp;
    temp.resize(signal.size());
    for (unsigned long long i = 0; i < signal.size(); i++)
    {
        temp[i] = signal[signal.size() - i - 1];
    }
    signal = temp;
}

void dSignal::Time_shift(float N)
{
    float temp = 0;
    if (N > 0) {
        for (unsigned long long i = 0; i < N; i++){
            temp = signal[0];
            for (unsigned long long j = 0; j < signal.size() - 1; j++)
                signal[j] = signal[j + 1];
            signal[signal.size() - 1] = temp;
        }
    } else if (N < 0) {
          temp = signal[signal.size() - 1];
          for (unsigned long long j = signal.size() - 1; j > 1; j++)
              signal[j] = signal[j - 1];
          signal[0] = temp;
    }
}

void dSignal::Expand(unsigned int a)
{
    //x[10] _ a = 2 -> x[5]
    //x[N] : a = x[div
    std::vector<float> temp;

    for (unsigned long long i = 0; i < signal.size(); i += a){
        temp.push_back(signal[i]);
    }
    signal = temp;
}
