#include <stdio.h>
#include <cuda_runtime.h>

__global__ void add(int *a, int *b, int *c, int n)
{
    int i = threadIdx.x;
    if(i < n)
        c[i] = a[i] + b[i];
}

int main()
{
    int n;
    printf("Enter size: ");
    scanf("%d", &n);

    int a[n], b[n], c[n];
    int *d_a, *d_b, *d_c;

    for(int i=0; i<n; i++)
        scanf("%d", &a[i]);

    for(int i=0; i<n; i++)
        scanf("%d", &b[i]);

    cudaMalloc(&d_a, n*sizeof(int));
    cudaMalloc(&d_b, n*sizeof(int));
    cudaMalloc(&d_c, n*sizeof(int));

    cudaMemcpy(d_a, a, n*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, n*sizeof(int), cudaMemcpyHostToDevice);

    add<<<1,n>>>(d_a, d_b, d_c, n);

    cudaMemcpy(c, d_c, n*sizeof(int), cudaMemcpyDeviceToHost);

    printf("Result: ");
    for(int i=0; i<n; i++)
        printf("%d ", c[i]);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return 0;
}
