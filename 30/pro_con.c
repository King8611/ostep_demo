#include<pthread.h>
#include<stdio.h>
#include<assert.h>
#include"../common.h"
#include"../common_threads.h"
#define MAX 10
int fill_ptr=0;
int use_ptr=0;
int buffer[MAX];
int count=0;
void put(int value){
	buffer[fill_ptr]=value;
	fill_ptr=(fill_ptr+1)%MAX;
	count++;
}
int get(){
	int tmp=buffer[use_ptr];
	use_ptr=(use_ptr+1)%MAX;
	count--;
	return tmp;
}
pthread_cond_t empty;
pthread_cond_t fill;

pthread_mutex_t mutex;
void *producer(void *arg){
	int i;
	int loops=(int)arg;
	for(i=0;i<loops;i++){
		Pthread_mutex_lock(&mutex);
		while(count==MAX)
			Pthread_cond_wait(&empty,&mutex);
		put(i);
		printf("producer put:%d\n",i);
		Pthread_cond_signal(&fill);
		Pthread_mutex_unlock(&mutex);
	}
	printf("producer end.\n");
	return NULL;
}
void *consumer(void *arg){
	int i;
	int loops=(int)arg;
	for(i=0;i<loops;i++){
		Pthread_mutex_lock(&mutex);
		while(count==0)
			Pthread_cond_wait(&fill,&mutex);
		int tmp=get();
		printf("consumer get:%d\n",tmp);
		Pthread_cond_signal(&empty);
		Pthread_mutex_unlock(&mutex);
	}
	printf("consumer end.\n");
	return NULL;
}
int main(){
	pthread_t p1,p2;
	printf("begin:\n");
	Pthread_create(&p1,NULL,producer,100);
	Pthread_create(&p2,NULL,consumer,100);

	Pthread_join(p1,NULL);
	Pthread_join(p2,NULL);
	printf("end.\n");
	return 0;
}
