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

package solutions;

import java.util.HashMap;
import java.util.Scanner;

public class QuickerKeyboard {

    private String name = "";
    private int maxNumBtnPress = 0;
    private HashMap<Character, Integer> hm = new HashMap<Character, Integer>();

    // constructor
    public QuickerKeyboard(String name, int maxNumBtnPress) {
        // HashMap is not user friendly!
        hm.put('_', 1);
        hm.put('\'', 2);
        hm.put('-', 3);
        hm.put('p', 4);
        hm.put('y', 5);
        hm.put('f', 6);
        hm.put('g', 5);
        hm.put('c', 4);
        hm.put('r', 3);
        hm.put('l', 2);
        hm.put('a', 2);
        hm.put('o', 3);
        hm.put('e', 4);
        hm.put('u', 5);
        hm.put('i', 6);
        hm.put('d', 7);
        hm.put('h', 6);
        hm.put('t', 5);
        hm.put('n', 4);
        hm.put('s', 3);
        hm.put('q', 4);
        hm.put('j', 5);
        hm.put('k', 6);
        hm.put('x', 7);
        hm.put('b', 8);
        hm.put('m', 7);
        hm.put('w', 6);
        hm.put('v', 5);
        hm.put('z', 4);
        hm.put('P', 8);
        hm.put('Y', 9);
        hm.put('F', 10);
        hm.put('G', 9);
        hm.put('C', 8);
        hm.put('R', 7);
        hm.put('L', 6);
        hm.put('A', 5);
        hm.put('O', 6);
        hm.put('E', 7);
        hm.put('U', 8);
        hm.put('I', 9);
        hm.put('D', 10);
        hm.put('H', 9);
        hm.put('T', 8);
        hm.put('N', 7);
        hm.put('S', 6);
        hm.put('Q', 5);
        hm.put('J', 6);
        hm.put('K', 7);
        hm.put('X', 8);
        hm.put('B', 9);
        hm.put('M', 8);
        hm.put('W', 7);
        hm.put('V', 6);
        hm.put('Z', 5);

        this.name = name;
        this.maxNumBtnPress = maxNumBtnPress;
        boolean constraints = checkConstraints(this.name, this.maxNumBtnPress);
        if (constraints == false) {
            System.out.print(
                    "Please enter the name contains only characters found on the keyboard (including capital letters).\n"
                            + "0 < length of name ≤ 180\n" + "0 < number of button presses ≤ 10000");
        }
    }

    public boolean checkConstraints(String name, int maxNumBtnPress) {
        if (name.length() > 0 && name.length() <= 180) {
            if (maxNumBtnPress > 0 && maxNumBtnPress <= 10000) {
                int count = 0;
                for (int i = 0; i < name.length(); i++) {
                    if (this.hm.containsKey(name.charAt(i)) == true) {
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

    public void checkPossibility() {
        int numBtnPress = 0;
        for (int i = 0; i < this.name.length(); i++) {
            numBtnPress += this.hm.get(this.name.charAt(i));
        }
        if (numBtnPress <= this.maxNumBtnPress) {
            System.out.println("Possible");
        } else {
            System.out.println("Not Possible");
        }
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        System.out.print("Name: ");
        String name = input.nextLine();
        System.out.print("Max number of button presses: ");
        int maxNumBtnPress = input.nextInt();
        input.close();

        QuickerKeyboard obj = new QuickerKeyboard(name, maxNumBtnPress);
        obj.checkPossibility();
    }

}
