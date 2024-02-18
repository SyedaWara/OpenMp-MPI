#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>

#define MAX 3000000000

int x;

void mergeSort(int a[], long long l, long long r);
void merge(int a[], long long l, long long m, long long r);
void mergeSortSequencial(int a[], long long l, long long r);

int main()
{
    FILE *fptr;
    double start, end;
    int *arr;
    arr = malloc(MAX * sizeof(int));

    long long i;
    long long num;
    srand(time(0));

    int num_threads;
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    for (i = 0; i < MAX; i++) {
        num = rand() % 100000;
        arr[i] = num;
    }

    

    start = omp_get_wtime();
    #pragma omp parallel num_threads(num_threads)
    {
        x = omp_get_num_threads();
        #pragma omp single
        mergeSort(arr, 0, MAX - 1);
    }

    end = omp_get_wtime();

    printf("Array Size: %lld, Threads: %d, Time Taken: %.2f\n", MAX, x, end - start);

    free(arr);
    return 0;
}
void merge(int *arr,long long l,long long m,long long r)
{
     long long i, j, k;
    long long n1 = m - l + 1;
    long long n2 = r - m;
 
    /* create temp arrays */
    
    int *Left = malloc(n1 * sizeof(int));
    int *Right = malloc(n2 * sizeof(int));
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        Left[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        Right[j] = arr[m + 1 + j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (Left[i] <= Right[j]) {
            arr[k] = Left[i];
            i++;
        }
        else {
            arr[k] = Right[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        arr[k] = Left[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        arr[k] = Right[j];
        j++;
        k++;
    }

	free(Left);
	free(Right);
}

void mergeSortSequencial(int arr[],long long l,long long r)
{
    if (l<r)
    {
        int m=(l + r)/2;
        mergeSortSequencial(arr,l,m);
        mergeSortSequencial(arr,m+1,r);
        merge(arr,l,m,r);
    }
}
void mergeSort(int a[],long long l,long long r)
{
    if (l<r)
    {
        if ((r-l)>1000)         {

		int m=(l+r)/2;
           #pragma omp task firstprivate (a,l,m)
                mergeSort(a,l,m);
            #pragma omp task firstprivate (a,m,r)
                mergeSort(a,m+1,r);
            #pragma omp taskwait 
            merge(a,l,m,r);
        }
        else
           mergeSortSequencial(a,l,r); 
    }
}

