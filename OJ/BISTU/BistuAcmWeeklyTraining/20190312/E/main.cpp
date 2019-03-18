#include <bits/stdc++.h>
using namespace std;

int main() {
    int n,k;
    cin >> n>>k;
    if(k<=n/2){
        cout << 3*n + k-1;
    }
    else if(k>n/2){
        cout << 3*n + n-k;
    }
    return 0;
}