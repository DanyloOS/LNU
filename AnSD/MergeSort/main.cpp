#include <iostream>
#include <functional>
#include <memory>

enum type {less, greater};

template <typename T, type e>
void mergeSort(T arr[], int arrsize);

void printArr(int A[], int size);

int main()
{
    int arrsize;

    std::cin >> arrsize;
    std::cout << std::endl;

    int *Data = new int [arrsize];
//    int Data[] = {2, 5, 1, 8, 34};
    for (int i = 0; i < arrsize; i++) {
        Data[i]= rand()%25;
    }
    printArr(Data,  arrsize);

    mergeSort<int, greater> (Data, arrsize);
//    merge(Data, 0, arrsize, arrsize/2);

    std::cout << std::endl;
    printArr(Data,  arrsize);

    //delete [] Data;
    return 0;
}

void printArr(int arr[], int size)
{
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << std::endl;
    }
    std::cout << std::endl;
}

template <typename T, type e>
void mergeSort(T arr[], int arrsize)
{
    std::function<bool(T,T)> predicate;

    switch (e)
    {
    case greater:
        predicate = [] (T x, T y) {
            return x < y ? true:false;
        };
    break;
    case less:
        predicate = [] (T x, T y) {
            return x > y ? true:false;
        };
    break;
    }

    //Algorithm
    if (arrsize > 1) {
        int const left_size = arrsize / 2;
        int const right_size = arrsize - left_size;

        //Передача діапазонів по силці
        mergeSort<T, e> (&arr[0], left_size);
        mergeSort<T, e> (&arr[left_size], right_size);

        /* Індекси:
         * lidx - індекс в лівому масиві
         * ridx - індекс в правому масиві
         * idx  - індекс в тимчасовому масиві*/

        int lidx = 0, ridx = left_size, idx = 0;

        std::unique_ptr<T[]> tmp_arr(new T[arrsize]);

        //Сортування підмасивів
        while (lidx < left_size || ridx < arrsize) {
            //Вибираємо найменший і кладемо його в тимчасовий масив
            if (predicate(arr[lidx], arr[ridx])){
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
                          std::make_move_iterator(&arr[arrsize]),
                          &tmp_arr[idx]);
                break;
            }
            if (ridx == arrsize) {
                std::copy(std::make_move_iterator(&arr[lidx]),
                          std::make_move_iterator(&arr[left_size]),
                          &tmp_arr[idx]);
                break;
            }
        }

        //Копіюємо відсортовану частину в початковий масив
        std::copy(&tmp_arr[0], &tmp_arr[arrsize], arr);
    }

    //Output
    for (int i = 0; i < arrsize; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << std::endl;
}
