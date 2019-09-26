#include <iostream>
#include <vector>

using namespace std;

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

vector<int> Conv(vector<int>& A, vector<int>& B, bool hint = 0)
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

    if (hint) {
            cout << endl;
            ShowArr(A);
            ShowArr(At, static_cast<int>(n));
            ShowArr(B);
            ShowArr(Bt, static_cast<int>(n));
        }

    int tempData = 0;
    for (unsigned long long i = 0; i < n; i++) {
        for (unsigned long long j = 0; j < n; j++)
            tempData += At[j]*Bt[j];

        F.push_back(tempData);
        if (hint) {
                    cout << "\n___\n";
                    ShowArr(At, static_cast<int>(n));
                    ShowArr(Bt, static_cast<int>(n));
                    cout << "  *= " << tempData << endl;
                }
        tempData = 0;

        for (unsigned long long k = 0; k < n - 1; k++)
            At[k] = At[k + 1];
        At[n - i - 1] = 0;
    }

    return F;
}


int main()
{
    vector<int> A, B = {};
    cout << "A[] = ";
    Pars(A);
    cout << "B[] = ";
    Pars(B);

    bool hint = 0;
    cout << "Do you want to see the process? 1/0\n";
    cin >> hint;
    vector<int> F = Conv(A, B, hint);

    cout << "{Fm} = (";
    for (unsigned long long i = 0; i < F.size(); i++) {
        if (i + 1 == F.size()){
            cout << F[i];
        } else {
        cout << F[i] << ", ";
        }
    }
    cout << ")\n";

    system("pause");
    return 0;
}
