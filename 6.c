#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#define size 5
int buffer[size];
sem_t mutex,empty,full;
int in = 0,out=0;
void *producer(void *args){
	int item = 1;
	while(1){
		sem_wait(&empty);
		sem_wait(&mutex);
		buffer[in] = item;
		printf("Ited produced:%d\n",item);
		item++;
		in = (in+1)%size;
		sem_post(&mutex);
		sem_post(&full);
		sleep(1);
	}
}
void *consumer(void *arg){
	int item;
	while(1){
		sem_wait(&full);
		sem_wait(&mutex);
		item = buffer[out];
		printf("COnsumed:%d\n",item);
		out = (out+1)%size;
		sem_post(&mutex);
		sem_post(&empty);
		sleep(1);
		}
}
int main(){
	pthread_t p,c;
	sem_init(&empty,0,size);
	sem_init(&full,0,0);
	sem_init(&mutex,0,1);

	pthread_create(&p,NULL,producer,NULL);
	pthread_create(&c,NULL,consumer,NULL);

	pthread_join(p,NULL);
	pthread_join(c,NULL);
	return 0;
}

