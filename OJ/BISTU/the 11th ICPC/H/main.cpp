//高年级的抽卡
#include <bits/stdc++.h>
using namespace std;

// 阶乘，longlong  到18，int到12 会溢出,所以根据排列组合公式，边除边存数字，不会导致数字太大
long long jiecheng(long long m){
    long long ans = 1;
    while(m>=1){
        ans = ans * m;
        m--;
    }
    return ans;
}

int main() {
    long long n,m;
    long long C = 0;
    double pow1,pow2;
    cin >>n>>m;
    pow1 = pow(0.8,m);
    pow2 = pow(0.2,n-m);


    double temp_ans = 1 ;

    for(int i = m; i>0; --i){
        temp_ans = temp_ans * n/i;
        n--;
    }

    temp_ans = temp_ans *jiecheng(n-m+1);

    printf("%.4lf\n",temp_ans*pow1*pow2);


    return 0;
}
