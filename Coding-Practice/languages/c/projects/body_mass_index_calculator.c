//
// function 1: separating digit in an integer
// function 2: body mass index calculator
// 
// data: 8/29/2019
//

// pre-processor
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// forward declaration
void function1(int num);
void function2(float weight, float height);

int main(void) {
	int num; // number to separate
	float weight; // user's weight to calculate
	float height; // user's height to calculate

	// separating digit in an integer
	puts("Enter an integer");
	scanf("%d",&num);
	function1(num);
	
	// body mass index calculator
	puts("Enter your weight in kilograms");
	scanf("%f", &weight);
	puts("Enter your height in meter");
	scanf("%f", &height);
	function2(weight, height);


	return 0;
}

// Input a random integer, separate the number into its individual digits and prints
// the digits separated from one another by three spaces each.
// ex. Input: 42139, output: 4   2   1   3   9
void function1(int num) {
	char output[100] = "";
	int remainder;
	int len;

	printf("Input is: %d\n", num);
	while (num != 0) {
		remainder = num % 10;
\		snprintf(output + strlen(output), 100 - strlen(output), "%d ", remainder);
		num = (num - remainder) / 10;
	}
	printf("Output is: %s\n", output);
	puts("===================");

}

// formulas for calculating BMI is: 
//   BMI = weightInKilograms / (heightInMeters ^ 2)
void function2(float weight, float height) {
	float result = weight / (height * height);

	printf("\nYour Body Mass Index (BMI): %4f\n", result);
	puts("BMI Reference Value:");
	puts("Underweight: less than 18.5");
	puts("Normal: between 18.5 and 24.9");
	puts("Overweight: between 25 and 29.9");
	puts("Obese: 30 or greater");

}






