/*
 * Author: Surya Teja
 * Linked list data structure
 */

#ifndef LLIST_H
#define LLIST_H
#include <stdbool.h>

// Node for the link list
typedef struct Node_ Node;
struct Node_ {
    int data;
    Node* next;
};

// Create a new node with data and next element (can be NULL)
Node* node_new( int data, Node* next );

// Link list structure
typedef struct LList_ {
    Node* head;
} LList;

// Create an empty list (head shall be NULL)
LList* llist_new();

// Traverse the linked list and return its size
int llist_size( LList* lst );

// Traverse the linked list and print each element
void llist_print( LList* lst );

int llist_get( LList* lst, int idx );

void llist_set( LList* lst, int idx, int data	);

bool llist_search( LList * lst, int key );

// Add a new element at the end of the list
LList* llist_append( LList* lst, int data );
// Add a new element at the beginning of the list
LList* llist_prepend( LList* lst, int data );
// Add a new element at the @idx index
LList* llist_insert( LList* lst, int idx, int data );
// Generates a new random list
LList* gen_randlist(int i, int j);
// Remove an element from the end of the list
LList* llist_remove_last( LList* lst );
// Remove an element from the beginning of the list
LList* llist_remove_first( LList* lst );
// Remove an element from an arbitrary position in the list
LList* llist_remove( LList* lst, int idx );

#endif // LLIST_H

