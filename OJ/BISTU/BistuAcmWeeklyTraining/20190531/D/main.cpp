#include <bits/stdc++.h>
using namespace std;

int main() {
    int a,b,n;
    cin >> n >> a >> b ;
    int t = n;
    for (int i = 0; i * a <=n ;i++){    //注意看题 ，i< n/a 就行了，否则runtime error(另除法不太好，换成乘法)
        if((n-a*i)%b==0){
            cout<<"YES"<<endl;
            cout << i<< " "<< (n-a*i)/b<<endl;
            return 0;
        }
    }
    cout<<"NO"<<endl;

    return 0;
}

