#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

// Get maximum value from array.
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

int findMax(int* Data, int size)
{
    int max = Data[0];
    for (int i = 0; i < size; i++)
        if (max < Data[i]) max = Data[i];
    return max;
}

// Count sort of arr[].
void countSort(int arr[], int n, int exp)
{
    // Count[i] array will be counting the number of array values having that 'i' digit at their (exp)th place.
    int i, count[10] = {0};
    int *output=new int [n];

    // Count the number of times each digit occurred at (exp)th place in every input.
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Calculating their cumulative count.
    for (i = 1; i < 10; i++)
        count[i] += count[i-1];

    // Inserting values according to the digit '(arr[i] / exp) % 10' fetched into count[(arr[i] / exp) % 10].
    for (i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Assigning the result to the arr pointer of main().
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

// Sort arr[] of size n using Radix Sort.
void RadixSort(int arr[], int n)
{
    int exp, m;
    m = findMax(arr, n);

    for (exp = 1; m/exp > 0; exp *= 10){
        countSort(arr, n, exp);
    }
}

int main()
{
//    srand(time(nullptr));

    int n;

//    cout<<"\nEnter the number of data element to be sorted: ";
//    cin>>n;

//    int* arr = new int [n];
    n = 1000;
    int arr[n];


    InputRandom(arr, n, 0, 1000);
//    for (int i = 0; i < n; i++) {
//        cin >> arr[i];
//    showData(arr, n);
    showData(arr,n);
    cout << "\n\n";
    RadixSort(arr, n);
    showData(arr, n);

    system("pause");
    return 0;
}
