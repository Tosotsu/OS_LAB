#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Variable declarations
    int i, j, n, bu[10], wa[10], tat[10], ct[10], max, t;
    float awt=0, att=0, temp=0;
    
    /* 
    n = number of processes
    bu[] = remaining burst time for each process
    wa[] = waiting time for each process
    tat[] = turnaround time for each process
    ct[] = original burst time for each process (copy)
    max = maximum burst time among all processes
    t = time quantum/slice for Round Robin
    awt = average waiting time
    att = average turnaround time
    temp = current time in simulation
    */
    
    // Get the number of processes from user
    printf("Enter the no of processes -- ");
    scanf("%d",&n);
    
    // Input burst time for each process
    for(i=0;i<n;i++)
    {
        printf("\nEnter Burst Time for process %d -- ", i+1);
        scanf("%d",&bu[i]);
        ct[i]=bu[i]; // Store original burst time for later calculations
    }
    
    // Get time quantum for Round Robin
    printf("\nEnter the size of time slice -- ");
    scanf("%d",&t);
    
    // Find the maximum burst time (used to determine number of iterations)
    max=bu[0];
    for(i=1;i<n;i++)
        if(max<bu[i])
            max=bu[i];
            
    // Round Robin scheduling algorithm implementation
    // Outer loop: Each iteration represents one complete round of execution
    for(j=0;j<(max/t)+1;j++)
        // Inner loop: Iterate through all processes
        for(i=0;i<n;i++)
            if(bu[i]!=0) // Only consider processes that have remaining burst time
                if(bu[i]<=t) // If process can complete in this time slice
                {
                    tat[i]=temp+bu[i]; // Calculate turnaround time (current time + remaining burst)
                    temp=temp+bu[i]; // Update current time
                    bu[i]=0; // Mark process as completed
                }
                else // Process needs more time than the current slice
                {
                    bu[i]=bu[i]-t; // Subtract time quantum from remaining burst time
                    temp=temp+t; // Increment current time by time quantum
                }
                
    // Calculate waiting time and summary statistics
    for(i=0;i<n;i++)
    {
        wa[i]=tat[i]-ct[i]; // Waiting time = Turnaround time - Burst time
        att+=tat[i]; // Sum of all turnaround times
        awt+=wa[i]; // Sum of all waiting times
    }
    
    // Display results
    printf("\nThe Average Turnaround time is -- %f",att/n);
    printf("\nThe Average Waiting time is -- %f",awt/n);
    printf("\n\tPROCESS\t BURST TIME \t WAITING TIME\tTURNAROUND TIME\n");
    
    // Display individual process statistics
    for(i=0;i<n;i++)
        printf("\t%d \t %d \t\t %d \t\t %d \n",i+1,ct[i],wa[i],tat[i]);
        
    
    return 0;
} 