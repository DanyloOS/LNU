#include <stdio.h>
#include <Windows.h>
#include <omp.h>

int main()
{
    SetConsoleOutputCP(65001);

    ///////////// 1 /////////////
#pragma omp parallel
    {
        printf("I am %d thread from %d threads!\n",
               omp_get_thread_num(), omp_get_num_threads());
    }

    ///////////// 2 /////////////
    int a = 2, b = 2;
    printf("\nПослідовна область: a = %d, b = %d\n", a, b);
#pragma omp parallel shared(a), private(b)
    {
        a = 3;
        b = 3;
#pragma omp master
        {
            printf("Паралельна область: a(shared) = %d, b(private) = %d\n", a, b);
        }
    }
    printf("Послідовна область: a = %d, b = %d\n", a, b);

    ///////////// 3 /////////////
    int n;
    printf("\nВведіть кількість потоків: ");
    scanf("%d", &n);
    omp_set_num_threads(n);
    printf("\n");


    ///////////// 4 /////////////

#pragma omp parallel
    {
#pragma omp sections
        {
#pragma omp section
            {
                printf("Перша секція, потік №%d\n", omp_get_thread_num());
            }
#pragma omp section
            {
                printf("Друга секція, потік №%d\n", omp_get_thread_num());
            }
#pragma omp section
            {
                printf("Третя секція, потік №%d\n", omp_get_thread_num());
            }
#pragma omp section
            {
                printf("Четверта секція, потік №%d\n", omp_get_thread_num());
            }
        }
    }

    return 0;
}
