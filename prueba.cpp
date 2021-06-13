/*  MPI_Reduce  */

#include <mpi.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>       /* time */
using namespace std;
#define N 10


int main(int argc, char *argv[]) {
    int me, numprocs;
    srand(time(NULL));

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &me);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    int rows_per_process = N/(numprocs-1);
    int data;


    if(me==0){

        data = 100; 

    }
    //MPI_Bcast(&data,1,MPI_INT,0,MPI_COMM_WORLD);
    //MPI_Barrier(MPI_COMM_WORLD);
    if(me == 0){
        data =1;
        MPI_Send(&data,1,MPI_INT,1,1,MPI_COMM_WORLD);                    
        data=2;
        MPI_Send(&data,1,MPI_INT,1,2,MPI_COMM_WORLD);                    
    } 	
	else {
        int a=0 ,b=0;
        MPI_Recv(&a,1,MPI_DOUBLE,0,2,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Recv(&b,1,MPI_DOUBLE,0,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        cout << a << endl; 
        cout << b << endl;

        //MPI_Barrier(MPI_COMM_WORLD);

        //int data;     
       // MPI_Recv(&a,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    }    
    MPI_Finalize();
}
    
    