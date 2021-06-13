/*  MPI_Reduce  */  

#include <mpi.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]) {
    int me, numprocs;
    long long N = 2048;
    int data[N];	 
    MPI_Status status;
    int count;
    MPI_Init(&argc,&argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &me); 
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs );
    int num = 1;

    double time_per_process=0;
    double initial_time_per_process=MPI_Wtime();
    //cout << numprocs << endl;
    if(numprocs > 2){
        MPI_Finalize();
        return 0;
    }
    


    if(me == 0){
        MPI_Ssend(&data,1,MPI_INT,1,0,MPI_COMM_WORLD); 
        while(num < N/2){
            num*=2;
            MPI_Recv(&data,num,MPI_INT,1,0,MPI_COMM_WORLD,&status);
            MPI_Get_count(&status,MPI_INT,&count);
            time_per_process = MPI_Wtime();
            //cout<<"process "<<me<<" has count: "<<count<<endl;
            cout<<"process "<<me<<" timer: "<<time_per_process-initial_time_per_process<<endl;
            
            num*=2;
            MPI_Ssend(&data,num,MPI_INT,1,0,MPI_COMM_WORLD); 
        }
        MPI_Recv(&data,num*2,MPI_INT,1,0,MPI_COMM_WORLD,&status);
        MPI_Get_count(&status,MPI_INT,&count);
        time_per_process = MPI_Wtime();
        //cout<<"process "<<me<<" has count: "<<count<<endl;
        cout<<"process "<<me<<" timer: "<<time_per_process-initial_time_per_process<<endl;

    }
    else{
        MPI_Recv(&data,1,MPI_INT,0,0,MPI_COMM_WORLD,&status); 
        time_per_process = MPI_Wtime();        
        //cout<<"process "<<me<<" has count: "<<count<<endl;
        cout<<"process "<<me<<" timer: "<<time_per_process-initial_time_per_process<<endl;        
        MPI_Get_count(&status,MPI_INT,&count);
        cout<<count<<endl;
        while(num < N/2){
            num*=2;
            MPI_Ssend(&data,num,MPI_INT,0,0,MPI_COMM_WORLD);
            num *=2;
            MPI_Recv(&data,num,MPI_INT,0,0,MPI_COMM_WORLD,&status); 
            MPI_Get_count(&status,MPI_INT,&count);
            time_per_process = MPI_Wtime();
            //cout<<"process "<<me<<" has count: "<<count<<endl;
            cout<<"process "<<me<<" timer: "<<time_per_process-initial_time_per_process<<endl;
        }
            MPI_Ssend(&data,num*2,MPI_INT,0,0,MPI_COMM_WORLD);
        
    } 

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
	
    
}
    
