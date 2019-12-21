#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
static int sig = 1;

void thread(void){
	int i;

	for(i=0;i<3;i++){
		sig++;
		printf("Pthread num is %d\n",sig);
	}
}

int main(void){
	pthread_t id;
	int i,ret;
	ret=pthread_create(&id,NULL,(void*)thread,NULL);

	if(ret!=0){//出错
		printf("Create pthread error!\n");
		exit(1);
	}

	pthread_join(id,NULL);

	for(i=0;i<3;i++){
		sig++;
		printf("Mthread num is %d\n",sig);
	}

	return 0;
}
