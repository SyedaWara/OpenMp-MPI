#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<omp.h>
#define MAX 500000


// function to swap elements
void swap(long int *a, long int *b) {
  long int t = *a;
  *a = *b;
  *b = t;
}

// function to find the partition position
long int partition(long int array[], long int low, long int high) {
  
  // select the rightmost element as pivot
  long int pivot = array[high];
  
  // pointer for greater element
  long int i = (low - 1);

  // traverse each element of the array
  // compare them with the pivot
  long int j;
  for (  j = low; j < high; j++) {
    if (array[j] <= pivot) {
        
      // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i++;
      
      // swap element at i with element at j
      swap(&array[i], &array[j]);
    }
  }

  // swap the pivot element with the greater element at i
  swap(&array[i + 1], &array[high]);
  
  // return the partition point
  return (i + 1);
}

void quickSort(long int array[], long int low, long int high) {
  if (low < high) {
    
    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on right of pivot
    long int pi = partition(array, low, high);
    
    // recursive call on the left of pivot
    quickSort(array, low, pi - 1);
    
    // recursive call on the right of pivot
    quickSort(array, pi + 1, high);
  }
}


// main function
long int main() {


  long double start,end;
	long int *arr;
	arr=(long int*)malloc(MAX*sizeof(long int));
	
	long long int i;
	long int num;
	srand(time(0));
  
  for (i = 0; i < MAX; i++) {

		num= rand() % 100000;
		arr[i]=num;
			
	}
	
  	//start=omp_get_wtime();

  quickSort(arr, 0, MAX - 1);
  
  //end=omp_get_wtime();

	printf("---Quick Sort Serial---\n");
	printf("Array Size : %d  , Time Taken: %Lf\n\n",MAX);
	free(arr);
 
    
    

    return 0;
}
