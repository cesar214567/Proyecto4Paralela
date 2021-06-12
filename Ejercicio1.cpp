/*  MPI_Reduce  */  

#include <mpi.h>
#include <iostream>
#include <stdlib.h>





using namespace std;

int main(int argc, char *argv[]) {
    int me, numprocs;
    long long N = 32;
    int data[N];	 
    MPI_Status status;
    int count;
    MPI_Init(&argc,&argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &me); 
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs );
    int num = 1;
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
            //cout<<"proceso "<<me<<" recieved "<<num<<" data"<<endl;
            MPI_Get_count(&status,MPI_INT,&count);
            cout<<count<<endl;
            num*=2;
            MPI_Ssend(&data,num,MPI_INT,1,0,MPI_COMM_WORLD); 
        }
        MPI_Recv(&data,num*2,MPI_INT,1,0,MPI_COMM_WORLD,&status);
        MPI_Get_count(&status,MPI_INT,&count);
        cout<<count<<endl;
        //cout<<"proceso "<<me<<" recieved "<<num*2<<" data"<<endl;
        
    }
    else{
        MPI_Recv(&data,1,MPI_INT,0,0,MPI_COMM_WORLD,&status); 
        //cout<<"proceso "<<me<<" recieved "<<num<<" data"<<endl;
        MPI_Get_count(&status,MPI_INT,&count);
        cout<<count<<endl;
        while(num < N/2){
            num*=2;
            MPI_Ssend(&data,num,MPI_INT,0,0,MPI_COMM_WORLD);
            num *=2;
            MPI_Recv(&data,num,MPI_INT,0,0,MPI_COMM_WORLD,&status); 
            //cout<<"proceso "<<me<<" recieved "<<num<<" data"<<endl;
            MPI_Get_count(&status,MPI_INT,&count);
            cout<<count<<endl;
        }
            MPI_Ssend(&data,num*2,MPI_INT,0,0,MPI_COMM_WORLD);
        
    } 

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
	
    
}
    
