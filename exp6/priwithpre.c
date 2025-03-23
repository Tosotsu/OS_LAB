#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct process {
char pname[4];
int at, bt, wt, tt, ct, rt, priority;
int remaining_bt; // To keep track of remaining burst time
} p[10], temp;

void main() {
int n, i, j;
float avgwt = 0, avgtt = 0, avgrt = 0;

printf("Enter the number of processes: ");
scanf("%d", &n);

for (i = 0; i < n; i++) {
printf("Enter the process name: ");
scanf("%s", p[i].pname);
printf("Enter the arrival time: ");
scanf("%d", &p[i].at);
printf("Enter the burst time: ");
scanf("%d", &p[i].bt);
printf("Enter the priority: ");
scanf("%d", &p[i].priority);
p[i].rt = -1;
p[i].remaining_bt = p[i].bt; // Initialize remaining burst time
}

// Sort processes by arrival time and priority
for (i = 0; i < n - 1; i++) {
for (j = 0; j < n - i - 1; j++) {
if (p[j].at > p[j + 1].at ||
(p[j].at == p[j + 1].at && p[j].priority > p[j + 1].priority)) {
temp = p[j];
p[j] = p[j + 1];
p[j + 1] = temp;
}
}
}

int currentTime = 0;
int completed = 0;
int isCompleted[10] = {0};

while (completed < n) {
int idx = -1;

// Find the highest priority process that has arrived and is not completed
for (i = 0; i < n; i++) {
if (!isCompleted[i] && p[i].at <= currentTime) {
if (idx == -1 || p[i].priority < p[idx].priority) {
idx = i;
}
}
}

if (idx != -1) {
// If this is the first time the process is being executed
if (p[idx].rt == -1) {
p[idx].rt = currentTime - p[idx].at;
}

// Execute the process for one time unit
currentTime++;
p[idx].remaining_bt--;

// Check if the process is completed
if (p[idx].remaining_bt == 0) {
p[idx].ct = currentTime;
p[idx].wt = currentTime - p[idx].at - p[idx].bt;
completed++;
isCompleted[idx] = 1;
}
} else {
currentTime++; // No process is ready to execute
}
}

// Calculate turnaround time for each process
for (i = 0; i < n; i++) {
p[i].tt = p[i].wt + p[i].bt;
}

// Print results
printf("\nPName\tPr\tAT\tBT\tWT\tTT\tCT\tRT\n");
for (i = 0; i < n; i++) {
printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
p[i].pname, p[i].priority, p[i].at, p[i].bt, p[i].wt, p[i].tt, p[i].ct, p[i].rt);
}

// Calculate averages
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

for (i = 0; i < n; i++) {
avgrt += p[i].rt;
}
avgrt /= n;
printf("Average Response Time = %f\n", avgrt);


printf("\nGantt Chart:\n");

currentTime = 0;

while (completed < n) {
int idx = -1;

for (i = 0; i < n; i++) {
if (!isCompleted[i] && p[i].at <= currentTime) {
if (idx == -1 || p[i].priority < p[idx].priority) {
idx = i;
}
}
}

if (idx != -1) {
while (p[idx].remaining_bt > 0 && completed < n) {
printf("%s --> (%d)", p[idx].pname, ++currentTime);
p[idx].remaining_bt--;

if (p[idx].remaining_bt == 0) { // Process finished execution
completed++;
isCompleted[idx] = 1;
break;
}

// Check for preemption after each time unit
for (j = 0; j < n; j++) {
if (!isCompleted[j] && j != idx && p[j].at <= currentTime &&
(idx == -1 || p[j].priority < p[idx].priority)) {
idx = j;
break;
}
}
}
} else {
currentTime++; // No process is ready to execute
}

}

printf("\n");
}
