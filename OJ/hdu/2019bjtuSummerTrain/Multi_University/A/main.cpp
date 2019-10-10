#include <bits/stdc++.h>
using namespace std;

long long calculate_four_npower(int n){
    long long ans;
    while(n--){
        ans = (ans * 4)%998244353;
    }
    return ans;
}

int main() {
    int T;
    int n,m;
    cin >> T;
   while(T--){
       cin >> n >> m;
       if(m == 0){
            cout << calculate_four_npower(n)<<endl;
            break;
       }
       else{
           int l[101],r[101],x[101];
           for(int i = 0; i < m; ++i){
               cin >> l[i] >> r[i] >> x[i];
           }


       }
   }
    return 0;
}

/*
 * m != 0
 *区间之间的关系条件分为三种情况。
 * 1.区间不相交，各自情况，相加
 * 2.区间相交但不包含重合，先考虑交叉的部分，再各自考虑
 * 3.区间存在包含，先满足小区间（小区间的x 一定 <= 大区间的 x）,再去满足大区间
 *
 *最坏的情况，m = 100个条件, 这些区间中三种情况都有，而且m给出的条件不一定是按从小的。
 * 开一个大小为N的数组A,赋初值0，m个条件中，被cue到的区间对应的A内数字+1，可以通过A内数字还原区间，然后呢？
 * 数字0 代表该空格没被cue, 1代表只被cue了一次....
 *
 *
 * 比如m=2 要满足两个条件。
 * 条件分别是2 4 2 和2 5 2.
 * 区间存在包含情况
 *
 * */