#include <bits/stdc++.h>
using namespace std;

int main() {
    int n,m,k;  //n处破了，棍子长m, 可用k段胶带
    int a[111111];
    cin >>n>>m>>k;
    for(int i = 0; i < n; ++i){
        cin >> a[i];
    }
    int cha[111111];
    //cha数组存储洞的大小
    for(int i = 0; i < n-1; ++i){
        cha[i] = a[i+1] -a[i];
    }
    sort(cha,cha+n-1);

    long long sum = 0;
    for(int i = 0; i < n-k; ++i){   //前n-k个小片段是完全可以用一块胶带粘的，所以sum这一块胶带
        sum += cha[i];
    }
    cout<<sum+k;//后k段直接用k个1cm的胶带覆盖（这些是不可以合并的洞）
    return 0;
}