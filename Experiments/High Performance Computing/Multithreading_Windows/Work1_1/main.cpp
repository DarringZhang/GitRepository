//基于CreateThread设计实现多线程程序
#include<windows.h>
#include<iostream>
using namespace std;

DWORD WINAPI FunOne(LPVOID param){
 while(true)
  	{
    	Sleep(1000);
    	cout<<"hello 1! \n";
  	}

 return 0;
}

DWORD WINAPI FunTwo(LPVOID param){
 while(true)
  	{
    	Sleep(1000);
    	cout<<"hello 2! \n";
  	}

 return 0;
}


int main(int argc, char* argv[]) {
	//利用一个整数变量input接收键盘输入。
  	int input=0;

	//创建两个线程，分别执行函数1 FunOne和函数2 FunTwo
	HANDLE hand1=CreateThread (NULL, 0, FunOne, (void*)&input, CREATE_SUSPENDED, NULL);
	HANDLE hand2=CreateThread (NULL, 0, FunTwo, (void*)&input, CREATE_SUSPENDED, NULL);
	
	 while(true){
		cin>>input;
		switch(input)
		{ 
			case 1:
				//恢复线程1工作，利用函数
				ResumeThread(hand1);
				break;
			case 2:
				//暂停线程1工作，利用函数
				SuspendThread(hand1);
				break;	
			case 3:
				//终止线程1工作，利用函数
				TerminateThread(hand1,1);
				break;	
			case 5:
				//恢复线程2工作，利用函数
				ResumeThread(hand2);
				break;
			case 6:
				//暂停线程2工作，利用函数
				SuspendThread(hand2);
				break;	
			case 7:
				//终止线程2工作，利用函数
				TerminateThread(hand2,2);
				break;	

		}
	}

	return 0;
}

