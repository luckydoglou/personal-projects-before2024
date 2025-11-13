/*
* Hanoi recursive algorithm:
*   a. move n-1 disks from peg 1 to peg 2, using peg 3 as a temprory holding area.
*   b. move the last disk (the largest) from peg 1 to peg 3.
*   c. move the n-1 disks from peg 2 to peg 3, using peg 1 as a temprary holding area.
* Date: 4/3/2020
*/

#include <stdio.h>

// forward declaration
void hanoi(unsigned int n, char start_peg, char end_peg, char temp_peg);

int main(void) {

  hanoi(3, 'A', 'B', 'C');

  return 0;
}

/*
* @param n, the number of disks to be moved
* @param start_peg, the peg on which these disks are initially threaded.
* @param end_peg, the peg to which this stack of disks is to be moved.
* @param temp_peg, the peg to be used as a temporary holding area.
*/
void hanoi(unsigned int n, char start_peg, char end_peg, char temp_peg) {
  // base case, the largest disk move the start to end peg
  if (n == 1) {
    printf("%c --> %c\n", start_peg, end_peg);
  } else {
    // move the smaller stack from start to temp peg
    hanoi(n - 1, start_peg, temp_peg, end_peg);
    // move the last disk from start to end
    hanoi(1, start_peg, end_peg, temp_peg);
    // move the smaller stack from temp to end peg
    hanoi(n - 1, temp_peg, end_peg, start_peg);
  }

}

