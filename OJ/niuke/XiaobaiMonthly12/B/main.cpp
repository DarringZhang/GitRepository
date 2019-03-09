#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >>T;
    double A,B,P;
    while(T-->0){
        cin>> A >>B >> P;
        cout<<pow(A,B)%P;
    }

    return 0;
}