/*
 * Author: Surya Teja
 * Floor structure
 */

#include <stdlib.h>
#include <stdio.h>
#include "LList.h"
#include "Lift.h"

#ifndef FLOOR_H
#define FLOOR_H

typedef struct Floor_ Floor;
struct Floor_ {

	int number;
	int request_button[2];
	LList* queue;
	LList* in_floor;
	LList* stair_case;
		
};

// Function to initialise floor
Floor new_floor (int);

// Function to initialise all floors
void initialise_floors(Floor []);

// Function to print the details of a floor
void print_floor(Floor);

#endif // FLOOR_H

