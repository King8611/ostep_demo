#include<stdio.h>
#include<pthread.h>
//#include"mythread.h"
#include"../common.h"
#include"../common_threads.h"
static volatile int count=0;
void mythread(void *arg){
	printf("%s:begin\n",(char*)arg);
	int i;
	for(i=0;i<1e7;i++){
		count=count+1;
	}
	printf("%s:done\n",(char*)arg);
	return NULL;
}
int main(int argc,char **argv){
	pthread_t p1,p2;
	printf("main:begin cout=%d \n",count);
	Pthread_create(&p1,NULL,mythread,"A");
	Pthread_create(&p2,NULL,mythread,"B");

	Pthread_join(p1,NULL);
	Pthread_join(p2,NULL);
	printf("main:done count=%d\n",count);
}
