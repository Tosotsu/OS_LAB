#include<stdio.h>
void main()
{
	int bsize[10],bno[10],process[10],flag[10],m,n,j,i,temp;
	printf("Enter the no of block:");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("Enter the size of block:");
		scanf("%d",&bsize[i]);
		flag[i]=0;
		bno[i]=i+1;
	}
	printf("Enter the no of process:");
	scanf("%d",&m);
	for(i=0;i<m;i++)
	{
		printf("Enter the size of process %d: ",i+1);
		scanf("%d",&process[i]);
	}
	for(i=0;i<n-1;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(bsize[i]>bsize[j])
			{
				temp=bsize[i];
				bsize[i]=bsize[j];
				bsize[j]=temp;
				temp=bno[i];
				bno[i]=bno[j];
				bno[j]=temp;
			}
		}
	}
	printf("process no\tprocess size\tblock\tblock size\n");
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			if(process[i]<=bsize[j]&&flag[j]==0)
			{
				flag[j]=1;
				break;
			}
		}
		if(flag[j]==1)
			printf("%d\t\t%d\t\t%d\t\t%d\n",i+1,process[i],bno[i],bsize[j]);
		else
			printf("%d\t%d\tcannot alocate\n",i+1,process[i]);
	}
}
	
	
	
	
	
		
