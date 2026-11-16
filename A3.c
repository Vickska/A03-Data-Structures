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
struct nameNode* searchLinkedList(char* searchName, struct nameNode* linkedList, int* comparisonCount);
void searchForNameTwice(char* searchName, struct nameNode* hashTable[], int* comparisonCount[2], struct nameNode* linkedList);

int main(void) {

	//initializing the master list and hash table
	nameNode* masterList = NULL;
	hashTable* nameHashTable = initializeHashTable();

	//loading the names from the names.txt file
	loadNames("./names.txt", &masterList, nameHashTable);

	//creating variable to keep track of comparisons made
	int* comparisonCount[2] = {0};

	// creating searchName variable to store user-entered name, and searchNode to store found name
	char searchName[30];
	nameNode* searchNode = NULL;

	//Asking the user for a search name
	printf("Enter a name to be searched for: ");
	fgets(searchName, sizeof(searchName), stdin);

	// removing the newline character
	searchName[strcspn(searchName, "\n")] = '\0';

	//Searching both the linked list and hash table
	searchForNameTwice(searchName, nameHashTable->Table, &comparisonCount, masterList);

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


// FUNCTION : searchLinkedList()
// DESCRIPTION: 
//      This function searches the sorted linked list for a name and 
//		returns a pointer to the node containing the name if found, or null if not.
// PARAMETERS:
//		char* searchName: the name being searched for
//		struct nameNode* linkedList: the master list being searched
//		int* comparison count: pointer to the int containing number of strcmp comparisons done
// RETURNS:
//		int hashNum: the bucket number of the name
struct nameNode* searchLinkedList(char* searchName, struct nameNode* linkedList, int* comparisonCount) {

	//storing the head of the linked list in a variable
	nameNode* current = linkedList;

	// creating a node to store the name if found
	nameNode* foundNode = NULL;

	//setting the comparison count to zero
	*comparisonCount = 0;

	// traversing through the list until the name is found
	while (current != NULL) {

		// incrementing the comparison count
		(*comparisonCount)++;

		//comparing the names
		int result = strcmp(current->name, searchName);

		// if the result is 0, the name has been found
		if (result == 0) {
			foundNode = current;
			return foundNode;
		}

		//since the list is sorted, if the result is a number greater than zero,
		// the current name has surpassed where the searchName would've been in the list
		// so the name hasn't been found
		if (result > 0) {

			return foundNode;
		}
		
		current = current->next;
	}

	return NULL;
}

// FUNCTION : searchForNameTwice()
// DESCRIPTION: 
//      This function searches the name hash table for a name twice 
// PARAMETERS:
//		char* searchName: the name being searched for
//		struct nameNode* hashTable[]: the hash table being searched
//		int* comparisoncount[2]: array containing the count of strcmp comparisons done
//								  in searching the sorted linked list (element 0) and 
//								  the hash table (element 1)  
 //		struct nameNode* linkedList: the master list being searched
// RETURNS:
//		None.
void searchForNameTwice(char* searchName, struct nameNode* hashTable[], int* comparisonCount[2], struct nameNode* linkedList) {

	//setting comparison counts to 0
	comparisonCount[0] = 0;
	comparisonCount[1] = 0;

	//searching for the name in the linked list
	nameNode* foundNode = searchLinkedList(searchName, linkedList, &comparisonCount[0]);

	//printing the results
	if (foundNode != NULL) {
		printf("\t %s was found in the linked List in %d comparisons\n", searchName, comparisonCount[0]);
	}
	else {
		printf("\t %s was NOT found in the linked List in %d comparisons\n", searchName, comparisonCount[0]);
	}

	//getting the hash bucket for the name
	int bucket = hash(searchName);

	//searching for the name in the hash table
	foundNode = searchLinkedList(searchName, hashTable[bucket], &comparisonCount[1]);

	//printing the results
	if (foundNode != NULL) {
		printf("\t %s was found in the hash table bucket in %d comparisons\n", searchName, comparisonCount[1]);
	}
	else {
		printf("\t %s was NOT found in the hash table bucket in %d comparisons\n", searchName, comparisonCount[1]);
	}
	
}