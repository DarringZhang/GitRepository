#include<iostream>
using namespace std;
int main(){
	freopen("input.txt","r",stdin);
	const string hexdigits = "0123456789ABCDEF";
	cout<<"Enter a series of numbers between 0 and 15"<<endl;
	string result;
	string::size_type n;
	while(cin>>n){
		if(n<hexdigits.size()){
			result += hexdigits[n];
		}
	}
	cout<<result<<endl;
	return 0;
} 
