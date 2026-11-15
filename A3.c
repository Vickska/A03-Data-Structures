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
	struct nameNode* nextName;
} nameNode;

typedef struct hashTable {
	nameNode* Table[127]
}hashTable;


int main(void) {

	return 0;
}

