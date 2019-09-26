#include <iostream>
#include <ctime>
#include <cmath>
#include <fstream>
#include <functional>
#include <memory>


using namespace std;
static ofstream sortingTimeTxt("sortingTime.txt", ios_base::app);

void bubbleSort(int Data[], int N);
void bubbleSort_m(int Data[], int N);
void selectionSort(int Data[], int N);
void insertionSort(int Data[], int N);
void shelleSort_m(int Data[], int N);
void mergeSort(int Data[], int N);
void QuickSort(int Data[], int N, int L, int R);
void CountingSort(int Data[], int N);
void RadixSort(int Data[], int N);
void inputData(int Data[], int N);
void copyDataForSorting(int Data[], int cData[], int N);
void makeRandomTxt(ofstream &randomTxt, int Data[], int N);
void makeSortedTxt(ofstream &sortedTxt, int Data[], int N, string filename);
void showData(int Data[], int N);

int main()
{
    srand(time(nullptr));
    ofstream randomTxt;
    ofstream sortedTxt;
    int N;
    long timeStart = clock();

    for (int i = 1; i <= 25; i++) {
        N = pow(2, i);
        int *Data = new int[N];
        int *cData = new int[N];
        makeRandomTxt(randomTxt, Data, N);
        cout << "starting sorting " << N << " elements\n\n";

        for (int j = 0; j < 3; j++) {
            inputData(Data, N);
            copyDataForSorting(Data, cData, N);

//            bubbleSort(cData, N);
//            makeSortedTxt(sortedTxt, cData, N,"bubbleSort.txt");
//            copyDataForSorting(Data, cData, N);

//            bubbleSort_m(cData, N);
//            makeSortedTxt(sortedTxt, cData, N,"bubbleSort_m.txt");
//            copyDataForSorting(Data, cData, N);

//            selectionSort(cData, N);
//            makeSortedTxt(sortedTxt, cData, N,"selectionSort.txt");
//            copyDataForSorting(Data, cData, N);

//            insertionSort(cData, N);
//            makeSortedTxt(sortedTxt, cData, N,"insertionSort.txt");
//            copyDataForSorting(Data, cData, N);

            shelleSort_m(cData, N);
            makeSortedTxt(sortedTxt, cData, N,"shelleSort_m.txt");
            copyDataForSorting(Data, cData, N);

            long timeStartMS = clock();
            mergeSort(cData, N);
            makeSortedTxt(sortedTxt, cData, N, "mergeSort.txt");
            sortingTimeTxt << "mergeSort() ended in: " << (clock() - timeStartMS) / (double) CLOCKS_PER_SEC << " seconds\n";
            cout << "mergeSort() ended in: " << (clock() - timeStartMS) / (double) CLOCKS_PER_SEC << " seconds\n";

            long timeStartQS = clock();
            QuickSort(cData, N, 0, N - 1);
            makeSortedTxt(sortedTxt, cData, N, "QuickSort.txt");
            sortingTimeTxt << "QuickSort() ended in: " << (clock() - timeStartQS) / (double) CLOCKS_PER_SEC << " seconds\n";
            cout << "QuickSort() ended in: " << (clock() - timeStartQS) / (double) CLOCKS_PER_SEC << " seconds\n";

            long timeStartCS = clock();
            CountingSort(cData, N);
            makeSortedTxt(sortedTxt, cData, N, "CountingSort.txt");
            sortingTimeTxt << "CountingSort() ended in: " << (clock() - timeStartCS) / (double) CLOCKS_PER_SEC << " seconds\n";
            cout << "CountingSort() ended in: " << (clock() - timeStartCS) / (double) CLOCKS_PER_SEC << " seconds\n";

            long timeStartRS = clock();
            RadixSort(cData, N);
            makeSortedTxt(sortedTxt, cData, N, "RadixSort.txt");
            sortingTimeTxt << "RadixSort() ended in: " << (clock() - timeStartRS) / (double) CLOCKS_PER_SEC << " seconds\n";
            cout << "RadixSort() ended in: " << (clock() - timeStartRS) / (double) CLOCKS_PER_SEC << " seconds\n";




            sortingTimeTxt << "\n_______________________________________________\n\n";
            cout << "\n______________________________________\n\n";
        }
    }
    cout << "sorting ended in: " << (clock() - timeStart) / (double) CLOCKS_PER_SEC << " seconds\n\n";
    return 0;
}
void inputData(int Data[], int N)
{
    for (int i = 0; i < N; i++)
        Data[i] = rand()%10000;
}
void copyDataForSorting(int Data[], int cData[], int N)
{
    for (int i = 0; i < N; i++)
        cData[i] = Data[i];
}

