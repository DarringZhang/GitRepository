#include <bits/stdc++.h>
using namespace std;

void LCSLen(int m,int n,char *x,char *y,int (*c)[100],int (*b)[100])
{      int i,j;
       c[0][0]=0;
       for (i = 1; i <= m; i++) c[i][0] = 0;

       for (j = 1; j <= n; j++) c[0][j] = 0;

       for (i = 1; i <= m; i++)
          for (j = 1; j <= n; j++) {
             if (x[i-1]==y[j-1]) {       //注意xy 的下标-1
                  c[i][j]=c[i-1][j-1]+1;
                  b[i][j]=1;
             }
             else if (c[i-1][j]>=c[i][j-1]){
                 c[i][j]=c[i-1][j];
                 b[i][j]=2;
             }

             else {
                 c[i][j]=c[i][j-1];
                 b[i][j]=3;
             }
          }
}

//算法复杂度O(m+n)
void LCS(int i,int j,char *x,int (*b)[100])
{
if (i ==0 || j==0) return;
if (b[i][j]== 1){
    LCS(i-1,j-1,x,b); cout<<x[i-1]<<" ";    //注意xy 的下标-1
}
else if (b[i][j]== 2)
    LCS(i-1,j,x,b);

else LCS(i,j-1,x,b);
}

int main() {
    char x[] = "ABCBDAB";
    char y[] = "BDCABA";
    int c[100][100] = {0};
    int b[100][100] = {0};

    LCSLen(7,6,x,y,c,b);
    cout<<"c:"<<endl;
    for(int i = 0; i <= 7; i++){
        for(int j = 0; j <= 6; j++){
            cout<<c[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"b:"<<endl;
    for(int i = 0; i <= 7; i++){
        for(int j = 0; j <= 6; j++){
            cout<<b[i][j]<<" ";
        }
        cout<<endl;
    }

    LCS(7,6,x,b);
    return 0;
}