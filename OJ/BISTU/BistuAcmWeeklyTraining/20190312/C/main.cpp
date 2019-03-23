#include <bits/stdc++.h>
using namespace std;
int main() {
    int n,i=1;
    int ans = 1;
    int a[222222];
    cin>>n;

//    while(n-->0){
//        cin>>a[i];
//        ++i;
//    }将n改变了！！！！
    int t = n;
    while(t-->0){
        cin>>a[i];
        ++i;
    }
     sort(a+1,a+1+n);
    //相差不超过5的一定挨在一起
    int flag=1;
    for(i=2;i<=n;++i){
        if(a[i]-a[flag]<=5){//范围在5以内,只后界限i后移
            ans = max(ans,i-flag+1);// 和当前的涉及到的长度i-flag+1取最大
        }
        else{
            flag++;//前界限 往后移
        }
    }
    cout << ans <<endl;
    return 0;
}