
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n,Max=0,p=0;
char c;
string s;
int main() {
    scanf("%d",&n);
    for(int i=0;i<=n;i++){
        c=getchar();
        if(c==' '){
            Max=max(Max,p);
            p=0;
        }else{
            if(c>='A'&&c<='Z'){
                p++;
                // cout<<c<<p<<endl;
            }
        }
    }
    Max=max(Max,p);
    printf("%d\n",Max);
    return 0;
}