/**
  * Program to simulate the working of pair of elevators
  * Author: Surya Teja
  * Main file - Lift simulation
  * File : main.c
  */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Lift.h"
#include "LList.h"
#include "Floor.h"
#include "Passenger.h"

// Database - Containing the structures of floors and people

Floor floors[NUM_OF_FLOORS];
Passenger psngrs[PEOPLE_COUNT];

void queue_to_lift ( Lift* l );
void lift_to_floor ( Lift* l );
void floor_to_queue ( int floor_idx );
void set_destinations ( LList* lst );
void update_waiting_ppl ( );
void update_walker( );
void set_lift_destination( Lift* lift1, Lift* lift2 );
void move_lift( Lift* lift1 );
void print_simulation( Lift *elev1, Lift *elev2 );

int main() {

	srand(time(NULL));

	int index = 1, i, floor_num;

	Lift* elev1 = create_lift();
	Lift* elev2 = create_lift();

	initialise_floors(floors);
	initialise_psngrs(psngrs);

	floors[0].in_floor = gen_randlist(15,30);
	printf("\nInitial people : ");
	llist_print(floors[0].in_floor);
	printf("\n");				

	while(1) {

		for( floor_num = 0; floor_num < NUM_OF_FLOORS; floor_num++ ) { 
			int t = 1;	//rand()%2;
			if(t) {
				floor_to_queue(floor_num);
				set_destinations(floors[floor_num].queue);	
			}
		}

		set_lift_destination( elev1, elev2 );
		set_lift_destination( elev2, elev1 );

		if(elev1->counter == elev1->max_count) {
			move_lift(elev1);
			if(elev1->current_floor == elev1->destination) {

				elev1->panel[elev1->current_floor] = 0;
				floors[elev1->current_floor].request_button[(elev1->direction+1)/2] = 0;

				if(elev1->current_floor == NUM_OF_FLOORS-1) {
					floors[elev1->current_floor].request_button[0] = 0;
				}
				
				else if (elev1->current_floor == 0) {
					floors[elev1->current_floor].request_button[1] = 0;
				}
				
				lift_to_floor(elev1);

			}
			elev1->counter = 0;
		}

		if(elev2->counter == elev2->max_count) {
			move_lift(elev2);
			if(elev2->current_floor == elev2->destination){

				elev2->panel[elev2->current_floor] = 0;
				floors[elev2->current_floor].request_button[(elev2->direction+1)/2] = 0;

				if(elev2->current_floor == NUM_OF_FLOORS-1) {
					floors[elev2->current_floor].request_button[0] = 0;
				}
				
				else if (elev2->current_floor == 0) {
					floors[elev2->current_floor].request_button[1] = 0;
				}
				
				lift_to_floor(elev2);	

			}
			elev2->counter = 0;
		}

		if(elev1->counter == 0) {
			queue_to_lift(elev1);
		}

		if(elev2->counter == 0) {
			queue_to_lift(elev2);
		}

		elev1->counter++;
		elev2->counter++;

		update_waiting_ppl();
		update_walker();

		elev1->dests = llist_new();
		elev2->dests = llist_new();
		print_simulation(elev1, elev2);
		sleep(1);
	//	getchar();
	}

	return 0;

}

/**
  * Function to print the current status of the elevators
  * Parameters : Pointer to lift 1 and 2
  * Return     : void
  */
  
void print_simulation(Lift *elev1, Lift *elev2)	{

	int iter, floor_num;
	LList* lst;

	for( floor_num = 0; floor_num < NUM_OF_FLOORS; floor_num++ ) { 
		printf("floor %d : in_floor ", floor_num);
		llist_print(floors[floor_num].in_floor);
		printf("        : queue    ", floor_num);
		llist_print(floors[floor_num].queue);
		printf("        : stairs   ", floor_num);
		
		for( iter = 0; iter < llist_size(floors[floor_num].stair_case); iter++ )	{
			printf("%d (%d,%d)  ", llist_get(floors[floor_num].stair_case,iter),
			 psngrs[llist_get(floors[floor_num].stair_case,iter)].current_floor,
			 psngrs[llist_get(floors[floor_num].stair_case,iter)].destination );
		}
		
		printf("\n\n");
	}
	
	printf("\n");
	printf("In lift 1 at %d floor: ", elev1->current_floor);
	llist_print(elev1->people);

	printf("In lift 2 at %d floor: ", elev2->current_floor);
	llist_print(elev2->people);

	printf("\n");
	printf("Lift 1 panel : ");
	for(floor_num = 0; floor_num < NUM_OF_FLOORS; floor_num++ ) {
		printf("%d ", elev1->panel[floor_num]);
	}
	printf("\n");

	printf("Lift 2 panel : ");
	for(floor_num = 0; floor_num < NUM_OF_FLOORS; floor_num++ ) {
		printf("%d ", elev2->panel[floor_num]);
	}
	printf("\n\n");
	printf("Lift 1 destination : %d\n", elev1->destination);
	printf("Lift 2 destination : %d\n", elev2->destination);

}

