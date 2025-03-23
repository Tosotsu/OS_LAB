# Experiment 9: Page Replacement Algorithms

## Overview
This experiment implements two page replacement strategies:
1. First In First Out (FIFO) (`fifo.c`)
2. Least Recently Used (LRU) (`lrume.c`)

## Algorithm Implementations

### 1. FIFO Implementation (`fifo.c`)
```c
// Key variables
int p[50];    // Page reference string
int fr[50];   // Frame array
int hit = 0;  // Hit counter
int fault = 0;// Page fault counter
int fi = 0;   // FIFO index

// Core FIFO logic
for(i = 0; i < n; i++) {
    printf("%d\t", p[i]);
    found = 0;
    
    // Check if page exists in frames
    for(k = 0; k < f; k++) {
        if(fr[k] == p[i]) {
            found = 1;
            hit++;
            for(j = 0; j < f; j++)
                printf("%d\t", fr[j]);    
            printf("hit\n");
            break;
        }
    }
    
    // If page fault occurs
    if(!found) {
        fr[fi] = p[i];
        fault++;
        fi = (fi + 1) % f;  // Circular update of FIFO index
        for(j = 0; j < f; j++)
            printf("%d\t", fr[j]);    
        printf("fault\n");
    }
}
```

The FIFO algorithm:
- Maintains a circular queue of frames
- Replaces oldest page when fault occurs
- Uses modulo operator for circular indexing
- Tracks hits and faults separately
- Displays frame state after each reference

### 2. LRU Implementation (`lrume.c`)
```c
// Frame structure with counter
struct frame {
    int frm;     // Frame content
    int fcount;  // Usage counter
} fr[10];

// Core LRU logic
for(i = 0; i < n; i++) {
    printf("%d\t", p[i]);
    found = 0;
    
    // Check if page exists in frames
    for(k = 0; k < f; k++) {
        if(fr[k].frm == p[i]) {
            found = 1;
            hit++;
            fr[k].fcount++;  // Update usage counter
            for(j = 0; j < f; j++)
                printf("%d\t", fr[j].frm);
            printf("\tHit \t\n");
            break;
        }
    }
    
    // If page fault occurs
    if(!found) {
        // Find least recently used frame
        least = fr[0].fcount;
        fi = 0;
        for(k = 0; k < f; k++) {
            if(fr[k].fcount < least) {
                least = fr[k].fcount;
                fi = k;
            }
        }
        
        // Replace frame and update counter
        fr[fi].frm = p[i];
        fr[fi].fcount++;
        fault++;
        
        for(j = 0; j < f; j++)
            printf("%d\t", fr[j].frm);
        printf("\tFault\n");
    }
}
```

The LRU algorithm:
- Uses a structure to track frame and its usage
- Maintains a counter for each frame
- Replaces frame with lowest counter value
- Updates counter on each access
- Provides detailed hit/fault information

## Input Format
```
For both algorithms:
1. Number of pages (n)
2. Page reference string
3. Number of frames (f)
```

## Output Format
```
FIFO Output:
page    frame           hit/fault
4       4       -1      -1      fault
7       4       7       -1      fault
6       4       7       6       fault
1       1       7       6       fault
7       1       7       6       hit
6       1       7       6       hit
1       1       7       6       hit
2       1       2       6       fault
7       1       2       7       fault
2       1       2       7       hit

LRU Output:
PAGES   FRAMES          HIT     FAULTS
4       4       -1      -1      Fault
7       4       7       -1      Fault
6       4       7       6       Fault
1       1       7       6       Fault
7       1       7       6       Hit
6       1       7       6       Hit
1       1       7       6       Hit
2       2       7       6       Fault
7       2       7       6       Hit
2       2       7       6       Hit
```

## Example Execution

### FIFO Example
```
Enter no of pages: 10
Enter control string:
4 7 6 1 7 6 1 2 7 2
Enter no of frames: 3

page    frame           hit/fault
4       4       -1      -1      fault
7       4       7       -1      fault
6       4       7       6       fault
1       1       7       6       fault
7       1       7       6       hit
6       1       7       6       hit
1       1       7       6       hit
2       1       2       6       fault
7       1       2       7       fault
2       1       2       7       hit

No of pages faults: 6
No of pages hit: 4
```

### LRU Example
```
Enter no of pages: 10
Enter control string:
4 7 6 1 7 6 1 2 7 2
Enter no of frames: 3

PAGES   FRAMES          HIT     FAULTS
4       4       -1      -1      Fault
7       4       7       -1      Fault
6       4       7       6       Fault
1       1       7       6       Fault
7       1       7       6       Hit
6       1       7       6       Hit
1       1       7       6       Hit
2       2       7       6       Fault
7       2       7       6       Hit
2       2       7       6       Hit

The no of page faults is 5
The no of page hits is 5
```

## Performance Analysis

### Time Complexity
1. FIFO: O(n × f)
   - n = number of page references
   - f = number of frames
   - Linear search for page in frames

2. LRU: O(n × f)
   - Additional overhead for counter maintenance
   - Linear search for least recently used frame

### Space Complexity
1. FIFO: O(f)
   - f = number of frames
   - Simple array storage

2. LRU: O(f)
   - Additional counter per frame
   - Structure-based storage

## Implementation Considerations

1. **Array Limitations**
   - FIFO: Maximum 50 pages/frames
   - LRU: Maximum 10 frames

2. **Data Structures**
   - FIFO: Simple arrays
   - LRU: Structure with frame and counter

3. **Counter Management**
   - FIFO: No counters needed
   - LRU: Counter per frame

## Common Issues and Solutions

1. **FIFO Issues**
   - Issue: Belady's Anomaly possible
   - Solution: Monitor fault rate with frame changes

2. **LRU Issues**
   - Issue: Counter overflow possible
   - Solution: Periodic counter reset
   - Issue: Linear search overhead
   - Solution: Consider heap implementation

## Usage Guidelines

1. Use **FIFO** when:
   - Simple implementation needed
   - Memory constraints exist
   - Quick decision making required

2. Use **LRU** when:
   - Better hit ratio needed
   - Can afford counter overhead
   - Memory access patterns are localized 