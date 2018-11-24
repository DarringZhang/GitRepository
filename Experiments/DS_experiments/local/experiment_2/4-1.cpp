#include<iostream>
#include<stack> //导入栈头文件，引用栈的结构存储运算符
#include<map> //键值对容器
using namespace std;

int main(){
	/*优先级比较原则：数字大的优先级大，左括号优先级最小，当前元素优先级小于等于栈顶元素，栈顶元素就要弹出，、
	  当前元素在和新的栈顶元素比较，直到新的栈顶元素是左括号或者优先级小于当前运算符，直接push当前运算符
	*/
	map<char,int> priority;//定义键值对char and int,规定运算符入栈出栈优先级
	priority['+'] = 1;
	priority['-'] = 1;
	priority['*'] = 2;
	priority['/'] = 2;
	
	int i = 0;
	string a;
	stack<char> s; 
	getline(cin,a);//接收字符串a，依题目要求，遇到空格也要当作字符接收而不是标志结束输入
 
	//单独处理字符串最前面正负号的情形，负号代表紧接着的数字为负数，就直接输出这个负数
	if(a[0]=='-'){
		cout<<"-";
		i++;
	}
	//正号不输出，跳过
	else if(a[0]=='+'){
		i++;
	}
	
	while(i<a.size()){
		if(a[i]==' ') {//中间遇到空格，依题意跳过
			i++;
			continue;
		}
		
		if(a[i]<='9'&&a[i]>='0'){//数字直接输出
				cout<<a[i];	
		}

		//若遇到+-,--,*-,/-,(-,代表当前a[i]='-'后的数字为负数，直接输出符号，不是运算符
		else if(a[i]=='-'&&(a[i-1]=='+'||a[i-1]=='-'||a[i-1]=='*'||a[i-1]=='/'||a[i-1]=='(')){
			cout<<'-';
		}
		//若遇)+,空格+等一系列非数字后面接+号的情况，这个正号跳过
		else if(a[i]=='+'&&a[i-1]!=')'&&a[i-1]!=' '&&!(a[i-1]<='9'&&a[i-1]>='0')) {
			i++;
			continue;
		}
		//遇到左括号就入栈
		else if(a[i]=='('){
			s.push(a[i]);
		}
		//遇到右括号就pop出栈，直到遇到右括号为止
		else if(a[i]==')'){
			char temp = s.top();
			while(temp!='('){
				cout<<temp;
				s.pop();
				temp = s.top();
			}
			s.pop();//pop出右括号
		}
		//如果遇到运算符
		else if(a[i]=='+'||a[i]=='-'||a[i]=='*'||a[i]=='/'){
			char cur  = a[i];
			
			if(s.empty()){//当前栈为空，不需要比较当前运算符与栈顶元素的优先级
				s.push(cur);
			}
			else{          //栈不为空，就要比较栈顶元素和当前运算符的优先级
				char top  = s.top();
				if(top=='('){  //栈顶元素是左括号，直接push入栈
					s.push(cur);
					top = cur; 
					i++; 
					continue;
				}
				while(priority[cur]<=priority[top]&&!s.empty()){
					cout<<top;//当前元素优先级小于等于栈顶元素，pop栈顶，直到遇到新的栈顶元素是(或者当前元素优先级大于新栈顶元素
					s.pop();
					if(!s.empty()){
						top = s.top();//判断在栈不空的情形下，获得新的栈顶元素
					}
				
					if(top=='('){
						s.push(cur);
					    top = cur; 
						break; 
					} 
				}
				if(priority[cur]>priority[top]||s.empty()){//当前元素优先级大于新栈顶元素，入栈
					s.push(cur);
				}
				
				
			}
		}
		i++;
		if(i==a.size()){//中缀表达式读取完毕
			while(!s.empty()){
			cout<<s.top();//pop出栈内剩余运算符
			s.pop();
			}
		}
	}
	while(!s.empty()){//彻底清空栈
		cout<<s.top();
		s.pop();
	}
	return 0;
}