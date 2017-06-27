/* 
 * CS61C Summer 2013
 * Name:
 * Login:
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "flights.h"
#include "timeHM.h"

struct flightSys {
    // Place the members you think are necessary for the flightSys struct here.
    airport_t* airportList;
};

struct  airport{
    // Place the members you think are necessary for the airport struct here.
    char* name;
    airport_t* next;
   flight_t* flightList;
};

struct flight {
    // Place the members you think are necessary for the flight struct here.
    airport_t* destination;
    timeHM_t departure;
    timeHM_t arrival;
    int cost;
    flight_t* next;
};

/*
   This should be called if memory allocation failed.
 */
static void allocation_failed() {
    fprintf(stderr, "Out of memory.\n");
    exit(EXIT_FAILURE);
}


/*
   Creates and initializes a flight system, which stores the flight schedules of several airports.
   Returns a pointer to the system created.
 */
flightSys_t* createSystem() {
    // Replace this line with your code
    flightSys_t* newSys = (flightSys_t*) malloc(sizeof(flightSys_t));
    if(!newSys) allocation_failed();
    else
     newSys->airportList = NULL;
    return newSys;
}


/* Given a destination airport, a departure and arrival time, and a cost, return a pointer to new flight_t. Note that this pointer must be available to use even
   after this function returns. (What does this mean in terms of how this pointer should be instantiated)?
*/

// Jiaping
flight_t* createFlight(airport_t* dest, timeHM_t dep, timeHM_t arr, int c) {
   // Replace this line with your code
   flight_t* newFlight = (flight_t*) malloc(sizeof(flight_t));
   //if(!newFlight) allocation_failed();
   //else{
       //newFlight->destination = (airport_t*) malloc(sizeof(airport_t));
      // if(!newFlight->destination) allocation_failed();
       newFlight->destination = dest;
       newFlight->departure = dep;
       newFlight->arrival = arr;
       if(c) newFlight->cost = c;
  // }
   return newFlight;
}

/*
   Frees all memory associated with this system; that's all memory you dynamically allocated in your code.
 */
 // Bowen
void deleteSystem(flightSys_t* s) {
    if (s==NULL) return;
    while (!(s->airportList)){
        airport_t * head=s->airportList;
        //free the memory allocated to airport
        while ((head->flightList)!=NULL){
            //free the memory allocated to flight
    	    flight_t* head2=head->flightList;
            head->flightList=head2->next;
            free(head2);
        }
        free(head->name);
        s->airportList=head->next;
        free(head);
    }
    free(s);
}


/*
   Adds a airport with the given name to the system. You must copy the string and store it.
   Do not store "name" (the pointer) as the contents it point to may change.
 */
// Jiaping
void addAirport(flightSys_t* s, char* name) {
    // Replace this line with your code
    if(name != NULL && s != NULL){
        airport_t* newAirport = (airport_t*) malloc(sizeof(airport_t));
        if(!newAirport){allocation_failed();}
        newAirport->name = malloc(sizeof(char)*(strlen(name)+1));
        if(!newAirport->name) {allocation_failed();}
        strcpy(newAirport->name, name); // use string copy to store contents
        newAirport->flightList = NULL;
        newAirport->next = NULL;
        airport_t* p = s->airportList;
        if(p == NULL) {s->airportList = newAirport;}
        else{
            while(p->next != NULL) p = p->next; // move pointer to the tail of linkedlist
            p->next = newAirport;
        }
    }
}


/*
   Returns a pointer to the airport with the given name.
   If the airport doesn't exist, return NULL.
 */
 
 //Jiaping
airport_t* getAirport(flightSys_t* s, char* name) {
    // Replace this line with your code
    if(name != NULL && s != NULL){
        airport_t* p = s->airportList;
        while(p!=NULL){
            if(!strcmp(p->name,name))
                return p;
            else
                p = p->next;
        }
    }
    return NULL;
}


/*
   Print each airport name in the order they were added through addAirport, one on each line.
   Make sure to end with a new line. You should compare your output with the correct output
   in flights.out to make sure your formatting is correct.
 */
 //Bowen
void printAirports(flightSys_t* s) {
    airport_t * a;
    airport_t * head=s->airportList;
    a=head;
    if (head!=NULL){
      while (a!= NULL){
        printf("%s",a->name);
        printf("\n");
        a=a->next;
      }
    }
    // Replace this line with your code
}


/*
   Adds a flight to src's schedule, stating a flight will leave to dst at departure time and arrive at arrival time.
 */
 // Bowen
