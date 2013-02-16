/**
  * File containing function definitions of passenger structure
  * Author: Surya Teja
  * Passenger structure (Implementation)
  */

#include "Lift.h"
#include "Passenger.h"
#include <stdlib.h>
#include <stdio.h>

/**
  * Function to initialise a passenger
  * Parameter : int identity
  * Return    : passenger p
  */
  
Passenger generate_psgnr (int identity) {

	Passenger p;
	p.id = identity;
	//p.age = 10 + rand()%60;
	p.current_floor = 0;
	//p.priority = 1 + rand()%5;
	//p.weight = (p.age < 18) ? 30 + rand()%20 : 45 + rand()%40;
	p.wait_time = 25+rand()%15;
	p.waited_time = 0;
	p.walking_speed = 20+rand()%10;
	p.destination = -1;
	p.progress = 0;

	return p;
}

/**
  * Function to initialise the list of passengers
  * Parameter : passengers array
  * Return    : void
  */
  
void initialise_psngrs(Passenger p[PEOPLE_COUNT]) {
	int i;
	for( i = 0; i < PEOPLE_COUNT; i++ ) {
		p[i] = generate_psgnr(i+1);
	}
}

/**
  * Function to print the details of passenger
  * Parameters : passenger p
  * Return     : void
  */

void get_psngr_details(Passenger p) {

	printf("Id : %d, Age : %d, Weight : %d\n", p.id, p.age, p.weight);
	printf("Priority : %d, Curr_floor : %d, ", p.priority, p.current_floor);
	printf("Wait time : %d\n" , p.wait_time);
	printf("Walk speed : %d\n", p.walking_speed);

}
