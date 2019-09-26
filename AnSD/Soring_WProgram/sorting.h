#ifndef SORTING_H
#define SORTING_H

#include <iostream>
#include <functional>
#include <memory>
#include <ctime>

enum SortingMethod {BubbleSort, BubbleSort_m, SelectionSort, InsertionSort, ShelleSort_m, MergeSort};

template <typename T> void swap_(T &arg1, T &arg2)
{
    T temp = arg1;
    arg1 = arg2;
    arg2 = temp;
}

template <typename T>
class Sorting
{
public:
    Sorting(T Data[], unsigned int N, SortingMethod srtMthd, double *srtTime = nullptr )//: srtMethod(srtMthd)
    {
        long timeStart;
        if (srtTime != nullptr)
            timeStart = clock();
        switch (srtMthd) {
        case BubbleSort: bubbleSort(Data, N); break;
        case BubbleSort_m: bubbleSort_m(Data, N); break;
        case SelectionSort: selectionSort(Data, N); break;
        case InsertionSort: insertionSort(Data, N); break;
        case ShelleSort_m: shelleSort_m(Data, N); break;
        case MergeSort: mergeSort(Data, N);
        }
        if (srtTime != nullptr)
            *srtTime = static_cast<double>((clock() - timeStart))/CLOCKS_PER_SEC;
    }

    void bubbleSort(T Data[], unsigned N);
    void bubbleSort_m(T Data[], unsigned N);
    void selectionSort(T Data[], unsigned N);
    void insertionSort(T Data[], unsigned N);
    void shelleSort_m(T Data[], unsigned N);
    void mergeSort(T Data[], unsigned N);

};

template<typename T> void Sorting<T>::bubbleSort(T arr[], unsigned N)
{
//    long timeStart = clock();
    for (unsigned int i = 0; i < N - 1; i++)
        for (unsigned int j = 0; j < N - i - 1; j++)
             if (arr[j] > arr[j + 1])
             {
                 swap_(arr[j],arr[j + 1]);
                 //showData(Data, N);
             }
//    cout << "bubbleSort() ended in: " << (clock() - timeStart) / (double) CLOCKS_PER_SEC << " seconds\n";
//    sortingTimeTxt << "bubbleSort() ended in: " << (clock() - timeStart) / (double) CLOCKS_PER_SEC << " seconds\n";
}
template<typename T> void Sorting<T>::bubbleSort_m(T arr[], unsigned N)
{
//    long timeStart = clock();
    bool swap_ped;
    for (unsigned int i = 0; i < N - 1; i++)
    {
        swap_ped = false;
        for (unsigned int j = 0; j < N - i - 1; j++)
             if (arr[j] > arr[j + 1])
             {
                 swap_(arr[j],arr[j + 1]);
                 swap_ped = true;
                 //showData(Data, N);
             }
        if (swap_ped == false) break;
    }
    //    sortingTimeTxt << "bubbleSort_m() ended in: " << (clock() - timeStart) / (double) CLOCKS_PER_SEC << " seconds\n";
}
template<typename T> void Sorting<T>::selectionSort(T arr[], unsigned N)
{
    unsigned min;
//    long timeStart = clock();
    for (unsigned int i = 0; i < N - 1; ++i) {
        unsigned int min = i;
        for (unsigned int j = i + 1; j < N; ++j)
            if (arr[j] < arr[min])
                min = j;

    swap_(arr[i], arr[min]);
    //showData(Data, N);
    }
//    sortingTimeTxt << "selectionSort() ended in: " << (clock() - timeStart) / (double) CLOCKS_PER_SEC << " seconds\n";
    //
}
template<typename T> void Sorting<T>::insertionSort(T arr[], unsigned N)
{
//    long timeStart = clock();
    unsigned int i, j;
    for (i = 1; i < N; ++i) {
        T tmp = arr[i];
        for (j = i - 1; j >= 0 && tmp < arr[j]; --j)
            arr[j+1] = arr[j];
        arr[j+1] = tmp;
        //showData(Data, N);
    }
    //    sortingTimeTxt << "insertionSort() ended in: " << (clock() - timeStart) / (double) CLOCKS_PER_SEC << " seconds\n";
}
template<typename T> void Sorting<T>::shelleSort_m(T arr[], unsigned N)
{
//    long timeStart = clock();
    for (int i = N/2; i > 0; i /= 2)
        for (int j = i; j < static_cast<int>(N); j++)
            for (int k = j - i; k >= 0; k -= i) {
                if (arr[k + i] >= arr [k]) break;
                swap_(arr[k], arr[k + i]);
            }
//            end:
//            continue;
//    sortingTimeTxt << "shelleSort_m() ended in: " << (clock() - timeStart) / (double) CLOCKS_PER_SEC << " seconds\n";
    //    cout << "shelleSort_m() ended in: " << (clock() - timeStart) / (double) CLOCKS_PER_SEC << " seconds\n";
}
template<typename T> void Sorting<T>::mergeSort(T arr[], unsigned N)
{
    //Algorithm
    if (N > 1) {
        unsigned int const left_size = N / 2;
        unsigned int const right_size = N - left_size;

        //Передача діапазонів по силці
        Sorting<T>::mergeSort (&arr[0], left_size);
        Sorting<T>::mergeSort (&arr[left_size], right_size);

        /* Індекси:
         * lidx - індекс в лівому масиві
         * ridx - індекс в правому масиві
         * idx  - індекс в тимчасовому масиві*/

        unsigned int lidx = 0, ridx = left_size, idx = 0;

        std::unique_ptr<T[]> tmp_arr(new T[N]);

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




#endif // SORTING_H
