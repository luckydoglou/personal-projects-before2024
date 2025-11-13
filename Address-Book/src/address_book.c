/*
 ============================================================================
 Name        : XHuangAddressBook.c
 Author      : Xiaolou Huang (Lor)
 Version     :
 Copyright   : Sping 2017
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "address_book.h"

void addContact(int index, char *secondPara, List *myList) {
	//variables
	char lastName[255];
	char firstName[255];
	char email[255];
	char phoneNumber[255];

	// separate the string into different pieces
	strcpy(lastName, strtok(secondPara, ","));
	strcpy(firstName, strtok(NULL, ","));
	strcpy(email, strtok(NULL, ","));
	strcpy(phoneNumber, strtok(NULL, "\n"));

	// pointers
	ContactNodePtr newNodePtr;
	ContactNodePtr previousNodePtr; // pointer to previous node in list
	ContactNodePtr currentNodePtr; // pointer to current node in list

	newNodePtr = (ContactNodePtr) malloc(sizeof(ContactNode)); // create a new node
	if (newNodePtr) {

		// assign the values into new node
		strcpy(newNodePtr->lastName, lastName);
		strcpy(newNodePtr->firstName, firstName);
		strcpy(newNodePtr->email, email);
		strcpy(newNodePtr->phoneNumber, phoneNumber);
		newNodePtr->nextPtr = NULL;

		// initialize the pointers
		previousNodePtr = NULL;
		currentNodePtr = myList->pStart;

		if (currentNodePtr == NULL) { // insert in an empty list
			myList->pStart = newNodePtr;
		} else {
			// find the right place to insert
			int ndx;
			for (ndx = 0; ndx < index; ndx++) {
				previousNodePtr = currentNodePtr;
				currentNodePtr = currentNodePtr->nextPtr;
			}
			if (index == 0) { // insert a node at beginning of the list
				newNodePtr->nextPtr = myList->pStart;
				myList->pStart = newNodePtr;
			} else if (currentNodePtr == NULL) { // insert in the end of the list
				previousNodePtr->nextPtr = newNodePtr;
				newNodePtr->nextPtr = NULL;
			} else { // insert in the middle of the list
				previousNodePtr->nextPtr = newNodePtr;
				newNodePtr->nextPtr = currentNodePtr;
			}
		}
	} else {
		printf("Can't allocate it in memory\n");
	}
}
void deleteContact(int index, List *myList) {
	// pointers
	ContactNodePtr previousNodePtr; // pointer to previous node in list
	ContactNodePtr currentNodePtr; // pointer to current node in list
	ContactNodePtr tempNodePtr; // temporary node pointer

	// initialize pointers
	previousNodePtr = NULL;
	currentNodePtr = myList->pStart;

	if (index == 0 && currentNodePtr != NULL && currentNodePtr->nextPtr == NULL) { // delete the last remaining node in the list
		free(currentNodePtr);
		currentNodePtr = NULL; // assign the currentNodePtr to NULL, since there is nothing in the list anymore
		myList->pStart = NULL; // empty the list. (currentNodePtr is a local variable, so we have to assign myList->pStart to NULL)
	} else {
		if (currentNodePtr != NULL) {
			int ndx;
			for (ndx = 0; ndx < index; ndx++) { // find the index location
				previousNodePtr = currentNodePtr;
				currentNodePtr = currentNodePtr->nextPtr;
			}
			if (currentNodePtr->nextPtr == NULL) { // delete the tail of the list
				tempNodePtr = currentNodePtr;
				previousNodePtr->nextPtr = NULL;
				free(tempNodePtr);
				tempNodePtr = NULL;
			} else if (index == 0) { // delete the first node in the list
				tempNodePtr = currentNodePtr;
				myList->pStart = currentNodePtr->nextPtr;
				free(tempNodePtr);
				tempNodePtr = NULL;
			} else { // delete middle of the list
				tempNodePtr = currentNodePtr;
				previousNodePtr->nextPtr = currentNodePtr->nextPtr;
				free(tempNodePtr);
				tempNodePtr = NULL;
			}
		}
	}
}
void getOneContact(int index, List *myList) {
	ContactNodePtr previousNodePtr; // pointer to previous node in list
	ContactNodePtr currentNodePtr; // pointer to current node in list

	previousNodePtr = NULL;
	currentNodePtr = myList->pStart;
	// locate pointer to right place
	if (currentNodePtr != NULL) {
		int ndx;
		for (ndx = 0; ndx < index; ndx++) {
			previousNodePtr = currentNodePtr;
			currentNodePtr = currentNodePtr->nextPtr;
		}
		// print out the formatted contact
		if (index == 0) {
			fprintf(stdout, "%s,%s,%s,%s\n", currentNodePtr->lastName,
					currentNodePtr->firstName, currentNodePtr->email,
					currentNodePtr->phoneNumber);
		} else {
			fprintf(stdout, "%s,%s,%s,%s\n", currentNodePtr->lastName,
					currentNodePtr->firstName, currentNodePtr->email,
					currentNodePtr->phoneNumber);
		}
	} else {
		printf("The list is empty\n");
	}
}
void getField(int index, char *secondPara, List *myList) {
	ContactNodePtr previousNodePtr; // pointer to previous node in list
	ContactNodePtr currentNodePtr; // pointer to current node in list

	previousNodePtr = NULL;
	currentNodePtr = myList->pStart;
	// locate pointer to right place
	if (currentNodePtr != NULL) {
		int ndx;
		for (ndx = 0; ndx < index; ndx++) {
			previousNodePtr = currentNodePtr;
			currentNodePtr = currentNodePtr->nextPtr;
		}
	}
	// find beginning node of the list
	if (index == 0) {
		if (memcmp(secondPara, "lastName", 8) == 0) {
			fprintf(stdout, "%s\n", currentNodePtr->lastName);
		} else if (memcmp(secondPara, "firstName", 9) == 0) {
			fprintf(stdout, "%s\n", currentNodePtr->firstName);
		} else if (memcmp(secondPara, "email", 5) == 0) {
			fprintf(stdout, "%s\n", currentNodePtr->email);
		} else if (memcmp(secondPara, "phoneNumber", 11) == 0) {
			fprintf(stdout, "%s\n", currentNodePtr->phoneNumber);
		}
	} else { // find the middle node of the list
		if (memcmp(secondPara, "lastName", 8) == 0) {
			fprintf(stdout, "%s\n", currentNodePtr->lastName);
		} else if (memcmp(secondPara, "firstName", 9) == 0) {
			fprintf(stdout, "%s\n", currentNodePtr->firstName);
		} else if (memcmp(secondPara, "email", 5) == 0) {
			fprintf(stdout, "%s\n", currentNodePtr->email);
		} else if (memcmp(secondPara, "phoneNumber", 11) == 0) {
			fprintf(stdout, "%s\n", currentNodePtr->phoneNumber);
		}
	}
}
int numberOfContacts(List *myList) {
	int length = 0;
	const int CONTACT_LIMIT = 1000;
	ContactNodePtr currentNodePtr;

	currentNodePtr = myList->pStart;
	// locate ptr to right place
	while (currentNodePtr != NULL) {
		currentNodePtr = currentNodePtr->nextPtr;
		length++;
		if (length > CONTACT_LIMIT)
			break;
	}
	return length;
}
void loadFile(char filePath[], List *myList) {
	// variables
	char eachLine[BUFSIZ + 1];
	int length;
	int ndx = 0;

	// fix the problem of '\n' at the end of input and output file names
	length = strlen(filePath);
	filePath[length - 1] = '\0';
//	if (filePath[length - 1] = '\r') {
//		filePath[length - 1] = '\0';
//	}

	FILE *filePtr = fopen(filePath, "r");
	fgets(eachLine, BUFSIZ, filePtr); // first header line

	ContactNodePtr currentNodePtr;
	currentNodePtr = myList->pStart;

	// find the index of end of list
	while (currentNodePtr != NULL) {
		ndx++;
		currentNodePtr = currentNodePtr->nextPtr;
	}

	while (fgets(eachLine, BUFSIZ, filePtr)) {
		// get each line and store it into four variables
//		fgets(eachLine, BUFSIZ, filePtr);
		addContact(ndx, eachLine, *(&myList));
		ndx++;
	}
	fclose(filePtr);
}
void saveFile(char *filePath, List *myList) {
	int length;
	ContactNodePtr currentNodePtr;

	// fix the problem of '\n' at the end of input and output file names
	length = strlen(filePath);
	filePath[length - 1] = '\0';

	FILE *filePtr = fopen(filePath, "w");
	if (filePtr != NULL) {
		fprintf(filePtr, "lastName,firstName,email,phoneNumber\n"); // header line in file

		currentNodePtr = myList->pStart;

		while (currentNodePtr != NULL) {
			// write each node into file
			fprintf(filePtr, "%s,%s,%s,%s\n", currentNodePtr->lastName,
					currentNodePtr->firstName, currentNodePtr->email,
					currentNodePtr->phoneNumber);
			// move to the next node
			currentNodePtr = currentNodePtr->nextPtr;
		}
	} else {
		printf("Can't open the file");
	}
	fclose(filePtr);
}
void editField(int index, char *secondPara, char *newValue, List *myList) {
	ContactNodePtr currentNodePtr;
	currentNodePtr = myList->pStart;

	// handle the \n of the newValue input
	int length = strlen(newValue);
	newValue[length - 1] = '\0';

	// index is zero
	if (index == 0) {
		if (memcmp(secondPara, "lastName", 8) == 0) {
			strcpy(currentNodePtr->lastName, newValue);
		} else if (memcmp(secondPara, "firstName", 9) == 0) {
			strcpy(currentNodePtr->firstName, newValue);
		} else if (memcmp(secondPara, "email", 5) == 0) {
			strcpy(currentNodePtr->email, newValue);
		} else if (memcmp(secondPara, "phoneNumber", 11) == 0) {
			strcpy(currentNodePtr->phoneNumber, newValue);
		}
	} else {
		int ndx;
		for (ndx = 0; ndx < index; ndx++) {
			currentNodePtr = currentNodePtr->nextPtr;
		}
		if (memcmp(secondPara, "lastName", 8) == 0) {
			strcpy(currentNodePtr->lastName, newValue);
		} else if (memcmp(secondPara, "firstName", 9) == 0) {
			strcpy(currentNodePtr->firstName, newValue);
		} else if (memcmp(secondPara, "email", 5) == 0) {
			strcpy(currentNodePtr->email, newValue);
		} else if (memcmp(secondPara, "phoneNumber", 11) == 0) {
			strcpy(currentNodePtr->phoneNumber, newValue);
		}
	}
}

void selectionSortContact(List *myList) {
	ContactNodePtr start;
	ContactNodePtr traverse;
	ContactNodePtr min;

	start = myList->pStart;

	while (start->nextPtr) {
		min = myList->pStart;
		traverse = start->nextPtr;

		while (traverse) {
			/* Find minimum element from list */
			if (memcmp(min->lastName, traverse->lastName, 255) > 0) {
				min = traverse;
			} else if (memcmp(min->lastName, traverse->lastName, 255) == 0) {
				if (memcmp(min->firstName, traverse->firstName, 255) > 0) {
					min = traverse;
				} else if (memcmp(min->email, traverse->email, 255) == 0) {
					if (memcmp(min->email, traverse->email, 255) > 0) {
						min = traverse;
					} else if (memcmp(min->email, traverse->email, 255) == 0) {
						if (memcmp(min->phoneNumber, traverse->phoneNumber, 255)
								> 0) {
							min = traverse;
						}
					}
				}
			}
			traverse = traverse->nextPtr;
		}
		swap(start, min);			// Put minimum element on starting location
		start = start->nextPtr;
	}
}
void swap(ContactNodePtr p1, ContactNodePtr p2) {
	ContactNodePtr temp;
	temp = p2->nextPtr;
	p2->nextPtr = p1;
	p1->nextPtr = temp;
}
