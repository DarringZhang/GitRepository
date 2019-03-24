#include<bits/stdc++.h>
using namespace std;
//用最少的动作将所有的烤串翻面
int main(){
    int n,k;
    cin>>n>>k;
    int p=2*k+1;
    int cnt=n/p+(n%p!=0);
    int yu=n%p;
    int i=k+1;
    if(yu<k+1&&yu)i-=k-yu+1;
    cout<<cnt<<endl;
    while(cnt--){
        cout<<i<<" ";
        i+=p;
    }
}