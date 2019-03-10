#include<iostream>
using namespace std;

int main(void) {
    long long m,n,a;  //考虑相乘
    cin>>m>>n>>a;     //  int/long  2* 10 ^9   longlong = 9 * 10^18    lld
    if(n%a == 0 && m%a != 0 ){
        cout<< (m/a) * (n/a) +  n/a  << endl;
    }
    else if(m%a == 0 && n%a != 0){
        cout<< (m/a) * (n/a) +  m/a  << endl;
    }
    else if(n%a != 0 && m%a != 0){
        cout<< (m/a) * (n/a) +  m/a + n/a  + 1 << endl;
    }
    else if(n%a == 0 && m%a == 0){
        cout<< (m/a) * (n/a)<<endl;
    }
    return 0;

}