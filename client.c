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


//main function

int main()
{
 int simulation_time;							//total simulation time
 int plane_no=1;								//airplane number
 int n_land=0,n_takeoff=0;						//no.of planes declared ready to land/takeoff
 int num_landed=0,num_takeoff=0;				//no.of planes landed/taken off
 double expected_takeoff, expected_landing;		//no.of planes taking off/landing in unit time
 int rand_landings,rand_takeoffs;				//no.of planes to be added to landing/takeoff queue
 
 StartSimulation(&simulation_time, &expected_takeoff, &expected_landing);
 printf("\n");
 
 plane_queue *land_front = NULL;
 plane_queue *land_rear = NULL;			//landing queue
 plane_queue *takeoff_front = NULL;
 plane_queue *takeoff_rear = NULL;		//takeoff queue
 
 for(int T=1; T<=simulation_time; T++)  //iterate over the given simulation time
 {
	rand_takeoffs = random_int(expected_takeoff);
	
	for(int planes = 0; planes < rand_takeoffs; planes++)
	{
		printf(" \tPlane %d is ready to takeoff\n", plane_no);
		n_takeoff++;
		if((count(&takeoff_front)) <= MAX)
			new_plane(&takeoff_front, &takeoff_rear, plane_no);	//add to takeoff queue
		
		else
		{
			printf(" \tPlane %d is told to wait\n",plane_no);
			new_plane(&takeoff_front, &takeoff_rear, plane_no);
		}
		
		plane_no++;
	}
 
	rand_landings = random_int(expected_landing);
	
	for(int planes = 0; planes < rand_landings; planes++ )
	{
		printf(" \tPlane %d is ready to land\n", plane_no);		//add to landing queue
		n_land++;
		if((count(&land_front)) <= MAX)
			new_plane(&land_front, &land_rear, plane_no);
		
		else
		{
			printf(" \tPlane %d is told to wait\n",plane_no);	//wait if queue is full
			new_plane(&land_front, &land_rear, plane_no);
		}
		plane_no++;
	}
 	
	if(count(&land_front) > 1 && count(&takeoff_front) > 0)
	{
		printf("\n %d:" ,T);
		printf(" \tPlane %d took off using runway 2\n",del_plane(&takeoff_front, &takeoff_rear));
		num_takeoff++;
		printf(" \tPlane %d landed using runway 1\n",del_plane(&land_front, &land_rear));
		num_landed++;
		printf(" \tPlane %d landed using runway 3\n",del_plane(&land_front, &land_rear));
		num_landed++;
	}
	
	else if(count(&land_front)==1 && count(&takeoff_front) > 0)
	{
		printf("\n %d:" ,T);
		printf(" \tPlane %d took off using runway 2\n",del_plane(&takeoff_front, &takeoff_rear));
		num_takeoff++;
		printf(" \tPlane %d landed using runway 1\n",del_plane(&land_front, &land_rear));
		num_landed++;
	}
 
	else if(count(&land_front)>1 && count(&takeoff_front)==0)	//landing queue is not empty
	{
		printf("\n %d:" ,T);
		printf("\tPlane %d landed using runway 1\n",del_plane(&land_front, &land_rear));
		num_landed++;
		printf("\tPlane %d landed using runway 3\n",del_plane(&land_front, &land_rear));	//runway 3 is used for landing
		num_landed++;
	}

	else if(count(&takeoff_front)>1 && count(&land_front)==0)	//landing queue is empty
	{
		printf("\n %d:" ,T);
		printf(" \tPlane %d took off using runway 2\n", del_plane(&takeoff_front, &takeoff_rear));
		num_takeoff++;
		printf(" \tPlane %d took off using runway 3\n", del_plane(&takeoff_front, &takeoff_rear));	//runway 3 is used for takeoff
		num_takeoff++;
		
	}
 
	else if(count(&takeoff_front)==1 && count(&land_front)==0)	//landing queue is empty
	{
		printf("\n %d:" ,T);
		printf(" \tPlane %d took off using runway 2\n",del_plane(&takeoff_front, &takeoff_rear));
		num_takeoff++;
	}
 
	else if(count(&land_front)==1 && count(&takeoff_front)==0)	//takeoff queue is empty
	{
		printf("\n %d:" ,T);
		printf(" \tPlane %d landed using runway 1\n", del_plane(&land_front, &land_rear));
		num_landed++;
	}
 
	else
	{
		printf("\n %d:" ,T);
		printf(" \tRunways are idle\n");	//runways are idle if both queues are empty
	}
 }
 
 //Simulation statistics
 printf("\n-----------------------------------------------------\n\n");
 printf("\n\n\tSimulation has concluded after %d units.\n", simulation_time);
 printf("\tTotal number of planes processed:  %d\n", plane_no-1);
 printf("\tNumber of planes landed:           %d\n", num_landed);
 printf("\tNumber of planes taken off:        %d\n", num_takeoff);
 printf("\tNumber of planes ready to land:    %d\n", n_land-num_landed);
 printf("\tNumber of planes ready to takeoff: %d\n", n_takeoff-num_takeoff);
 printf("\n");
 
 return 0;
}
