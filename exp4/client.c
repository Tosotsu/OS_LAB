#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>

void main() {
    int shmid, i;
    int *shm, *it, a[10];
    long size = 1000;
    key_t key;
    printf("Enter the key: ");
    scanf("%d", &key);
    shmid = shmget(key, size, IPC_CREAT | 0660); 
    shm = shmat(shmid, NULL, 0);
    it = shm;
    printf("Enter the elements: ");
    for (i = 0; i < 10; i++) {
        scanf("%d", &a[i]);
        it[i] = a[i]; 
    }
    it[10] = 1; 
}
