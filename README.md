# Operating Systems Lab Programs

This repository contains various C programs demonstrating operating system concepts and system calls.

## Experiment 3: System Calls and Process Management

### 1. Fork System Call (`fork.c`)
This program demonstrates the use of the fork() system call to create child processes.
- Creates a child process using fork()
- Shows process IDs of both parent and child processes
- Implements proper process synchronization using wait()

Key concepts:
- Process creation
- Parent-child relationship
- Process IDs
- Process synchronization

### 2. File Status Information (`stat.c`)
This program shows how to get file information using the stat() system call.
- Takes a filename as input
- Displays various file attributes:
  - Last access time
  - Inode number
  - Block size
  - File mode
  - User ID
  - Group ID

Key concepts:
- File metadata
- System calls for file information
- File permissions and ownership

### 3. Directory Operations (`dirent.c`)
This program demonstrates directory operations using the dirent.h library.
- Takes a directory path as input
- Lists all files and directories in the specified path
- Shows inode numbers and names of directory entries

Key concepts:
- Directory traversal
- File system structure
- Directory entries

## Experiment 4: Inter-Process Communication

### Client-Server Communication
- `server.c`: Implements a basic server using socket programming
- `client.c`: Implements a client that connects to the server
- Demonstrates socket-based communication between processes

Key concepts:
- Socket programming
- Client-server architecture
- Inter-process communication

## Experiment 5: Process Synchronization

### Semaphore Implementation (`semaphore.c`)
- Implements process synchronization using semaphores
- Demonstrates solution to producer-consumer problem
- Handles critical section and mutual exclusion

Key concepts:
- Semaphores
- Process synchronization
- Critical section problem
- Producer-consumer problem

## Experiment 6: CPU Scheduling Algorithms

1. First Come First Serve (FCFS)
   - `fcfswithat.c`: FCFS with arrival time
   - `fcfswithout at.c`: FCFS without arrival time

2. Shortest Job First (SJF)
   - `sjfs.c`: Basic SJF implementation
   - `sjfwithat.c`: SJF with arrival time
   - `sjf with pr wihout at.c`: SJF with priority without arrival time

3. Priority Scheduling
   - `prioritysjfat.c`: Priority scheduling with SJF
   - `priwithpre.c`: Priority scheduling with preemption

Key concepts:
- CPU scheduling algorithms
- Process scheduling
- Arrival time handling
- Priority-based scheduling
- Preemptive vs non-preemptive scheduling

## Experiment 7: Deadlock Avoidance

### Banker's Algorithm (`bankersalgorithm.c`)
- Implements the banker's algorithm for deadlock avoidance
- Handles multiple resources and processes
- Determines safe sequence of process execution

Key concepts:
- Deadlock avoidance
- Resource allocation
- Safe state verification

## Experiment 8: Memory Management

### Memory Allocation Strategies
1. `firstfit.c`: First Fit memory allocation
2. `bestfit.c`: Best Fit memory allocation
3. `bestme.c`: Enhanced Best Fit implementation

Key concepts:
- Memory allocation algorithms
- Memory fragmentation
- Memory block management

## Experiment 9: Page Replacement Algorithms

1. `fifo.c`: First In First Out page replacement
2. `lrume.c`: Least Recently Used page replacement

Key concepts:
- Page replacement policies
- Memory management
- Cache management
- Page faults handling

## Experiment 10: Disk Scheduling

1. `fcfs.c`: First Come First Serve disk scheduling
2. `scan.c`: SCAN disk scheduling algorithm
3. `cscan.c`: Circular SCAN (C-SCAN) algorithm

Key concepts:
- Disk scheduling algorithms
- Seek time optimization
- Head movement strategies
