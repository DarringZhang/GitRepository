#include <bits/stdc++.h>
using namespace std;

void Loading ( int x[ ],int w[ ],  int c,  int n,  int *t )
//x[ ]存储集装箱的选中情况， w[ ]存储集装箱的编号
// c 为轮船的剩余载重量， n 为集装箱的个数， t 为排序后每个集装箱原来的序号。
{
    sort(w,t,n);  //将n个集装箱按照重量w非减序排序
     for (int i = 1; i <= n; i++)
               x[i] = 0;
      for (int i = 1; i <= n && w[t[i]] <= c; i++)
        {     x[t[i]] = 1;
               c = c-w[t[i]];
        }
}


int main() {
    int x[100] = {0};
    int c = 19;
    int n = 5;
    int w[5] = {5,3,8,6,9};
    int t[5] = {1,2,3,4,5};
    Loading(x,w,c,n,t);

    for(int i = 0; i < 5; ++i){
        cout<<x[i]<<" ";
    }
    return 0;
}