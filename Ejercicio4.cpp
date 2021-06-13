#include <math.h>
#include <mpi.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>       /* time */
using namespace std;
#define N 10

int main(int argc, char *argv[]) {
    int me, numprocs;
	int data, res, sum;
    srand(time(NULL));
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &me);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    int rows_per_process = N/(numprocs-1);
    int nums[rows_per_process][N];
    if(me==0){
        int A[N][N];
        for (int i=0;i<N;i++){
            for(int j =0;j<N;j++){
                A[i][j]=rand()%10;
                printf()
            }
        }
        for(int i = rows_per_process; i < N; ++i){
            //printf("hello %d\n", A[i][0]);
            MPI_Send(&A[i],N,MPI_INT,i/rows_per_process, 0, MPI_COMM_WORLD);
            //printf("Sent to process %d in iteration %d\n", i/rows_per_process, i);
        }
        for(int i = 0 ; i < rows_per_process ; ++i){
            for(int j = 0; j < N; ++j)
                nums[i][j] = A[i][j];
        }
    }
    else{
        for(int i = 0; i < rows_per_process ; ++i)
            MPI_Recv(&nums[i],N,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    }
    data = 0;

    for(int i = 0; i < rows_per_process; ++i){
        sum = 0.0;
        for (int j = 0; j < N; ++j)
            sum += fabs(nums[i][j]);
        if(sum > data)
            data = sum;
    }
    
    MPI_Reduce(&data, &res, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    if(me==0)
        printf("Res is %d\n",res);
}