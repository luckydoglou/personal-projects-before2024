//============================================================================
// Name        : ChandlelierShopping.cpp
// Author      : Xiaolou Huang (Lor)
// Version     :
// Copyright   : Your copyright notice
// Description : Problem1, Ansi-style
//============================================================================

//	1 - Chandelier Shopping
//	Ada Lovelace wants to buy a chandelier, but doesn’t know how many layers she can afford. The first layer has 1 crystal, and each layer above has 1 crystal more than the layer below it. A chandelier costs $100 per crystal.
//	Given a number of layers, tell Ada Lovelace the price of the chandelier and display what the chandelier would look like, representing each crystal as ‘$’ (shown in the examples below).
//	Constraints
//	3 ≤ Input < 232-1 Input is an integer.
//	Example 1.1
//	Input
//	6
//	Output
//	 Price: $2100
//	 $!$!$!$!$!$
//	 $-$-$-$-$
//	 $!$!$!$
//	 $-$-$
//	 $!$
//	 $
//	Example 1.2
//	Input
//	3
//	Output
//	 Price: $600
//	 $!$!$
//	 $-$
//	 $
//

#include <iostream>
// using namespace std;
#define priceForEachCrystal 100  // price for every crystal

void chandelierShopping(int layers);

int main() {

	int layers;

	std::cout << "How many layers do you want: " << std::endl;
	std::cin >> layers;

	chandelierShopping(layers);
	return 0;
}

void chandelierShopping(int layers) {
	// variables declaration
	int price;
	int crystals = 0;
	bool symbol = true;

	for (int i = 1; i <= layers; i++) {
		crystals += i;
	}

	// formating output
	price = crystals * priceForEachCrystal;  // total price
	std::cout << "Price: $" << price << std::endl;
	for (int j = 1; j <= layers; j++) {
		std::cout << "$";  // first '$' of every layer

		// alternating symbol '!' and '-'
		if (symbol == true) {
			for (int k = j; k <= layers - 1; k++) {
				std::cout << "!$";
			}
			std::cout << std::endl;
			symbol = false;
		} else {
			for (int k = j; k <= layers - 1; k++) {
				std::cout << "-$";
			}
			std::cout << std::endl;
			symbol = true;
		}
	}
}

