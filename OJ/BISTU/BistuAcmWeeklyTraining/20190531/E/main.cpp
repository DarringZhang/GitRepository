#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    int sum=0,y=0;
    int tong[10]={0};
    int k,i;
    cin>>n>>k;
    for(i=0;i<n;i++){
        int x;
        cin>>x;
        sum+=x/10;
        tong[x%10]++;
        y+=(100-x)/10;

    }

    for(i=9;i>0;i--){

        if(tong[i]*(10-i)<=k){
            k-=tong[i]*(10-i);
            sum+=tong[i];
        }
        else{
            sum+=k/(10-i);
            cout<<sum;
            return 0;

        }
    }
    cout<<sum+min(y,k/10);
}