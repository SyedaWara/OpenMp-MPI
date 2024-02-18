#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define MAX 100000000
#define THRESHOLD 1000  // Adjust this threshold based on experimentation

void swap(long long *a, long long *b);
long long partition(long long arr[], long long start, long long end);
void insertionSort(long long arr[], long long start, long long end);
void quickSort(long long arr[], long long start, long long end);

int main() {
    double start, end;
    long long *arr;
    int x;  // Number of threads
    int i;
    long long num;

    printf("Enter the number of threads: ");
    scanf("%d", &x);

    arr = malloc(MAX * sizeof(long long));

    srand(time(0));
    for (i = 0; i < MAX; i++) {
        num = rand() % 100000;
        arr[i] = num;
    }

    omp_set_num_threads(x);

    start = omp_get_wtime();
    quickSort(arr, 0, MAX - 1);
    end = omp_get_wtime();

    printf("Array size: %d , Threads: %d , Time taken: %.2lf sec\n", MAX, x, end - start);
    free(arr);
    return 0;
}

void swap(long long *a, long long *b) {
    long long t = *a;
    *a = *b;
    *b = t;
}

long long partition(long long arr[], long long start, long long end) {
    long long pivot = arr[end];
    long long i = (start - 1);

    for (long long j = start; j <= end - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[end]);
    return (i + 1);
}

void insertionSort(long long arr[], long long start, long long end) {
    for (long long i = start + 1; i <= end; i++) {
        long long key = arr[i];
        long long j = i - 1;

        while (j >= start && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void quickSort(long long arr[], long long start, long long end) {
    long long index;
    if (start < end) {
        if (end - start + 1 < THRESHOLD) {
            // Use sequential sort for small subarrays
            insertionSort(arr, start, end);
        } else {
            index = partition(arr, start, end);

            #pragma omp parallel
            {
                #pragma omp single nowait
                {
                    #pragma omp task
                    quickSort(arr, start, index - 1);
                    #pragma omp task
                    quickSort(arr, index + 1, end);
                }
            }
 }
}
}
