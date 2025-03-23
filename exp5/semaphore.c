#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
sem_t mutex,full,empty;
int buffer[5],r=-1,f=-1,item,i;
void*produce(void*arg);
void*consume(void*arg);
void main()
{
	pthread_t t1,t2;
	sem_init(&mutex,0,1);
	sem_init(&full,0,0);
	sem_init(&empty,0,5);
	pthread_create(&t1,NULL,produce,NULL);
	pthread_create(&t2,NULL,consume,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
}

void*produce(void*arg)
{
	int i;
	for(i=0;i<10;i++)
	{
		sem_wait(&empty);
		sem_wait(&mutex);
		printf("Produced item is %d \n",i);
		buffer[(++r)%5]=i;
		sleep(1);
		sem_post(&mutex);
		sem_post(&full);
	}
}

void*consume(void*arg)
{
	int i,item;
	for(i=0;i<10;i++)
	{
		sem_wait(&full);
		sem_wait(&mutex);
		item=buffer[(++f)%5];
		printf("Consumed item");
		printf("%d\n",item);
		sleep(1);
		sem_post(&mutex);
		sem_post(&empty);
	}
}
















/*
OUTPUT

Produced item is 0 
Produced item is 1 
Produced item is 2 
Produced item is 3 
Produced item is 4 
Consumed item0
Consumed item1
Consumed item2
Consumed item3
Consumed item4
Produced item is 5 
Produced item is 6 
Produced item is 7 
Produced item is 8 
Produced item is 9 
Consumed item5
Consumed item6
Consumed item7
Consumed item8
Consumed item9




*/
