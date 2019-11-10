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

/*//vector<float> Conv(vector<float>& A, vector<float>& B, bool hint)
//{
//    vector<float> F;
//    unsigned long long n = B.size() + A.size() - 1;
//    float* At = new float[n];
//    float* Bt = new float[n];

//    // Занулюємо масиви
//    for (unsigned long long i = 0; i < n; i ++)
//    {
//        At[i] = 0;
//        Bt[i] = 0;
//    }

//    // Розставляємо масиви в правильних порядках
//    for (unsigned long long i = 0; i < A.size(); i++)
//        At[n - (A.size() - i)] = A[i];
//    B = Reverse(B);
//    for (unsigned long long i = 0; i < B.size(); i++)
//        Bt[i] = B[i];

//    float tempData = 0;
//    for (unsigned long long i = 0; i < n; i++) {
//        for (unsigned long long j = 0; j < n; j++)
//            tempData += At[j]*Bt[j];

//        F.push_back(tempData);
//        if (hint) {
//            cout << "\n___\n";
//            ShowArr(At, n);
//            ShowArr(Bt, n);
//            cout << "  *= " << tempData << endl;
//        }
//        tempData = 0;

//        for (unsigned long long k = 0; k < n - 1; k++)
//            At[k] = At[k + 1];
//        At[n - i - 1] = 0;
//    }

//    return F;
//}*/
