# Experiment 3: System Calls in UNIX/Linux

This experiment demonstrates the use of essential system calls in UNIX/Linux operating systems for file operations, directory access, and process management. It consists of three programs demonstrating different system calls.

## Concept Overview

System calls are the interface between user-level programs and the operating system kernel. They provide programs with services such as file operations, process creation, and directory access.

```
┌─────────────────┐                 ┌─────────────────┐
│   User Program  │ System Calls    │     Kernel      │
│  (User Space)   │────────────────►│  (Kernel Space) │
└─────────────────┘                 └─────────────────┘
```

## Implementation Details

### 1. Directory Entry Program (`dirent.c`)

This program demonstrates how to open and read directory contents using the `dirent.h` library.

```c
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

void main() {
    char path[50];
    DIR *dir;
    struct dirent *directory; 

    printf("ENTER THE PATH: ");
    scanf("%s", path); 
    dir = opendir(path); 
    while ((directory = readdir(dir)) != NULL) {
        printf("Inode: %lu\n", directory->d_ino);
        printf("Name: %s\n", directory->d_name);
    }
    closedir(dir);
}
```

#### Line-by-Line Explanation:

1. **Headers (Lines 1-3):**
   - Include necessary headers for directory operations
   - `dirent.h` provides directory entry structure and functions

2. **Variable Declaration (Lines 5-7):**
   - `path`: Stores the directory path input by the user
   - `dir`: Directory stream pointer
   - `directory`: Pointer to directory entry structure

3. **Opening Directory (Lines 9-11):**
   - Gets directory path from user
   - `opendir()` system call opens the directory and returns a pointer

4. **Reading Directory Entries (Lines 12-15):**
   - Uses a while loop with `readdir()` to iterate through all entries
   - Displays the inode number and filename for each entry

5. **Closing Directory (Line 16):**
   - `closedir()` releases resources associated with the directory stream

### 2. File Status Program (`stat.c`)

This program demonstrates the use of the `stat()` system call to get detailed information about a file.

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void main() {
    char file[50];
    struct stat *nfile;
    nfile = (struct stat*)malloc(sizeof(struct stat));

    printf("Enter the file name: ");
    scanf("%s", file); 

    stat(file, nfile);

    printf("Last access time: %ld\n", nfile->st_atime); 
    printf("Inode number: %lu\n", nfile->st_ino); 
    printf("Block size: %ld\n", nfile->st_blksize); 
    printf("File mode: %o\n", nfile->st_mode);
    printf("User ID: %u\n", nfile->st_uid);
    printf("Group ID: %u\n", nfile->st_gid);
    free(nfile); 
}
```

#### Line-by-Line Explanation:

1. **Headers (Lines 1-3):**
   - Include necessary headers for file status operations
   - `sys/stat.h` provides the stat structure and functions

2. **Variable Declaration (Lines 5-7):**
   - `file`: Stores the filename input by user
   - `nfile`: Pointer to a stat structure
   - Dynamically allocates memory for the stat structure

3. **File Information Retrieval (Lines 9-12):**
   - Gets filename from user
   - `stat()` system call fills the structure with file information

4. **Information Display (Lines 14-19):**
   - Displays various file attributes:
     - Access time
     - Inode number
     - Block size
     - File permissions mode
     - User and group IDs

5. **Memory Cleanup (Line 20):**
   - Frees dynamically allocated memory

### 3. Process Creation Program (`fork.c`)

This program demonstrates process creation and management using the `fork()` system call.

```c
#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h> 

void main() {
    pid_t p;
    p = fork();
    printf("%d", p);
    if (p < 0) {
        printf("ERROR");
        exit(1); 
    } else if (p > 0) {
        wait(NULL); 
        printf("Parent process \n");
        printf("Process ID: %d\n", getpid());
        printf("Parent Process ID: %d\n", getppid());
    } else {
        printf("Child process \n");
        printf("Process ID: %d\n", getpid());
        printf("Parent Process ID: %d\n", getppid());
    }
}
```

#### Line-by-Line Explanation:

1. **Headers (Lines 1-5):**
   - Include necessary headers for process operations
   - `unistd.h` for fork() and process ID functions
   - `sys/wait.h` for wait() function

2. **Process Creation (Lines 7-9):**
   - `pid_t p`: Process ID variable
   - `fork()` creates a new child process
   - Returns child's PID to parent and 0 to child

3. **Error Handling (Lines 10-13):**
   - Checks if fork failed (p < 0)
   - Exits with error code if process creation failed

4. **Parent Process (Lines 14-18):**
   - Executes when p > 0 (in the parent process)
   - `wait(NULL)` suspends parent until child terminates
   - Displays parent's process ID and its parent's process ID

5. **Child Process (Lines 19-23):**
   - Executes when p = 0 (in the child process)
   - Displays child's process ID and its parent's process ID

## Visual Example of Execution

### Directory Entry Program:
```
$ gcc dirent.c -o dirent
$ ./dirent
ENTER THE PATH: /home/user/documents
Inode: 1234567
Name: file1.txt
Inode: 1234568
Name: file2.txt
Inode: 1234569
Name: .
Inode: 1234570
Name: ..
```

### File Status Program:
```
$ gcc stat.c -o stat
$ ./stat
Enter the file name: example.txt
Last access time: 1617283456
Inode number: 7654321
Block size: 4096
File mode: 644
User ID: 1000
Group ID: 1000
```

### Process Creation Program:
```
$ gcc fork.c -o fork
$ ./fork
1234Child process 
Process ID: 1235
Parent Process ID: 1234
Parent process 
Process ID: 1234
Parent Process ID: 1000
```

## Process Creation Visualization

```
          Original Process
              (PID: 1234)
                  │
                  │ fork()
                  │
          ┌───────┴───────┐
          │               │
     Child Process    Parent Process
      (PID: 1235)      (PID: 1234)
          │               │
     Executes code    wait() for child
     for p == 0       Executes code for p > 0
```

## How to Run

1. Compile each program:
   ```bash
   gcc dirent.c -o dirent
   gcc stat.c -o stat
   gcc fork.c -o fork
   ```

2. Run each program:
   ```bash
   ./dirent
   ./stat
   ./fork
   ```

## Key Concepts Demonstrated

1. **Directory Operations:**
   - Opening and reading directory entries
   - Accessing directory metadata

2. **File Status Retrieval:**
   - Getting detailed information about files
   - Understanding file attributes and permissions

3. **Process Management:**
   - Process creation with fork()
   - Parent-child relationships
   - Process synchronization with wait()
   - Process identification with getpid() and getppid()

## Common Issues and Solutions

1. **Directory Access Permissions:**
   - Ensure you have read permissions for the directory
   - Use absolute paths if relative paths don't work

2. **File Not Found Errors:**
   - Verify file exists in the given path
   - Check for typos in the filename

3. **Fork Failure:**
   - May occur when system resources are low
   - Check errno for specific reason
   - Implement proper error handling 