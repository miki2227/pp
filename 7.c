#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, n, sum=0, total=0;
    int a[100], local[100];

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    n = size * 2;

    if(rank==0)
    {
        printf("Array: ");
        for(int i=0;i<n;i++)
        {
            a[i]=i+1;
            printf("%d ",a[i]);
        }
    }

    MPI_Scatter(a,2,MPI_INT,local,2,MPI_INT,0,
                MPI_COMM_WORLD);

    for(int i=0;i<2;i++)
        sum += local[i];

    MPI_Reduce(&sum,&total,1,MPI_INT,MPI_SUM,0,
               MPI_COMM_WORLD);

    if(rank==0)
        printf("\nTotal sum = %d\n",total);

    MPI_Finalize();
    return 0;
}
