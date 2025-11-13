//  Name: Xiaolou Huang (Lor)
//
//    1 - Chandelier Shopping
//    Ada Lovelace wants to buy a chandelier, but doesn’t know how many layers she can afford. The first layer has 1 crystal, and each layer above has 1 crystal more than the layer below it. A chandelier costs $100 per crystal.
//    Given a number of layers, tell Ada Lovelace the price of the chandelier and display what the chandelier would look like, representing each crystal as ‘$’ (shown in the examples below).
//    Constraints
//    3 ≤ Input < 232-1 Input is an integer.
//    Example 1.1
//    Input
//    6
//    Output
//     Price: $2100
//     $!$!$!$!$!$
//     $-$-$-$-$
//     $!$!$!$
//     $-$-$
//     $!$
//     $
//    Example 1.2
//    Input
//    3
//    Output
//     Price: $600
//     $!$!$
//     $-$
//     $

package solutions;

import java.util.Scanner;

public class ChandelierShopping {

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        System.out.println("How many layers do you want: ");
        int layers = input.nextInt();
        chandelier(layers);
    }

    public static void chandelier(int layers) {
        // variables
        final int valueOfEachCrystals = 100;
        int price = 0;
        int crystals = 0;
        boolean symbol = true;  // for alternating the '!' and '-'

        for (int i = layers; i >= 1; i--) {
            crystals += i;
        }
        price = crystals * valueOfEachCrystals; // price

        // format the output
        System.out.println("Price: $" + price);  // price output
        for (int j = 1; j <= layers; j++) {
            System.out.print("$");  // first '$' for each row
            
            // alternating true and false
            if (symbol == true) {
                for (int k = layers - 1; k >= j; k--) {
                    System.out.print("!" + "$");
                }
                symbol = false;
            } else {
                for (int k = layers - 1; k >= j; k--) {
                    System.out.print("-" + "$");
                }
                symbol = true;
            }
            System.out.println();
        }
    }
}
