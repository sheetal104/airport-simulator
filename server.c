//HEADER FILES

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<ctype.h>
#include"interface.h"

#ifdef __MINGW32__
	#define clear system("cls")
#elif __unix__
	#define clear system("clear")
#endif

#define MAX 5 //maximum no.of elements in the queue

//Function to take in simulation details
void StartSimulation(int *simulation_time, double *expected_takeoff, double *expected_landing)
{
	int flag = 0;
    char choice;
	 
	 printf("\n SIMULATION OF AN AIRPORT WITH 3 RUNWAYS\n");
     printf("\n One plane can land or depart in each unit of time.\n");
     printf(" Up to %d planes can be waiting to land or take off at any time.\n", MAX);
	 printf("\n---------------------------------------------------------------------\n");
	 printf("\n How many units of time will the simulation run? ");
	 scanf("%d", simulation_time);
	 
	do
    {
        printf(" \n Expected number of arrivals per unit time: ");
		scanf("%lf", expected_landing);
		printf("\n Expected number of departures per unit time: ");
		scanf("%lf", expected_takeoff);
		printf("\n");

        if (*expected_landing < 0.0 || *expected_takeoff < 0.0)
        {
            printf(" These numbers must be non-negative.\n");
            flag = 0;
        }
        else
        {
            if (*expected_landing + *expected_takeoff > 1.0)
            {
                printf(" The airport will become saturated. Read new numbers(y/n)? ");
                scanf(" %c", &choice);
                if (tolower(choice) == 'y')		//read values again if user says yes
                    flag = 0;
                else
                    flag = 1;
            }
            else
                flag = 1;
        }
    } while (flag == 0);
	 
	clear; //clear screen
}

//Function to generate a random non-negative integer 
//according to Poisson distribution with expected value as a parameter
int random_int(double expected_value)
{
	int n=0; 							//no.of iterations
	float x = rand()/(double)RAND_MAX;  //pseudorandom number
	
	while(x > exp(-(expected_value*2))) 
	{
		n++;
		x *= rand()/(double)RAND_MAX;
	}
	
	return n;
}

//Function to insert new plane element
void new_plane(plane_queue **front, plane_queue **rear, int plane_num)
{
	 plane_queue *temp = (plane_queue *)malloc(sizeof(plane_queue));
	 temp->plane = plane_num;
	 temp->next = NULL;
	 
	 if(*front == NULL && *rear == NULL)       //if there are no elements
	 {
		 *front = temp;
		 *rear = temp;
	 }
	 
	 else
	 {
		 (*rear)->next = temp;  			  //insert element from the rear end
		 *rear = temp;
	 }
	 
}

//Function to delete an element and return pointer to next one
int del_plane(plane_queue **front, plane_queue **rear)
{
	plane_queue *temp = (plane_queue *)malloc(sizeof(plane_queue));
	
	if(*front == *rear)				//if there is only 1 element
	{
		temp = *front;
		*front = NULL;
		*rear = NULL;
		return temp->plane;
	}
	
	else if( *front != *rear)	   //delete element from the front and point to the next element
	{
		temp = *front;
		*front = (*front)->next;
		return temp->plane;
	}

}

//Function to count no.of elements in the queue
int count(plane_queue **front)
{
	int count = 0;
	plane_queue *temp = (plane_queue *)malloc(sizeof(plane_queue));
	temp = *front;				//start from beginning
	
	while(temp != NULL)			//count till the end
	{
		count++;
		temp = temp->next;		//move to next element
	}
	
	return count;
}