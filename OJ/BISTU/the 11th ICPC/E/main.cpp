#include <bits/stdc++.h>
using namespace std;
int main() {
    int m,n;
    cin>>n>>m;
    if(m%n!=0){
        cout<<m/n+1;
    }
    else{
        cout<<m/n;
    }
    return 0;
}

