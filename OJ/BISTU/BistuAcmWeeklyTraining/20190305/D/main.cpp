#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
using namespace std;

//重点思路是排序

int main() {
    int a[200000];
    int count,aim;
    cin>> count>>aim;
    for(int i = 0; i < count; ++i){
        cin >> a[i];
    }
    sort(a,a+count);

    if((a[aim] == a[aim-1]) || (a[aim] == a[aim-1] + 1)|| aim == 0){
        cout<< "-1";
    }
    else {
        cout << a[aim-1] + 1;
    }
    return 0;
}