/**
  * Function to move the lift and update its current floor
  * Parameters : pointer to lift lift1
  * Return     : void
  */
  
void move_lift( Lift *lift1 ) {

	if(lift1->destination > lift1->current_floor ) {
		lift1->current_floor++;
		if(lift1->current_floor == NUM_OF_FLOORS-1) {
			lift1->direction = -1;
		}
	}

	else if(lift1->destination < lift1->current_floor ) {
		lift1->current_floor--;
		if(lift1->current_floor == 0) {
			lift1->direction = 1;
		}
	}

}

/**
  * Function to set the next immediate destination of lift 
  * Parameters : pointers to the lifts lift1 and lift2
  * Return     : void
  */

void set_lift_destination( Lift* lift1, Lift* lift2 ) {

	int floor_num;
	int flag = 0;

	if(lift1->direction == 1) {

		for( floor_num = lift1->current_floor + 1; floor_num < NUM_OF_FLOORS; floor_num++ ) {
			if(((lift1->panel)[floor_num] == 1) || ((!llist_search(lift2->dests, floor_num)) && (floors[floor_num].request_button[1] == 1))) {

				if(flag == 0) {
					lift1->destination = floor_num;
					lift1->direction = 1;
					flag = 1;
				}

				llist_append(lift1->dests, floor_num);
			}
		}

		for( floor_num = NUM_OF_FLOORS-1; floor_num >= 0 && flag == 0; floor_num-- ) {
			if((floor_num != lift1->current_floor) && (((lift1->panel)[floor_num] == 1) 
			 || (!llist_search(lift2->dests, floor_num) && (floors[floor_num].request_button[0] == 1)))) {

				lift1->destination = floor_num;
				flag = 1;

				if(floor_num>lift1->current_floor) {
					lift1->direction = 1;
				}

				else {
					lift1->direction = -1;
				}

				llist_append(lift1->dests, floor_num);
				break;
			}
		}


		for( floor_num = 0; floor_num < lift1 -> current_floor && flag == 0; floor_num++ ) {
			if(!llist_search(lift2->dests, floor_num)) {
				if(floors[floor_num].request_button[1] == 1) {
					lift1->destination = floor_num;
					flag = 1;
					lift1->direction = -1;
					llist_append(lift1->dests, floor_num);
					break;
				}
			}

		}
	}

	else {

		for( floor_num = lift1->current_floor - 1; floor_num >= 0; floor_num-- ) {
			if(((lift1->panel)[floor_num] == 1) || (!llist_search(lift2->dests, floor_num) && (floors[floor_num].request_button[0] == 1))) {

				if(flag == 0) {
					lift1->destination = floor_num;
					lift1->direction = -1;
					flag = 1;
				}

				llist_append(lift1->dests, floor_num);
			}
		}

		for( floor_num = 0; floor_num < NUM_OF_FLOORS && flag == 0; floor_num++ ) {
			if((floor_num != lift1->current_floor) && (((lift1->panel)[floor_num] == 1)  
			|| (!llist_search(lift2->dests, floor_num) && (floors[floor_num].request_button[1] == 1)))) {
				lift1->destination = floor_num;
				flag = 1;

				if(floor_num > lift1->current_floor) {
					lift1->direction = 1;
				}

				else {
					lift1->direction = -1;
				}

				llist_append(lift1->dests, floor_num);			
				break;
			}
		}


		for( floor_num = NUM_OF_FLOORS - 1; floor_num >  lift1 -> current_floor && flag == 0; floor_num-- ) {
			if(!llist_search(lift2->dests, floor_num)) {
				if(floors[floor_num].request_button[0] == 1) {
					lift1->destination = floor_num;
					flag = 1;
					lift1->direction = 1;
					llist_append(lift1->dests, floor_num);
					break;
				}
			}
		}

	}
}

/** 
  * Function to check for the waiting tolerance of people
  * Parameters : -
  * Return     : void
  */
  
