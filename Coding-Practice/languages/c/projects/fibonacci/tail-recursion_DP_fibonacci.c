/*
* Tail recursion and dynamic programming for fibonacci numbers
* Date: 4/4/2020
*/

#include <stdio.h>

int fib_tail(int n, int x1, int x2);
int fib_dp(int n);
int fib_dp_helper(int n, int fibArr[]);

int main(void) {

  printf("fib_tail(5): %d\n", fib_tail(5, 0, 1));
  printf("fib_dp(5): %d\n", fib_dp(5));


  return 0;
}

// when call this function, x1, x2 have to be 0 and 1
int fib_tail(int n, int x1, int x2) {
  if (n == 0) {
    return x1;
  }
  if (n == 1) {
    return x2;
  }
  return fib_tail(n - 1, x2, x1 + x2);
}

// dynamic programming, recursion with memorization
int fib_dp(int n) {
  int fibArr[n + 1];

  for (int i = 0; i <= n; i++) {
    fibArr[i] = -1;
  }

  fib_dp_helper(n, fibArr);
  return fibArr[n];
}

int fib_dp_helper(int n, int fibArr[]) {
  if (n <= 1) {
    fibArr[n] = n;
  }

  if (fibArr[n] != -1) {
    return fibArr[n];
  } else {
    return fibArr[n] = fib_dp_helper(n - 1, fibArr) + fib_dp_helper(n - 2, fibArr);
  }

}

