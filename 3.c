#include <stdio.h>
#include <omp.h>

void merge(int a[], int l, int m, int r)
{
    int b[100], i=l, j=m+1, k=0;

    while(i<=m && j<=r)
        b[k++] = (a[i]<a[j]) ? a[i++] : a[j++];

    while(i<=m) b[k++] = a[i++];
    while(j<=r) b[k++] = a[j++];

    for(i=l,k=0; i<=r; i++)
        a[i] = b[k++];
}

void sort(int a[], int l, int r, int p)
{
    if(l<r)
    {
        int m=(l+r)/2;

        if(p)
        {
            #pragma omp parallel sections
            {
                #pragma omp section
                sort(a,l,m,p);

                #pragma omp section
                sort(a,m+1,r,p);
            }
        }
        else
        {
            sort(a,l,m,0);
            sort(a,m+1,r,0);
        }

        merge(a,l,m,r);
    }
}

int main()
{
    int a[100], b[100], n;

    printf("Enter size: ");
    scanf("%d",&n);

    for(int i=0;i<n;i++)
        scanf("%d",&a[i]), b[i]=a[i];

    double s,e,t1,t2;

    s=omp_get_wtime();
    sort(a,0,n-1,0);
    t1=omp_get_wtime()-s;

    s=omp_get_wtime();
    sort(b,0,n-1,1);
    t2=omp_get_wtime()-s;

    printf("Sorted array: ");
    for(int i=0;i<n;i++)
        printf("%d ",b[i]);

    printf("\nSequential Time: %f",t1);
    printf("\nParallel Time: %f",t2);
    printf("\nSpeedup: %f",t1/t2);

    return 0;
}
