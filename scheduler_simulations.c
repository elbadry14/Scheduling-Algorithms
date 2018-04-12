#include <stdio.h>
#include <stdlib.h>
#define MAX_BURST 10
#define PRIORITY_LEVELS 5
#define MAX_ARRIVAL 8
#define MAX_PROCESSES 10
#define MAX_TIME 200
#define preemptive 1
#define nonpreemptive 0
/* Define a PCB (Process Control Block) */
struct process{
	int pid;
	int burst;
	int priority;
	int arrival;
};
typedef struct process Process;

/* Process initialization */
Process process_init(int,int,int,int);
void sort_readyQ(Process [],int);

/* Scheduling Algorithm Prototypes */
void fcfs(int [],Process [],int);
void sjf(int [],int p,Process [],int);
void hpf(int [],int p,Process [],int);
void rr(int [],Process [],int);

/* Display Gantt Chart of processes */
void gannt_chart(int []);

int main(){
	int i;
	int totalburst=0;
	int pid;
	int burst;
	int priority;
	int arrival;
	int pGannt[MAX_TIME];
	int n; // number of processes
	/* Define the ready queue */
	Process readyQ[MAX_PROCESSES]; //Array is used to implement the ready queue

	/* Initialize a ready queue */
	srand(time(0));
	n = (rand() % MAX_PROCESSES) + 1;
	pid = 1;
	while (pid<=n){
		burst = (rand() % MAX_BURST) + 1;
		priority = (rand() % PRIORITY_LEVELS);
		arrival = (rand()% MAX_ARRIVAL);
		readyQ[pid-1] = process_init(pid,burst,priority,arrival);
		totalburst += readyQ[pid-1].burst;
		pid +=1;
	}
	sort_readyQ(readyQ,n); //sort by arrival time
	/* Display Processes */
	printf("Processes in the Ready Queue: \n");
	for(i=0;i<n;i++){
		printf("P[%d]: arrival time = %d, burst time = %d, priority = %d\n",readyQ[i].pid,readyQ[i].arrival,readyQ[i].burst,readyQ[i].priority);
	}
	printf("-----------------------------------------------------------\n");
	/* Start scheduling algorithms */
	printf("\nFirst Come First Served Scheduling Gannt Chart:\n");
	fcfs(pGannt,readyQ,n);
	gannt_chart(pGannt);
	printf("\nNon-Preemptive Shortest Job First Scheduling Gannt Chart:\n");
	sjf(pGannt,nonpreemptive,readyQ,n);
	gannt_chart(pGannt);
	printf("\nPreemptive Shortest Job First Scheduling Gannt Chart:\n");
	sjf(pGannt,preemptive,readyQ,n);
	gannt_chart(pGannt);
	printf("\nNon-Preemptive Priority Scheduling Gannt Chart:\n");
	hpf(pGannt,nonpreemptive,readyQ,n);
	gannt_chart(pGannt);
	printf("\nPreemptive Priority Scheduling Gannt Chart:\n");
	hpf(pGannt,preemptive,readyQ,n);
	gannt_chart(pGannt);
	printf("\nRound Robin Scheduling Gannt Chart:\n");
	rr(pGannt,readyQ,n);
	gannt_chart(pGannt);

	return 0;
}

Process process_init(int pid, int burst, int priority, int arrival){

	Process proc;
	proc.pid = pid;
	proc.burst = burst;
	proc.priority = priority;
	proc.arrival = arrival;
	return proc;
}

void sort_readyQ(Process readyQ[],int n){
	Process tempP;
	int i,j;
	for(i=0;i<n-1;i++){
		for(j=i+1;j<n;j++){
			if(readyQ[i].arrival > readyQ[j].arrival){
				tempP = readyQ[i];
				readyQ[i] = readyQ[j];
				readyQ[j] = tempP;
			}
		}
	}
}

