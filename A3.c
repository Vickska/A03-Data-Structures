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

int main(void) {

	return 0;
}


// METHOD : initializeName()
// DESCRIPTION: 
//      This function initializes a new node to store a name
// PARAMETERS:
//	   char* name: the name being added to a node
// RETURNS:
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

