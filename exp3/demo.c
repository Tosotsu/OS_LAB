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

