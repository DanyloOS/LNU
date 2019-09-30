#include <iostream>
#include <vector>

using namespace std;

vector<float> Conv(vector<float> &A, vector<float> &B, bool hint = 0);
void Reverse(vector<float> &A);
void Pars(vector<float> &A);

template <typename T>
void ShowArr(T* A, int size);
template <typename T>
void ShowArr(vector<T> &A);

vector<float> Scaling(vector<float> A, vector<float> B);
vector<float> Revers(vector<float> A, vector<float> B);
vector<float> Time_shift(vector<float> A, vector<float> B);
vector<float> Expansion(vector<float> A, vector<float> B);

int main()
{
    vector<float> A, B = {};
    cout << "A[] = ";
    Pars(A);
    cout << "B[] = ";
    Pars(B);

    vector<float> C = Conv(A, B, 1);
    ShowArr(A);
    ShowArr(B);
    ShowArr(C);
}

template <typename T>
void ShowArr(vector<T> &A)
{
    for(unsigned long long i = 0; i < A.size(); i++){
        cout << i << " " << A[i] << endl;
    }
    cout << endl;
}
template <typename T>
void ShowArr(T* A, int size)
{
    for(int i = 0; i < size; i++){
        cout << i << " " << A[i] << endl;
    }
    cout << endl;
}

void Pars(vector<float> &A)
{
    string arrs;
    getline(cin, arrs);

    int tempI = 0;
    float tempD = 0, tempRoz = 1;
    bool flag1 = 0;
    for (unsigned long long i = 0; i < arrs.size(); i++){
        if (arrs[i] != ' ' && arrs[i] != '.' && !flag1) {
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
        } else if (arrs[i] == '.'){
            flag1 = 1;
        } else if (flag1 && (arrs[i] >= '0' && arrs[i] <= '9')) {
            tempRoz *= 0.1;
            switch (arrs[i]) {
            case '1': {tempD += 1*tempRoz; break;}
            case '2': {tempD += 2*tempRoz; break;}
            case '3': {tempD += 3*tempRoz; break;}
            case '4': {tempD += 4*tempRoz; break;}
            case '5': {tempD += 5*tempRoz; break;}
            case '6': {tempD += 6*tempRoz; break;}
            case '7': {tempD += 7*tempRoz; break;}
            case '8': {tempD += 8*tempRoz; break;}
            case '9': {tempD += 9*tempRoz; break;}
            case '0': {tempD += 0*tempRoz; break;}
            }
        } else {
            A.push_back((float)(tempI) + tempD);
            tempI = 0;
            tempD = 0;
            tempRoz = 1;
            flag1 = 0;
        }
    }
    A.push_back((float)(tempI) + tempD);
}


void Reverse(vector<float> &A)
{
    vector<float> tempA;
    tempA.resize(A.size());
    for (unsigned long long i = 0; i < A.size(); i++)
    {
        tempA[i] = A[A.size() - i - 1];
    }
    A = tempA;
}

vector<float> Conv(vector<float>& A, vector<float>& B, bool hint)
{
    vector<float> F;
    unsigned long long n = B.size() + A.size() - 1;
    float* At = new float[n];
    float* Bt = new float[n];

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

    float tempData = 0;
    for (unsigned long long i = 0; i < n; i++) {
        for (unsigned long long j = 0; j < n; j++)
            tempData += At[j]*Bt[j];

        F.push_back(tempData);
        if (hint) {
            cout << "\n___\n";
            ShowArr(At, n);
            ShowArr(Bt, n);
            cout << "  *= " << tempData << endl;
        }
        tempData = 0;

        for (unsigned long long k = 0; k < n - 1; k++)
            At[k] = At[k + 1];
        At[n - i - 1] = 0;
    }

    return F;
}

vector<float> Scaling(vector<float> A, float a)
{
    return A;
}

vector<int> Revers(vector<int> A, vector<int> B)
{
    return A;
}

vector<int> Time_shift(vector<int> A, vector<int> B)
{
    return A;
}

vector<int> Expansion(vector<int> A, vector<int> B)
{
    return A;
}
