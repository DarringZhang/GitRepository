#include <bits/stdc++.h>
using namespace std;

void Table(int n,int a[20][20])
{
    void Copy(int n,int a[20][20]);
    if(n==1)
    {
        a[1][1]=1; return;
    }

    Table(n/2,a);
    Copy(n/2,a);
}

void Copy(int n,int a[20][20]) {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            a[i][j + n] = a[i][j] + n;   //右上角等于左上角加n(顺次增加队伍编号)；
            a[i + n][j] = a[i][j + n]; //左下角的值等于右上角的值；
            a[i + n][j + n] = a[i][j]; //右下角的值等于左上角的值；}
        }
}


void Table_non_curency(int k, int  a[20][20])
{
    int  n=1;
    for(int i=1;i<=k;i++) n*=2;//计算运动员数
    for(int i=1;i<=n;i++)a[1][i]=i;//输出日程表第一行
    int m=1;//控制每一次填充表格的起始位置
    for(int s=1;s<=k;s++){ //k个阶段，从左到右
        n/=2;
        for(int t=1;t<=n;t++)   //每个阶段有n次循环
            for(int i=m+1;i<=2*m;i++)
                for(int j=m+1;j<=2*m;j++){
                    a[i][j+(t-1)*m*2-m]=a[i-m][j+(t-1)*m*2];//左下角的值等于右上角的值
                    a[i][j+(t-1)*m*2]=a[i-m][j+(t-1)*m*2-m]; //右下角的值等于左上角的值
                }
        m*=2;}
}



int main() {
    void Table(int n,int a[20][20]);
    void Table_non_curency(int k, int  a[20][20]);

    srand((unsigned)time(NULL));
    int n;
    cin >> n;
    int a[20][20];
    int b[20][20];
    clock_t start = clock();

    Table(n,a);
//    for(int i = 1; i<= n ; ++i){
//        for(int j = 1; j<= n; ++j){
//            cout<<a[i][j]<< " ";
//        }
//        cout<<endl;
//    }

    printf("Build  %ld miu seconds \n",(clock() - start) );

    start = clock();
    Table_non_curency(n,b);
    printf("Build  %ld miu seconds \n",(clock() - start) );

    return 0;
}