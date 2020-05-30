#include<pthread.h>
#include<stdio.h>
#include<assert.h>
#include"../common.h"
#include"../common_threads.h"
int buffer;
int count=0;
void put(int value){
	assert(count==0);
	printf("producer:%d\n",value);
	count=1;
	buffer=value;
}
int get(){
	assert(count==1);
	count=0;
	return buffer;
}
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
void *producer(void *arg){
	int i;
	int loops=(int)arg;
	for(i=0;i<loops;i++){
		Pthread_mutex_lock(&mutex);
		if(count==1)
			Pthread_cond_wait(&cond,&mutex);
		put(i);
		Pthread_cond_signal(&cond);
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
		if(count==0)
			Pthread_cond_wait(&cond,&mutex);
		int tmp=get();
		Pthread_cond_signal(&cond);
		Pthread_mutex_unlock(&mutex);
		printf("consumer %d\n",tmp);
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
