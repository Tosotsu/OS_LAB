# Experiment 8: Memory Management Algorithms

## Overview
This experiment implements three memory allocation strategies:
1. First Fit (`firstfit.c`)
2. Best Fit (`bestfit.c`)
3. Enhanced Best Fit (`bestme.c`)

## Algorithm Implementations

### 1. First Fit (`firstfit.c`)
```c
// Key variables
int psize[10];  // Process sizes
int bsize[10];  // Block sizes
int all[10];    // Allocation array
int flag[10];   // Block allocation status

// Core allocation logic
for(i=1; i<=n; i++) {
    for(j=1; j<=m; j++) {
        if((bsize[j] >= psize[i]) && (flag[j] == 0)) {
            all[i] = j;
            flag[j] = 1;
            break;
        }
    }
}
```

The First Fit algorithm:
- Takes process sizes and block sizes as input
- For each process, scans blocks sequentially
- Allocates first block that is large enough
- Uses flag array to track allocated blocks
- Stores allocation results in all[] array

### 2. Best Fit (`bestfit.c`)
```c
// Key variables
int bsize[10];  // Block sizes
int bno[10];    // Block numbers
int process[10]; // Process sizes
int flag[10];   // Block allocation status

// Sort blocks by size
for(i=0; i<n-1; i++) {
    for(j=i+1; j<n; j++) {
        if(bsize[i] > bsize[j]) {
            // Swap block sizes
            temp = bsize[i];
            bsize[i] = bsize[j];
            bsize[j] = temp;
            // Maintain block numbers
            temp = bno[i];
            bno[i] = bno[j];
            bno[j] = temp;
        }
    }
}

// Allocation logic
for(i=0; i<m; i++) {
    for(j=0; j<n; j++) {
        if(process[i] <= bsize[j] && flag[j] == 0) {
            flag[j] = 1;
            break;
        }
    }
}
```

The Best Fit algorithm:
- Sorts blocks in ascending order by size
- Maintains original block numbers during sorting
- Allocates process to smallest sufficient block
- Uses flag array to track allocations

### 3. Enhanced Best Fit (`bestme.c`)
```c
// Key variables
int bsize[10];  // Block sizes
int bno[10];    // Block numbers
int process[10]; // Process sizes
int flag[10];   // Block allocation status

// Enhanced sorting with flag maintenance
for(i = 0; i < n-1; i++) {
    for(j = i+1; j < n; j++) {
        if(bsize[i] > bsize[j]) {
            // Swap block sizes
            temp = bsize[i];
            bsize[i] = bsize[j];
            bsize[j] = temp;
            
            // Swap block numbers
            temp = bno[i];
            bno[i] = bno[j];
            bno[j] = temp;
            
            // Maintain allocation flags
            temp = flag[i];
            flag[i] = flag[j];
            flag[j] = temp;
        }
    }
}

// Enhanced allocation with status tracking
for(i = 0; i < m; i++) {
    int allocated = 0;
    for(j = 0; j < n; j++) {
        if(process[i] <= bsize[j] && !flag[j]) {
            flag[j] = 1;
            allocated = 1;
            break;
        }
    }
    // Status reporting
    if(allocated) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\tAllocated\n", 
              i+1, process[i], bno[j], bsize[j]);
    } else {
        printf("%d\t\t%d\t\t-\t\t-\t\tNot Allocated\n", 
              i+1, process[i]);
    }
}
```

The Enhanced Best Fit algorithm:
- Improves on Best Fit with better status tracking
- Maintains allocation flags during sorting
- Provides detailed allocation status reporting
- Better handles allocation failures

## Input Format
```
For all algorithms:
1. Number of blocks (n)
2. Size of each block
3. Number of processes (m)
4. Size of each process
```

## Output Format
```
Process No    Process Size    Block No    Block Size    Status
1            23              3           30            Allocated
2            12              1           15            Allocated
3            20              -           -             Not Allocated
```

## Example Execution

### First Fit Example
```
Enter the no of process: 3
Enter the process size: 23
Enter the process size: 6
Enter the process size: 7
Enter the no of block: 3
Enter the block size: 12
Enter the block size: 20
Enter the block size: 30

process no    process size    block size    allocated block
1            23              12            3
2            6               20            1
3            7               30            2
```

### Best Fit Example
```
Enter the no of block: 3
Enter the size of block: 15
Enter the size of block: 30
Enter the size of block: 12
Enter the no of process: 2
Enter the size of process 1: 10
Enter the size of process 2: 20

process no    process size    block    block size
1            10              3        12
2            20              1        30
```

## Common Issues and Solutions

1. **Memory Fragmentation**
   - First Fit: High external fragmentation
   - Best Fit: Better fragmentation handling
   - Enhanced Best Fit: Best fragmentation management

2. **Performance**
   - First Fit: O(n) search time
   - Best Fit: O(n log n) due to sorting
   - Enhanced Best Fit: O(n log n) with better allocation

3. **Implementation Considerations**
   - Array size limitations (max 10)
   - No memory compaction
   - Static allocation only

## Usage Guidelines

1. Use **First Fit** when:
   - Quick allocation is priority
   - Memory blocks are similarly sized
   - Simple implementation needed

2. Use **Best Fit** when:
   - Memory utilization is important
   - Block sizes vary significantly
   - Can afford sorting overhead

3. Use **Enhanced Best Fit** when:
   - Need detailed allocation tracking
   - Memory utilization is critical
   - Better error handling required 