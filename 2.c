#include <stdio.h>
#include <omp.h>

int main()
{
    int a[10][10], b[10][10], c[10][10];
    int n;

    printf("Enter size: ");
    scanf("%d", &n);

    printf("Enter matrix A:\n");
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            scanf("%d", &a[i][j]);

    printf("Enter matrix B:\n");
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            scanf("%d", &b[i][j]);

    double start = omp_get_wtime();

    #pragma omp parallel for
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            c[i][j] = 0;
            for(int k=0; k<n; k++)
                c[i][j] += a[i][k] * b[k][j];
        }

    double end = omp_get_wtime();

    printf("Result:\n");
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
            printf("%d ", c[i][j]);
        printf("\n");
    }

    printf("Execution time: %f\n", end-start);

    return 0;
}
