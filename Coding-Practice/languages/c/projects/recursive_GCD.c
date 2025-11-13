/*
* Recursive Greeatest Common Divisor (Euclidean algorithm):
*   The gcd of x and y is defined recursively as follows: If y is equal to 0,
*   then gcd(x, y) is x; otherwise gcd(x, y) is gcd(y, x % y), 
*   where % is the remainder operator.
* Date: 4/4/2020
*/

#include <stdio.h>

int gcd(int x, int y);

int main(void) {

  int x = gcd(48, 18);
  printf("GCD for 48 and 18 is: %d\n", x);

  return 0;
}

int gcd(int x, int y) {
  if (x % y == 0) {
    return y;
  } else {
    return gcd(y, x % y);
  }
}

