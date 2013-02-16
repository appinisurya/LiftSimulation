/**
 * File containing definitions of functions of floor structure
 * Author: Surya Teja
 * Floor structure (Implementation)
 */

#include "Floor.h"
#include <stdlib.h>
#include <stdio.h>

/**
  * Function to initialise a floor
  * Parameter : int floor_number
  * Return    : floor structure
  */
  
Floor new_floor (int floor_number) {
	
	Floor f;
	f.number = floor_number;
	f.request_button[0] = 0;
	f.request_button[1] = 0;
	f.queue = llist_new();
	f.in_floor = llist_new();
	f.stair_case = llist_new();

	return f;
}

/**
  * Function to initialise all floors in the building
  * Parameter : array of floors
  * Return    : void
  */
  
void initialise_floors(Floor floors[NUM_OF_FLOORS]){
	
	int floor_num;
	for( floor_num = 0; floor_num < NUM_OF_FLOORS; floor_num++ ) {
		floors[floor_num] = new_floor(floor_num);
	}
	
}

/**
  * Function to print the details of a floor
  * Parameter : floor structure
  * Return    : void
  */
  
void print_floor(Floor f) {

	printf("Floor : %d", f.number);
	printf("Requests (up : down) : %d : %d\n", f.request_button[0], f.request_button[0]);
	printf("Queue : ");
	llist_print(f.queue);
	printf("\nIn the floor : ");
	llist_print(f.in_floor);

}	
