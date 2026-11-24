#include <stdio.h>
#include <omp.h>

int isPrime(int n)
{
    if(n < 2)
        return 0;

    for(int i=2; i*i<=n; i++)
        if(n%i == 0)
            return 0;

    return 1;
}

int main()
{
    int n, count=0;
    double start, end, seq, par;

    printf("Enter limit: ");
    scanf("%d",&n);

    start = omp_get_wtime();

    for(int i=2; i<=n; i++)
        if(isPrime(i))
            count++;

    end = omp_get_wtime();
    seq = end-start;

    printf("\nSequential Time: %f",seq);
    printf("\nNumber of primes: %d",count);

    for(int t=2; t<=8; t*=2)
    {
        count=0;
        omp_set_num_threads(t);

        start = omp_get_wtime();

        #pragma omp parallel for reduction(+:count)
        for(int i=2; i<=n; i++)
            if(isPrime(i))
                count++;

        end = omp_get_wtime();
        par = end-start;

        printf("\n\nThreads: %d",t);
        printf("\nParallel Time: %f",par);
        printf("\nSpeedup: %f",seq/par);
        printf("\nEfficiency: %f %%",(seq/par)/t*100);
    }

    return 0;
}