void bubbleSort(int Data[], int N)
{
    long timeStart = clock();
    for(int i = 0; i < N - 1; i++)
        for(int j = 0; j < N - i - 1; j++)
             if(Data[j] > Data[j + 1])
                 swap(Data[j],Data[j + 1]);
    cout << "bubbleSort() ended in: " << (clock() - timeStart) / (double) CLOCKS_PER_SEC << " seconds\n";
    sortingTimeTxt << "bubbleSort() ended in: " << (clock() - timeStart) / (double) CLOCKS_PER_SEC << " seconds\n";

}
void bubbleSort_m(int Data[], int N)
{
    long timeStart = clock();
    bool swapped;
    for(int i = 0; i < N - 1; i++)
    {
        swapped = false;
        for(int j = 0; j < N - i - 1; j++)
             if(Data[j] > Data[j + 1]) {
                 swap(Data[j],Data[j + 1]);
                 swapped = true;
                 //showData(Data, N);
             }
        if(swapped == false) break;
    }
    sortingTimeTxt << "bubbleSort_m() ended in: " << (clock() - timeStart) / (double) CLOCKS_PER_SEC << " seconds\n";
    cout << "bubbleSort_m() ended in: " << (clock() - timeStart) / (double) CLOCKS_PER_SEC << " seconds\n";
}
void selectionSort(int Data[], int N) {
    long timeStart = clock();
    for (int i = 0; i < N - 1; ++i) {
        int min = i;
        for (int j = i + 1; j < N; ++j){
            if( Data[j] < Data[min] )
                min = j;
        }
    swap(Data[i], Data[min]);
    }
    sortingTimeTxt << "selectionSort() ended in: " << (clock() - timeStart) / (double) CLOCKS_PER_SEC << " seconds\n";
    cout << "selectionSort() ended in: " << (clock() - timeStart) / (double) CLOCKS_PER_SEC << " seconds\n";
}
void insertionSort(int Data[], int N ) {
    long timeStart = clock();
    int i, j;
    for (i = 1; i < N; ++i) {
        double tmp = Data[i];
        for (j = i - 1; j >= 0 && tmp < Data[j]; --j)
            Data[j+1] = Data[j];
        Data[j+1] = tmp;
    }
    sortingTimeTxt << "insertionSort() ended in: " << (clock() - timeStart) / (double) CLOCKS_PER_SEC << " seconds\n";
    cout << "insertionSort() ended in: " << (clock() - timeStart) / (double) CLOCKS_PER_SEC << " seconds\n";
}
void shelleSort_m(int Data[], int N)
{
    long timeStart = clock();
    for (int i = N/2; i > 0; i /= 2)
        for (int j = i; j < N; j++)
            for (int k = j - i; k >= 0; k -= i) {
                if (Data[k + i] >= Data [k]) break;
                swap(Data[k], Data[k + i]);
            }
    sortingTimeTxt << "shelleSort_m() ended in: " << (clock() - timeStart) / (double) CLOCKS_PER_SEC << " seconds\n";
    cout << "shelleSort_m() ended in: " << (clock() - timeStart) / (double) CLOCKS_PER_SEC << " seconds\n";
}

void mergeSort(int arr[], int N)
{
    //Algorithm
    if (N > 1) {
        unsigned int const left_size = N / 2;
        unsigned int const right_size = N - left_size;

        //Передача діапазонів по силці
        mergeSort (&arr[0], left_size);
        mergeSort (&arr[left_size], right_size);

        /* Індекси:
         * lidx - індекс в лівому масиві
         * ridx - індекс в правому масиві
         * idx  - індекс в тимчасовому масиві*/

        unsigned int lidx = 0, ridx = left_size, idx = 0;

        std::unique_ptr<int[]> tmp_arr(new int[N]);

        //Сортування підмасивів
        while (lidx < left_size || ridx < N) {
            //Вибираємо найменший і кладемо його в тимчасовий масив
            if (arr[lidx] < arr[ridx]){
                tmp_arr[idx++] = std::move(arr[lidx]);
                lidx++;
            } else {
                tmp_arr[idx++] = std::move(arr[ridx]);
                ridx++;
            }

            //Якщо підмасив пройдений - з'єднюємо з сусіднім підмасивом
            //Після цього виходим і заново сортуємо отриманий масив
            if (lidx == left_size){
                std::copy(std::make_move_iterator(&arr[ridx]),
                          std::make_move_iterator(&arr[N]),
                          &tmp_arr[idx]);
                break;
            }
            if (ridx == N) {
                std::copy(std::make_move_iterator(&arr[lidx]),
                          std::make_move_iterator(&arr[left_size]),
                          &tmp_arr[idx]);
                break;
            }
        }

        //Копіюємо відсортовану частину в початковий масив
        std::copy(&tmp_arr[0], &tmp_arr[N], arr);
    }
}


void QuickSort(int *Array, int N, int L, int R)
{
    int Left = L,Right = R;
    int middle = (R+L)/2 ;
    int x = Array [middle];

    do
    {
        while (Array[Left]<x)
            Left ++ ;

        while (x<Array[Right])
            Right -- ;


        if (Left<=Right)
        {
            swap(Array[Left],Array[Right]);
            Left ++ ;
            Right -- ;
        }
    }
    while (Left<Right);

    if (L<Right)
        QuickSort (Array, N, L, Right);

    if (Left<R)
        QuickSort (Array, N, Left, R);
}

void CountingSort(int* A, int n)
{
    int k = A[0];
    for (int i = 0; i < n; i++)
        if (k < A[i]) k = A[i];
    int *C = new int [++k];
    int *B = new int [n];

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

    for (int i = 0; i < n; i++) {
        A[i] = B[i];
    }
    delete [] B;
    delete [] C;
}

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
    m = arr[0];
    for (int i = 0; i < n; i++)
        if (m < arr[i]) m = arr[i];

    for (exp = 1; m/exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

void makeRandomTxt(ofstream &randomTxt, int Data[], int N)
{
    long timeStart = clock();
    randomTxt.open("randomTxt.txt");
    for (int i = 0; i < N; i++)
        randomTxt << Data[i] << ' ';
    randomTxt.close();
    cout << "makeRandomTxt() ended in: " << (clock() - timeStart) / (double) CLOCKS_PER_SEC << " seconds\n\n";
}
void makeSortedTxt(ofstream &sortedTxt, int Data[], int N, string filename)
{
    sortedTxt.open(filename);
    for (int i = 0; i < N; i++)
        sortedTxt << Data[i] << '\n';
    sortedTxt.close();
}
