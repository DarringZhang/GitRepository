#include <bits/stdc++.h>
using namespace std;
/*理清思路，过程不要太复杂
 1.将时间全都化成分钟
 2.算出时间差sub 除以2  =  中间的分钟
 3.前面的时间h1 m1 进位适当加上 sub/2
 */
int main() {
    int h1,m1,h2,m2;
    char ch;
    cin>>h1>>ch>>m1;
    cin>>h2>>ch>>m2;
    int min1 = m1 + 60*h1;
    int min2 = m2 + 60*h2;
    int sub = min2-min1; //先暂且不管正负
    sub/=2;   //得出中间的分钟数

    m1 +=sub;
    while(m1>=60){
        m1-=60;
        h1++;
    }

    //注意小时和分钟 小于10 时规范格式 补上0
    // %02d 不足两位的在前面补上0
    printf("%02d:%02d\n", h1, m1);


    return 0;
}