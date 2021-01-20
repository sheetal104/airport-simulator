
//Queue structure 
typedef struct queue
{
	int plane; 			//data value ie identification number of the airplane
	
	struct queue *next; //pointer to next element
	
}plane_queue;			//structure variable

//Function to take in simulation details
void StartSimulation(int *simulation_time, double *expected_landing, double *expected_takeoff);

//Function to insert new plane element
void new_plane(plane_queue **front, plane_queue **rear, int plane_num);

//Function to delete an element and return pointer to next one
int del_plane(plane_queue **front, plane_queue **rear);

//Function to count no.of elements in the queue
int count(plane_queue **front);

//Function to generate a random non-negative integer 
int random_int(double expected_value);
