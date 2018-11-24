/*
	subject：Data Structure 
	To: experiment1_problem4.3
	Creator: 张丹颖2017011760
	date:2018.10.08
*/ 

#include<iostream>
#include<string>
using namespace std;

string Plus(string m,string n){
	int m_length = m.size(),n_length = n.size(),carry= 0;
	
	//对于少数有无效零的数字，首先外层用if进行简单判断，若首位不是无效零，不需进入while,省时
	
	//用erase函数去掉无效零
	if(m[0]=='0'){
		while(m_length-->0){
			if(m[0]=='0'){
				m.erase(0,1);	
			}
			if(m[0]!='0'){
				break;
			}	
		}
	
	}
	
	if(n[0]=='0'){
		while(n_length-->0){
			if(n[0]=='0'){
				n.erase(0,1);	
			}
			if(n[0]!='0'){
				break;
			}	
		}
	
	}
	
	//人为规定，被加数为较长的字符串
	if(m.size()<n.size()){
		string temp = m;
		m = n;
		n = temp;
	}
	
	 m_length = m.size();
	 n_length = n.size();	
	 

	while(m_length>0){ 
		int a,b,sum;
		a = m[m_length-1]-'0';//字符转换为数字
		
		if(n_length>0){
			b = n[n_length-1] -'0';
		} 
		else{
			b = 0; 
		}
		
		sum = a+b+carry;
		
		if(sum>=10){
			m[m_length-1] = '0' +sum%10;//相加满10进位
			carry = 1;
		} 
		else{
			m[m_length-1] = '0' +sum;
			carry = 0;
		}
		
		m_length--;
		n_length--;
	} 
	
	
	if(carry ==1){//主语最后两个数相加可能进位
		m = "1" + m;
	}
	
	return m;
}

int main(){
	int times ,i = 1;
	cin>>times;
	//格式化输出	
	while(times-->0){
			string a,b; 
			cin>>a>>b;
			cout<<"Case "<<i<<":"<<endl;
			cout<<a<<" + "<<b<<" = "<< Plus(a,b)<<endl;
			i++;	
	}
	
	return 0;
}

