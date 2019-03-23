#include <bits/stdc++.h>
using namespace std;
//观察样例图，发现皇后占领的地方将地图划成四块区域，只要王和目标在同一块区域，Yes



//tips:在同一块区域 可以利用数学符号，正负->正，正正正，负负正
int f(int a,int b){
    if(a<b){
        return  -1;
    }
    return 1;
}
int main() {
    int n,a1,a2,b1,b2,c1,c2;
    cin >>n >>a1>>a2>>b1>>b2>>c1>>c2;
    if(f(a1,b1)*f(a1,c1)<0){//  a皇后夹在b国王和c目标之间
        cout<<"NO";
        return 0;
    }

    if(f(a2,b2)*f(a2,c2)<0){
        cout<<"NO";
        return 0;
    }

    cout<<"YES";
    return 0;
}

/*我的想法很复杂：将皇后占领的地方全都标志成1，卡在不知道怎么标对角线
 * int a[1002][1002] = {0};
    int n,a1,a2,b1,b2,c1,c2;
    cin >>n >>a1>>a2>>b1>>b2>>c1>>c2;
    for(int i = 0 ; i <n ; ++i){
        for(int j = 0; j < n ;++j){
            if(i==a1||j==a2){
                a[i][j]=1;
            }
        }
    }

    for(int i = 0 ; i <n ; ++i){
        for(int j = 0; j < n ;++j){

        }
    }
 * */