#include <bits/stdc++.h>
using namespace std;

void Knapsack(int * v, int* w, int n, int W, int (*c)[100])
//v为存储物品价值的数组，w为存储物品重量的数组，n为物品的数量，W为背包的容量
{   int ww;
    for ( ww=0;ww <= W;ww++)   c[0][ww]=0;//没有物品可以选择
    for  (int i=0;i<=n;i++)         c[i][0]=0;  //物品总重不超过0
    for(int i=1;i<=n;i++)
    { for ( ww=1;ww <= W;ww++)
            if(w[i]<=ww)
            { if(v[i]+c[i-1][ww-w[i]]>c[i-1][ww])
                    c[i][ww]=v[i]+c[i-1][ww-w[i]];
              else c[i][ww]=c[i-1][ww];
            }
            else c[i][ww]=c[i-1][ww];
    }
}

void TraceBack(int (*c)[100], int *w, int W, int n,int *x)
//数组x中的值为最优解，x[i]=1表示第i个物品可以放入背包。
{
    if (W<=0) return; //递归调用终止条件。
    if (c[n-1][W-1]==c[n-2][W-1]) {
        x[n]=0;
        TraceBack(c,w,W,n-1,x);
    } else {
        x[n]=1;
        W-=w[n];
        TraceBack(c,w,W,n-1,x);
    }
}

int main() {
    int v[] = {1,6,18,22,28};
    int w[] = {1,2,5,6,7};
    int x[100] = {0};
    int W = 11;
    int c[100][100] = {0};

    Knapsack(v,w,5,11, c);
    TraceBack(c,w, W, 5, x);

    for(int i = 0; i < 5; ++i){
        cout<<x[i]<<" ";
    }
    return 0;
}