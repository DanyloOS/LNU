#pragma once

#include <windows.h>
#include <omp.h>

#define UNIQ_VAR_IMPL_2(lineone, prefix) _uniq_var_##lineone##prefix
#define UNIQ_VAR_IMPL(lineone, prefix) UNIQ_VAR_IMPL_2(lineone, prefix)
#define UNIQ_VAR(prefix) UNIQ_VAR_IMPL(__LINE__, prefix)

#define CLOCK(func)                                                                 \
{                                                                                   \
    double UNIQ_VAR(_start) = omp_get_wtime();                                      \
    func;                                                                           \
    double UNIQ_VAR(_end) = omp_get_wtime();                                        \
    printf("Elapsed time for %s: %f\n", #func, UNIQ_VAR(_end) - UNIQ_VAR(_start));  \
}

#define CLOCK_MSG(func, msg)                                                               \
{                                                                                          \
    double UNIQ_VAR(_start) = omp_get_wtime();                                             \
    func;                                                                                  \
    double UNIQ_VAR(_end) = omp_get_wtime();                                               \
    printf("Час виконання %s %s: %f с\n", #func, msg, UNIQ_VAR(_end) - UNIQ_VAR(_start));  \
}
