//
// Hello World
//

#include <stdio.h>
#include <stdlib.h>

#define FUNC(x, y) x * x + y * y

// void to_upper(char* original);
//void func(int x);

// struct point_2d {
// 	int x;
// 	int y;
// };

int main() {

	int x = 3;
	int y = 5;
	printf("FUNC result: %d\n", FUNC(++x, ++y));

	// C Array with Pointer
	// char *p;
	// char ma[2][2];
	// ma[0][0] = 'a';
	// ma[0][1] = 'b';
	// ma[1][0] = 'c';
	// ma[1][1] = '\0';

	// p = ma;
	// while (*p) {
	// 	printf("%c", *p);
	// 	p++;
	// }
	// puts("");

	//=====
	// Pointer with 'const'
	// const int i = 5;
	// int *j;

	// j = &i;
	// *j = *j + 2;

	// printf("i is %d\n", i);

	//=====
	// pass by value
	// int x;

	// x = 0;
	// printf("x is %d\n", x);
	// func(x);
	// printf("x is %d\n", x);

	//=====
	// struct initialize
	// struct point_2d* data[5];
	// for (int i = 0; i < 5; i++) {
	// 	struct point_2d* tmp = (struct point_2d*) malloc(sizeof(struct point_2d));
	// 	tmp->x = i;
	// 	tmp->y = i * i;
	// 	data[i] = tmp;
	// }
	// for (int i = 0; i < 5; i++) {
	// 	printf("Point #%d, %d, %d\n", i, data[i]->x, data[i]->y);
	// }

	//=====
	// pointer size
	// char *charPtr;
	// int *intPtr;
	// char x = 50; // ASCII "2"

	// printf("char: %c\n", x);
	// printf("size of char ptr size: %d\n", sizeof(charPtr));
	// printf("size of int ptr size: %d\n", sizeof(intPtr));
	// printf("size of int size: %d\n", sizeof(int));
	// printf("size of char size: %d\n", sizeof(char));

	//
	// float x = 3.0f;
	// printf("%f", x);
	// to_upper("hello world");

	return 0;
}

// void to_upper(char* original) {
// 	char *capstr;
// 	unsigned int i;
// 	capstr = original;
// 	printf("%c\n", capstr[2]);
// }

// void func(int x) {
// 	x = x + 5;
// 	printf("func, x is %d\n", x);
// }