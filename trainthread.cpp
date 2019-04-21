//c++ program to schedule trains using 
  //priority scheduling and threads.

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep()
#include <pthread.h> 
using namespace std;
struct train
{ 
int time,bt,priority,tid; 
}; 
struct train t[50];
void intro()
{
	cout<<"\n\n\n\t\t\t\t\t----------TRAIN SCHEDULING SYSTEM----------";
	cout<<"\n\n\t\t\t\t\t\tMADE BY   .: Abhishek Kumar Saxena        "; 
	cout<<"\n\n\n\n\t\t\t\t\t\t\t    JIIT\n\n\n";
}
bool comp(train a,train b) 
{ 
if(a.time == b.time) 
{ 
return a.priority<b.priority; 
} 
else
{ 
	return a.time<b.time; 
} 
} 
void get_wt_time(int wt[],int n) 
{ 
int service[50]; 
service[0]=0; 
wt[0]=0; 
for(int i=1;i<n;i++) 
{ 
service[i]=t[i-1].bt+service[i-1]; 
wt[i]=service[i]-t[i].time+1; 
	if(wt[i]<0) 
	{ 
	wt[i]=0; 
	} 
} 
} 
void get_tat_time(int tat[],int wt[],int n) 
{ 
for(int i=0;i<n;i++) 
{ 
	tat[i]=t[i].bt+wt[i]; 
} 	
} 
void findgc(int n) 
{ 
int wt[50],tat[50]; 
double wavg=0,tavg=0; 
get_wt_time(wt,n); 
get_tat_time(tat,wt,n); 	
int stime[50],ctime[50]; 
stime[0]=1; 
ctime[0]=stime[0]+tat[0]; 
for(int i=1;i<n;i++) 
	{ 
		stime[i]=ctime[i-1]; 
		ctime[i]=stime[i]+tat[i]-wt[i]; 
	} 	
cout<<"\tTrain Id\tArrival_time\tDeparture_time\tTurn_Around_Time\tWaiting_Time"<<endl; 	
for(int i=0;i<n;i++) 
	{ 
		wavg += wt[i]; 
		tavg += tat[i]; 		
		cout<<"\t"<<t[i].tid<<"\t\t"<< 
			stime[i]<<"\t\t"<<ctime[i]<<"\t\t"<< 
			tat[i]<<"\t\t\t"<<wt[i]<<endl; 
	} 	

	cout<<"\n\n\tAverage waiting time is : "; 
	cout<<"\t"<<wavg/(float)n<<endl; 
	cout<<"\t"<<"Average turnaround time : "; 
	cout<<"\t"<<tavg/(float)n<<endl; 
}  
void *driver(void *vargp)//function using thread.
    {
        pthread_t thread_id1; 
        sleep(2);
		char ch;
        int n,arrivaltime[10],bursttime[10],priority[10];
        printf ("\tEnter the n : ");
        scanf("\t%d",&n);
        for (int j=0;j<n;j++)
        {
            cout<<"\tEnter the arrival time of train "<<j+1<<" : ";
            cin>>arrivaltime[j];
            cout<<"\tEnter the passing time (burst time) of train "<<j+1<<" : ";

            cin>>bursttime[j];
            cout<<"\tEnter the priority of train "<<j+1<<" : ";
            cin>>priority[j];
        } 	
		for(int i=0;i<n;i++) 
		{ 
			t[i].time=arrivaltime[i]; 
			t[i].bt=bursttime[i]; 
			t[i].priority=priority[i]; 
			t[i].tid=i+1; 
		} 	
		sort(t,t+n,comp); 	
		findgc(n); 
}
int main() 
{
    pthread_t thread_id;
	cout<<"\n\n\n\t\t\t\t\t###########################################";
	cout<<"\n\n\n\t\t\t\t\t#-----------------------------------------#";
	cout<<"\n\n\n\t\t\t\t\t#---------TRAIN SCHEDULING SYSTEM---------#";
	cout<<"\n\n\n\t\t\t\t\t#-----------------------------------------#";
	cout<<"\n\n\n\t\t\t\t\t###########################################\n\n\n";
    char ch='y';
    while (ch=='y')
    { 
    
    printf("\tThread is used in next step (wait here)\n"); 
    pthread_create(&thread_id, NULL, driver, NULL); 
    pthread_join(thread_id, NULL); 
    printf("\tThis is portion after Thread\n");
	cout<<"\tEnter y to run : ";
    cin>>ch;
    }
    if (ch!='y')
   	{
        cout<<"\tYou terminated the program"<<endl;
        intro();
    }    
     
    exit(0); 
	
	return 0; 
} 
 
