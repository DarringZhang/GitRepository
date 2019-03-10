#include <bits/stdc++.h>
using namespace std;

//重点思路是排序sort

int main() {
    int a[222222];
    int count,aim;
    cin>> count>>aim;//比结果小或等的数有aim个
    for(int i = 0; i < count; ++i){
        cin >> a[i];
    }
    sort(a,a+count);

    //首先考虑数组下标的情况，数组下标要>=0;所以aim==0挑出来
    if(aim==0){  //没有比结果小或等的数
        if(a[0] > 1){//最小的数都大于一了，没有比  一  更小的数，1是最小的
            cout << 1;
        }
        else{
            cout << -1;//最小的数 = 1 ，不存在结果在最小的数1前面
        }
        return 0;
    }

    if(a[aim] == a[aim-1]) cout <<-1;//第aim 个数  个它后面的相等，没有空给结果插
    else cout <<a[aim-1]; //结果就是第aim个数,小于或等于第aim数
    return 0;
}