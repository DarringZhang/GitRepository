#include <bits/stdc++.h>
using namespace std;
//0代表false 1代表true
int main() {
    int n,k,d;
    int a[101]={0};
    cin>>n>>k;
    while(n--){
        cin>>d;
        a[d%k]++;
    }
    int ans = 0;
    for(int i = 1; i <= k/2 -(k%2==0);i++){
        //若k是偶数，刨去0，余数还剩1——n-1,奇数个；对称的两边两两配对后，还剩一个，要少一个循环，在后面的if(!k%2)补上
        ans+= min(a[i],a[k-i])*2;//能配成几对，看少的那个
    }
    if(!(k%2)){//k是偶数
        ans += a[k/2]/2*2;//除以2   为了向下取整，乘以2  变pair为个数
    }
    cout<<ans+a[0]/2*2;
    return 0;
}