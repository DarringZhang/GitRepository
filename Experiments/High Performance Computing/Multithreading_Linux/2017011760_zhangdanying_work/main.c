#include <pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <unistd.h>

char goal[7] = "TikTok";


void FunOne(void){
	FILE *fp = fopen("TikTok.txt","r");
	if(fp == NULL){
		printf("该文件不存在");
		return;
	}

	char file1[1024];
	
	printf("我在运行1外面\n");
	while(fgets(file1,sizeof(file1),fp)){ //每1024字节读一次
		sleep(1);
		char *p;
		p = strstr(file1,goal);
		if(p){
			int num1 = p-file1+1;
			printf("文件1中找到文件,文件在第%d个位置\n",num1);	
		}
		else{
                        printf("文件1暂时没找到\n");
                }

	}
	 
	fclose(fp);
}


void FunTwo(void){
	FILE *fp = fopen("November11th.txt","r");
        if(fp == NULL){
                printf("该文件不存在");
                return;
        }

        char file2[1024];

        printf("我在运行2外面\n");
        while(fgets(file2,sizeof(file2),fp)){ //每1024字节读一次
		sleep(1);
                char* p;
                p = strstr(file2,goal);
                if(p){
			int num = p-file2+1;
                        printf("文件2中找到文件,文件在第%d个位置\n",num);
                }else{
			printf("文件2暂时没找到\n");
		}
        }

        fclose(fp);

	
}


int main(int argc, char* argv[]) {
	

  	static pthread_t id1,id2;

	int res2 = pthread_create (&id2,NULL,(void*)FunTwo,NULL);

	//创建两个线程，分别执行函数1 FunOne和函数2 FunTwo
	int res1 = pthread_create(&id1,NULL,(void*)FunOne,NULL);
//	sleep(2);//ms 和s的区别

//	int res2 = pthread_create (&id2,NULL,(void*)FunTwo,NULL);

	//sleep(2);//记得小写，区别
	pthread_join(id1,NULL);
	pthread_join(id2,NULL);


	return 0;
}

