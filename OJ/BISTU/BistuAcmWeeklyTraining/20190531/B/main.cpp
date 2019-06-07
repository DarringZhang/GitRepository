#include <bits/stdc++.h>
using namespace std;

int main() {
    int A,B,C,N;
    cin >>A>>B>>C>>N;

    if(A+B-C>=N){
        cout << -1;
    }

    else if(C>A||C>B){
        cout << -1;
    }
    else{
        cout << N-(A-C+B)<<endl;
    }

    return 0;
}