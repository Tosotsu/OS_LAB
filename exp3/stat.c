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

