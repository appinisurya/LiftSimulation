/*
 * Author: Surya Teja
 * Lift structure
 */

#ifndef LIFT_H
#define LIFT_H
#include "LList.h"
#define NUM_OF_FLOORS 7

typedef struct Lift_ Lift;
struct Lift_ {

	int panel[NUM_OF_FLOORS];
	LList* people;              // List of identities of people
	int direction;
	int destination;
	int counter;
	int max_count;
	LList* dests;	
	int current_floor;
	int max_limit;              // Maximum number of people
	
};

// Function to create a new lift
Lift* create_lift();

// Function to print the details of lift
void print_lift(Lift*);

#endif // LIFT_H

