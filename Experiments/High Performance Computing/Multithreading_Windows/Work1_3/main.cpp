//
#include<windows.h>
#include<iostream>
#include<string>
using namespace std;

DWORD WINAPI FunOne(LPVOID param){

	char *goal = (char*)param;
	string strGoal(goal);

	char One[2000];
	freopen("TikTok.txt","r",stdin);

	string strOne(One);
	cin>>strOne;
	fclose(stdin);


	int i;
	cout<<"��������1����"<<endl;
	while(true)
  	{	
		Sleep(1000);
		cout<<"��������1����"<<endl;
		
    		 i = strOne.find(strGoal);

		 if(i != -1){
			cout<<"�ļ�1�ҵ���!!!!,λ����"<<endl;
			cout<<i<<endl;
			
		 }
		 else{
			 cout<<"�ļ�1��ʱû�ҵ� "<<endl;
		 }
	
  	}
	 return 0;
}


DWORD WINAPI FunTwo(LPVOID param){
	char *goal = (char*)param;
	string strGoal(goal);

char Two[2000];
freopen("November11th.txt","r",stdin);
string strTwo(Two);
cin>>strTwo;
fclose(stdin);

	int i ;
	cout<<"��������2����"<<endl;
 while(true)
  	{
		 Sleep(1000);
		 cout<<"��������2����"<<endl;
	
    	 i = strTwo.find(strGoal);
		 if(i != -1){
			 cout<<"�ļ�2�ҵ���+++++ ,λ����"<<endl;
			 cout<<i<<endl;
			 
		 }
		  else{
			 cout<<"�ļ�2��ʱû�ҵ� "<<endl;
		 }
		 
		 
  	}

 return 0;
}


int main(int argc, char* argv[]) {
	
	 char goal[7] = "TikTok";

	//���������̣߳��ֱ�ִ�к���1 FunOne�ͺ���2 FunTwo
	HANDLE hand1=CreateThread (NULL, 0, FunOne, &goal, 0, NULL);
	Sleep(1000);

	HANDLE hand2=CreateThread (NULL, 0, FunTwo, &goal, 0, NULL);
	Sleep(2000);
	

	return 0;
}
