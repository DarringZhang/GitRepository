#include<iostream>
#include <string.h>//引入函数 strlen ，但是接受的参数是char*,string 也可使用.size()获得长度
using namespace std;

int main(void) {
    int n;
    int length;
    cin >> n;
    string s;
    while(n--){
        cin >> s;
        length = strlen(s.c_str());//.c_str() 将string转换为char数组
        if(length <= 10){
            cout<<s<<endl;
        }
        else{
            cout<<s[0]<<length-2<< s[length-1]<<endl;
        }
    }

}