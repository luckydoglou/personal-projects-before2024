/**  Xiaolou Huang (Lor)
 Problem 3
 Copyright © 2018 XIAOLOU HUANG. All rights reserved.
 
 binary -> decimal : return type: str
 decimal -> binary : return type:str
 
 int -> str : std::to_string(int)
 str -> int : stoi(str)
 
 // initialize the 2d vector 'numList'
 numList.resize(this->row, std::vector<std::string>(column));
 
 // How to avoid "Implicit conversion loses integer precision" warning?  ---  add a cast
 
 // Have to pass in the address of the private element(vector) in order to modify it. Use pointer! Can't avoid it
 
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

#include <iostream>
#include <string>
#include <vector>

class BinaryBias {
private:
    int row = 0;
    int column = 2;
    std::vector<std::vector<std::string>> numList;
    
public:
    // constructor
    BinaryBias(int start, int end, int increment) {
        int i = start;
        while (i <= end) {
            this->row++; // find out the length of the row
            i += increment;
        }
        
        // initialize the numList
        numList.resize(this->row, std::vector<std::string>(column));
        
        // assign values into each column
        for (int j = 0; j < this->row; j++) {
            this->numList[j][0] = std::to_string(j * increment);
            this->numList[j][1] = decimalToBinary(numList[j][0]);
        }
    }
    
    std::string decimalToBinary(std::string dec);
    int countOneInBiStr(std::string *biStrPtr);
    void sort(std::vector<std::vector<std::string>> *numList);
    void print();
    
}; // end of BinaryBias class

//
std::string BinaryBias::decimalToBinary(std::string dec) {
    int decInt = 0;
    std::vector<int> biReverse;
    std::string biStr = "";
    
    // convert string to int
    decInt = std::stoi(dec);
    
    // do the calculation, and assign the number into biReverse
    do {
        biReverse.push_back(decInt % 2);
        decInt /= 2;
    } while(decInt > 0);
    
    // reverse the number in vector and convert back to string
    for (int i = ((int)biReverse.size() - 1); i >= 0; i--) {
        if (biReverse.at(i) == 0) {
            biStr.append("0");
        } else if (biReverse.at(i) == 1) {
            biStr.append("1");
        }
    }
    return biStr;
}

//
int BinaryBias::countOneInBiStr(std::string *biStrPtr) {
    int countOnes = 0;
    for (int i = 0; i < (*biStrPtr).length(); i++) {
        if ((*biStrPtr).at(i) == '1') {
            countOnes++;
        }
    }
    return countOnes;
}

//
void BinaryBias::sort(std::vector<std::vector<std::string>> *numLst) {
    numList = *numLst;
    // bubble sort
    for (int i = 0; i < numList.size() - 1; i++) {

        for (int j = 0; j < numList.size() - i - 1; j++) {
            // get number of '1's
            int numOne_j = countOneInBiStr(&numList[j][1]);
            int numOne_jPlus1 = countOneInBiStr(&numList[j + 1][1]);
            
            if(numOne_j > numOne_jPlus1) { // compare bi str
                std::swap(numList[j], numList[j + 1]);
            } else if (numOne_j == numOne_jPlus1) {
                if(stoi(numList[j][0]) > stoi(numList[j][0])) { // compare int value
                    std::swap(numList[j], numList[j + 1]);
                }
            }
        }
    }
}

//
void BinaryBias::print() {
    sort(&(this->numList));
    // print the numList
    for (int i = 0; i < this->numList.size(); i++) {
        printf("%d ", stoi(this->numList[i][0]));
    }
}

int main() {
    
    int start = 0;
    int end = 0;
    int increment = 0;
    std::cout << "What number to start: ";
    std::cin >> start;
    std::cout << "\nWhat number to end: ";
    std::cin >> end;
    std::cout << "\nWhat is the increment: ";
    std::cin >> increment;
    
    BinaryBias obj(start, end, increment);
    obj.print();
    
    return 0;
}