void addFlight(airport_t* src, airport_t* dst, timeHM_t* departure, timeHM_t* arrival, int cost) {
    if (src!=NULL){
    	/**flight_t* newFlight=(flight_t* ) malloc(sizeof(flight_t));
        if (!newFlight){
    		allocation_failed();
        }
        newFlight->destination=dst;
        //newFlight->destination->next=NULL;
        //newFlight->destination->flightList=NULL;
        //newFlight->destination->name =(char*) malloc(sizeof(char)*(strlen(dst->name)+1));
    	newFlight->departure=*departure;
    	newFlight->arrival=*arrival;
    	newFlight->cost=cost;
        newFlight->next=NULL;*/
    	//strcpy(newFlight->destination->name,dst->name);
    	flight_t* newFlight=createFlight(dst,*departure,*arrival,cost);
        flight_t* head=src->flightList;
        if (head==NULL){
        	src->flightList=newFlight;
        }
        else{
        	while (head->next != NULL)
        		head=head->next;
            head->next = newFlight;
        }
    }
    // Replace this line with your code
}


/*
   Prints the schedule of flights of the given airport.

   Prints the airport name on the first line, then prints a schedule entry on each 
   line that follows, with the format: "destination_name departure_time arrival_time $cost_of_flight".

   You should use printTime (look in timeHM.h) to print times, and the order should be the same as 
   the order they were added in through addFlight. Make sure to end with a new line.
   You should compare your output with the correct output in flights.out to make sure your formatting is correct.
 */
 
 //Bowen
void printSchedule(airport_t* s) {
    if (s!=NULL){
    printf ("AIRPORT: %s",s->name);
    printf("\n");
    flight_t* a=s->flightList;
    while (a!= NULL){
        printf("%s ",a->destination->name);
        printTime(&a->departure);
        printf(" ");
        printTime(&a->arrival);
        printf(" ");
        printf("$%d\n",a->cost);
        a=a->next;
      }
    }
    // Replace this line with your code
}


/*
   Given a src and dst airport, and the time now, finds the next flight to take based on the following rules:
   1) Finds the cheapest flight from src to dst that departs after now.
   2) If there are multiple cheapest flights, take the one that arrives the earliest.

   If a flight is found, you should store the flight's departure time, arrival time, and cost in departure, arrival, 
   and cost params and return true. Otherwise, return false. 

   Please use the function isAfter() from time.h when comparing two timeHM_t objects.
 */
 //Bowen
bool getNextFlight(airport_t* src, airport_t* dst, timeHM_t* now, timeHM_t* departure, timeHM_t* arrival, int* cost) {
    if(!src || !dst) return false;
    flight_t *p=src->flightList;
    flight_t *nextFlight=NULL;
    bool flag=false;
    while (p!=NULL){
    	if (!strcmp(p->destination->name, dst->name) && isAfter(&(p->departure),now)){
    		flag = true;
            if(!nextFlight) nextFlight = p;   // first found flight that apply both rules
            else if(p->cost < nextFlight->cost) nextFlight = p;
            else if(p->cost == nextFlight->cost && isAfter(&(nextFlight->arrival),&(p->arrival))) nextFlight = p;
        }
        p = p->next;
    }
    if (nextFlight!=NULL){
  		*departure=nextFlight->departure;
   		*arrival=nextFlight->arrival;
   		*cost=nextFlight->cost;
   	}
    return flag;
}

/* Given a list of flight_t pointers (flight_list) and a list of destination airport names (airport_name_list), first confirm that it is indeed possible to take these sequences of flights,
   (i.e. be sure that the i+1th flight departs after or at the same time as the ith flight arrives) (HINT: use the isAfter and isEqual functions).
   Then confirm that the list of destination airport names match the actual destination airport names of the provided flight_t struct's.
   sz tells you the number of flights and destination airport names to consider. Be sure to extensively test for errors (i.e. if you encounter NULL's for any values that you might expect to
   be non-NULL, return -1).

   Return from this function the total cost of taking these sequence of flights. If it is impossible to take these sequence of flights, if the list of destination airport names
   doesn't match the actual destination airport names provided in the flight_t struct's, or if you run into any errors mentioned previously or any other errors, return -1.
*/
// Jiaping
int validateFlightPath(flight_t** flight_list, char** airport_name_list, int sz) {
    // Replace this line with your code
    int totalCost = 0;
    int i = 0;
    if(!flight_list) return -1;
    while(i<sz){
        //printf("here2\n");
        //printf("%p\n",flight_list);
        //printf("here3\n");
        if(*(flight_list+i+1) == NULL) break;
        else if(!isAfter(&((*(flight_list+i+1))->departure), &((*(flight_list+i))->arrival)) && !isEqual(&((*(flight_list+i+1))->departure),&((*(flight_list+i))->arrival)))
            {printf("here1\n");return -1;} // return -1 if the next flight doesn't depart after or at the same time with the former one
        else if(strcmp(*(airport_name_list+i), (*(flight_list+i))->destination->name)) {return -1;} // return -1 if the name doesn't match
        else {totalCost = totalCost+ ((*(flight_list+i))->cost);i++;}
    }
    return totalCost;
}
