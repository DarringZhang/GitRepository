#include <bits/stdc++.h>
using namespace std;
int main() {
    int bar_num;
    int a[333333];  //最大33554432  ，这里开到30万，因为题目的n 范围
    cin >> bar_num;
    for(int i = 0; i < bar_num; ++i){
        cin >> a[i];
    }

    sort(a,a+bar_num);

    int coupon;
    cin >> coupon;
    //注意最终都是要加起来的，不需要循环分两次coupon加
//    for(int i = 0; i < coupon;++i){
//        int t ;
//        cin >> t;
//        int b[222222];
//        for(int j = 0; j < t; ++j){
//            b[j] = a[bar_num - t + j];
//        }
//        int sum = 0;
//        for(int j = 1; j < t; ++ j){
//            sum+=b[j];
//        }
//        for(int j = 0; j < bar_num - t; ++ j){
//            sum+=a[j];
//        }
//        cout << sum<<endl;
//    }

   long long sum = 0;
    for(int i = 0; i < bar_num; ++i){
        sum += a[i]; //30万个亿级别的数相加 注意 sum是 long long
    }

    int t;

    for(int i = 0; i < coupon; ++i){
        cin >> t;
        cout << sum - a[bar_num-t] << endl;
    }






/*
 *  第qi贵的不买,第k大 就是  第n-k个
 * */


    return 0;
}
