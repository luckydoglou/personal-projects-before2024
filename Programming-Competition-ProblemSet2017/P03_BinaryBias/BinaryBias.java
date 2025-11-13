/**  Xiaolou Huang (Lor)
  Problem 3
  Copyright © 2018 XIAOLOU HUANG. All rights reserved.

    binary -> decimal : Integer.parseInt(value, 2), return type:int
    decimal -> binary : Integer.toBinaryString(int), return type:int
    
    str -> int : Integer.parseInt(str) or Interger.valueof(str)
    int -> str : Integer.toString(int) or String.valueof(int)

    // initialize array: int[][] arr = new int[row][column]
    
 Binary Representations of Numbers:
 00000 - 0   00001 - 1   00010 - 2   00011 - 3   00100 - 4
 00101 - 5   00110 - 6   00111 - 7   01000 - 8   01001 - 9
 01010 - 10  01011 - 11  01100 - 12  01101 - 13  01110 - 14
 01111 - 15  10000 - 16  10001 - 17  10010 - 18  10011 - 19
 10100 - 20  10101 - 21

 Example1 input:
     What number to start: 0
     What number to end: 20
     What is the increment: 1
 Example1 output:
     0 1 2 4 8 16 3 5 6 9 10 12 17 18 20 7 11 13 14 19 15
 Example2 input:
     What number to start: 0
     What number to end: 22
     What is the increment: 3
 Example2 output:
     0 3 6 9 12 18 21 15
**/

package solutions;
import java.util.Scanner;

public class BinaryBias {
    
    private int row = 0;
    private int column = 2;
    private String[][] numList;
    
    // constructor
    // create a 2d array with decimal value in column 0, binary value in column 1
    public BinaryBias(int start, int end, int increment) {
        for (int i = start; i <= end; i += increment) {
            this.row++;
        }
        
        this.numList = new String[this.row][this.column]; // initialize the array
        
        for (int i = 0; i < this.row; i++) {
            this.numList[i][0] = Integer.toString(i * increment); // assign decimal number into column 0
            this.numList[i][1] = Integer.toBinaryString(i * increment); // assign binary number into column 1
        } 
    }
    
    // this method counts number of '1's in binary string
    public int countOneInBiStr(String str) {
        int count = 0;
        for (int i = 0; i < str.length(); i++) {
            if (str.charAt(i) == '1') {
                count++;
            }
        }
        return count;
    }
     
    public void swap(String[][] arr, int i, int j) {
        String[][] temp = {{"", ""}};
        temp[0] = arr[i];
        arr[i] = arr[j];
        arr[j] = temp[0];
    }
    
    public void sort(String[][] arr) {
        // bubble sort
        for (int i = 0; i < this.row - 1; i++) {
            
            for (int j = 0; j < this.row - i - 1; j++) {
                // get the number of ones in binary str
                int numOne_j = countOneInBiStr(arr[j][1]);
                int numOne_jPlus1 = countOneInBiStr(arr[j + 1][1]);
                // check and swap
                if (numOne_j > numOne_jPlus1) {
                    swap(arr, j, j + 1);
                } else if (numOne_j == numOne_jPlus1) {
                    if (Integer.parseInt(arr[j][0]) > Integer.parseInt(arr[j + 1][0])) {
                    swap(arr, j, j + 1);
                    }
                }
            }
        }
    }
    
    public void print() {
        sort(this.numList);
        for (int i = 0; i < numList.length; i++) {
            System.out.printf("%d ", Integer.parseInt(numList[i][0]));
        }
    }   

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        System.out.print("What number to start: ");
        int start = input.nextInt();
        System.out.print("What number to end: ");
        int end = input.nextInt();
        System.out.print("What number to increment: ");
        int increment = input.nextInt();
        input.close();
        
        BinaryBias obj = new BinaryBias(start, end, increment);
        obj.print();    
    }   
}



