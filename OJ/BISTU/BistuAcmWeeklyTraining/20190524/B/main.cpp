#include <bits/stdtr1c++.h>
using namespace std;

int main() {
    int n,m;
    char s[1002] = {' '};
    char t[1002] = {' '};

    cin >> n >> m;

    cin >> s >> t;

    int chcnt = 0;
    int chid[1001] = {0};

    for(int i = 0; i < n;i++){

        for(int j = 0; j < m;){
            if(t[j]==s[i]&&t[j+1]!=s[i+1]&&j <= m-1){
                chid[chcnt++] = j+1;
                i++;
                j = i+1;
                break;
                cout<<"hah";
            }
            else{
                j++;
            }
        }
    }

    cout << chcnt<< endl;
    for(int i = 0; i < chcnt; ++i){
        cout << chid[i]<<" ";
    }
    return 0;
}