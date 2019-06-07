#include <bits/stdc++.h>
using namespace std;

int main() {
    int n,n1,n2;
    int a[100001] = {0};
    cin >> n>>n1>>n2;
    for(int i = 0; i < n; ++i){
        cin >> a[i];
    }

    sort(a,a+n);
    reverse(a,a+n);

    if(n1 > n2){
        swap(n1,n2);
    }

    int i;
    double  ans1 = 0;
    double  ans2 = 0;
    for(i = 0 ; i < n1; ++i){
        ans1 += a[i];
    }
    ans1/=n1;

    int j;
    for(j = i ; i < n2+n1; ++i){
        ans2 += a[i];
    }
    ans2/=n2;

    printf("%.8f",ans1+ans2);
    return 0;
}