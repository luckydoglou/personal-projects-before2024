//
// selection sort
// keep selecting min in rest of array and put it at the end of sorted array
//
// Xiaolou Huang (Lor)
// 10/1/2019
//

#include <stdio.h>
#include <stdlib.h>

void selection_sort(int *arr, int arrSize);
void print_array(int *arr, int arrSize);
void swap(int *e1, int *e2);

int main(void) {
	int arr[] = {8, 3, 2, 6, 9, 1, 4, 5};
	int arrSize = sizeof(arr) / sizeof(arr[0]);

	puts("Original array unsorted:");
	print_array(arr, arrSize);

	selection_sort(arr, arrSize);

	puts("After selection sort:");
	print_array(arr, arrSize);

	return 0;
}

void selection_sort(int *arr, int arrSize) {
	int i, j, minPos;

	for (i = 0; i < arrSize; i++) {
		minPos = i;
		for (j = i; j < arrSize; j++) {
			if (arr[minPos] > arr[j]) {
				minPos = j;
			} 
		}
		swap(&arr[minPos], &arr[i]);
	}
}

void swap(int *e1, int *e2) {
	int temp;
	temp = *e1;
	*e1 = *e2;
	*e2 = temp;
}

void print_array(int *arr, int arrSize) {
	int i;
	for (i = 0; i < arrSize - 1; i++) {
		printf("%d, ", arr[i]);
	}
	printf("%d.\n", arr[arrSize - 1]);
}

