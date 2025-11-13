// 
// Insertion sort, similar to bubble sort.
// Instead of moving elements up in bubble sort, it moves element down
// Xiaolou Huang (Lor)
// 9/29/2019
// 

#include <stdio.h>
#include <stdlib.h>

// function declaration
void insertionSort(int *arr, int arrSize);
void insertionSort_recursive(int *arr, int arrSize);
void swap(int *e1, int *e2);
void printArr(int *arr, int arrSize);

int main(void) {
	int arr[8] = {9, 4, 1, 2, 7, 3, 6, 8};
	int arrSize = sizeof(arr) / sizeof(arr[0]);

	// printf("size0: %d\n", sizeof(arr));
	// printf("size1: %d\n", sizeof(*arr));
	// printf("size3: %d\n", sizeof(arr[0]));
	// printf("size4: %d\n", sizeof(arr) / sizeof(arr[0]));

	printArr(arr, arrSize);
	insertionSort(arr, arrSize);
	insertionSort_recursive(arr, arrSize);
	printArr(arr, arrSize);

	return 0;
}

void insertionSort(int *arr, int arrSize) {
	int i, j;

	for (i = 1; i < arrSize; i++) {
		j = i;
		// move down the element to its correct position
		while (j > 0 && arr[j - 1] > arr[j]) {
	 		swap(&arr[j], &arr[j - 1]);
	 		j = j - 1;
		}
	}
}

void insertionSort_recursive(int *arr, int arrSize) {
	int i;

	if (arrSize == 1) {
		return;
	}
	insertionSort_recursive(arr, arrSize - 1);

	// insert the element arr[i] into right position
	i = arrSize - 1;
	while (i > 0 && arr[i - 1] > arr[i]) {
		swap(&arr[i], &arr[i - 1]);
		i = i - 1;
	}
}

void swap(int *e1, int *e2) {
	int temp;
	temp = *e1;
	*e1 = *e2;
	*e2 = temp;
}

void printArr(int *arr, int arrSize) {
	int i;
	puts("Elements in the array:");
	for (i = 0; i < arrSize; i++) {
		printf("%d ", arr[i]);
	}
	puts("");
}

