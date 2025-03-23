# Experiment 10: Disk Scheduling Algorithms

## Overview
This experiment implements three disk scheduling strategies:
1. FCFS (First Come First Serve) (`fcfs.c`)
2. SCAN (Elevator) (`scan.c`)
3. C-SCAN (Circular SCAN) (`cscan.c`)

## Algorithm Implementations

### 1. FCFS Implementation (`fcfs.c`)
```c
// Key variables
int s[30];    // Sequence array
int n;        // Number of requests
int in;       // Initial head position
int tst = 0;  // Total seek time

// Core FCFS logic
printf("moment form :");
printf("%d->%d->", in, s[0]);

// Calculate total seek time
for(i = 0; i < n; i++) {
    tst = tst + abs(s[i] - in);
    in = s[i];
}

// Print movement sequence
for(i = 1; i < n; i++) {
    if(i == (n-1))
        printf("%d", s[i]);
    else
        printf("%d->", s[i]);
}
```

The FCFS algorithm:
- Takes sequence of requests and initial head position
- Processes requests in order of arrival
- Calculates absolute seek time between positions
- Maintains total seek time counter
- Displays movement sequence

### 2. SCAN Implementation (`scan.c`)
```c
// Key variables
int seq[20];  // Request sequence
int initial;  // Initial head position
int pre;      // Previous head position
int max;      // Maximum cylinder count
int total = 0;// Total seek time
int side;     // Direction (1: right, 2: left)

// Sort requests
for(i = 0; i < n-1; i++) {
    for(j = i+1; j < n; j++) {
        if(seq[i] > seq[j]) {
            temp = seq[i];
            seq[i] = seq[j];
            seq[j] = temp;
        }
    }
}

// Determine direction based on previous position
if(pre > initial)
    side = 1;  // Moving right
else
    side = 2;  // Moving left

// Service requests based on direction
if(side == 1) {
    // Move left first
    for(i = pos-1; i >= 0; i--) {
        total += abs(initial - seq[i]);
        printf("->%d", seq[i]);
        initial = seq[i];
    }
    // Then move right
    for(i = pos+1; i < n-1; i++) {
        total += abs(initial - seq[i]);
        printf("->%d", seq[i]);
        initial = seq[i];
    }
} else if(side == 2) {
    // Move right first
    for(i = pos+1; i < n; i++) {
        total += abs(initial - seq[i]);
        printf("->%d", seq[i]);
        initial = seq[i];
    }
    // Then move left
    for(i = pos-1; i > 0; i--) {
        total += abs(initial - seq[i]);
        printf("->%d", seq[i]);
        initial = seq[i];
    }
}
```

The SCAN algorithm:
- Sorts requests in ascending order
- Determines direction from previous head position
- Services requests in one direction until end
- Then reverses direction and services remaining requests
- Calculates total seek time during movement

### 3. C-SCAN Implementation (`cscan.c`)
```c
// Key variables
int seq[20];  // Request sequence
int initial;  // Initial head position
int max;      // Maximum cylinder count
int total = 0;// Total seek time

// Add boundary points to sequence
seq[n] = 0;      // Add minimum cylinder
seq[n+1] = max;  // Add maximum cylinder
seq[n+2] = initial;
n = n + 3;

// Sort all positions
for(i = 0; i < n-1; i++) {
    for(j = i+1; j < n; j++) {
        if(seq[i] > seq[j]) {
            temp = seq[i];
            seq[i] = seq[j];
            seq[j] = temp;
        }
    }
}

// Find initial position in sorted sequence
for(i = 0; i < n; i++)
    if(seq[i] == initial)
        pos = i;

// Service requests in one direction
printf("\nHead movement\n");
printf("%d", initial);
for(i = pos-1; i >= 0; i--) {
    total = total + abs(initial - seq[i]);
    printf("->%d", seq[i]);
    initial = seq[i];
}

// Jump to end and service remaining
for(i = n-1; i > pos; i--) {
    total = total + abs(initial - seq[i]);
    printf("->%d", seq[i]);
    initial = seq[i];
}
```

The C-SCAN algorithm:
- Adds boundary points (0 and max) to sequence
- Sorts all positions including boundaries
- Services requests in one direction only
- Jumps back to start when reaching end
- Calculates total seek time including jumps

## Input Format
```
For all algorithms:
1. Number of requests (n)
2. Request sequence
3. Initial head position
Additional for SCAN/C-SCAN:
4. Maximum cylinder count
5. Previous head position (SCAN only)
```

## Output Format
```
FCFS Output:
moment form: 50->93->183->37->122->14->124->65->67
the total seek time of the sequence is 640

SCAN Output:
Head movement
50->37->14->0->65->67->93->122->124->183
Total seek time = 236

C-SCAN Output:
Head movement
50->37->14->0->183->124->122->93->67->65
Total seek time = 382
```

## Example Execution

### FCFS Example
```
Enter the no of sequence: 8
Enter the sequence: 93 183 37 122 14 124 65 67
Enter the initial number: 50

moment form: 50->93->183->37->122->14->124->65->67
the total seek time of the sequence is 640
```

### SCAN Example
```
Enter the no of sequence: 8
Enter the sequence: 93 183 37 122 14 124 65 67
Enter the initial head position: 50
Enter the previous head position: 60
Enter the maximum cylinder count: 200

Head movement
50->37->14->0->65->67->93->122->124->183
Total seek time = 236
```

### C-SCAN Example
```
Enter the no of sequence: 8
Enter the sequence: 93 183 37 122 14 124 65 67
Enter the initial head position: 50
Enter the maximum cylinder count: 200

Head movement
50->37->14->0->183->124->122->93->67->65
Total seek time = 382
```

## Performance Analysis

### Time Complexity
1. FCFS: O(n)
   - n = number of requests
   - Simple sequential processing

2. SCAN: O(n log n)
   - Sorting overhead
   - Linear traversal in both directions

3. C-SCAN: O(n log n)
   - Sorting overhead
   - Single direction traversal

### Space Complexity
All algorithms: O(n)
- Storage for request sequence
- Additional variables for tracking

## Implementation Considerations

1. **Array Limitations**
   - FCFS: Maximum 30 requests
   - SCAN/C-SCAN: Maximum 20 requests

2. **Direction Handling**
   - FCFS: No direction consideration
   - SCAN: Based on previous position
   - C-SCAN: Always one direction

3. **Boundary Handling**
   - FCFS: No boundaries
   - SCAN: Reverses at boundaries
   - C-SCAN: Jumps from max to min

## Common Issues and Solutions

1. **FCFS Issues**
   - Issue: High seek time
   - Solution: Best for sequential requests

2. **SCAN Issues**
   - Issue: Direction determination
   - Solution: Track previous position

3. **C-SCAN Issues**
   - Issue: Long return seek
   - Solution: Consider request density

## Usage Guidelines

1. Use **FCFS** when:
   - Request pattern is sequential
   - Implementation simplicity needed
   - Fairness is priority

2. Use **SCAN** when:
   - Requests are scattered
   - Want to minimize seek time
   - Both directions are important

3. Use **C-SCAN** when:
   - Uniform service needed
   - One-way scan preferred
   - Can handle longer return seeks 