//括号匹配（栈的应用）
#include<iostream>
#include<stack>
using namespace std;

int main(){
	string str;
	stack <char> s;
	cin>>str;
	for(int i=0;i<str.size();i++){
		if(str[i]=='('){//但凡是左括号，为等待右括号匹配的待定项，入栈
			s.push('(');
		}
		else {        //若为右括号
			if(!s.empty()){
				if(s.top()=='('){//运气好，栈顶元素刚好与之匹配，左括号出栈，跳出本次，进行下一次循环
					s.pop();
					continue;
				}
				else{
					cout<<"NO"<<endl;//当前右括号str[i]没有与之匹配的，本次匹配失败，输出No,程序结束
					return 0;
				}
			}
			else{             //直到栈空，没能匹配当前str[i];输出No
				cout<<"NO"<<endl;
				return 0;
			}
			
		}
	}
	if(s.empty()){//最后结束，栈空，说明每个都匹配完毕
		cout<<"YES"<<endl;
	}
	else if(!s.empty()){//否则，还有未成对的，匹配失败
		cout<<"NO"<<endl;
	}
	return 0;
}