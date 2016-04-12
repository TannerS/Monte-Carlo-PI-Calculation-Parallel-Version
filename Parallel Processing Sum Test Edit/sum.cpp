#include "mpi.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>

#define TRIALS 20
#define ARRAY_SIZE 100000000
#define AREA 4

// argc = cpu count, argv = file.cpp
int main (int argc,  char *argv[])
{
	srand(time(0));
	int sum, ran;
	double startwtime, endwtime;
	float min, max;
	double x_ran, y_ran, totalTime;
	float pi;
	int myid, numprocs;
	int s, s0, startIndex, endIndex, i, part_sum, j;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int namelen;

	totalTime = 0;
	sum = 0;
	ran = 0;
	min = 0.0;
	max = 1.0;
	pi = 0;
	part_sum = 0;

	printf("Calculating");

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Get_processor_name(processor_name, &namelen);

	fprintf(stderr, "process %d on %s\n", myid, processor_name);
	fflush(stderr);

	if (myid == 0)
	{
		s = (int)floor(ARRAY_SIZE / numprocs);
		s0 = s + (ARRAY_SIZE%numprocs);
	}

	MPI_Bcast(&s, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&s0, 1, MPI_INT, 0, MPI_COMM_WORLD);

	startIndex = s0 + (myid-1)*s;
	endIndex = startIndex + s;

	for (j=1; j<=TRIALS; j++)
	{ 
		if (myid == 0) 
		{
			startwtime = MPI_Wtime();
		}

		sum = 0;
		part_sum = 0;

		if (myid == 0)
		{ 
			for (i=0; i<s0; i++) 
			{
				x_ran = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				y_ran = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				if (((x_ran * x_ran) + (y_ran * y_ran)) <= 1)
					part_sum++;
			}
		}
		else //slave's work
		{
			for (i = startIndex; i < endIndex; i++)
			{
				x_ran = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				y_ran = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				if (((x_ran * x_ran) + (y_ran * y_ran)) <= 1)
					part_sum++;
			}
		}
  
		MPI_Reduce(&part_sum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

		/*
		printf("TETS: " + sum); 
		printf("TETS: " + part_sum);
		*/



		pi = AREA * ((float)sum / ARRAY_SIZE);

		if (myid == 0) 
		{
			double runTime;
			endwtime = MPI_Wtime();
			runTime = endwtime - startwtime;
			printf("Trial %d : Execution time (sec) = %f\n", j, runTime);
			totalTime += runTime;
		}
	}
  

	//if id is the master (which gets all the data back at the end??)
	if (myid == 0)
	{
		printf("Average time for %d trials = %f\n", TRIALS, totalTime / TRIALS);
		printf("PI %5.9f\n", pi);
	}

	printf("End program");

	MPI_Finalize();

 }

