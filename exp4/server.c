#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>

int main() {
    int shmid;
    int *shm, *it;
    long size = 1000;
    key_t key;
    printf("Enter the key: ");
    scanf("%d", &key);
    shmid = shmget(key, size, 0); 
    shm = shmat(shmid, NULL, 0); 
    it = shm;
    printf("Server: Received data from client:\n");
    for (int i = 0; i < 10; i++) {
        printf(" %d ", it[i]); 
    }
    printf("\n");
    return 0;
}
