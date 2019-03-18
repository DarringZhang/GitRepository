#include <bits/stdc++.h>
using namespace std;

int main() {
   long long a[222222];
   long long n;
   cin >>n;
   for(int i = 0; i< n; ++i){
       cin >> a[i];
   }
   sort(a,a+n);
   cout<<a[n-2]<<" "<<a[1];
    return 0;
}