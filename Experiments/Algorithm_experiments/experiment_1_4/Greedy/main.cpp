#include <bits/stdc++.h>
using namespace std;
int n = 11;

void GreedySelector(int n, int s[], int f[], bool A[])
{      //各活动的起始时间和结束时间存储于数组s和f中且按结束时间的非减序排列
    A[1]=true;
       int j=1;

       for (int i=2;i<=n;i++) {
          if (s[i]>=f[j]) { A[i]=true; j=i; }
          else A[i]=falase;
       }
}

int main() {

    bool A[11] = {false};
    int s[11] = {1,3,0,5,3,5,6,8,8,2,12};
    int f[11] = {4,5,6,7,8,9,10,11,12,13,14};

    sort(f,f+n);
    GreedySelector(n,s,f,A);

    for(int i = 0; i < n; ++i){
        if(A[i]){
            cout<<1<<" ";
        }
        else{
            cout<<0<<" ";
        }
    }
    return 0;
}