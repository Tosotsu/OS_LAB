# CPU Scheduling Algorithms (Experiment 6)

This experiment implements various CPU scheduling algorithms to understand process scheduling in operating systems.

## Core Concepts

### Process Attributes
```c
struct process {
    char pname[20];    // Process name
    int at;           // Arrival time
    int bt;           // Burst time
    int wt;           // Waiting time
    int tt;           // Turnaround time
    int ct;           // Completion time
};
```

### Time Metrics
```
Waiting Time (WT) = Start Time - Arrival Time
Turnaround Time (TT) = Completion Time - Arrival Time
                     = Waiting Time + Burst Time
Completion Time (CT) = Time at which process completes execution
```

## 1. First Come First Serve (FCFS) with Arrival Time

### Algorithm Explanation
FCFS is the simplest scheduling algorithm that executes processes in the order they arrive.

```
Visual Example:

Process  Arrival  Burst
P1         0       6
P2         2       4
P3         4       2

Timeline:
0      6        10     12
|---P1---|---P2---|P3--|

Gantt Chart:
P1 --> (6) P2 --> (10) P3 --> (12)
```

### Implementation Breakdown

```c
// 1. Sort processes by arrival time
for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - i - 1; j++) {
        if (p[j].at > p[j + 1].at) {
            temp = p[j];
            p[j] = p[j + 1];
            p[j + 1] = temp;
        }
    }
}

// 2. Calculate times for each process
int currentTime = 0;
for (i = 0; i < n; i++) {
    // If CPU is idle, move to next arrival
    if (currentTime < p[i].at) {
        currentTime = p[i].at;
    }
    // Calculate waiting time
    p[i].wt = currentTime - p[i].at;
    // Update current time and calculate completion
    currentTime += p[i].bt;
    p[i].ct = currentTime;
}
```

## 2. Shortest Job First (SJF)

### Algorithm Explanation
SJF selects the process with the shortest burst time next.

```
Visual Example:

Process  Burst
P1        6
P2        4
P3        2

Timeline:
0    2      6        12
|--P3--|--P2--|---P1---|

Gantt Chart:
P3 --> (2) P2 --> (6) P1 --> (12)
```

### Implementation Breakdown

```c
// 1. Sort processes by burst time
for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - i - 1; j++) {
        if (p[j].bt > p[j + 1].bt) {
            temp = p[j];
            p[j] = p[j + 1];
            p[j + 1] = temp;
        }
    }
}

// 2. Calculate waiting time
p[0].wt = 0;  // First process
for (i = 1; i < n; i++) {
    p[i].wt = p[i-1].bt + p[i-1].wt;
}
```

## Visual Process Flow

```
Input Process:
┌─────────────┐
│ Process Data│
└──────┬──────┘
       │
       ▼
┌─────────────┐
│   Sort by   │
│ Criteria    │
└──────┬──────┘
       │
       ▼
┌─────────────┐
│  Calculate  │
│   Times     │
└──────┬──────┘
       │
       ▼
┌─────────────┐
│   Display   │
│   Results   │
└─────────────┘
```

## Common Metrics Calculation

```
For each process:
1. Waiting Time (WT):
   - FCFS: currentTime - arrival_time
   - SJF: previous_process_completion_time

2. Turnaround Time (TT):
   TT = WT + BT

3. Average Times:
   Average WT = Total WT / number_of_processes
   Average TT = Total TT / number_of_processes
```

## Output Format

```
Process Table:
PName    AT    BT    WT    TT    CT
P1       0     6     0     6     6
P2       2     4     4     8     10
P3       4     2     6     8     12

Gantt Chart:
P1 --> (6) P2 --> (10) P3 --> (12)
```

## Key Differences Between Algorithms

1. **FCFS with Arrival Time**
   - Considers arrival time
   - May have CPU idle time
   - No process preemption
   - Simple but potentially inefficient

2. **SJF**
   - Ignores arrival time
   - No idle time between processes
   - Optimal average waiting time
   - Potential starvation for long processes

## Common Issues and Solutions

1. **Process Starvation**
   - Problem: Long processes never execute
   - Solution: Aging mechanism or hybrid algorithms

2. **Convoy Effect (in FCFS)**
   - Problem: Short processes wait for long ones
   - Solution: Consider using SJF or priority scheduling

3. **CPU Idle Time**
   - Problem: CPU remains idle despite ready processes
   - Solution: Implement work-conserving algorithms

## How to Run

```bash
# Compile
gcc fcfswithat.c -o fcfs
gcc sjfs.c -o sjf

# Run
./fcfs
./sjf

# Input Format
Number of processes: 3
Process name: P1
Arrival time: 0    # Only for FCFS
Burst time: 6
...
```

## Example Test Cases

```
Test Case 1:
Processes: P1(0,6), P2(2,4), P3(4,2)
Expected Output FCFS:
- P1: WT=0, TT=6
- P2: WT=4, TT=8
- P3: WT=6, TT=8

Test Case 2:
Processes: P1(6), P2(4), P3(2)
Expected Output SJF:
- P3: WT=0, TT=2
- P2: WT=2, TT=6
- P1: WT=6, TT=12
``` 