/*
#include "mpi.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define TRIALS 20
#define ARRAY_SIZE 1000000

// argc = cpu count, argv = file.cpp
int main (int argc,  char *argv[])
{
 int myid, numprocs;
 double startwtime, endwtime;
 int namelen;
 int* numbers = new int[ARRAY_SIZE];
 int i, j, sum, part_sum;
 int s, s0, startIndex, endIndex;
 double totalTime;

 char processor_name[MPI_MAX_PROCESSOR_NAME];
 // init MPI execution environment
 MPI_Init(&argc, &argv);
 // Determines the size of the group associated with a communicator
 // all processes are enrolled in a "universe" called MPI_Comm_size
 // also give it the number ofp rocessors
 // all processees execute MPI_Comm_size
 // &numproces returns the cpu count that was passed in by argc
 MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
 // Determines the rank of the calling process in the communicator
 // each process is given a unique rank from 0 - (p-1)
 // each process finds its own rank or id
 MPI_Comm_rank(MPI_COMM_WORLD, &myid);
 // Gets the name of the processor
 MPI_Get_processor_name(processor_name, &namelen);
 // display info
 fprintf(stderr, "process %d on %s\n", myid, processor_name);
 // flush stream
 fflush(stderr);  
 

 for (int i=0; i<ARRAY_SIZE; i++)
    numbers[i] = i;  //could be randomly generated


 // if rank == 0, it means it is the master node (process 0)
 if (myid == 0) 
 {
   // example, cpu = 4
   // 1000000 / 4 = 250,000
   s = (int)floor(ARRAY_SIZE / numprocs);
   // 250,000 + 1000000 % 4 (% first, + second)
   // = 250000
   s0 = s + ARRAY_SIZE % numprocs;
 }

 //Broadcasts a message from the process with rank "root" to all other processes of the communicator
 // int MPI_Bcast( void *buffer, int count, MPI_Datatype datatype, int root,  MPI_Comm comm )


buffer (input/output para, rest is input)
	starting address of buffer (choice)
count
	number of entries in buffer (integer) / number of itemsto send
datatype
	data type of buffer (handle)
root
	rank of broadcast root (integer)
comm
	communicator (handle)



 // in class notes
 // sends same data to each of a group of processes
 MPI_Bcast(&s, 1, MPI_INT, 0, MPI_COMM_WORLD);
 MPI_Bcast(&s0, 1, MPI_INT, 0, MPI_COMM_WORLD);

 startIndex = s0 + (myid-1)*s;
 endIndex = startIndex + s;
 totalTime = 0;
 

 for (j=1; j<=TRIALS; j++)
 { 
   if (myid == 0) 
   {
     startwtime = MPI_Wtime();
   }
   sum = 0;
   part_sum = 0;

   if (myid == 0) //master;s work
    {  //compute sum of master's numbers
       for (i=0; i<s0; i++) 
       {
         part_sum += numbers[i];
      }
    }
   else //slave's work
    {
      for (i= startIndex; i<endIndex; i++) 
       {
        part_sum += numbers[i];
       }
    }
  
   //  a gather operation gathers elements from each process into process 0 using dynamically 
   // allocated memory in root process
   // MPI_Reduce() is a gather operation combined with specified arthmetic/logical 
   // operation 
   MPI_Reduce(&part_sum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

   if (myid == 0) 
   {
     double runTime;
     endwtime = MPI_Wtime();
     runTime = endwtime - startwtime;
     printf("Trial %d : Execution time (sec) = %f\n", j, runTime);
     totalTime += runTime;

//printf("Sum %5.9f\n", sum);
   }
  } //end for j
  

 //if id is the master (which gets all the data back at the end??)
  if (myid == 0)
     printf("Average time for %d trials = %f\n", TRIALS, totalTime/TRIALS);
printf("Sum %5.9f\n", sum);



  // terminate MPI execution enviroment 
  MPI_Finalize();

 }

 */