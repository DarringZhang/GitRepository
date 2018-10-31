//平台第二题
#include<iostream>
#include<stack>
using namespace std;

double conpute(double a,double b,char c){//对从栈中弹出来的两个数字和一个符号做识别计算处理
	if(c=='+'){
		return a+b;
	}
	else if(c=='-'){
		return a-b;
	}
	else if(c=='*'){
		return a*b;
	}
	else {
		return a/b;
	}
}

double TransCharToNum(char a){//将符号转化成可以计算的数字
	return a-'0';
}



int main(){
	string str;
	stack <double>s;  //栈专门存储数字
	double sum = 0;
	cin>>str;          //输入字符串
	for(int i = 0;i<str.size();i++){
		if(str[i] >= '0' && str[i] <= '9'){//遇到数字字符，就转化成真正的数字后push入栈
			s.push(TransCharToNum(str[i]));
		}
		else if(!s.empty()){              //否则遇到运算符，开始计算,这个运算符肯定是计算刚刚push进去的栈顶的两个元素
			double FirstTop = s.top();
			s.pop();
			double SecondTop = s.top();
			s.pop();
			sum = conpute(SecondTop,FirstTop,str[i]);//取出栈顶两个元素，识别这个运算符并计算
			s.push(sum);                  //将运算结果push入栈顶，参与下一个运算符号的运算
		}    
	} 
	printf("%f\n",s.top());//最后运算结果肯定是栈顶元素
	s.pop();              //清空栈
	 
	return 0;
}