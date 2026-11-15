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
	nameNode* Table[SIZE];
}hashTable;

//Function Prototypes
nameNode* initializeName(char* name);
struct nameNode* insertSorted(struct nameNode* head, char* name);
hashTable* initializeHashTable();
int hash(char* name);
void loadNames(char* filename, struct nameNode** list, struct hashTable* nHashTable);

int main(void) {

	//initializing the master list and hash table
	nameNode* masterList = NULL;
	hashTable* nameHashTable = initializeHashTable();

	//loading the names from the names.txt file
	loadNames("./names.txt", &masterList, nameHashTable);

	return 0;
}


// FUNCTION : initializeName()
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
		printf("Memory allocation failed.\n");
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

// FUNCTION : initializeHashTable()
// DESCRIPTION: 
//      This function initializes the hash table and all its buckets
// PARAMETERS:
//		None.
// RETURNS:
//		hashTable* nameHashTable: the initialized hash table
hashTable* initializeHashTable() {
	
	//allocating memory for the hash table
	hashTable* nameHashTable = (hashTable*)malloc(sizeof(hashTable));

	// if memory allocation fails, an error is shown
	if (nameHashTable == NULL) {
		printf("Memory allocation failed.\n");
		exit(1);
	}

	// going through each bucket in the hash table and setting its head to NULL
	for (int i = 0; i < SIZE; i++) {
		nameHashTable->Table[i] = NULL;
	}

	// returning the hash table
	return nameHashTable;
}

// FUNCTION : insertSorted()
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

		// traversing the list while the current name is still alphabetically less than or equal to the new name
		while (current != NULL && strcmp(current->name, newName->name) <= 0) {
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

// FUNCTION : hash()
// DESCRIPTION: 
//      This function hashes a name and gets its bucket number
// PARAMETERS:
//		char* name: the name being inserted into the hash table
// RETURNS:
//		int hashNum: the bucket number of the name
int hash(char* name) {

	int hashNum = 0;

	// getting the sum of all characters in the name
	for (int i = 0; i < name[i] != '\0'; i++) {
		hashNum = hashNum + name[i];
	}

	// getting the remainder of the sum divided by the bucket size
	hashNum = hashNum % SIZE;

	// returning the bucket number
	return hashNum;

}

// FUNCTION : loadNames()
// DESCRIPTION: 
//      This function loads the names from a file and sorts them into the master list and the name hash table
// PARAMETERS:
//		char* filename: the filename containing the names
//		struct nameNode** list: pointer to the head of the master list
//		struct hashTable* nHashTable: the name hash table
// RETURNS:
//		None.
void loadNames(char* filename, struct nameNode** list, struct hashTable* nHashTable) {

	//Opening the name file to read from
	FILE* file = fopen(filename, "r");

	if (file == NULL) {
		printf("Error opening file");
		exit(1);
	}

	//creating a buffer to only receive 30 characters max
	char buffer[31];
	while (fgets(buffer, sizeof(buffer), file)) {

		// removing the new line character from the end of the read line
		buffer[strcspn(buffer, "\n")] = '\0';

		//inserting in the master list
		 *list = insertSorted(*list, buffer);

		//inserting into the hash tables
		int bucket = hash(buffer);
		nHashTable->Table[bucket] = insertSorted(nHashTable->Table[bucket], buffer);

	}
	//closing the file once all names are read
	fclose(file);

}