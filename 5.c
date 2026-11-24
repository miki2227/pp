#include <stdio.h>
#include <omp.h>

#define N 1000

int main()
{
    omp_set_num_threads(4);

    omp_sched_t types[] = {
        omp_sched_static,
        omp_sched_dynamic,
        omp_sched_guided
    };

    char *names[] = {"Static", "Dynamic", "Guided"};

    for(int k = 0; k < 3; k++)
    {
        omp_set_schedule(types[k], 10);

        double start = omp_get_wtime();

        #pragma omp parallel for schedule(runtime)
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < i * 100; j++);
        }

        printf("%s time = %f\n", names[k],
               omp_get_wtime() - start);
    }

    return 0;
}
