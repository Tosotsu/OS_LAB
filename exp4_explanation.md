# Experiment 4: Inter-Process Communication Using Shared Memory

This experiment demonstrates Inter-Process Communication (IPC) using shared memory in Linux/Unix systems. The implementation consists of two programs: a client and a server that communicate through a shared memory segment.

## Concept Overview

Shared memory is one of the fastest IPC mechanisms where multiple processes can directly access a common memory segment. Here's how it works:

```
┌──────────────┐                 ┌──────────────┐
│   Client     │                 │    Server    │
│   Process    │                 │   Process    │
└──────┬───────┘                 └──────┬───────┘
       │                                │
       │        ┌──────────────┐       │
       │        │              │       │
       └───────►│    Shared    │◄──────┘
               │    Memory     │
               │              │
               └──────────────┘
```

## Implementation Details

### 1. Client Program (`client.c`)

```c
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>

void main() {
    int shmid, i;
    int *shm, *it, a[10];
    long size = 1000;
    key_t key;
    
    // Get key from user
    printf("Enter the key: ");
    scanf("%d", &key);
    
    // Create shared memory segment
    shmid = shmget(key, size, IPC_CREAT | 0660); 
    
    // Attach to shared memory
    shm = shmat(shmid, NULL, 0);
    it = shm;
    
    // Write data to shared memory
    printf("Enter the elements: ");
    for (i = 0; i < 10; i++) {
        scanf("%d", &a[i]);
        it[i] = a[i]; 
    }
    it[10] = 1; 
}
```

#### Line-by-Line Explanation:

1. **Headers (Lines 1-4):**
   - Include necessary headers for IPC and shared memory operations
   
2. **Variable Declaration (Lines 7-10):**
   - `shmid`: Shared memory segment identifier
   - `shm`, `it`: Pointers to shared memory
   - `size`: Size of shared memory segment (1000 bytes)
   - `key`: Unique key for shared memory identification

3. **Shared Memory Creation (Line 15):**
   - `shmget(key, size, IPC_CREAT | 0660)`
   - Creates a new shared memory segment
   - `0660` sets read/write permissions for user and group

4. **Memory Attachment (Lines 18-19):**
   - `shmat()` attaches the process to shared memory
   - Returns a pointer to the shared memory segment

5. **Data Writing (Lines 22-26):**
   - Reads 10 integers from user
   - Writes them to shared memory
   - Sets a flag (it[10] = 1) to indicate completion

### 2. Server Program (`server.c`)

```c
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>

int main() {
    int shmid;
    int *shm, *it;
    long size = 1000;
    key_t key;
    
    // Get the same key used by client
    printf("Enter the key: ");
    scanf("%d", &key);
    
    // Access existing shared memory
    shmid = shmget(key, size, 0); 
    
    // Attach to shared memory
    shm = shmat(shmid, NULL, 0); 
    it = shm;
    
    // Read and display data
    printf("Server: Received data from client:\n");
    for (int i = 0; i < 10; i++) {
        printf(" %d ", it[i]); 
    }
    printf("\n");
    return 0;
}
```

#### Line-by-Line Explanation:

1. **Headers and Variables (Lines 1-10):**
   - Similar to client program
   
2. **Shared Memory Access (Line 14):**
   - `shmget()` without IPC_CREAT flag
   - Accesses existing shared memory segment
   
3. **Memory Attachment (Lines 17-18):**
   - Attaches to the same shared memory segment
   
4. **Data Reading (Lines 21-24):**
   - Reads and displays the integers written by client

## Visual Example of Execution

```
Terminal 1 (Client)                Terminal 2 (Server)
─────────────────────             ─────────────────────
$ gcc client.c -o client          $ gcc server.c -o server
$ ./client                        $ ./server
Enter the key: 1234               Enter the key: 1234
Enter the elements:               Server: Received data from client:
10 20 30 40 50                    10  20  30  40  50  60  70  80  90  100
60 70 80 90 100
```

## Memory Layout Visualization

```
Shared Memory Segment (1000 bytes)
┌────────────────────────────────────────┐
│  10  │  20  │  30  │  40  │  50  │    │
├────────────────────────────────────────┤
│  60  │  70  │  80  │  90  │ 100  │  1 │
└────────────────────────────────────────┘
   ▲                                  ▲
   │                                  │
   └── Data Array (10 integers)       └── Flag
```

## How to Run

1. Compile both programs:
   ```bash
   gcc client.c -o client
   gcc server.c -o server
   ```

2. Run the client first:
   ```bash
   ./client
   ```

