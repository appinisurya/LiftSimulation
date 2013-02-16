/*
 * Author: Surya Teja
 * Linked list data structure (Implementation)
 */

#include "LList.h"
#include "Passenger.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>	
	
Node* node_new( int data, Node* next )
{
 /**
   * Function to create a new node 
   * Parameters : Int data and a pointer to next node
   * Return     : Pointer to the node created
   */
   
	Node* new_node;
	new_node = (Node*)malloc(sizeof(Node));
	
	new_node -> data = data;
	new_node -> next = next;
	
	return new_node;
}

LList* llist_new()
{
 /**
   * Function to create a new list
   * Parameters : ---
   * Return     : Returns pointer to the new list
   */
   
	LList *new_list;
	new_list = (LList*)malloc(sizeof(LList));
	new_list -> head = NULL;
	return new_list;
}

LList* gen_randlist(int start, int end) {

 /**
   * Function to create a random list
   * Parameters : ---
   * Return     : Returns pointer to the random list
   */

	LList* lst = llist_new();
	int hash [PEOPLE_COUNT], i;
	int s, size;
	s = size = start + rand()%(end-start+1);

	for( i = 0; i < size; i++ ) {
		hash [i] = 0;		
	}

	int idx;
	
	while(size--) {	
		
		idx = rand()%(PEOPLE_COUNT);
		
		if(hash[idx] == 0)  {
			llist_append(lst,idx);
			hash[idx] = 1;
		}
		
		else {
			for(i = 1; i <= s; i++) {
				if(hash[(i+idx)%s] == 0) {
				llist_append(lst,(	i+idx)%s);
					hash[(i+idx)%s] = 1;
					break;
				}
			}
		}
	}
	
	return lst;
}

int llist_size( LList* list )
{
 /**
   * Function to find the size of the list
   * Parameters : Pointer to the list
   * Return     : Size of the list
   */
   
    int count = 0;
	Node* node;
	node = list -> head;
	while( node!= NULL )
	{
		node = node -> next;
		count++;
	}
	free( node );
	return count;
}

void llist_print( LList* list )
{
 /** 
   * Function to print the elements of the list
   * Parameters : Pointer to the list
   * Output     : Prints the list
   */
	
	Node * node;
	node = list -> head;
	
	while( node != NULL )
	{
		printf( "%d ", node -> data );
		node = node -> next;
	}
	free( node );
	printf( "\n" );
}

LList* llist_append( LList* lst, int data )
{ 
 /** 
   * Function to append an element to the list
   * Parameters : Pointer to the list and the data item to be appended
   * Return     : Returns the pointer to the appended list
   */
   
    if( lst -> head == NULL )
    	lst -> head = node_new( data, NULL );
    else
    {
        Node* node;
        node = lst -> head;
    	while( node -> next	!= NULL )
    		node = node -> next;

		node -> next = node_new( data, NULL );
	}
	
	return lst;
}

LList* llist_prepend( LList* lst, int data )
{
 /**
   * Function to prepend an element to the list
   * Parameters : Pointer to the list and the data item to be prepended
   * Return     : The pointer to the prepended list
   */
   
	Node* node;
	node = (Node*)malloc(sizeof(Node));
	node -> data = data;
	node -> next = lst -> head;
	lst -> head = node; 
	
	return lst;
}

LList* llist_insert( LList* lst,int idx, int data )
{
 /**
   * Function to insert a data item at idx location of the list
   * Parameters : Pointer to the list, the location and the data item to be inserted
   * Return     : Returns pointer to the modified list
   */
   
    int i;
    Node* node;
    node = lst -> head;   
    if( idx == 0 )
	    return llist_prepend( lst, data );
    
    for( i = 1; i < idx; i++ )
        node = node -> next;
    
    node -> next = node_new( data, node -> next );
    
    return lst;
}
	
LList* llist_remove_last( LList* lst )
{
 /**
   * Function to remove the last element from the list
   * Parameters : Pointer to the list
   * Return     : Returns the pointer to the modified list
   */
   
    Node* node;
    Node* node_prev;
    node_prev = (Node*)malloc(sizeof(Node));
    
    node = lst -> head;
    if( node -> next == NULL )
    {
    	lst -> head = NULL;
    	return lst;
	}
	
    while( node -> next != NULL )
    {
    	node_prev = node;
        node = node -> next;
    }
    
    free( node );
    node_prev -> next = NULL;
    
    return lst;
}

LList* llist_remove_first( LList * lst )
{
 /**
   * Function to remove the first element from the list
   * Parameters : Pointer to the list
   * Return     : Returns the pointer to the modified list
   */

    Node* node;
    node = lst -> head -> next;
    free( lst -> head );
    lst -> head = node;
    
    return lst;
}
    
LList* llist_remove( LList * lst, int idx )
{
 /**
   * Function to remove the element at idx location from the list
   * Parameters : Pointer to the list and position of the element to be removed
   * Return     : Returns the pointer to the modified list
   */
   
    int i;
    Node * node;
    node = lst -> head;
    if( idx == 0 )
    {
        lst -> head = node -> next;
        free( node );
        return lst;
    }
    
    for( i = 1; i < idx; i++ )
        node = node -> next;
    
    free( node -> next );
    node -> next = node -> next -> next;
    
    return lst;
}

bool llist_search( LList * lst, int key )
{
 /**
   * Function to search the element in the list
   * Parameters : Pointer to the list and the data element
   * Return : Returns found or not
   */
   
    int i;
    Node * node;
    
    if(lst == NULL) {
		return false;
	}
	
    node = lst -> head;
    while(node!=NULL){
        if(node->data == key)
        	return true;
        node = node -> next;
    }
    
    return false;
}

int llist_get( LList * lst, int idx )
{
 /**
   * Function to print the element at idx th location of the list
   * Parameters : Pointer to the list and location of the element to be printed
   * Return : Returns the idx th element
   */
   
    int i;
    Node * node;
    
    node = lst -> head;
    for ( i = 0; i< idx; i++ )
        node = node -> next;
	return node -> data;    
}

void llist_set( LList * lst, int idx, int set_data )
{
 /**
   * Function to set the element value at idx th location of the list
   * Parameters : Pointer to the list and location of the element to be printed
   * Return : ---
   */
   
    int i;
    Node * node;
   
    node = lst -> head;
    for ( i = 0; i< idx; i++ )
        node = node -> next;

	node -> data = set_data;    
}
