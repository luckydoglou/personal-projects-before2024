import java.util.Scanner;

/**
 * Xiaolou Huang (Lor) Problem 10 Copyright © 2018 XIAOLOU HUANG. All rights
 * reserved.
 *
 * 
 * Number of blossoms on Day t is denoted by B(t) B(0) = 1 B(1) = 2 B(2) = 3
 * When t > 2, B(t) = B(t-3) + B(t-1)%B(t-2) Sequence: 1 2 3 2 4 3 5 6 4 9...
 * 
 * Constraints 0 ≤ Input< 100 Input is an integer. Example 10.1 Input 10 Output
 * 7 Example 10.2 Input 34 Output 472
 *
 */
public class P10_BountifulBlossoms {

    public static int numberOfBlossoms(int t) {

        if (t < 3) {
            return t + 1;
        }

        return numberOfBlossoms(t - 3) + numberOfBlossoms(t - 1) % numberOfBlossoms(t - 2);
    }

    // Main
    public static void main(String[] args) {

        System.out.println("Enter the day: ");
        Scanner input = new Scanner(System.in);
        int day = input.nextInt();

        System.out.println(numberOfBlossoms(day));

        input.close();
    }
}
