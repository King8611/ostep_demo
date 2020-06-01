#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include"../common.h"
#include"../common_threads.h"
#define MAX 25
int buffer[MAX];
int count=0;
int fill=0;
int use=0;
sem_t mutex;
sem_t full;
sem_t empty;
int get(){
	int tmp=buffer[use];
	use=(use+MAX+1)%MAX;
	count--;
	return tmp;
}
int put(int value){
	buffer[fill]=value;
	fill=(fill+1)%MAX;
	count++;
}
void *produce(void *arg){
	int loops=(int)arg;
	for(int i=0;i<loops;i++){
		sem_wait(&empty);
		sem_wait(&mutex);
		put(i);
		printf("products put %d,and count=%d\n",i,count);
		sem_post(&mutex);
		sem_post(&full);
	}
}
void *consumer(void *arg){
	int loops=(int)arg;
	for(int i=0;i<loops;i++){
		sem_wait(&full);
		sem_wait(&mutex);
		int tmp=get();
		printf("consumer get %d,and count=%d\n",tmp,count);
		sem_post(&mutex);
		sem_post(&empty);
	}
}
int main(){
	pthread_t pro,con;
	sem_init(&empty,0,MAX);
	sem_init(&full,0,0);
	sem_init(&mutex,0,1);

	Pthread_create(&pro,NULL,produce,100);
	Pthread_create(&con,NULL,consumer,100);
	Pthread_join(pro,NULL);
	Pthread_join(con,NULL);
}
