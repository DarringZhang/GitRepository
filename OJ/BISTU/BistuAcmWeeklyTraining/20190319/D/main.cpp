#include <bits/stdc++.h>
using namespace std;
/*知识点：正整数n 可分解为 n = p1^ni   * p2^n2  *p3^n3 ……pi^ni
 * pi 为两两不同的质数
n的约数有 (n1+1)*(n2+1)*……(ni+1)个

 若求A/B的约数个数，A可分解为p1^a1*p2^a2*...*pk^ak，B可分解为q1^b1*q1^b2*...*qk^bk,

 则A/B的约数个数 为(a1-b1+1)*(a2-b2+1)*(a3-b3+1)...*(ak-bk+1).
 */
int main() {
    long long i=0,j=0;//注意i 为ll 而不是int，后面有i*i
    int p[111] = {0};
    long long b;
    cin >> b;

    if(b==1){
        cout<<1;
        return 0;
    }

/*素数是因子为1和本身
 *
 *  如果数c不是素数，则还有其他因子，其中的因子，假如为a,b.其中必有一个大于sqrt(c)
 *  一个小于sqrt(c) 。所以m必有一个小于或等于
 * 其平方根的因数，那么验证素数时就只需要验证到其平方根就可以了。
 * 即一个合数一定含有小于它平方根的质因子。
 */

    for ( i = 2;i * i <= b; ++i){//求小于b 的所有约数
        if(b%i==0){//b可以被这个i整除，b可分解成指数形式
            int cnt = 0;
            while(b%i==0){
                b/=i;
                cnt++;
            }
            p[j++]=cnt; //存储指数

            //分出这部分指数后剩下的b  接着分,b值缩小
        }
    }

    if(b>1){//如果 b这个正整数大于一，不是1，还能被1约
        p[j++]=1;
    }

    int time = 1;
    for(i = 0; i < j; ++i){
        time*=p[i]+1;
    }
    cout<<time;
    return 0;
}