3. In another terminal, run the server:
   ```bash
   ./server
   ```

4. Use the same key value in both programs.

## Key Concepts Demonstrated

1. **Shared Memory Operations:**
   - Creation (`shmget`)
   - Attachment (`shmat`)
   - Access permissions

2. **Process Synchronization:**
   - Using same key for shared memory access
   - Simple flag-based synchronization

3. **Data Sharing:**
   - Direct memory access between processes
   - Array data transfer

## Common Issues and Solutions

1. **Permission Denied:**
   - Ensure proper permissions (0660) are set
   - Run both programs as same user

2. **Invalid Key:**
   - Use same key value in both programs
   - Key should be a positive integer

3. **Segment Exists:**
   - Remove existing segments if needed:
   ```bash
   ipcrm -M <key>
   ``` 

## Additional Example: Shared Memory with Sorting

This implementation shows how to use shared memory for sorting elements between client and server processes.

### 1. Client Program (Alternative Implementation)

```c
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<stdlib.h>

void main()
{
    int shmid, i;
    int *shm, *it, a[10], s;
    long size = 1000;
    key_t key;
    
    printf("Enter the key: ");
    scanf("%d", &key);
    
    // Create shared memory with read/write for all (0666)
    shmid = shmget(key, size, IPC_CREAT | 0666);
    shm = shmat(shmid, NULL, 0);
    it = shm;
    
    // Input elements directly into shared memory
    printf("Enter the elements: ");
    for(i = 0; i < 5; i++) {
        scanf("%d", (it+i));
    }
    
    printf("------------------------------\n");
    sleep(100);  // Wait for server to process
    
    // Read and display sorted elements
    it = shm;    
    for(i = 0; i < 5; i++) {
        printf("%d\n", *(it+i));
        s = s + (*it);
    }
}
```

### 2. Server Program (Sorting Implementation)

```c
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/shm.h>

void main()
{
    int shmid, i, s=0;
    int *shm, *it, j, t;
    long size = 1000;
    key_t key;
    
    printf("Enter the key: ");
    scanf("%d", &key);
    
    shmid = shmget(key, size, IPC_CREAT | 0666);
    shm = shmat(shmid, NULL, 0);
    it = shm;
    
    printf("Elements are: ");
    
    // Bubble sort implementation on shared memory
    for(i = 0; i < 5; i++)
        for(j = 0; j < 5-i-1; j++)
            if (*(it+j) > *(it+j+1)) {
                t = *(it+j);
                *(it+j) = *(it+j+1);
                *(it+j+1) = t;
            }
    
    // Display sorted elements
    it = shm;    
    for(i = 0; i < 5; i++) {
        printf("%d\n", *(it+i));
        s = s + (*it);
    }
}
```

### Key Differences from Previous Implementation

1. **Direct Memory Access:**
   - Uses pointer arithmetic (`it+i`) for memory access
   - Writes directly to shared memory without intermediate array

2. **Sorting Functionality:**
   - Server implements bubble sort on shared memory
   - In-place sorting of shared memory segment

3. **Synchronization:**
   - Uses `sleep(100)` in client for simple synchronization
   - Allows server time to sort the data

### Example Execution

```
Terminal 1 (Client)                Terminal 2 (Server)
─────────────────────             ─────────────────────
$ gcc client.c -o client          $ gcc server.c -o server
$ ./client                        $ ./server
Enter the key: 5678               Enter the key: 5678
Enter the elements:               Elements are:
30 10 50 20 40                   10
                                 20
                                 30
                                 40
                                 50
```

### Memory Layout During Sorting

```
Before Sorting:
┌────────────────────────────┐
│  30  │  10  │  50  │  20  │  40  │
└────────────────────────────┘

During Sorting (Bubble Sort):
Step 1: │  10  │  30  │  50  │  20  │  40  │
Step 2: │  10  │  30  │  20  │  50  │  40  │
Step 3: │  10  │  20  │  30  │  50  │  40  │
Final:  │  10  │  20  │  30  │  40  │  50  │
```

### Implementation Notes

1. **Memory Access:**
   - Uses pointer arithmetic for efficient memory access
   - Direct manipulation of shared memory contents

2. **Sorting Algorithm:**
   - Implements bubble sort in shared memory
   - Operates directly on shared memory segment
   - No need for additional memory allocation

3. **Synchronization:**
   - Basic synchronization using sleep
   - Could be improved with proper synchronization mechanisms

4. **Error Handling:**
   - Basic implementation without extensive error checking
   - Production code should include proper error handling 