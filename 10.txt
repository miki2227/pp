#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cuda_runtime.h>

__global__ void add(int *a,int *b,int *c,int n)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if(i<n)
        c[i] = a[i] + b[i];
}

int main()
{
    int n=1000;
    int *a,*b,*c;
    int *d_a,*d_b,*d_c;

    a=(int*)malloc(n*sizeof(int));
    b=(int*)malloc(n*sizeof(int));
    c=(int*)malloc(n*sizeof(int));

    for(int i=0;i<n;i++)
    {
        a[i]=i;
        b[i]=i;
    }

    clock_t s=clock();

    for(int i=0;i<n;i++)
        c[i]=a[i]+b[i];

    clock_t e=clock();

    printf("CPU time: %f\n",
           (double)(e-s)/CLOCKS_PER_SEC);

    cudaMalloc(&d_a,n*sizeof(int));
    cudaMalloc(&d_b,n*sizeof(int));
    cudaMalloc(&d_c,n*sizeof(int));

    s=clock();

    cudaMemcpy(d_a,a,n*sizeof(int),cudaMemcpyHostToDevice);
    cudaMemcpy(d_b,b,n*sizeof(int),cudaMemcpyHostToDevice);

    add<<<(n+255)/256,256>>>(d_a,d_b,d_c,n);

    cudaMemcpy(c,d_c,n*sizeof(int),cudaMemcpyDeviceToHost);

    e=clock();

    printf("GPU time: %f\n",
           (double)(e-s)/CLOCKS_PER_SEC);

    printf("Result: %d\n",c[999]);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    free(a);
    free(b);
    free(c);

    return 0;
}
