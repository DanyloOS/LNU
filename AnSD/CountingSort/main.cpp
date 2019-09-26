#include <iostream>

using namespace std;
int k = 0;
int k0 = 0;

void InputRandom(int* Data, int size, int a, int b)
{
    for (int i = 0; i < size; i++) {
        Data[i] = rand()%(b - a) + a;
    }
}

void showData(int* Data, int size)
{
    for (int i = 0; i < size; i++) {
        cout << Data[i] << "\t";
    }
    cout << endl;
}

void findMinNMax(int* Data, int size, int &min, int &max)
{
    min = max = Data[0];
    for (int i = 0; i < size; i++) {
        if (min > Data[i]) min = Data[i];
        if (max < Data[i]) max = Data[i];
    }
}

void CountingSort(int* A, int n)
{
//    int* C = new int [k];
    int C[++k];
//    int* B = new int [n];
    int B[n];

    for (int i = 0; i <= k - 1; i++)
        C[i] = 0;
    for (int i = 0; i <= n - 1; i++)
        C[A[i]]++;
    for (int j = 1; j <= k - 1; j++)
        C[j] =  C[j] + C[j - 1];
    for (int i = n - 1; i >= 0; i--) {
        C[A[i]] = C[A[i]] - 1;
        B[C[A[i]]] = A[i];
    }

//    int *C = new int [k];
//    for(int i = 0; i <= k; i++)
//        C[i] = 0;
//    for(int j = 1; j < n; j++)
//        C[A[j]]++;//2
//    for(int i=1;i<=k;i++)
//        C[i]+=C[i-1];//3
//    for(int j=n;j>=1;j--){
//        B[C[A[j]]]=A[j];//4
//        C[A[j]]=C[A[j]]-1;//5
//    }
    showData(B, n);
}


int main()
{
    int arrSize = 1000;
    int *Data = new int[arrSize];
    InputRandom(Data, arrSize, 0, 1000);
    showData(Data, arrSize);

    cout << "\n\n";
    findMinNMax(Data, arrSize, k0, k);

    CountingSort(Data, arrSize);
    //showData(Data, arrSize);

    return 0;
}
