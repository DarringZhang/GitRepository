//����beginthread���ʵ�ֶ��̳߳���
#include<windows.h>
#include<iostream>
#include<process.h>
using namespace std;

//��������ȫ��Event�����ֱ���ʵ����������Ҫ����һ��Ϊʲô��ȫ�ֱ�����
//ȫ�֣�ʹ�����̶߳��ܲ�������������
HANDLE evRead, evFinish;

//�������������壬�ֱ�����߳�1���߳�2��������
void ReadThread(LPVOID param)
{
	//��read�����У���Ҫ�ȵ�evRead����źź����ִ�д�ӡ"reading"���ܣ��������ǰ�����ȴ��������п��ƣ�
	WaitForSingleObject (evRead ,INFINITE);
	cout<<"Reading"<<endl;
	SetEvent (evFinish); 
}

void WriteThread(LPVOID param)
{
	cout<<"Writing"<<endl;
	//ִ�����ӡ"writing"������Event����
	SetEvent (evRead);
}

int main(int argc, char* argv[]) {
	//�������д���������Event����һ��ʵ��Ҫ��1���ڶ���ʵ��Ҫ��2
	evRead = CreateEvent (NULL ,FALSE ,FALSE ,NULL) ;
	evFinish = CreateEvent (NULL ,FALSE ,FALSE ,NULL) ;

	//�������д��������̣߳�
	_beginthread(ReadThread , 0 , NULL) ;
	_beginthread(WriteThread , 0 , NULL) ;

	//read�̹߳�����ɺ��������ӡ"The Program is End"��ִ����ϣ�
	WaitForSingleObject (evFinish,INFINITE);
	cout<<"The Program is End"<<endl;
	return 0;
}
