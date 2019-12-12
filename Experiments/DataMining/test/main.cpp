#define _CRT_SECURE_NO_WARNINGS    //防止程序运行时提示函数不安全的信息；
#include<fstream>
#include<cstdio>
#include<iostream>
using namespace std;



const char goal[7] = "TikTok";
const string strGoal(goal);


int  FunOne(LPVOID param){
    char One[] = "Tik";
    string strOne(One);
    int i;
        //freopen("D://TikTok.txt","r",stdin);
        int i = strGoal.find(strOne);
        if(i > 0){
            cout<<"找到了 ";
            break;
        }
        cout<<i<<endl;
        cout<<"暂时没找到 ";


    return 0;
}






int main()
{
    int a, b, sum = 0.0;
    freopen("F://1.txt", "r", stdin);
    scanf("%d %d", &a, &b);

        sum += a * b;

    cout << sum << endl;

    return 0;
}
