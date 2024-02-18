#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

long long MAX=2000000000;

void merge(int *arr, long long l, long long m, long long r) {
    long long i, j, k;
    long long n1 = m - l + 1;
    long long n2 = r - m;

    // Create temp arrays
    int *Left = malloc(n1 * sizeof(int));
    int *Right = malloc(n2 * sizeof(int));

    // Check if memory allocation is successful
    if (Left == NULL || Right == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        Left[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        Right[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (Left[i] <= Right[j]) {
            arr[k] = Left[i];
            i++;
        } else {
            arr[k] = Right[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = Left[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = Right[j];
        j++;
        k++;
    }

    free(Left);
    free(Right);
}

void mergeSort(int arr[], long long l, long long r) {
    if (l < r) {
        long int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void printArray(int A[], long long size) {
    long int i;
    for (i = 0; i < size; i++)
        printf("%ld ", A[i]);
    printf("\n");
}

int main() {
    double start, end;
    int *arr;
    arr = malloc(MAX * sizeof(int));

    long long i;
    long long num;
    srand(time(0));

    for (i = 0; i < MAX; i++) {
        num = rand() % 100000;
        arr[i] = num;
    }

    start = omp_get_wtime();
    mergeSort(arr, 0, MAX - 1);
    end = omp_get_wtime();


    printf("---Merge Sort Serial---\n");
    printf("Array Size: %ld, Time Taken: %.3f\n\n", MAX, end - start);



    free(arr);
    return 0;
}
