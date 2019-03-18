#include <bits/stdc++.h>
using namespace std;
int main() {
    int chapters;
    int a[10002];
    cin >> chapters;
    for(int j = 0; j < 2*chapters;j+=2){
        cin >> a[j];
        cin >> a[j+1];
    }

    int k;
    cin >> k;
    int flag = chapters,i = 0;
    while(chapters-->0){
        if(k >= a[i]&&k <= a[i+1]){
            cout << flag;
            break;
        }
        else{
            flag--;
            i+=2;
        }
    }


    return 0;
}
