//����CreateThread���ʵ�ֶ��̳߳���
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
	//����һ����������input���ռ������롣
  	int input=0;

	//���������̣߳��ֱ�ִ�к���1 FunOne�ͺ���2 FunTwo
	HANDLE hand1=CreateThread (NULL, 0, FunOne, (void*)&input, CREATE_SUSPENDED, NULL);
	HANDLE hand2=CreateThread (NULL, 0, FunTwo, (void*)&input, CREATE_SUSPENDED, NULL);
	
	 while(true){
		cin>>input;
		switch(input)
		{ 
			case 1:
				//�ָ��߳�1���������ú���
				ResumeThread(hand1);
				break;
			case 2:
				//��ͣ�߳�1���������ú���
				SuspendThread(hand1);
				break;	
			case 3:
				//��ֹ�߳�1���������ú���
				TerminateThread(hand1,1);
				break;	
			case 5:
				//�ָ��߳�2���������ú���
				ResumeThread(hand2);
				break;
			case 6:
				//��ͣ�߳�2���������ú���
				SuspendThread(hand2);
				break;	
			case 7:
				//��ֹ�߳�2���������ú���
				TerminateThread(hand2,2);
				break;	

		}
	}

	return 0;
}

