#include<stdio.h>
#include<string.h>
struct process
{
	char pname[4];
	int alloc[10],max[10],need[10];
}p[10];
void main()
{
	int n,res,c=0,i,j,k,available[10],finish[10],flag;
	printf("Enter the no of process:");
	scanf("%d",&n);
	struct process p[n],safer[10];
	printf("Enter no of resources:");
	scanf("%d",&res);
	for(i=0;i<n;i++)
	{
		finish[i]=0;
		printf("Enter the process name:");
		scanf("%s",p[i].pname);
		printf("Enter the  allocation of %s\n",p[i].pname);
		for(j=0;j<res;j++)
			scanf("%d",&p[i].alloc[j]);
		printf("Enter the max allocation of %s\n",p[i].pname);
		for(j=0;j<res;j++)
			{
				scanf("%d",&p[i].max[j]);
				p[i].need[j]=p[i].max[j]-p[i].alloc[j];
			}
	}
	printf("Enter available resource:");
	for(j=0;j<res;j++)
		scanf("%d",&available[j]);
	printf("Process\tAllocation\tMax\tNeed\n");
	for(i=0;i<n;i++)
	{
		printf("%s\t",p[i].pname);
		for(j=0;j<res;j++)
			printf("%d\t",p[i].alloc[j]);
		printf("\t");
		for(j=0;j<res;j++)
			printf("%d\t",p[i].max[j]);
		printf("\t");
		for(j=0;j<res;j++)
			printf("%d\t",p[i].need[j]);
		printf("\n");
	}
	
	printf("Available matrix\n");
	for(i=0;i<res;i++)
		printf("%d\t",available[i]);
	printf("\n");
	int y=0;
	for(k=0;k<n;k++)
	{
		for(i=0;i<n;i++)
		{
			if(finish[i]==0)
			{
				flag=1;
				for(j=0;j<res;j++)
				{
					if(p[i].need[j]>available[j])
					{
						flag=0;
						
						break;
					}
				}
				if(flag==1)
				{
					safer[c++]=p[i];
					for(y=0;y<res;y++)
						available[y]+=p[i].alloc[y];
					finish[i]=1;
				}
			}
		}
	}
	flag=1;
	for(i=0;i<n;i++)
	{
		if(finish[i]==0)
		{
			flag=0;
			break;
		}
	}
	if(flag==1)
	{
		printf("fale sequense\n");
		for(i=0;i<n;i++)
		{
			printf("%s\t",safer[i].pname);
			printf("\n");
		}
		}
	else
	{
			printf("No safe sequence\n");
	}
		
}

