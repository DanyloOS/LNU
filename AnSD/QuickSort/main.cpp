#include <iostream>
using namespace std;
static int counter = 0;
static int counter1 = 0;
void showData(int*, int);
void showData(int*, int, int);

int Partition(int *arr, int left, int right)
{
    int pivot = arr[right];
    int i = left - 1;
    for (int  j = left; j <= right - 1; j++) {
        counter1 ++;
        if (arr[j] <= pivot){
            counter++;
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[right]);
    counter++;
    return i + 1;
}

void QuickSort(int *arr, int p, int r)
{
    int q;

    if (p < r) {
        q = Partition(arr, p, r);
        QuickSort(arr, p, q - 1);
        QuickSort(arr, q + 1, r);
    }
}

void InputRandom(int* Data, int size, int a, int b)
{
    for (int i = 0; i < size; i++)
        Data[i] = rand()%(b - a) + a;
}

void showData(int* Data, int size)
{
    for (int i = 0; i < size; i++)
        cout << Data[i] << "\t";
    cout << endl;
}

int main()
{
    int n = 1000;
    int arr[n];
//    for(int k = 0 ; k < 6 ; k++ )cin>>a[k];
    InputRandom(arr, n, 0, 1000);
    showData(arr, n);
    QuickSort(arr, 0, n - 1);
    showData(arr, n);

    cout << "\n\nCounter = " << counter << endl << "counter2 = " << counter1 << endl;


    return 0;
}

void showData(int* Data, int f, int l)
{
    for (int i = f; i <= l; i++)
        cout << Data[i] << endl;
    cout << endl;
}
