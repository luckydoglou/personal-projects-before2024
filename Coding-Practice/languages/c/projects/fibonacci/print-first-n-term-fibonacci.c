//
// print n terms of Fibonacci number in normal way and recursive way
// Xiaolou Huang (Lor)
// 10/1/2019
//

#include <stdio.h>
#include <stdlib.h>

void fibonacci(unsigned int n);
unsigned int fibonacci_recursive(int *fibArr, unsigned int n);
void print_array(int *arr, unsigned int n);

int main(void) {
	unsigned int nTerm = 20;

	puts("Print Fibonacci in normal way");
	fibonacci(nTerm);

	// int fibArr[nTerm] = (int *)malloc(sizeof(int) * nTerm);
	puts("Print Fibonacci in recursive way");
	int fibArr[nTerm];
	fibonacci_recursive(fibArr, nTerm);
	print_array(fibArr, nTerm);

	return 0;
}

void fibonacci(unsigned int n) {
	int fibArr[n];
	int i;

	// if n is less than or equal to 2
	if (n <= 2) {
		print_array(fibArr, n);
		return;
	}

	// if n is greater than 2
	if (n > 2) {
		fibArr[0] = 1;
		fibArr[1] = 1;
		for (i = 2; i < n; i++) {
			fibArr[i] = fibArr[i - 1] + fibArr[i - 2];
		}
		print_array(fibArr, n);
	}
}

unsigned int fibonacci_recursive(int *fibArr, unsigned int n) {
	if (n == 1 || n == 2) { // base cases
		fibArr[0] = 1;
		fibArr[1] = 1;
		return 1;
	} else {
		return fibArr[n - 1] = fibonacci_recursive(fibArr, n - 1) \
		 + fibonacci_recursive(fibArr, n - 2);
	}
}

void print_array(int *arr, unsigned int n) {
	int i;

	if (n < 1) { // if n is less than 1
		printf("Error, input has to be greater than or equal to 1");
		return;
	} else if (n == 1) { // if n is 1
		puts("1 term of fibonacci number is:\n1.");
		return;
	} else if (n == 2) { // if n is 2
		puts("2 terms of fibonacci number are:\n1, 1.");
		return;
	}

	// if n > 2
	printf("%d terms of fibonacci numbers are:\n", n);
	for (i = 0; i < n - 1; i++) {
		printf("%d, ", arr[i]);
	}
	printf("%d.\n", arr[n - 1]);		// print last fib number
}

