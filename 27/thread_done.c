#include<stdio.h>
#include<pthread.h>
#include<assert.h>
#include<stdlib.h>
#include"../common.h"
#include"../common_threads.h"
typedef struct myarg_t{
	int a,b;
}myarg_t;
typedef struct myret_t{
	int x,y;
}myret_t;
void mythread(void *arg){
	myarg_t *m=(myarg_t *)arg;
	printf("%d %d\n",m->a,m->b);
	myret_t *r=malloc(sizeof(myret_t));
	r->x=1;
	r->y=2;
	return (void*)r;
}
int main(int argc,char ** argv){
	int rc;
	pthread_t p;
	myret_t *m;
	myarg_t args;
	args.a=10;
	args.b=20;
	Pthread_create(&p,NULL,mythread,&args);
	Pthread_join(p,(void**)&m);
	printf("returned %d %d\n",m->x,m->y);
}
