// C PROGRAM WHICH TAKES INPUT FROM USER ABOUT PROCESS DEATILS AND DISPLAYS GANTT-CHART AND AVG TURN-AROUND-TIME,AVG WAITING-TIME IN TERMINAL BY DEFINED CPU SHEDULING ALGORITHMS
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
//USER-DEFINED STRUCTURE FOR PROCESSES
typedef struct process{
	char name[5];
	int bt;
	int at;
	int wt,ta,ct;
	int flag;
}processes;

//FOR SORTING PROCESSES
void b_sort(processes temp[],int n)
{
	processes t;
	int i,j;
	for(i=1;i<n;i++)
		for(j=0;j<n-i;j++){
			if(temp[j].at > temp[j+1].at){
				t = temp[j];
				temp[j] = temp[j+1];
				temp[j+1] = t;
			}
		}
}
//FOR TAKING INPUT PROCESSES
int accept(processes P[]){
	int i,n;
	printf("\n Enter total number of processes : ");
	scanf("%d",&n);
	for(i=0;i<n;i++){
		printf("\n PROCESS [%d]",i+1);
		printf(" Enter process name : ");
		scanf("%s",&P[i].name);
		printf(" Enter burst time : ");
		scanf("%d",&P[i].bt);
		printf(" Enter arrival time : ");
		scanf("%d",&P[i].at);
	}
	printf("\n|| PROCESSES\tBURST-TTIME\tARRIVAL TIME ||\t ");
	for(i=0;i<n;i++)
		printf("\n    %s \t\t    %d \t\t    %d ",P[i].name,P[i].bt,P[i].at);
	return n;
}

// FCFS Algorithm
void FCFS(processes P[],int n){
	processes temp[10];
	int sumw=0,sumt=0;
	int x = 0;
	float avgwt=0.0,avgta=0.0;
	int i,j;
	for(i=0;i<n;i++)
		temp[i]=P[i];

	b_sort(temp,n);

		printf("\n\n PROCESSES\tBURST-TIME\tARRIVAL-TIME");
		for(i=0;i<n;i++)
			printf("\n %s \t\t %d \t\t %d",temp[i].name,temp[i].bt,temp[i].at);

		sumw = temp[0].wt = 0;
		sumt = temp[0].ta = temp[0].bt - temp[0].at;
		temp[0].ct=temp[0].at+temp[0].ta;
		for(i=1;i<n;i++){
			temp[i].wt = (temp[i-1].bt + temp[i-1].at + temp[i-1].wt) - temp[i].at;;
			temp[i].ta = (temp[i].wt + temp[i].bt);
			temp[i].ct=(temp[i].at+temp[i].ta);
			sumw+=temp[i].wt;
			sumt+=temp[i].ta;
		}
		avgwt = (float)sumw/n;
		avgta = (float)sumt/n;
		printf("\n\n PROCESSES\tBURST-TIME\tARRIVAL-TIME\tCOMPLETION-TIME\tWAITING-TIME\tTURN-AROUND-TIME\t");
		for(i=0;i<n;i++)
			printf("\n %s \t\t %d \t\t %d \t\t %d \t\t %d \t\t\t %d",temp[i].name,temp[i].bt,temp[i].at,temp[i].ct,temp[i].wt,temp[i].ta);
		
		printf("\n\n GANTT CHART\n ");
         printf("|0|\t<A>\t ");
		 for(i=1;i<=n;i++){
		 	x+=temp[i-1].bt;
		 	printf("|%d|\t",x);
            if(i!=n){
                printf("<%s>\t",temp[i].name);
            }
		 }
		printf("\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.",avgwt,avgta);
}

//SHORTEST REMAINING TIME FIRST - Pre-emptive (Shortest Job First WITH PREEMPTION)
void SRTF(processes P[],int n){
	int i,t_total=0,tcurr,b[10],min_at,j,x,min_bt;
	int sumw=0,sumt=0;
	float avgwt=0.0,avgta=0.0;
	processes temp[10],t;

	for(i=0;i<n;i++){
		temp[i]=P[i];
		t_total+=P[i].bt;
	}

	b_sort(temp,n);

	for(i=0;i<n;i++)
		b[i] = temp[i].bt;

	i=j=0;
	printf("\n GANTT CHART\n\n |%d|  <%s> ",i,temp[i].name);
	for(tcurr=0;tcurr<t_total;tcurr++){

		if(b[i] > 0 && temp[i].at <= tcurr)
			b[i]--;

		if(i!=j)
			printf(" |%d|  <%s>  ",tcurr,temp[i].name);

		if(b[i]<=0 && temp[i].flag != 1){
		
			temp[i].flag = 1;
			temp[i].wt = (tcurr+1) - temp[i].bt - temp[i].at;
			temp[i].ta = (tcurr+1) - temp[i].at;
			sumw+=temp[i].wt;
			sumt+=temp[i].ta;
		}
		j=i;	min_bt = 999;
		for(x=0;x<n;x++){
		
			if(temp[x].at <= (tcurr+1) && temp[x].flag != 1){
			
				if(min_bt != b[x] && min_bt > b[x]){
					min_bt = b[x];
					i=x;
				}
			}
		}
		
	}
	for(i=0;i<n;i++)
		temp[i].ct=temp[i].at+temp[i].ta;
	printf("|%d|",tcurr);
	avgwt = (float)sumw/n;	avgta = (float)sumt/n;
	printf("\n\n PROCESSES\tBURST-TIME\tARRIVAL-TIME\tCOMPLETION-TIME\tWAITING-TIME\tTURN-AROUND-TIME");
		for(i=0;i<n;i++)
			printf("\n %s \t\t %d \t\t %d \t\t %d\t\t %d\t\t %d",temp[i].name,temp[i].bt,temp[i].at,temp[i].ct,temp[i].wt,temp[i].ta);
	printf("\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.",avgwt,avgta);
}

//MAIN FUNCTION WITCH BINDS WHOLE PROGRAMM
int main(){
	printf("\n\n SIMULATION OF CPU SCHEDULING ALGORITHMS\n");
	processes P[10];
	int ch,n;
	do{
        printf("\n--------------------------------------------");
		printf("\n Options:");
        printf("\n ");
		printf("\n 0. Enter process data.");
		printf("\n 1. FCFS");
		printf("\n 2. SRTF (Pre-emptive)");
		printf("\n 3. Exit");
        printf("\n--------------------------------------------");
        printf("\n SELECT : ");
		scanf("%d",&ch);
		switch(ch){
			case 0:
				n=accept(P);
				break;
			case 1:
				FCFS(P,n);
				break;
			case 2:
				SRTF(P,n);
				break;
			case 3:exit(0);	
		}
	}while(ch != 3);
	getch();
	return 0;
}