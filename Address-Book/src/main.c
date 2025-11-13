/*
 * main.c
 *
 *  Created on: May 1, 2017
 *      Author: xhuang8
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "address_book.h"

int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0); // turn off output buffering

	// variables
	char buffer[BUFSIZ + 1];
	char command[BUFSIZ + 1];
	int index;
	char firstPara[BUFSIZ + 1];
	char secondPara[BUFSIZ + 1];
	char newValue[BUFSIZ + 1]; // new value for editing filed
	char filePath[BUFSIZ + 1]; // input file name to load or save

	// create a empty list
	List myList;
	myList.pStart = NULL;

	printf("Ready\n");
	fgets(command, BUFSIZ, stdin);
	while (command[0] != 'q') {
		switch (command[0]) {
		case 'a':
			// add a new contact (four fields)
			index = atoi(fgets(buffer, BUFSIZ, stdin));
			fgets(firstPara, BUFSIZ, stdin);
			addContact(index, firstPara, &myList);
			break;
		case 'd':
			// delete a contact
			index = atoi(fgets(buffer, BUFSIZ, stdin));
			deleteContact(index, &myList);
			break;

		case 'g':
			// get a 0-based contact, output all four fields, if the ndx if higher, warn user
			index = atoi(fgets(buffer, BUFSIZ, stdin));
			getOneContact(index, &myList);
			break;
		case 'f':
			// get a 0-based contact specific field
			index = atoi(fgets(buffer, BUFSIZ, stdin));
			fgets(secondPara, BUFSIZ, stdin);
			getField(index, secondPara, &myList);
			break;

		case 'n':
			// get the number of contacts in the list
			printf("%d\n", numberOfContacts(&myList));
			break;
		case 'l':
			// load information from a .CSV file
			fgets(filePath, BUFSIZ, stdin);
			loadFile(filePath, &myList);
			break;
		case 's':
			// save the contacts to a .CVS file, overwritten if it already exist
			fgets(filePath, BUFSIZ, stdin);
			saveFile(filePath, &myList);
			break;
		case 'e':
			// edit the specific field in a contact
			index = atoi(fgets(buffer, BUFSIZ, stdin));
			fgets(secondPara, BUFSIZ, stdin);
			fgets(newValue, BUFSIZ, stdin);
			editField(index, secondPara, newValue, &myList);
			break;
		case 'o':
			// sorting the file
			selectionSortContact(&myList);
			break;
		default:
			puts("Please enter correct command: ");
		}
		fgets(command, BUFSIZ, stdin);
	}
	printf("Complete\n");
	return EXIT_SUCCESS;
}