/* Display Gannt chart */
void gannt_chart(int pGannt[]){
	int i=0;
	int j;
	int f = 0;
	int c=0;
	int pNow;
	printf("-------------------------------------------------------------\n");
	if(pGannt[0]!=-1){pNow = pGannt[0];}
	i = 0;
	while(pGannt[i]!=-1){
		if(pGannt[i]==pNow){
			f = 0;
			c++;
			i++;
		}
		else{
			f=1;
		}
		if(f==1){
			printf("|");
			for(j=1;j<=((2*c-2)/2);j++){
				printf(" ");
			}
			printf("P%d",pNow);
			for(j=1;j<=((2*c-2)/2);j++){
				printf(" ");
			}
			c = 0;
			pNow = pGannt[i];
		}
	}
	printf("|");
	for(j=1;j<=((2*c-2)/2);j++){
		printf(" ");
	}
	printf("P%d",pNow);
	for(j=1;j<=((2*c-2)/2);j++){
		printf(" ");
	}
	printf("|\n");
	printf("-------------------------------------------------------------\n");
}
/* Scheduling Algorithm Implementations */
void fcfs(int pGannt[], Process readyQ[],int n){
	Process p[MAX_PROCESSES];
	int i;
	int j;
	int t;
	// clear time units (they will be loaded with pid of running processes)
	for(i=0;i<MAX_TIME;i++){
		pGannt[i]=-1;
	}
	//Copy ready queue in a temp queue
	for(i=0;i<n;i++){
		p[i]=readyQ[i];
	}
	i = 0;
	t = 0;
	while(i<n){
		if(t<p[i].arrival){
			pGannt[t]=0;
			t++;
		}
		else {
			for(j=0;j<p[i].burst;j++){
				pGannt[t+j]=p[i].pid;
			}
			t = t + j;
			i+=1;
		}
	}
}
void sjf(int pGannt[],int preemption, Process readyQ[],int n){
	Process p[MAX_PROCESSES];
	int i;
	// clear time units (they will be loaded with pid of running processes)
	for(i=0;i<MAX_TIME;i++){
		pGannt[i]=-1;
	}
	//Copy ready queue in a temp queue
	for(i=0;i<n;i++){
		p[i]=readyQ[i];
	}
	if(preemption == nonpreemptive){
             int t=0;
         int ff = 0;
        Process temp;
          int s=n;



    while(s){
       int  j=0;
        ff=0;
        int m;
        Process kl[n];

        for(i=0;i<n;i++){

            if( (t >= p[i].arrival) &&(p[i].burst!=MAX_TIME) ){
                kl[j]=p[i];
                ff=1;
                j++;
                m=j;
            }
        }

        if(ff){

            for(i=0;i<m-1;i++){
                for(j=i+1;j<m;j++){
                    if(kl[i].burst > kl[j].burst){
                        temp = kl[i];
                        kl[i] = kl[j];
                        kl[j] = temp;
                    }
                }
            }

            for(j=0;j < kl[0].burst ;j++){
				pGannt[t+j]=kl[0].pid;
            }
            t = t + j;

            for(i=0;i<n;i++){
                if( kl[0].pid == p[i].pid ){
                    p[i].burst=MAX_TIME;
                   // k1[i].burst=MAX_TIME;


                }
            }
            s=s-1;
        }
        else{
            pGannt[t]=0;
			t=t+1;
        }

    }
		//your code here
	}
	if(preemption == preemptive){
            int t=0,j,ff=0,s=n;
		Process po[n],temp;

		for(i=0;i<n;i++){
            po[i]=p[i];
        }
        while(s){
            int m;
            j=0;
            ff=0;
            Process kl[n];

            for(i=0;i<n;i++){
                if( (t >= po[i].arrival) && (po[i].burst!=MAX_TIME)  ){
                    kl[j]=po[i];
                    ff=1;
                    j++;
                    m=j;
                }
            }

            if(ff){
                for(i=0;i<m-1;i++){
                    for(j=i+1;j<m;j++){
                        if(kl[i].burst > kl[j].burst){
                            temp = kl[i];
                            kl[i] = kl[j];
                            kl[j] = temp;
                        }
                    }
                }
               // for(j=0;j<kl[0].burst;j++){
                pGannt[t]=kl[0].pid;
               // }

                for(i=0;i<n;i++){
                    if( kl[0].pid == po[i].pid ){

                        po[i].burst--;
                        if(po[i].burst==0){
                            po[i].burst=MAX_TIME;
                            --s;
                        }


                        break;
                    }
                }
                t++;
            }
            else{
                pGannt[t]=0;
                t++;
            }
        }
		//your code here
	}
}
void hpf(int pGannt[],int preemption,Process readyQ[],int n){
	Process p[MAX_PROCESSES];
	int i;
	// clear time units (they will be loaded with pid of running processes)
	for(i=0;i<MAX_TIME;i++){
		pGannt[i]=-1;
	}
	//Copy ready queue in a temp queue
	for(i=0;i<n;i++){
		p[i]=readyQ[i];
	}
	if(preemption == nonpreemptive){
               int t=0;
         int ff = 0;
        Process temp;
          int s=n;



    while(s){
       int  j=0;
        ff=0;
        int m;
        Process kl[n];

        for(i=0;i<n;i++){

            if( (t >= p[i].arrival) &&(p[i].priority!=MAX_TIME) ){
                kl[j]=p[i];
                ff=1;
                j++;
                m=j;
            }
        }

        if(ff){

            for(i=0;i<m-1;i++){
                for(j=i+1;j<m;j++){
                    if(kl[i].priority < kl[j].priority){
                        temp = kl[i];
                        kl[i] = kl[j];
                        kl[j] = temp;
                    }
                }
            }

            for(j=0;j < kl[0].burst;j++){
				pGannt[t+j]=kl[0].pid;
            }
            t = t + j;

            for(i=0;i<n;i++){
                if( kl[0].pid == p[i].pid ){
                    p[i].priority=MAX_TIME;
                   // k1[i].burst=MAX_TIME;


                }
            }
            s=s-1;
        }
        else{
            pGannt[t]=0;
			t=t+1;
        }

    }
		//yo
		//your code here
	}
	if(preemption == preemptive){
              int t=0;
         int ff = 0;
        Process temp;
        Process po[n];
        for(i=0;i<n;i++){
            po[i]=p[i];
        }


          int s=n;


    while(s){
       int  j=0;
        ff=0;
        int m;
        Process kl[n];

        for(i=0;i<n;i++){

            if( (t >= po[i].arrival) &&(po[i].priority!=MAX_TIME) ){
                kl[j]=po[i];
                ff=1;
                j++;
                m=j;
            }
        }

        if(ff){

            for(i=0;i<m-1;i++){
                for(j=i+1;j<m;j++){
                    if(kl[i].priority < kl[j].priority){
                        temp = kl[i];
                        kl[i] = kl[j];
                        kl[j] = temp;
                    }
                    else if (kl[i].priority ==kl[j] .priority){
                       if (kl[i].burst< kl[j].burst){
                           kl[0]=kl[i] ;}
                        else
                            kl[0]=kl[j];
                    }
                }
            }


				pGannt[t]=kl[0].pid;



            for(i=0;i<n;i++){
                if( kl[0].pid == po[i].pid ){
                        po[i].burst--;
                        if(po[i].burst==0){
                            po[i].priority=MAX_TIME;
                            --s;
                        }


                        break;

                   }
            }
            t++;

        }
        else{
            pGannt[t]=0;
			t=t+1;
        }

    }
		//yo
		//your code here
	}
}
void rr(int pGannt[],Process readyQ[],int n){
	Process p[MAX_PROCESSES];
	int i,flag=0,time_quantum,time;
	// clear time units (they will be loaded with pid of running processes)
	for(i=0;i<MAX_TIME;i++){
		pGannt[i]=-1;
	}
	//Copy ready queue in a temp queue
	for(i=0;i<n;i++){
		p[i]=readyQ[i];
	}

    printf("Enter Time Quantum:\t");
    scanf("%d",&time_quantum);

    for(time=0,i=0;n!=0;)
    {
    if(p[i].burst<=time_quantum && p[i].burst>0)
    {
      time+=p[i].burst;
      p[i].burst=0;
      flag=1;
    }
    else if(p[i].burst>0)
    {
      p[i].burst-=time_quantum;
      time+=time_quantum;
    }
    if(p[i].burst==0 && flag==1)
    {
      n--;
      printf("P[%d]\t",i+1);
      flag=0;
    }
    if(i==n-1)
      i=0;
    else if(p[i+1].arrival<=time)
      i++;
    else
      i=0;
  }
	// your code here
}
