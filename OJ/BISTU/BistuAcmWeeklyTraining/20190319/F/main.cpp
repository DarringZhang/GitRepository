#include<bits/stdc++.h>
using namespace std;
int main() {
    char a[111111];
    cin>>a;
    int m = 999999;
    for(int i = 0;i < 26; ++i){
        int count =1,maxn = 1;
        for(int j = 0; a[j]!= '\0';j++){
            if(a[j]==i+'a')
                count = 1;
            else
                count++;
                maxn = max(count,maxn);
        }
        m = min(m,maxn);
    }
    return 0;
}