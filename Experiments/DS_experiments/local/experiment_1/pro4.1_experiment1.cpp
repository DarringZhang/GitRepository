
/*
	subject：Data Structure 
	To: experiment1_problem4.1
	Creator: 张丹颖2017011760
	date:2018.10.0
*/ 

#include<iostream>
#include<string>
using namespace std;

//定义函数将string转换存储有效数字的数组
int TransStringToArray(string a ,int *orig){

	int length=0,flag=0; 
	
	
		int sum = 0;
		while(length++<(int)a.size()){//string类的size()函数返回的是unsigned integer(无符号数)类型。而用在for循环时，
										//正常不会出错，但作为判断条件时，当s.length()等于0时，s.length()-1 不等于 -1
										//所以这里用（int）强制转换

			//将字符转化为对应大小的数字
			if(a[length-1]!=','){//遍历到有效数字，从后往前遍历
				sum*=10;    //sum 确定该数是处于个位，十位还是百位等
				int temp = a[length-1]-'0';//字符数字转化为int型数字
				sum+=temp;  
			}
			else{       //遇到分割标记“,”或者空格，代表该数字由字符转化为数字完毕，可以将sum存入数组中
				orig[flag++] = sum;
				sum = 0;//sum 清零
			}
		}
		
	orig[flag++] = sum;//第一个没有进入else,也要注意存入
	return flag;
}

//定义Plus函数
void Plus(string m,string n){
	int m_numLength ,n_numLength;
	int carry= 0,i=0,m_num[100],n_num[100];//carry进位，数组存数字
	//25个质数存储在数组中，用空间换时间
	const int primeNumber[25] ={2,3,5,7,11,13,17,19,23,29,
								31,37,41,43,47,53,59,61,67,71,
								73,79,83,89,97};
	
	if(m.size()<n.size()){//将被加数规定为较长的string
		string temp = m;
		m = n;
		n = temp;
	}
	
	m_numLength = TransStringToArray(m,m_num);
	n_numLength = TransStringToArray(n,n_num);
	int t = m_numLength;
	
	while(m_numLength>0){ 
		int a,b,sum;
		a = m_num[m_numLength-1];//取出个位数
		
		if(n_numLength>0){
			b = n_num[n_numLength-1];
		} 
		else{
			b = 0; 
		}
		
		sum = a+b+carry;
		
		if(sum>=primeNumber[i]){//需要进位
			m_num[m_numLength-1] = sum%primeNumber[i];//大的数组的最后一位更新为进位后的余数
			carry = 1;
		} 
		else{
			m_num[m_numLength-1] = sum;//不需进位，直接更新
			carry = 0;
		}
		
		m_numLength--;//移位遍历
		n_numLength--;
		i++;
	} 
	
	
	if(carry ==1){//注意 ！！考虑最后一位数进位的问题，仅需要在输出时补上“1,”
		cout<<"1,";
	}
	
 
	m_numLength = t ;
	int j = 0;
	while (m_num[j] == 0 && !carry) j++;//无效零（本来就有无效零或者不是需要补上“1,”的情况），不输出
	for(;j<m_numLength-1;++j){
		cout<<m_num[j]<<',';
	}
	cout<<m_num[m_numLength-1]<<endl;//标准化格式，最后一位单独输出

}


int main(){
	string a,b; 
	while(1){
		cin>>a>>b;		
		if(a=="0"&&b=="0"){//a and b都是零时结束！
			break;
		}
		else{
			Plus(a,b);
		}
	
	}
	return 0;
}


