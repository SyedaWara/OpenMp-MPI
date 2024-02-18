#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define MAX 100

void mergeSort(int a[], int l, int r);
void merge(int a[], int l, int m, int r);

int main() {
    MPI_Init(NULL, NULL);
    int my_rank, no_proc;
    double start, end;
    int *arr;
    arr = malloc(MAX * sizeof(int));

    long long i;
    int num;
    srand(time(0));

    for (i = 0; i < MAX; i++) {
        num = rand() % 100000;
        arr[i] = num;
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &no_proc);

   //Calculates the size of each partition for MPI processes.
    int partition_size = MAX / no_proc;
    //printf("partitionsize=%d\n",partition_size);
    start = MPI_Wtime();

    int *local_array;
    local_array = malloc(partition_size * sizeof(int));

    MPI_Scatter(arr, partition_size, MPI_INT, local_array, partition_size, MPI_INT, 0, MPI_COMM_WORLD);

    mergeSort(local_array, 0, (partition_size - 1));

    int *final_arr;

    if (my_rank == 0) {
        final_arr = malloc(MAX * sizeof(int));
    }

    MPI_Gather(local_array, partition_size, MPI_INT, final_arr, partition_size, MPI_INT, 0, MPI_COMM_WORLD);

    if (my_rank == 0) {
        mergeSort(final_arr, 0, (MAX - 1));
        end = MPI_Wtime();

        printf("Array Size: %d, Processes: %d, Time Taken: %f seconds\n", MAX, no_proc, end - start);

        free(final_arr);
    }

    free(arr);
    free(local_array);

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

    return 0;
}

/********** Merge Function **********/
void merge(int *arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    int *Left = malloc(n1 * sizeof(int));
    int *Right = malloc(n2 * sizeof(int));

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        Left[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        Right[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
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

    /* Copy the remaining elements of L[], if there are any */
    while (i < n1) {
        arr[k] = Left[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there are any */
    while (j < n2) {
        arr[k] = Right[j];
        j++;
        k++;
    }

    free(Left);
    free(Right);
}

void mergeSort(int a[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

