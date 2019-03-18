#include <bits/stdc++.h>
using namespace std;
int main() {
    int a,b,c;
    cin>>a>>b>>c;
    if(
            /* a+b==c||a*b==c||a-b==c||a/b==c
            ||a+c==b||a-c==b||a*c==b||a/c==b
            ||b+c==a||b-c==a||b*c==a||b/c==a
            ||b+a==c||b-a==c||b*a==c||b/a==c
            ||c+b==a||c-b==a||c*b==a||c/b==a
            ||c+a==b||c-a==b||c*a==b||c/a==b
             */
            a+b==c||a*b==c
            ||b+c==a||b*c==a
           ||c+a==b||c*a==b
       )

    {
       cout<<"Yes";
    }
    else cout<<"No";
    return 0;
}


//坑一：2 2 5  因为5/2 ！=2  改法1  题目说的是 正整数int.但可以换成double
//改法2：减法是加法的逆运算，除法是乘法的逆运算（避开除法），省掉这两套，再者a+b和b+a相同。。。。。总共六个等式。