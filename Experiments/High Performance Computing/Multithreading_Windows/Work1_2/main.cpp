//基于beginthread设计实现多线程程序
#include<windows.h>
#include<iostream>
#include<process.h>
using namespace std;

//定义两个全局Event变量分别来实现上述控制要求（想一下为什么用全局变量）
//全局，使两个线程都能操作这两个变量
HANDLE evRead, evFinish;

//声明两个函数体，分别代表线程1和线程2工作内容
void ReadThread(LPVOID param)
{
	//在read进程中，需要等到evRead这个信号后才能执行打印"reading"功能，因此在其前面加入等待函数进行控制，
	WaitForSingleObject (evRead ,INFINITE);
	cout<<"Reading"<<endl;
	SetEvent (evFinish); 
}

void WriteThread(LPVOID param)
{
	cout<<"Writing"<<endl;
	//执行完打印"writing"后设置Event变量
	SetEvent (evRead);
}

int main(int argc, char* argv[]) {
	//主函数中创建这两个Event，第一个实现要求1，第二个实现要求2
	evRead = CreateEvent (NULL ,FALSE ,FALSE ,NULL) ;
	evFinish = CreateEvent (NULL ,FALSE ,FALSE ,NULL) ;

	//主函数中创建两个线程，
	_beginthread(ReadThread , 0 , NULL) ;
	_beginthread(WriteThread , 0 , NULL) ;

	//read线程工作完成后，主程序打印"The Program is End"后执行完毕，
	WaitForSingleObject (evFinish,INFINITE);
	cout<<"The Program is End"<<endl;
	return 0;
}
