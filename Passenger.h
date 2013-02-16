/*
 * Author: Surya Teja
 * Passenger structure
 */

#ifndef PASSENGER_H
#define PASSENGER_H
#include <stdlib.h>
#include <stdio.h>
#define PEOPLE_COUNT 100

typedef struct Passenger_ Passenger;
struct Passenger_ {

	int id;
	int age;
	int weight;
	int priority;
	int waited_time;
	int progress;
	int wait_time;
	int destination;
	int current_floor;
	int walking_speed;
		
};

// Function to generate a new passenger
Passenger generate_psgnr(int);

// Function to initialise the database with passengers
void initialise_psngrs(Passenger []);

// Function to print the details of passenger
void get_psngr_details(Passenger);

#endif // PASSENGER_H
