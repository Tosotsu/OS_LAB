#include<stdio.h>

void main() {
    int bsize[10], bno[10], process[10], flag[10];
    int m, n, i, j, temp;
    
    printf("Enter the number of blocks: ");
    scanf("%d", &n);
    
   
    for(i = 0; i < n; i++) {
        printf("Enter size of block %d: ", i+1);
        scanf("%d", &bsize[i]);
        bno[i] = i + 1;  
        flag[i] = 0;     
    }
    
    
    for(i = 0; i < n-1; i++) {
        for(j = i+1; j < n; j++) {
            if(bsize[i] > bsize[j]) {
                
                temp = bsize[i];
                bsize[i] = bsize[j];
                bsize[j] = temp;
                
                
                temp = bno[i];
                bno[i] = bno[j];
                bno[j] = temp;
                
                
                temp = flag[i];
                flag[i] = flag[j];
                flag[j] = temp;
            }
        }
    }
    
    printf("Enter number of processes: ");
    scanf("%d", &m);
    for(i = 0; i < m; i++) {
        printf("Enter size of process %d: ", i+1);
        scanf("%d", &process[i]);
    }
    
    
    printf("\nProcess No\tProcess Size\tBlock No\tBlock Size\tStatus\n");
    for(i = 0; i < m; i++) {
        int allocated = 0;
        
        
        for(j = 0; j < n; j++) {
            if(process[i] <= bsize[j] && !flag[j]) {
                flag[j] = 1;
                allocated = 1;
                break;
            }
        }
        
       
        if(allocated) {
            printf("%d\t\t%d\t\t%d\t\t%d\t\tAllocated\n", 
                  i+1, process[i], bno[j], bsize[j]);
        } else {
            printf("%d\t\t%d\t\t-\t\t-\t\tNot Allocated\n", i+1, process[i]);
        }
    }
}

