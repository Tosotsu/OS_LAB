#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct process {
    char pname[4]; 
    int bt,wt,tt,pr;       
} p[10], temp;

void main() {
    int n, i, j;
    float avgwt = 0, avgtt = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter the process name: ");
        scanf("%s", p[i].pname); 
        printf("Enter the burst time: ");
        scanf("%d", &p[i].bt);
        printf("Enter the priority: ");
        scanf("%d", &p[i].pr); 
    }


    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (p[j].pr > p[j + 1].pr) { 
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

  
    int currentTime = 0;
    for (i = 0; i < n; i++) {
        p[i].wt = currentTime; 
        currentTime += p[i].bt; 
    }

    for (i = 0; i < n; i++) {
        p[i].tt = p[i].wt + p[i].bt; 
    }

    
    printf("\nProcess Name\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%s\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               p[i].pname, p[i].bt, 
               p[i].pr, p[i].wt, p[i].tt);
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
        if (i < n - 1) {
            printf(" --> "); 
        }
    }
    
    printf("\n"); 
}

