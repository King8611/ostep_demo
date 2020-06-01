#include<stdio.h>
#include"../common.h"
#include"../common_threads.h"
#include<semaphore.h>
#include<pthread.h>
sem_t s;
void *child(void *arg){
	printf("child\n");
	sem_post(&s);
	return NULL;
}
int main(){
	sem_init(&s,0,0);
	printf("parent:begin\n");
	pthread_t c;
	Pthread_create(&c,NULL,child,NULL);
	sem_wait(&s);
	printf("parent:end\n");
	return 0;
}