void update_waiting_ppl ( ) {

	int floor_num, iter, t;
	int id;
	Passenger p;

	for( floor_num = 0; floor_num < NUM_OF_FLOORS; floor_num++ ) {
		for( iter = 0; iter < llist_size( floors[floor_num].queue ); iter++ ) {

			id = llist_get(floors[floor_num].queue, iter);
			t = psngrs[id].waited_time++;
			p = psngrs[id];

			if(t > p.wait_time) {

				if(p.destination > p.current_floor) { 
					llist_append(floors[floor_num].stair_case, id);
				}
				else {
					llist_append(floors[floor_num-1].stair_case, id);
				}

				llist_remove(floors[floor_num].queue, iter);
				iter--;
			}
		}
	}
}

/**
  * Function to update the status of people walking in staircase
  * Parameters : -
  * Return     : void
  */
  
void update_walker () {

	int floor_num, iter, walk_progress;
	Passenger p;
	int id;

	for( floor_num = 0; floor_num < NUM_OF_FLOORS; floor_num++ ) {
		LList* lst = floors[floor_num].queue;
		for( iter = 0; iter < llist_size( floors[floor_num].stair_case ); iter++ ) {

			id = llist_get(floors[floor_num].stair_case , iter);
			p = psngrs[id];
			walk_progress = psngrs[id].progress++;

			if(walk_progress >= p.walking_speed) {
				psngrs[id].progress = 0;

				if(p.destination > psngrs[id].current_floor) { 
					psngrs[id].current_floor++;
				}
				else if(p.destination < psngrs[id].current_floor) {
					psngrs[id].current_floor--;
				}

				if(p.destination == psngrs[id].current_floor) {
					llist_append(floors[psngrs[id].current_floor].in_floor, id);
					psngrs[id].destination = -1;
					psngrs[id].waited_time = 0;
				}
				else {
					llist_append(floors[psngrs[id].current_floor].queue, id);
				}

				llist_remove(floors[floor_num].stair_case, iter);
				iter--;
			}

		}
	}

}

/**
  * Function to set destination of people in waiting queue
  * Paramters : LList* lst which is the waiting queue
  * Return    : void
  */
  
void set_destinations( LList* lst ) {

	int iter;

	for( iter = 0; iter < llist_size(lst); iter++ ) {

		if(psngrs[llist_get(lst,iter)].destination == -1) {
			psngrs[llist_get(lst,iter)].destination = (psngrs[llist_get(lst,iter)].current_floor + 1 + rand()%(NUM_OF_FLOORS-1))%(NUM_OF_FLOORS);
			int t = psngrs[llist_get(lst,iter)].destination > psngrs[llist_get(lst,iter)].current_floor ? 1 : 0;
			(floors[psngrs[llist_get(lst,iter)].current_floor]).request_button[t] = 1;
		}

	}

	return;
}

/**
  * Function to move people from waiting queue to lift
  * Parameters : Pointer to the lift l
  * Return     : void
  */
  
void queue_to_lift ( Lift* l ) {

	int data;
	int iter;
	LList* lst = floors[l->current_floor].queue;

	for( iter = 0; iter < llist_size(lst) && (llist_size(l->people) < l->max_limit); iter++ ) {

		data = llist_get(lst, iter);	

		if( ((psngrs[data]).destination - l->current_floor)*(l->direction) > 0 ) {

			(psngrs[data]).waited_time = 0;
			llist_append(l->people, data);
			llist_remove(lst, iter);
			(l->panel)[(psngrs[data]).destination] = 1;
			iter--;

		}

	}

	return;	
}

/**
  * Function to move people from lift to floor
  * Parameters : Pointer to lift l
  * Return     : void
  */
  
void lift_to_floor ( Lift* l ) {

	int data;
	int iter;

	for( iter = 0; iter < llist_size(l->people); iter++ ) {

		data = llist_get(l->people, iter);

		if(psngrs[data].destination == (l->current_floor)) {
			psngrs[data].destination = -1;
			psngrs[data].current_floor = l->current_floor;
			llist_append(floors[l->current_floor].in_floor, data);
			llist_remove(l->people, iter);
			iter--;
		}

	}

	return;	
}

/**
  * Function to move people in floor to waiting queue for lift
  * Parameters : floor index
  * Return     : void
  */
  
void floor_to_queue ( int floor_idx ) {

	int size;
	if(llist_size(floors[floor_idx].in_floor) > 0) {
		size = (2+rand()%3)*(llist_size(floors[floor_idx].in_floor))/(8);
	}
	else {
		size = 0;
	}

	int data, count;
	for( count = 0; count < size; count++ ) {

		int rand_idx = (rand()%llist_size(floors[floor_idx].in_floor));
		data = llist_get(floors[floor_idx].in_floor,rand_idx);

		llist_append(floors[floor_idx].queue, data);
		llist_remove(floors[floor_idx].in_floor, rand_idx);

	}	

	return;	 
}

