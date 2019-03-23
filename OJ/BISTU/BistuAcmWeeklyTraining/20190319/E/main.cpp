#include<bits/stdc++.h>
using namespace std;

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