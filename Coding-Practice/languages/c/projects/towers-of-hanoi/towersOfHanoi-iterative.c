/*
* Hanoi iterative algorithm:
*   First establish the standards: number the  disks from 1 (the smallest) to N (the largest)
*   Follow three principles:
*     1. move odd-numbered disks only clockwise and even-numbered disks only counterclockwise
*     2. Do not move the same disk twice in succession
*     3. Do not place a larger disk on top of a smaller one
*  Date: 4/3/2020
*/

#include <stdio.h>
#include <math.h>

// forward declarations
void hanoi(char n);

int main(void) {

  hanoi(4);

  return 0;
}

/*
* @param n, the number of disks to be moved
*/
void hanoi(char n) {
  int numOfMoves = pow(2, n) - 1;
  int pegA[255];
  int pegB[255];
  int pegC[255];
  int *pegA_ptr = pegA;
  int *pegB_ptr = pegB;
  int *pegC_ptr = pegC;
  int prevMovedDisk = 0; // prevent move same disk twice in succession

  // initialize peg A, B, C.
  // set the number to 99999 as empty, and prevent agains principle three
  for (int i = 0; i < 255; i++) {
    pegA[i] = 99999;
    pegB[i] = 99999;
    pegC[i] = 99999;
  }
  // set the bottom of pegs to 99999 to prevent incorrect value when index out of bound 
  pegA_ptr++;
  pegB_ptr++;
  pegC_ptr++;

  // initialize n disks on peg A
  for (int i = n; i > 0; i--) {
    *pegA_ptr = i;
    pegA_ptr++;
  }
  pegA_ptr--; // move to top disk

  // total of moves
  for (int i = 1; i <= numOfMoves; i++) {
    printf("\ni = %d\n", i);
    printf("prevMovedDisk: %d\n", prevMovedDisk);
    printf("pegA_ptr: %d, pegB_ptr: %d, pegC_ptr: %d\n", *pegA_ptr, *pegB_ptr, *pegC_ptr);
    // check top disk on each peg until find a valid move
    //printf("pegA_ptr after init: %d\n", *pegA_ptr);
    if (*pegA_ptr != prevMovedDisk) { // check top disk on peg A
      // check disk number is even or odd
      if ((*pegA_ptr % 2 == 0) && (*pegA_ptr < *pegC_ptr)) { // even go counter-clockwise
        // move the disk to the target location
        // make sure pointers move back to correct location after
        pegC_ptr++;
        *pegC_ptr = *pegA_ptr;
        *pegA_ptr = 99999;
        pegA_ptr--;
        prevMovedDisk = *pegC_ptr;
        printf("Move disk from %c to %c\n", 'A', 'C');
        continue;
      } else if ((*pegA_ptr % 2 == 1) && (*pegA_ptr < *pegB_ptr)) { // odd go clockwise
        // move the disk to the target location
        // make sure pointers move back to correct location after
        pegB_ptr++;
        *pegB_ptr = *pegA_ptr;
        *pegA_ptr = 99999;
        pegA_ptr--;
        prevMovedDisk = *pegB_ptr;
        printf("Move disk from %c to %c\n", 'A', 'B');
        continue;
      }
    }
    if (*pegB_ptr != prevMovedDisk) { // check top disk on peg B
      // check disk number is even or odd
      if ((*pegB_ptr % 2 == 0) && (*pegB_ptr < *pegA_ptr)) { // even go counter-clockwise
        // move the disk to the target location
        // make sure pointers move back to correct location after
        pegA_ptr++;
        *pegA_ptr = *pegB_ptr;
        *pegB_ptr = 99999;
        pegB_ptr--;
        prevMovedDisk = *pegA_ptr;
        printf("Move disk from %c to %c\n", 'B', 'A');
        continue;
      } else if ((*pegB_ptr % 2 == 1) && (*pegB_ptr < *pegC_ptr)) { // odd go clockwise
        // move the disk to the target location
        // make sure pointers move back to correct location after
        pegC_ptr++;
        *pegC_ptr = *pegB_ptr;
        *pegB_ptr = 99999;
        pegB_ptr--;
        prevMovedDisk = *pegC_ptr;
        printf("Move disk from %c to %c\n", 'B', 'C');
        continue;
      }
    } 
    if (*pegC_ptr != prevMovedDisk) { // check top disk on peg C
      // check disk number is even or odd
      if ((*pegC_ptr % 2 == 0) && (*pegC_ptr < *pegB_ptr)) { // even go counter-clockwise
        // move the disk to the target location
        // make sure pointers move back to correct location after
        pegB_ptr++;
        *pegB_ptr = *pegC_ptr;
        *pegC_ptr = 99999;
        pegC_ptr--;
        prevMovedDisk = *pegB_ptr;
        printf("Move disk from %c to %c\n", 'C', 'B');
        continue;
      } else if ((*pegC_ptr % 2 == 1) && (*pegC_ptr < *pegA_ptr)) { // odd go clockwise
        // move the disk to the target location
        // make sure pointers move back to correct location after
        pegA_ptr++;
        *pegA_ptr = *pegC_ptr;
        *pegC_ptr = 99999;
        pegC_ptr--;
        prevMovedDisk = *pegA_ptr;
        printf("Move disk from %c to %c\n", 'C', 'A');
        continue;
      }
    }
  } // end of for loop
}


