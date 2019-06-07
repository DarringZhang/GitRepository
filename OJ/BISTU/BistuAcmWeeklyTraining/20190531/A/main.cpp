#include <bits/stdc++.h>
using namespace std;
const int maxn = 101;

int main() {
    int n,x;
    cin >> n >> x;
    int a[maxn] = {0};
    int b[maxn] = {0};


    for(int i = 0; i < n ; ++i){
        cin >> a[i];
        b[a[i]] = 1;
    }


    int cnt = 0;

    if(b[x] == 1){
        cnt++;
    }

    for(int i = 0; i < x; ++i){
        if(b[i] == 0){
            cnt++;
        }
    }

    cout<<cnt<<endl;

    return 0;
}