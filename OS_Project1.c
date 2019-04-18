//Multilevel Queue Scheduling of Round Robin and SROT

#include<stdio.h>
 typedef struct 
{
	int pid;
	int bt;
	int art;
}Process;
void Queue1();
void Queue2();
void findWaitingTime(Process proc[], int n,int wt[]) 
{ 
    int rt[n]; 
    for (int i = 0; i < n; i++) 
        rt[i] = proc[i].bt; 
  
    int complete = 0, t = 0, minm = 100000; 
    int shortest = 0, finish_time,j; 
    bool check = false; 
  
    // Process until all processes gets 
    // completed 
    while (complete != n) { 
  
        // Find process with minimum 
        // remaining time among the 
        // processes that arrives till the 
        // current time` 
        for ( j = 0; j < n; j++) { 
            if ((proc[j].art <= t) && 
            (rt[j] < minm) && rt[j] > 0) { 
                minm = rt[j]; 
                shortest = j; 
                check = true; 
            } 
        } 
  
        if (check == false) { 
            t++; 
            continue; 
        } 
        rt[shortest]--;
        minm = rt[shortest]; 
        if (minm == 0) 
            minm = 100000; 
   
        if (rt[shortest] == 0) { 
            complete++; 
            check = false; 
            finish_time = t + 1; 

            wt[shortest] = finish_time - 
                        proc[shortest].bt - 
                        proc[shortest].art; 
  
            if (wt[shortest] < 0) 
                wt[shortest] = 0; 
        } 
        t++; 
    } 
} 
  
// Function to calculate turn around time 
void findTurnAroundTime(Process proc[], int n, 
                        int wt[], int tat[]) 
{ 
    for (int i = 0; i < n; i++) 
        tat[i] = proc[i].bt + wt[i]; 
} 
  
// Function to calculate average time 
void findavgTime(Process proc[], int n) 
{ 
    int wt[n], tat[n], total_wt = 0, 
                    total_tat = 0,i; 

    findWaitingTime(proc, n, wt); 
    findTurnAroundTime(proc, n, wt, tat);  
    printf(" Processes\t Burst time\t Waiting time\t  Turn around time\n"); 
  
    for ( i = 0; i < n; i++) { 
        total_wt = total_wt + wt[i]; 
        total_tat = total_tat + tat[i]; 
        printf( " %d        \t ", proc[i].pid );
        printf(" %d        \t ",proc[i].bt) ;
		printf(" %d        \t ",wt[i]); 
        printf(" %d        \t ", tat[i]) ; printf("\n"); 
    } 
  
    printf( "\nAverage waiting time = ");
        printf("%f", (float)total_wt / (float)n); 
    printf("\nAverage turn around time = ");
        printf("%f", (float)total_tat / (float)n); 
} 
void Queue1()
{
	printf("\nRound Robin Scheduling\n");
	  int count,j,n,time,remain,flag=0,time_quantum; 
  int wait_time=0,turnaround_time=0,at[10],bt[10],rt[10]; 
  printf("Enter Total Process:\t "); 
  scanf("%d",&n); 
  remain=n; 
  for(count=0;count<n;count++) 
  { 
    printf("Enter Arrival Time and Burst Time for Process Process Number %d :",count+1); 
    scanf("%d",&at[count]); 
    scanf("%d",&bt[count]); 
    rt[count]=bt[count]; 
  } 
  printf("Enter Time Quantum:\t"); 
  scanf("%d",&time_quantum); 
  printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n"); 
  for(time=0,count=0;remain!=0;) 
  { 
    if(rt[count]<=time_quantum && rt[count]>0) 
    { 
      time+=rt[count]; 
      rt[count]=0; 
      flag=1; 
    } 
    else if(rt[count]>0) 
    { 
      rt[count]-=time_quantum; 
      time+=time_quantum; 
    } 
    if(rt[count]==0 && flag==1) 
    { 
      remain--; 
      printf("P[%d]\t|\t%d\t|\t%d\n",count+1,time-at[count],time-at[count]-bt[count]); 
      wait_time+=time-at[count]-bt[count]; 
      turnaround_time+=time-at[count]; 
      flag=0; 
    } 
    if(count==n-1) 
      count=0; 
    else if(at[count+1]<=time) 
      count++; 
    else 
      count=0; 
  } 
  printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n); 
  printf("Avg Turnaround Time = %f",turnaround_time*1.0/n); 
  
}
void Queue2()
{
	printf("\nQueue2 :\n");
	printf("\nShortest Job first Scheduling\n"); 
	printf("Enter Total Number of Processes:\t"); 
	int limit,count;
	scanf("%d", &limit);  
	Process proc[limit]; 
	for(count = 0; count < limit; count++) 
	{ 
		printf("\nProcess ID:\t"); 
		scanf("%d", &proc[count].pid); 
		printf("Arrival Time:\t"); 
		scanf("%d", &proc[count].art); 
		printf("Burst Time:\t"); 
		scanf("%d", &proc[count].bt);  
	}

	findavgTime(proc,limit);
}

int main()
{
	int p1,p2;
	int q1=1,q2=2;
	printf("Enter the priority of the queue %d\n",q1);
	scanf("%d",&p1);
	printf("Enter the priority of the queue %d\n",q2);
	scanf("%d",&p2);
	if(p1<p2)
	{
	  Queue1();
	  Queue2();
	}
	else if(p1>p2){
	 Queue2();
     Queue1();
	}
}
