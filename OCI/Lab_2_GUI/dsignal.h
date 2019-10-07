#ifndef DSIGNAL_H
#define DSIGNAL_H

#include <QVector>

class dSignal
{
public:
    dSignal();

    static QVector<double> Scale(QVector<double> signal, float a);
    static QVector<double> Reverse(QVector<double> signal);
    static QVector<double> Time_shift(QVector<double> signal, int N);
    static QVector<double> Expand(QVector<double> signal, unsigned int a);
    static QVector<double> Addition(QVector<double> signal1, QVector<double> signal2);
    static QVector<double> Multiplication(QVector<double> signal1, QVector<double> signal2);
    static QVector<double> Conv(QVector<double> signal1, QVector<double> signal2);
};

#endif // DSIGNAL_H
