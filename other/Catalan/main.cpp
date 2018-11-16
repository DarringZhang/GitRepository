#include <iostream>
using namespace std;
/*输入一个整数n，计算h(n)。其递归式如下：h(n)= h(0)*h(n-1)+h(1)*h(n-2) +h(2)*h(n-3)+ ... + h(n-1)h(0)
 * (其中n>=2，h(0) = h(1) = 1)
 * 该递推关系的解为：h(n)=C(2n,n)/(n+1) (n=1,2,3,...)

*/

//计算卡特兰数的第n项h（n）
int Catalan(int n){
    if(n<=1){       //h(0) = h(1) = 1
        return 1;
    }
    int *h = new int[n+1];
    h[0] = h[1] = 1;
    for(int i = 2;i<=n;i++){//依次计算h[2],h[3].....
        h[i] = 0;
        for(int j = 0; j < i; j++){
            h[i] += h[j] * h[i-1-j];
        }
    }
    int result = h[n];
    delete[] h;
    return result;
}
int main() {
    int in;
    while(1){
        cin>>in;
        cout<<Catalan(in)<<endl;
    }
    return 0;
}