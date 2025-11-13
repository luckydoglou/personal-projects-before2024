#  Xiaolou Huang (Lor)
#  Problem 4
#  Copyright © 2018 XIAOLOU HUANG. All rights reserved.
#
#  The keyboard wraps horizontally and vertically (so pressing D Pad right on “s” moves to “a” 
#  and pressing D Pad up of “f” moves to “b”), and the current position always starts on “_” in
#  the upper left hand corner.
#
# Constraints
#    The name contains only characters found on the keyboard (including capital letters).
#    0 < length of name ≤ 180
#    0 < number of button presses ≤ 10000
#    The number of button presses is an integer.
#
# Sample Input1:
#    Name: Shenandoah
#    Max number of button presses: 50
# Sample Output1:
#    Not Possible
# Sample Input2:
#    Name: Lord_Reginald_Protector_of_the_Brickyard_Realm
#    Max number of button presses:100
# Sample Output2:
#    Not Possible
#
#
#

class QuickerKeyboard:
    
    __name = ""
    __maxNumBtnPress = 0
    __keyBoard = {"_" : 1, "'" : 2, "-" : 3, "p" : 4, "y" : 5, "f" : 6, "g" : 5, "c" : 4, "r" : 3, "l" : 2,
                "a" : 2, "o" : 3, "e" : 4, "u" : 5, "i" : 6, "d" : 7, "h" : 6, "t" : 5, "n" : 4, "s" : 3,
                "q" : 4, "j" : 5, "k" : 6, "x" : 7, "b" : 8, "m" : 7, "w" : 6, "v" : 5, "z" : 4,
                "P" : 8, "Y" : 9, "F" : 10, "G" : 9, "C" : 8, "R" : 7, "L" : 6,
                "A" : 5, "O" : 6, "E" : 7, "U" : 8, "I" : 9, "D" : 10, "H" : 9, "T" : 8, "N" : 7, "S" : 6,
                "Q" : 5, "J" : 6, "K" : 7, "X" : 8, "B" : 9, "M" : 8, "W" : 7, "V" : 6, "Z" : 5}
    
    def __init__(self, name, maxNumBtnPress):
        self.__name = name
        self.__maxNumBtnPress = maxNumBtnPress
        # check constraints
        constrain = self.checkConstraint(name, maxNumBtnPress)
        if constrain == True:
            self.checkPossibility(self.__name, self.__maxNumBtnPress)
        else:
            print("Plase enter the name contains only characters found on the keyboard (including capital letters), \n0 < length of name ≤ 180, \n0 < number of button presses ≤ 10000")
        
    def checkConstraint(self, name, maxNumBtnPress):
        if len(name) > 0 and len(name) < 180:
            if maxNumBtnPress > 0 and maxNumBtnPress < 10000:
                count = 0
                for i in range(len(name)):
                    if name[i] in self.__keyBoard.keys():
                        count += 1
                if count == len(name):
                    return True
                
        else:
            return False

    def checkPossibility(self, name, maxNumBtnPress):
        totalBtnPress = 0
        for i in range(len(name)):
            totalBtnPress += self.__keyBoard.get(name[i])
        if totalBtnPress <= maxNumBtnPress:
            print("Possible")
        else:
            print("Not Possible")

        
def main():
    name = input("Name: ")
    maxNumBtnPress = int(input("Max number of button presses: "))
    
    QuickerKeyboard(name, maxNumBtnPress)
    
main()



