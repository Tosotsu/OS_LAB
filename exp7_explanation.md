# Experiment 7: Banker's Algorithm Implementation

## Overview
The Banker's Algorithm is a deadlock avoidance algorithm that determines whether allocating resources to a process will lead to a safe state or not.

## Code Structure

### 1. Process Structure
```c
struct process {
    char pname[4];           // Process name
    int alloc[10];          // Current allocation
    int max[10];            // Maximum need
    int need[10];           // Remaining need
} p[10];
```

### 2. Key Variables
```c
int available[10];    // Available resources
int finish[10];       // Track completed processes
struct process safer[10];  // Store safe sequence
```

## Algorithm Implementation Breakdown

### 1. Input Phase
```c
// Get process and resource count
printf("Enter the no of process:");
scanf("%d", &n);
printf("Enter no of resources:");
scanf("%d", &res);

// For each process
for(i = 0; i < n; i++) {
    finish[i] = 0;  // Initialize as unfinished
    
    // Get allocation and max needs
    printf("Enter the allocation of %s\n", p[i].pname);
    for(j = 0; j < res; j++)
        scanf("%d", &p[i].alloc[j]);
        
    printf("Enter the max allocation of %s\n", p[i].pname);
    for(j = 0; j < res; j++) {
        scanf("%d", &p[i].max[j]);
        // Calculate remaining need
        p[i].need[j] = p[i].max[j] - p[i].alloc[j];
    }
}
```

### 2. Safety Algorithm
```c
int y = 0;
for(k = 0; k < n; k++) {
    for(i = 0; i < n; i++) {
        if(finish[i] == 0) {  // If process not finished
            flag = 1;
            // Check if needs can be satisfied
            for(j = 0; j < res; j++) {
                if(p[i].need[j] > available[j]) {
                    flag = 0;
                    break;
                }
            }
            if(flag == 1) {
                // Add to safe sequence
                safer[c++] = p[i];
                // Release resources
                for(y = 0; y < res; y++)
                    available[y] += p[i].alloc[y];
                finish[i] = 1;
            }
        }
    }
}
```

## Visual Representation

### 1. Resource Allocation Table
```
Process  Allocation   Max    Need
         R1 R2 R3    R1 R2 R3    R1 R2 R3
P1       0  1  0     7  5  3     7  4  3
P2       2  0  0     3  2  2     1  2  2
P3       3  0  2     9  0  2     6  0  0
P4       2  1  1     2  2  2     0  1  1
```

### 2. Safety Check Process
```
Step 1: Initial State
Available: [3, 3, 2]
Unfinished: [P1, P2, P3, P4]

Step 2: Check Each Process
┌─────────────────────────┐
│ Check if Need ≤ Available│
└─────────────┬───────────┘
              ▼
┌─────────────────────────┐
│ If Yes:                 │
│ 1. Add to safe sequence │
│ 2. Release resources    │
│ 3. Mark as finished    │
└─────────────────────────┘
```

## Example Execution

```
Input:
Number of processes: 4
Number of resources: 3

Process P1:
Allocation: 0 1 0
Max: 7 5 3

Process P2:
Allocation: 2 0 0
Max: 3 2 2

Available: 3 3 2

Output:
Safe Sequence: P2 -> P4 -> P1 -> P3
```

## Key Points to Understand

1. **Resource States**
   ```
   Available = Total - Σ(Allocated)
   Need = Max - Allocation
   ```

2. **Safety Check**
   - Process can run if Need ≤ Available
   - After running, resources are released
   - All processes must complete for safe state

3. **Data Structures Used**
   ```c
   finish[] -> Track completed processes
   safer[] -> Store safe sequence
   available[] -> Track available resources
   ```

## Common Issues and Solutions

1. **Deadlock Situation**
   - Problem: No process can run (Need > Available)
   - Solution: No safe sequence exists

2. **Resource Release**
   ```c
   // When process completes
   available[j] += p[i].alloc[j];  // Release all resources
   ```

3. **Need Calculation**
   ```c
   need[j] = max[j] - alloc[j];  // Must be non-negative
   ```

## Testing the Algorithm

### Test Case 1: Safe State
```
Processes: 4
Resources: 3
Available: [3, 3, 2]

Expected: Find safe sequence
Result: P2 -> P4 -> P1 -> P3
```

### Test Case 2: Unsafe State
```
Processes: 4
Resources: 3
Available: [1, 1, 1]

Expected: No safe sequence
Result: "No safe sequence"
```

## Execution Flow Diagram
```
Input Data
    │
    ▼
Initialize Arrays
    │
    ▼
Calculate Need Matrix
    │
    ▼
Safety Algorithm
    │
    ▼
Check Safe Sequence
    │
    ▼
Output Result
```

## Time Complexity
- Worst case: O(n² × m)
  - n = number of processes
  - m = number of resource types
- Space complexity: O(n × m) 