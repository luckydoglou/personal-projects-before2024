/*
 * address_book.h
 *
 *  Created on: May 1, 2017
 *      Author: xhuang8
 */
#ifndef ADDRESS_BOOK_H_
#define ADDRESS_BOOK_H_
#define MAX 255

// contact struct
struct contactNode{
	char lastName[MAX];
	char firstName[MAX];
	char email[MAX];
	char phoneNumber[MAX];
	struct contactNode *nextPtr;
};
// contact pointer
typedef struct contactNode ContactNode;
typedef ContactNode *ContactNodePtr;

typedef struct list {
	ContactNodePtr pStart;
}List;

// function declaration
void addContact(int index, char *secondPara, List *pList);
void deleteContact(int index, List *myList);
void getOneContact(int index, List *myList);
void getField(int index, char *secondPara, List *myList);

int numberOfContacts(List *myList);
void loadFile(char filePath[], List *myList);
void saveFile(char *filePath, List *myList);

void editField(int index, char *secondPara, char *newValue, List *myList);
void selectionSortContact(List *myList);
void swap(ContactNodePtr p1, ContactNodePtr p2);
#endif /* ADDRESS_BOOK_H_ */
