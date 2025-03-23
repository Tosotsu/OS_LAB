# CPU Scheduling Algorithms Comparison

## Code Structure Differences

### 1. Process Structure Variations

```c
// FCFS without AT
struct process {
    char pname[20];
    int bt, wt, tt, ct;
}

// FCFS/SJF with AT
struct process {
    char pname[20];
    int at, bt, wt, tt, ct;
}

// Priority with AT
struct process {
    char pname[20];
    int at, bt, wt, tt, ct, priority;
}
```

## Completion Time Calculation Methods

### 1. FCFS Without Arrival Time (`fcfswithout at.c`)
```c
int currentTime = 0;
for (i = 0; i < n; i++) {
    p[i].ct = currentTime + p[i].bt;  // Simple addition
    currentTime = p[i].ct;
    p[i].tt = p[i].ct;                // TT = CT (since AT = 0)
    p[i].wt = p[i].tt - p[i].bt;      // WT = TT - BT
}
```
**Key Points:**
- No sorting needed
- Sequential execution
- CT = Previous CT + BT
- No idle time consideration

### 2. FCFS With Arrival Time (`fcfswithat.c`)
```c
// First sort by arrival time
for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - i - 1; j++) {
        if (p[j].at > p[j + 1].at) {
            temp = p[j];
            p[j] = p[j + 1];
            p[j + 1] = temp;
        }
    }
}

int currentTime = 0;
for (i = 0; i < n; i++) {
    if (currentTime < p[i].at) {
        currentTime = p[i].at;    // Handle CPU idle time
    }
    p[i].wt = currentTime - p[i].at;
    currentTime += p[i].bt;
    p[i].ct = currentTime;
    p[i].tt = p[i].ct - p[i].at;
}
```
**Key Points:**
- Requires sorting by arrival time
- Handles CPU idle time
- CT considers arrival time
- WT = Start time - AT

### 3. SJF Without Arrival Time (`sjfs.c`)
```c
// Sort by burst time
for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - i - 1; j++) {
        if (p[j].bt > p[j + 1].bt) {
            temp = p[j];
            p[j] = p[j + 1];
            p[j + 1] = temp;
        }
    }
}

p[0].wt = 0;
for (i = 1; i < n; i++) {
    p[i].wt = p[i-1].bt + p[i-1].wt;
}

for (i = 0; i < n; i++) {
    p[i].tt = p[i].wt + p[i].bt;
    p[i].ct = p[i].tt;           // CT = TT (since AT = 0)
}
```
**Key Points:**
- Sorts by burst time only
- CT equals TT (no arrival time)
- Minimizes average waiting time

### 4. SJF With Arrival Time (`sjfwithat.c`)
```c
int currentTime = 0;
int completed = 0;
while (completed < n) {
    int shortest = -1;
    int minBurst = INT_MAX;
    
    // Find shortest job among arrived processes
    for (i = 0; i < n; i++) {
        if (p[i].at <= currentTime && !p[i].completed && 
            p[i].bt < minBurst) {
            shortest = i;
            minBurst = p[i].bt;
        }
    }
    
    if (shortest == -1) {
        currentTime++;
        continue;
    }
    
    p[shortest].ct = currentTime + p[shortest].bt;
    p[shortest].tt = p[shortest].ct - p[shortest].at;
    p[shortest].wt = p[shortest].tt - p[shortest].bt;
    p[shortest].completed = 1;
    completed++;
    currentTime = p[shortest].ct;
}
```
**Key Points:**
- Dynamic selection of shortest job
- Considers both AT and BT
- Handles CPU idle time
- More complex implementation

### 5. Priority with Preemption (`priwithpre.c`)
```c
int currentTime = 0;
int completed = 0;
while (completed < n) {
    int highest = -1;
    int maxPriority = -1;
    
    // Find highest priority among arrived processes
    for (i = 0; i < n; i++) {
        if (p[i].at <= currentTime && !p[i].completed && 
            p[i].priority > maxPriority) {
            highest = i;
            maxPriority = p[i].priority;
        }
    }
    
    if (highest == -1) {
        currentTime++;
        continue;
    }
    
    p[highest].rt--;  // Reduce remaining time
    currentTime++;
    
    if (p[highest].rt == 0) {
        p[highest].ct = currentTime;
        p[highest].tt = p[highest].ct - p[highest].at;
        p[highest].wt = p[highest].tt - p[highest].bt;
        p[highest].completed = 1;
        completed++;
    }
}
```
**Key Points:**
- Preemptive execution
- Considers priority and AT
- Process can be interrupted
- Most complex CT calculation

## Completion Time Comparison Table

| Algorithm | Completion Time Formula | Considerations |
|-----------|------------------------|----------------|
| FCFS w/o AT | CT = Previous CT + BT | Sequential only |
| FCFS w/ AT | CT = max(Current Time, AT) + BT | Idle time possible |
| SJF w/o AT | CT = Sum of previous BTs | Shortest first |
| SJF w/ AT | CT = Current Time + BT of shortest | Dynamic selection |
| Priority w/ Pre | CT = Time when RT becomes 0 | Can be interrupted |

## Key Implementation Differences

1. **Sorting Requirements**
   - FCFS w/o AT: No sorting
   - FCFS w/ AT: Sort by arrival time
   - SJF w/o AT: Sort by burst time
   - SJF w/ AT: Dynamic selection
   - Priority: Dynamic by priority

2. **Time Calculations**
   ```
   Without AT:
   CT = Previous CT + BT
   TT = CT
   WT = TT - BT
   
   With AT:
   CT = max(Current Time, AT) + BT
   TT = CT - AT
   WT = TT - BT
   ```

3. **Process Selection**
   - FCFS: Sequential
   - SJF: Shortest burst time
   - Priority: Highest priority
   - With AT: Must check arrival time
   - Preemptive: Can interrupt

## Visual Comparison of CT Calculation

```
FCFS without AT:
0    3    7      12
|----|----|-------|
P1   P2   P3   
CT=BT CT=3+4 CT=7+5

FCFS with AT:
0  2    6    9      14
|-|----|----|-------|
  P1   P2   P3   
  AT=2 AT=4 AT=6

SJF with AT:
0  2  4    8      14
|-|--|----|-------|
  P3 P2   P1   
  BT=2 BT=4 BT=6
``` 