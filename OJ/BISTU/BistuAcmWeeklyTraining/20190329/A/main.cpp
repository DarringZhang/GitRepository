#include <bits/stdc++.h>
using namespace std;

int main() {
    set<int> s;
    int n;
    cin>>n;

    int input;
    for(int i = 0; i < n; ++i){
        cin >> input;
        if(input !=0){
            s.insert(input);
        }
    }

    cout<<s.size()<<endl;

    return 0;
}