/*  MPI_Reduce  */

#include <mpi.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>       /* time */
using namespace std;
#define N 120

int main(int argc, char *argv[]) {
    int me, numprocs;
	int data, res;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &me);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    int rows_per_process = N/(numprocs);
    int A[N][N];
    int v[N], x[N]={0},lx[rows_per_process]={0};
    double initial_time,ending_time,ending_time2;
    double scatter_time,scatter_time2,gather_time,gather_time2;
    int lA[rows_per_process][N];

    if(me==0){
        srand(time(NULL));
        int A[N][N];
        for (int i=0;i<N;i++){
            for(int j =0;j<N;j++){
                A[i][j]=rand()%10;
            }
            v[i]=rand()%10;
        }
    }

    MPI_Barrier( MPI_COMM_WORLD);    
    scatter_time=MPI_Wtime();
    initial_time=scatter_time;
    MPI_Scatter( (int**)A , N*rows_per_process , MPI_INT , (int**)lA , N*rows_per_process , MPI_INT ,0 , MPI_COMM_WORLD);
    MPI_Barrier( MPI_COMM_WORLD);    
    scatter_time2=MPI_Wtime();
    if (me==0){
        cout<<"scatter time with procesors = "<<numprocs<<"lasted: "<<scatter_time2-scatter_time<<endl;
    }   

    MPI_Bcast((int*)v,N,MPI_INT,0,MPI_COMM_WORLD);


    cout<<"proceso "<<me<<"  of " <<numprocs<<endl;


    for (int i = 0;i<rows_per_process;i++){
        for (int j = 0;j<N;j++){
            lx[i]+=lA[i][j]*v[j];
        }
    }

    MPI_Barrier( MPI_COMM_WORLD);    
    gather_time = MPI_Wtime();
    MPI_Gather( (int*)lx, rows_per_process , MPI_INT , (int*)x , rows_per_process , MPI_INT , 0 , MPI_COMM_WORLD);
    MPI_Barrier( MPI_COMM_WORLD);    
    gather_time2=MPI_Wtime();
    if(me==0){
        cout<<"gather time with procesors = "<<numprocs<<"lasted: "<<gather_time2-gather_time<<endl;
    }
    
    if (me==0){
        int sx[N]={0};
        ending_time=MPI_Wtime();

        /*for(int i=0;i<N;i++){
            cout<<x[i]<<" ";
        }cout<<endl;
        cout<<endl;*/
        for (int i=0;i<N;i++){
            for(int j =0;j<N;j++){
                sx[i]+=A[i][j]*v[j];
            }
            //cout<<sx[i]<<" ";
        }//cout<<endl;
        ending_time2=MPI_Wtime();
        cout<<"el proceso paralelo con Num_Procesos = "<<numprocs<<" demoro: "<<ending_time-initial_time<<endl;
        cout<<"el proceso secuencial con Num_Procesos = "<<numprocs<<"demoro: "<<ending_time2-ending_time<<endl;

    
    }
    
    MPI_Finalize();
    return 0;
}
    
    