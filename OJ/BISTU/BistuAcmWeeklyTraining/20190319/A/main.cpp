#include <bits/stdc++.h>
using namespace std;
int main() {
   int n;
   cin >> n;

      for(int i = n; i >0 ; --i){
          if(n%i==0){
              cout << i << endl;
              for(int j = 0; j < i; ++j){
                  cout << n/i <<" ";
              }
          }
          return 0;
          }
 }

//直接输出n个1：
/*
 * while(n--){
    cout<<1;
    if(n){
        cout<<" ";
    }
}
 *
 * */
