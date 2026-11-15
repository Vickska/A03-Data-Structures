/*
FILE          : A3.c
PROJECT       : SENG1050 - A03 – COMPARE SORTED LINKED LISTS WITH HASH TABLES  
PROGRAMMER    : Vicky Nyangoma Kamanyire
FIRST VERSION : 2026 - 11 - 15
DESCRIPTION:  This program compares the efficiency of searching a sorted linked list and a hash table

			  Link to Github repository:
*/
#pragma warning (disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// defining the constant bucket size
#define SIZE 127

//defining structs
typedef struct nameNode {
	char* name;
	struct nameNode* next;
} nameNode;

typedef struct hashTable {
	nameNode* Table[SIZE]
}hashTable;

//Function Prototypes
nameNode* initializeName(char* name);
struct nameNode* insertSorted(struct nameNode* head, char* name);

int main(void) {

	return 0;
}


// METHOD : initializeName()
// DESCRIPTION: 
//      This function initializes a new node to store a name
// PARAMETERS:
//	   char* name: the name being added to a node
// RETURNS:
//		nameNode* node: the new node containing the name
nameNode* initializeName(char* name) {

	//allocating memory for the nameNode
	nameNode* node = (nameNode*)malloc(sizeof(nameNode));

	// if there is no memory, null is returned
	if (node == NULL) {
		printf("Memory allocation failed");
		return NULL;
	}

	//allocating memory for the name string
	node->name = malloc(strlen(name) + 1);

	// if there is no memory, the node memory is freed and null is returned
	if (node->name == NULL) {
		free(node);
		return NULL;
	}

	// updating the node info
	strcpy(node->name, name);
	node->next = NULL;

	return node;
}

// METHOD : insertSorted()
// DESCRIPTION: 
//      This function inserts a new nameNode into a list in its correct alphabetical position
// PARAMETERS:
//	   char* name: the name being added
// RETURNS:
//		nameNode* head: the head of the list being inserted to
struct nameNode* insertSorted(struct nameNode* head, char* name) {

	//creating a node to store new names
	nameNode* newName = initializeName(name);

	//inserting at the beginning of the list
	if (head == NULL || (strcmp(newName->name, head->name) < 0)) {
		newName->next = head;
		head = newName;

	}
	//inserting in the middle/end of the list
	else {
		struct nameNode* current = head;
		struct nameNode* previous = NULL;

		// traversing the list while the current name is still alphabetically less than the new name
		while (current != NULL && strcmp(current->name, newName->name) < 0) {
			previous = current;
			current = current->next;
		}

		//updating the list once a spot has been found
		previous->next = newName;
		newName->next = current;
	}

	//returning the head of the list
	return head;
}

