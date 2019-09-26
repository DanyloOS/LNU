#include <iostream>
#include <vector>

using namespace std;

template <typename T> vector<T> Conv(vector<T> &A, vector<T> &B);
template <typename T> void Reverse(vector<T> &A);
template <typename T> void Pars(vector<T> &A);

void ShowArr(int* A, int size);
void ShowArr(vector<int> &A);


template <typename T> vector<T> Scaling(vector<T> A, vector<T> B);
template <typename T> vector<T> Revers(vector<T> A, vector<T> B);
template <typename T> vector<int> Time_shift(vector<T> A, vector<T> B);
template <typename T> vector<int> Expansion(vector<T> A, vector<T> B);

int main()
{
    vector<float> A, B = {};
    cout << "A[] = ";
    Pars<float> (A);
    cout << "B[] = ";
    Pars(B);


}

void ShowArr(vector<int> &A)
{
    for(unsigned long long i = 0; i < A.size(); i++){
        cout << i << " " << A[i] << endl;
    }
    cout << endl;
}
void ShowArr(int* A, int size)
{
    for(int i = 0; i < size; i++){
        cout << i << " " << A[i] << endl;
    }
    cout << endl;
}

template <typename T>
void Pars(vector<int> &A)
{
    string arrs;
    getline(cin, arrs);

    int tempI = 0;
    for (unsigned long long i = 0; i < arrs.size(); i++){
        if (arrs[i] != ' ') {
            switch (arrs[i]) {
            case '1': {tempI = tempI * 10 + 1; break;}
            case '2': {tempI = tempI * 10 + 2; break;}
            case '3': {tempI = tempI * 10 + 3; break;}
            case '4': {tempI = tempI * 10 + 4; break;}
            case '5': {tempI = tempI * 10 + 5; break;}
            case '6': {tempI = tempI * 10 + 6; break;}
            case '7': {tempI = tempI * 10 + 7; break;}
            case '8': {tempI = tempI * 10 + 8; break;}
            case '9': {tempI = tempI * 10 + 9; break;}
            case '0': {tempI = tempI * 10 + 0; break;}
            }
        } else {
            A.push_back(tempI);
            tempI = 0;
        }
    }
    A.push_back(tempI);
}

template <typename T>
void Reverse(vector<int> &A)
{
    vector<int> tempA;
    tempA.resize(A.size());
    for (unsigned long long i = 0; i < A.size(); i++)
    {
        tempA[i] = A[A.size() - i - 1];
    }
    A = tempA;
}

template <typename T>
vector<T> Conv(vector<T>& A, vector<T>& B)
{
    vector<int> F;
    unsigned long long n = B.size() + A.size() - 1;
    int* At = new int[n];
    int* Bt = new int[n];

    // Занулюємо масиви
    for (unsigned long long i = 0; i < n; i ++)
    {
        At[i] = 0;
        Bt[i] = 0;
    }

    // Розставляємо масиви в правильних порядках
    for (unsigned long long i = 0; i < A.size(); i++)
        At[n - (A.size() - i)] = A[i];
    Reverse(B);
    for (unsigned long long i = 0; i < B.size(); i++)
        Bt[i] = B[i];

    int tempData = 0;
    for (unsigned long long i = 0; i < n; i++) {
        for (unsigned long long j = 0; j < n; j++)
            tempData += At[j]*Bt[j];

        F.push_back(tempData);
        tempData = 0;

        for (unsigned long long k = 0; k < n - 1; k++)
            At[k] = At[k + 1];
        At[n - i - 1] = 0;
    }

    return F;
}

vector<float> Scaling(vector<float> A, float a)
{

}

vector<int> Revers(vector<int> A, vector<int> B)
{

}

vector<int> Time_shift(vector<int> A, vector<int> B)
{

}

vector<int> Expansion(vector<int> A, vector<int> B)
{

}
