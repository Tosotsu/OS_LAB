#include<stdio.h>
void main()
{
	int psize[10],bsize[10],all[10],i,j,n,m,flag[10];
	char pname;
	printf("Enter the no of process : ");
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		printf("Enter the process size : ");
		scanf("%d",&psize[i]);
	}
	for(i=1;i<=n;i++)
	{
		all[i]=-1;
	}
	printf("Enter the no of block : ");
	scanf("%d",&m);
	for(i=1;i<=m;i++)
	{
		flag[i]=0;
		printf("Enter the block size : ");
		scanf("%d",&bsize[i]);
	}
	
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			if((bsize[j]>=psize[i])&&(flag[j]==0))
			{
				all[i]=j;
				flag[j]=1;
				break;
			}
		}
	}
	printf("process no\tprocess size\tblock size\tallocated block\n");
	for(i=1;i<=n;i++)
	{	
		printf("%d\t\t%d\t\t%d\t\t%d\n",i,psize[i],bsize[i],all[i]);	
	if(all[i]=-1)
		printf("%d",all[i]);
	else
		printf("not allocated");
	}		
}		
			
			
			
/*			
Enter the no of process : 3
Enter the process size : 23
Enter the process size : 6
Enter the process size : 7
Enter the no of block : 3
Enter the block size : 12
Enter the block size : 20
Enter the block size : 30
process no	process size	block size	allocated block
1		23		12		3
-12		6		20		1
-13		7		30		2
	*/		
			
			
			
			
			
			
			
