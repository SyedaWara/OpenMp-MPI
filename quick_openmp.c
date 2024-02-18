// C++ program to implement the Quick Sort
// using OMP
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>
#define MAX 500000000
long int x;

void swap(long int *a,long int *b);
long int partition(long int arr[], long int start, long int end);
void quickSort(long int arr[], long int start, long int end);

// Driver Code
long int main()
{
	
	long double start,end;
	long int *arr;
	arr=(long int*)malloc(MAX*sizeof(long int));
	long long  int i;
	long int num;
	srand(time(0));
	for (i = 0; i < MAX; i++) {
		num= rand() % 100000;
		arr[i]=num;		
	}
    start=omp_get_wtime();
	x=omp_get_num_threads();
        quickSort(arr, 0, MAX-1);   
	end=omp_get_wtime();
	
    printf("Array size: %d , Threads: %d , Time taken: %.2Lf sec\n",MAX,x,end-start);
    free(arr);
    return(0);
}

// Function to swap two numbers a and b
void swap(long int* a, long int* b)
{
	long int t = *a;
	*a = *b;
	*b = t;
}
// Function to perform the partitioning
// of array arr[]
long int partition(long int arr[], long int start, long int end){
	// Declaration
	long int pivot = arr[end];
	long int i = (start - 1);
	// Rearranging the array
	for (long int j = start; j <= end - 1; j++) {
		if (arr[j] < pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[end]);
	// Returning the respective index
	return (i + 1);
}
// Function to perform QuickSort Algorithm
// using openmp
void quickSort(long int arr[], long int start, long int end){
	// Declaration
	long int index;
	if (start < end) {
		// Getting the index of pivot
		// by partitioning
		index = partition(arr, start, end);
// Parallel sections
#pragma omp parallel sections
		{
#pragma omp section
			{
				// Evaluating the left half
				quickSort(arr, start, index - 1);
			}
#pragma omp section
			{
				// Evaluating the right half
				quickSort(arr, index + 1, end);
			}
		}
	}
}

