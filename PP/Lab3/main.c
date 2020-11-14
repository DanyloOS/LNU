#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <helper.h>

static const int FUNC_N = 1e6;
static omp_lock_t lock_mltp;

double func(double x)
{
    return (1 - 1 / ((2 * x) * (2 * x)));
}

void ProductionOfSeries_crt(double *x, int doParallel)
{
#pragma omp parallel for if (doParallel)
    for (int i = 1; i < FUNC_N; i += 1)
    {
        double temp = func(i);
#pragma omp critical (MULTIPLICATION)
        {
            *x *= temp;
        } // end critical
    } // end parallel
}

void ProductionOfSeries_atm(double *x, int doParallel)
{
#pragma omp parallel for if (doParallel)
    for (int i = 1; i < FUNC_N; i += 1)
    {
#pragma omp atomic
        *x *= func(i);
    } // end parallel
}

void ProductionOfSeries_lck(double *x)
{
    omp_init_lock(&lock_mltp);
#pragma omp parallel for
    for (int i = 1; i < FUNC_N; i += 1)
    {
        double temp = func(i);
        omp_set_lock(&lock_mltp);
        *x *= temp;
        omp_unset_lock(&lock_mltp);
    } // end parallel for

    omp_destroy_lock(&lock_mltp);
}

inline static void print_result(double Production)
{
    printf("N = 10^%d, Production = %.12f, eps = %.0e\n\n",
           (int)log10(FUNC_N), Production, fabs(Production - 2.0/M_PI));
}

int main()
{
    double Production = 1;

    CLOCK(ProductionOfSeries_atm(&Production, 0));
    print_result(Production);

    Production = 1;
    CLOCK(ProductionOfSeries_atm(&Production, 1));
    print_result(Production);

    Production = 1;
    CLOCK(ProductionOfSeries_crt(&Production, 0));
    print_result(Production);

    Production = 1;
    CLOCK(ProductionOfSeries_crt(&Production, 1));
    print_result(Production);

    Production = 1;
    CLOCK(ProductionOfSeries_lck(&Production));
    print_result(Production);

    return 0;
}
