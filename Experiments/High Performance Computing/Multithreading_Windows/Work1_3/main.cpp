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
	cout<<"我在运行1外面"<<endl;
	while(true)
  	{	
		Sleep(1000);
		cout<<"我在运行1里面"<<endl;
		
    		 i = strOne.find(strGoal);

		 if(i != -1){
			cout<<"文件1找到了!!!!,位置是"<<endl;
			cout<<i<<endl;
			
		 }
		 else{
			 cout<<"文件1暂时没找到 "<<endl;
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
	cout<<"我在运行2外面"<<endl;
 while(true)
  	{
		 Sleep(1000);
		 cout<<"我在运行2里面"<<endl;
	
    	 i = strTwo.find(strGoal);
		 if(i != -1){
			 cout<<"文件2找到了+++++ ,位置是"<<endl;
			 cout<<i<<endl;
			 
		 }
		  else{
			 cout<<"文件2暂时没找到 "<<endl;
		 }
		 
		 
  	}

 return 0;
}


int main(int argc, char* argv[]) {
	
	 char goal[7] = "TikTok";

	//创建两个线程，分别执行函数1 FunOne和函数2 FunTwo
	HANDLE hand1=CreateThread (NULL, 0, FunOne, &goal, 0, NULL);
	Sleep(1000);

	HANDLE hand2=CreateThread (NULL, 0, FunTwo, &goal, 0, NULL);
	Sleep(2000);
	

	return 0;
}
