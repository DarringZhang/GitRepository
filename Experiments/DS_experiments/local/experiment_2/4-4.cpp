//进制转换（栈的经典应用）
#include<iostream>
#include<stack>
using namespace std;

void conversion(int num,int n){
	stack <int> s;//进制转换每次取余，获得的个位数正好按照后进先出的排列顺序----栈结构
	while(num){
		s.push(num%n);//将每次取得的余数push入栈
		num/=n;//num除以n取整，更新num
	}
	while(!s.empty()){//逐个打印出n进制数
		cout<<s.top();
		s.pop();
	} 
}

int main(){
	int num,n;
	cin>>num>>n;
	if(num==0){//单独考虑0的任何进制都是0
		cout<<"0"<<endl;
		return 0;
	}
	conversion(num,n);
	return 0;
}