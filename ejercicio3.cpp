/*  MPI_Reduce  */

#include <mpi.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>       /* time */
using namespace std;
#define N 10


int main(int argc, char *argv[]) {
    int me, numprocs;
	int data, res;
    srand(time(NULL));

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &me);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    int rows_per_process = N/(numprocs-1);
    int v[N], x[N]={0};

    if (me ==0){
        for (int i=0;i<N;i++){
            v[i]=rand()%10;

        }
    }
    MPI_Bcast(&v,N,MPI_INT,0,MPI_COMM_WORLD);

    if(me==0){
        int A[N][N];
        for (int i=0;i<N;i++){
            for(int j =0;j<N;j++){
                A[i][j]=rand()%10;
            }
        }
        for(int i = 0; i < N; i++){
            MPI_Send(&A[i][0],N,MPI_INT,i/rows_per_process+1,i,MPI_COMM_WORLD);                    
            //MPI_Ssend(&A[i],N,MPI_INT,(i+1),0,MPI_COMM_WORLD); 
        }
        //receive
        for(int i = 0; i < N; i++){
            MPI_Recv(&x[i],1,MPI_INT,i/rows_per_process+1,i,MPI_COMM_WORLD,MPI_STATUS_IGNORE);        
        }
        for(int i = 0; i < N; i++){
            cout<<x[i]<<" ";
        }cout<<endl; 


    } 	
	else {
        int mat[N];
        int var = 0;
        for(int i = 0; i < rows_per_process; i++){
            var = 0;
            MPI_Recv(&mat,N,MPI_DOUBLE,0,(me-1)*rows_per_process+i,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            for (int j = 0; j < N; j++ ){
                var  += mat[j]*v[j];
            }
            MPI_Send(&var, 1, MPI_INT, 0, (me-1)*rows_per_process+i, MPI_COMM_WORLD);
        }
    }    

    MPI_Finalize();
}
    
    