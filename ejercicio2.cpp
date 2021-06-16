/*  MPI_Reduce  */

#include <mpi.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[]) {
    int me, numprocs;
	double data[2];
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &me);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    if(me==0){
        data[0] = 1000;
        MPI_Ssend(&data,2,MPI_DOUBLE,me+1,0,MPI_COMM_WORLD); 
        MPI_Recv(&data,2,MPI_DOUBLE,numprocs-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        data[1] += MPI_Wtime();
        cout << me << ": " << data[0] << " con tiempo " << data[1] << endl;
    } 	
	else {
        MPI_Recv(&data,2,MPI_DOUBLE,me-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        data[0] += 100*me;
        data[1] += MPI_Wtime();
        MPI_Ssend(&data,2,MPI_DOUBLE,(me+1)%numprocs,0,MPI_COMM_WORLD); 
    }    
    MPI_Finalize();
}
