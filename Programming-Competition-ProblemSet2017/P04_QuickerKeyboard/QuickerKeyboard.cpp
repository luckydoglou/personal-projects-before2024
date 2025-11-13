// Xiaolou Huang (Lor)
// Problem 4
// Copyright © 2018 XIAOLOU HUANG. All rights reserved.
//
// The keyboard wraps horizontally and vertically (so pressing D Pad right on “s” moves to “a”
// and pressing D Pad up of “f” moves to “b”), and the current position always starts on “_” in
// the upper left hand corner.
//
// Constraints
//   The name contains only characters found on the keyboard (including capital letters).
//   0 < length of name ≤ 180
//   0 < number of button presses ≤ 10000
//   The number of button presses is an integer.
//
// Sample Input1:
//      Name: Shenandoah
//      Max number of button presses: 50
// Sample Output1:
//      Not Possible
// Sample Input2:
//      Name: Lord_Reginald_Protector_of_the_Brickyard_Realm
//      Max number of button presses:100
// Sample Output2:
//      Not Possible

#include <iostream>
#include <string>
#include <map>

class QuickerKeyboard {
private:
    
    // map data structure to store keyboard info with how many button presses need to each letter
    std::map<char, int> mp = {
        {'_', 1}, {'\'', 2}, {'-', 3}, {'p', 4}, {'y', 5}, {'f', 6}, {'g', 5}, {'c', 4}, {'r', 3}, {'l', 2}, {'a', 2},
        {'o', 3}, {'e', 4}, {'u', 5}, {'i', 6}, {'d', 7}, {'h', 6}, {'t', 5}, {'n', 4}, {'s', 3}, {'q', 4}, {'j', 5},
        {'k', 6}, {'x', 7}, {'b', 8}, {'m', 7}, {'w', 6}, {'v', 5}, {'z', 4}, {'P', 8}, {'Y', 9}, {'F', 10}, {'G', 9},
        {'C', 8}, {'R', 7}, {'L', 6}, {'A', 5}, {'O', 6}, {'E', 7}, {'U', 8}, {'I', 9}, {'D', 10}, {'H', 9}, {'T', 8},
        {'N', 7}, {'S', 6}, {'Q', 5}, {'J', 6}, {'K', 7}, {'X', 8}, {'B', 9}, {'M', 8}, {'W', 7}, {'V', 6}, {'Z', 5}
    };
    
    std::string name = "";
    int maxNumBtnPress = 0;
public:
    QuickerKeyboard(std::string name, int maxNumBtnPress) {
        this->name = name;
        this->maxNumBtnPress = maxNumBtnPress;
        
        // check constraints
        bool constraint = checkConstraints(this->name, this->maxNumBtnPress);
        if (constraint == false) {
            std::cout << "Plase enter the name contains only characters found on the keyboard (including capital letters)" << std::endl;
            std::cout << "0 < length of name ≤ 180" << std::endl;
            std::cout << "0 < number of button presses ≤ 10000" << std::endl;
        }
    }
    
    bool checkConstraints(std::string name, int maxNumBtnPress);
    void checkPossibility();
    
};

bool QuickerKeyboard::checkConstraints(std::string name, int maxNumBtnPress) {
    if (name.length() > 0 && name.length() <= 180) {
        if (maxNumBtnPress > 0 && maxNumBtnPress <= 10000) {
            int count = 0;
            for (int i = 0; i < name.length(); i++) {
                    if (this->mp.find(name.at(i)) != mp.end()) {
                        count++;
                    }
            }
            if (count == name.length()) {
                return true;
            }
        }
    }
    return false;
}

void QuickerKeyboard::checkPossibility() {
    int numBtnPress = 0;
    for (int i = 0; i < this->name.length(); i++) {
        numBtnPress += this->mp.at(name.at(i));
    }
    if (numBtnPress <= this->maxNumBtnPress) {
        std::cout << "Possible" << std::endl;
    } else {
        std::cout << "Not Possible" << std::endl;
    }
}

int main(int argc, const char * argv[]) {
    
    std::string name;
    int maxNumBtnPress;
    
    std::cout << "Name: ";
    std::cin >> name;
    std::cout << "\nMax number of button presses: ";
    std::cin >> maxNumBtnPress;
    
    QuickerKeyboard obj(name, maxNumBtnPress);
    obj.checkPossibility();
    
    return 0;
}



