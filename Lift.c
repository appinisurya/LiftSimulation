/**
  * File containing definitions of functions of lift structure
  * Author: Surya Teja
  * Lift structure (Implementation)
  */

#include "Lift.h"
#include <stdio.h>
#include <stdlib.h> 		

/**
  * Function to initialise a lift
  * Parameter : -
  * Return    : lift l
  */
  
Lift* create_lift() {

	int floor_num;
	Lift* l = (Lift*)malloc(sizeof(Lift));;

	l->current_floor = 0;
	l->people = llist_new();
	l->direction = 1;
	l->max_limit = 8;
	l->dests = llist_new();
	l->counter = 0;
	l->max_count = 5;
	l->destination = 0;

	for( floor_num = 0; floor_num < NUM_OF_FLOORS; floor_num++ ) {
		l->panel[floor_num] = 0;
	}

	return l;
}

/**
  * Function to print the details of a lift
  * Parameter : pointer to the lift l
  * Return    : void
  */
  
void print_lift(Lift* l) {

	printf("Lift Floor : %d, Direction : %d\n", l->current_floor, l->direction);
	printf("Max limit : %d\n In lift : ", l->max_limit);
	llist_print(l->people);
	printf("\n");

}
