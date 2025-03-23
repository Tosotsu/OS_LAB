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

