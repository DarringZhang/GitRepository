#include <bits/stdc++.h>
using namespace std;

long long calculate_four_npower(int n){
    long long ans;
    while(n--){
        ans = (ans * 4)%998244353;
    }
    return ans;
}

int main() {
    int T;
    int n,m;
    cin >> T;
   while(T--){
       cin >> n >> m;
       if(m == 0){
            cout << calculate_four_npower(n)<<endl;
            break;
       }
       else{
           int l[101],r[101],x[101];
           for(int i = 0; i < m; ++i){
               cin >> l[i] >> r[i] >> x[i];
           }

       }
   }
    return 0;
}