#  Xiaolou Huang (Lor)
#  Problem 3
#  Copyright © 2018 XIAOLOU HUANG. All rights reserved.
#
#    binary -> decimal : int("bi-num", 2) return type:int
#    decimal -> binary : bin(num) return type:str
#
# Binary Representations of Numbers:
# 00000 - 0   00001 - 1   00010 - 2   00011 - 3   00100 - 4
# 00101 - 5   00110 - 6   00111 - 7   01000 - 8   01001 - 9
# 01010 - 10  01011 - 11  01100 - 12  01101 - 13  01110 - 14
# 01111 - 15  10000 - 16  10001 - 17  10010 - 18  10011 - 19
# 10100 - 20  10101 - 21
#
# Example1 input:
#     What number to start: 0
#     What number to end: 20
#     What is the increment: 1
# Example1 output:
#     0 1 2 4 8 16 3 5 6 9 10 12 17 18 20 7 11 13 14 19 15
# Example2 input:
#     What number to start: 0
#     What number to end: 22
#     What is the increment: 3
# Example2 output:
#     0 3 6 9 12 18 21 15 

class BinaryBias:
    
    __numList = [] # this list will contain the integer and its binary form
    
    def __init__(self, start, end, increment):
        count = 0
        for i in range(start, end + 1, increment):
            count += 1
        self.__numList = [[0 for x in range(2)] for y in range(count)] # initialize the list
        count = 0
        for j in range(start, end + 1, increment):
            self.__numList[count][0] = j
            self.__numList[count][1] = self.decimalToBinary(j)
            count += 1
        
    def decimalToBinary(self, dec):
        return bin(int(dec))[2:] # return binary form in string type
        
    def binaryToDecimal(self, bi):
        return int(str(bi), 2) # return decimal form in string type
            
    def countingOneInBinaryString(self, binaryString):
        x = 0
        for i in range(len(binaryString)):
            if (binaryString[i] == "1"):
                x += 1
        return x
        
    def sortNumList(self, numList):
        # insertion sort / bubble sort
        n = len(numList)
     
        # Traverse through all array elements
        for i in range(n):
            
            # Last i elements are already in place
            # traverse the array from 0 to n-i-1
            # Swap if the element found is greater
            # than the next element
            for j in range(0, n - i - 1):
                
                numOnes_j = self.countingOneInBinaryString(numList[j][1])
                numOnes_jPlus1 = self.countingOneInBinaryString(numList[j + 1][1])
                # if binary string is bigger, bubble it up, if binary string is the same, compare the integer value
                if numOnes_j > numOnes_jPlus1:
                    numList[j], numList[j + 1] = numList[j + 1], numList[j]
                elif numOnes_j == numOnes_jPlus1:
                    if numList[j][0] > numList[j + 1][0]:
                        numList[j], numList[j + 1] = numList[j + 1], numList[j]
    
    def toString(self):
        self.sortNumList(self.__numList)
        for i in range(len(self.__numList)):
            print(self.__numList[i][0], end=" ")


def main():
    start = int(input("What number to start: "))
    end = int(input("What number to end: "))
    increment = int(input("What is the increment: "))
        
    obj = BinaryBias(start, end, increment)
    obj.toString()

main()


