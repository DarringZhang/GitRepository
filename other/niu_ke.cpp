#include<iostream>
using namespace std;
long long f(long long n)
{
    if (n < 20180001) return n + 2017;
    return f(f(n - 2018));
}
int main()
{
    long long n;
    while(1){
	cin >> n;
    cout << f(n) << endl;
	}
   
    return 0;
}
