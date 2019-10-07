#include "dsignal.h"


QVector<double> dSignal::Scale(QVector<double> signal, float a)
{
    QVector<double> temp = {};

    for (int i = 0; i < signal.size(); i++)
    {
        temp.push_back(signal[i]*a);
    }
    signal = temp;
    return signal;
}

QVector<double> dSignal::Reverse(QVector<double> signal)
{
    QVector<double> temp;
    temp.resize(signal.size());
    for (int i = 0; i < signal.size(); i++)
    {
        temp[i] = signal[signal.size() - i - 1];
    }
    signal = temp;
    return signal;
}

QVector<double> dSignal::Time_shift(QVector<double> signal, int N)
{
    QVector<double> temp;
    temp = signal;
    if (N > 0)
        for(int i = 0; i < N; i++)
            temp.push_front(0);
    else if (N < 0 )
        for (int i = 0; i > N; i--)
            temp.pop_front();

    return temp;
}

QVector<double> dSignal::Expand(QVector<double> signal, unsigned int a)
{
    QVector<double> temp;

    for (int i = 0; i < signal.size(); i += a){
        temp.push_back(signal[i]);
    }
    signal = temp;
    return signal;
}

QVector<double> dSignal::Addition(QVector<double> signal1, QVector<double> signal2)
{
    QVector<double> result;
    int biggerSize = (signal1.size() > signal2.size()) ? signal1.size() : signal2.size();
    result.resize(biggerSize);
    int index = 0;
    for (index = signal1.size(); index < signal2.size(); index++)
        signal1.push_back(0);
    for (index = signal2.size(); index < signal1.size(); index++)
        signal2.push_back(0);
    for (int i = 0; i < biggerSize; i++)
        result[i] = signal1[i] + signal2[i];
    return result;
}

QVector<double> dSignal::Multiplication(QVector<double> signal1, QVector<double> signal2)
{
    QVector<double> result;
    int biggerSize = (signal1.size() > signal2.size()) ? signal1.size() : signal2.size();
    result.resize(biggerSize);
    int index = 0;
    for (index = signal1.size(); index < signal2.size(); index++)
        signal1.push_back(0);
    for (index = signal2.size(); index < signal1.size(); index++)
        signal2.push_back(0);
    for (int i = 0; i < biggerSize; i++)
        result[i] = signal1[i] * signal2[i];
    return result;
}
QVector<double> dSignal::Conv(QVector<double> signal1, QVector<double> signal2)
{
    QVector<double> F;
    int n = signal2.size() + signal1.size() - 1;
    double* At = new double[n];
    double* Bt = new double[n];

    // Занулюємо масиви
    for (int i = 0; i < n; i ++)
    {
        At[i] = 0;
        Bt[i] = 0;
    }

    // Розставляємо масиви в правильних порядках
    for (int i = 0; i < signal1.size(); i++)
        At[n - (signal1.size() - i)] = signal1[i];
    signal2 = Reverse(signal2);
    for (int i = 0; i < signal2.size(); i++)
        Bt[i] = signal2[i];

    double tempData = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            tempData += At[j]*Bt[j];

        F.push_back(tempData);
        tempData = 0;

        for (int k = 0; k < n - 1; k++)
            At[k] = At[k + 1];
        At[n - i - 1] = 0;
    }

    return F;
}
