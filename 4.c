#include <stdio.h>
#include <omp.h>

int x = 10;

#pragma omp threadprivate(x)

int main()
{
    omp_set_num_threads(4);

    #pragma omp parallel copyin(x)
    {
        printf("Thread %d: x = %d\n", omp_get_thread_num(), x);

        x += omp_get_thread_num();

        printf("Thread %d: Updated x = %d\n",
               omp_get_thread_num(), x);
    }

    return 0;
}
