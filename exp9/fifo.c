#include<stdio.h>
void main()
{
	int n,f,p[50],fr[50],i,j,k,found,hit=0,fault=0,fi=0;
	printf("Enter no of pages:\n");
	scanf("%d",&n);
	printf("Enter control string:\n");
	for(i=0;i<n;i++)
		scanf("%d",&p[i]);
	printf("Enter no of frames:\n");
	scanf("%d",&f);
	for(i=0;i<f;i++)
		fr[i]=-1;
	printf("page\tframe\t\t\thit/fault\n");
	for(i=0;i<n;i++)
	{
		printf("%d\t",p[i]);
		found=0;
		for(k=0;k<f;k++)
		{
			if(fr[k]==p[i])
			{
				found=1;
				hit++;
				for(j=0;j<f;j++)
					printf("%d\t",fr[j]);	
				printf("hit\n");
				break;
			}
		}
		if(!found)
		{
			fr[fi]=p[i];
			fault++;
			fi=(fi+1)%f;
			for(j=0;j<f;j++)
				printf("%d\t",fr[j]);	
			printf("fault\n");
		}
	}
	printf("No of pages faults: %d\n",fault);
	printf("No of pages hit: %d\n",hit);
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
/*	
OUTPUT
Enter no of pages:
10
Enter control string:
4
7
6
1
7
6
1
2
7
2
Enter no of frames:
3
page	frame			hit/fault
4	4	-1	-1	fault
7	4	7	-1	fault
6	4	7	6	fault
1	1	7	6	fault
7	1	7	6	hit
6	1	7	6	hit
1	1	7	6	hit
2	1	2	6	fault
7	1	2	7	fault
2	1	2	7	hit
No of pages faults: 6
No of pages hit: 4
	*/
