#include<stdio.h>
#include<pthread.h>
#include"../common.h"
#include"../common_threads.h"
static volatile int count=0;
static int flag[2];
static int turn;
static void init(){
	flag[0]=flag[1]=0;
	turn=0;
}
static void lock(int self){
	flag[self]=1;
	turn=1-self;
	while((flag[1-self]==1)&&(turn==1-self));
}
static void unlock(int self){
	flag[self]=0;
}
void *mythread(int arg){
	int i;
	printf("%d :begin\n",arg);
	for(int i=0;i<1e7;i++){
		lock(arg);
		count=count+1;
		unlock(arg);
	}
	printf("%d :end\n",arg);
	return NULL;
}
int main(int argc,char **argv){
	pthread_t p1,p2;
	init();
	printf("hellowrold!\n");
	printf("main:begin count=%d\n",count);
	Pthread_create(&p1,NULL,mythread,1);
	Pthread_create(&p2,NULL,mythread,0);

	Pthread_join(p1,NULL);
	Pthread_join(p2,NULL);
	printf("main:done count=%d\n",count);
}
