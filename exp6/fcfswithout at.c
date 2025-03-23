#include <stdio.h>
#include <stdlib.h>

struct process {
    char pname[4];
    int bt, wt, tt, ct; 
} p[10];

void main() {
    int n, i;
    float avgwt = 0, avgtt = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter the process name: ");
        scanf("%s", p[i].pname);
        printf("Enter the burst time: ");
        scanf("%d", &p[i].bt);
    }

   
    p[0].wt = 0; 
    for (i = 1; i < n; i++) {
        p[i].wt = p[i - 1].bt + p[i - 1].wt;
    }

   
    for (i = 0; i < n; i++) {
        p[i].tt = p[i].wt + p[i].bt;
        p[i].ct = p[i].tt; 
    }

    
    printf("\nProcess Name\tBurst Time\tWaiting Time\tTurnaround Time\tCompletionTime\n");
    for (i = 0; i < n; i++) {
        printf("%s\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               p[i].pname, p[i].bt, p[i].wt, p[i].tt, p[i].ct);
    }

    
    for (i = 0; i < n; i++) {
        avgwt += p[i].wt;
    }
    avgwt /= n;
    printf("Average Waiting Time = %f\n", avgwt);

    
    for (i = 0; i < n; i++) {
        avgtt += p[i].tt;
    }
    avgtt /= n;
    printf("Average Turnaround Time = %f\n", avgtt);

    
    printf("\nGantt Chart:\n");
    int totalBurstTime = 0; 
    for (i = 0; i < n; i++) {
        totalBurstTime += p[i].bt; 
        printf("%s --> (%d)", p[i].pname, totalBurstTime); 
        }
    printf("\n");
}

