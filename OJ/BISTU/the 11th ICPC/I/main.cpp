#include <bits/stdc++.h>
using namespace std;
int main() {
    int n,m;
    int p1,p2;
    cin >> n>>m;
    int a[101]= {0};
    for(int i = 1; i <= m; ++i){
        cin>>p1>>p2;
        a[p1]++;
        a[p2]++;
    }

/*    if(n-1>m){
//        cout<<"No";
//        return 0;
    }
*/
    for(int i = 1; i <= m; ++i){
        if(a[i]%2 !=0){
            cout<<"No";
            return 0;
        }
    }
    cout<<"Yes";

}



//（本题）欧拉图：经过每条边，且边不重复
// 判定方法：
/*针对有向图来说：
    1.图G是连通的，不能有孤立的点存在。
    2.每个顶点的入度要等于出度。
    针对无向图来说：
    1.图G是连通的，不能有孤立的点存在。
    2.度数为奇数的点的个数为0。
*/
// 哈密顿图 ： 经过每个点，且点不允许重复
/*
 * (2）设G是n（n>=3）阶无向简单图，若对于G中的每一对不相邻的顶点u，v，均有
d（u）+d（v）>=n-1
则G中存在哈密顿通路。又若
d（u）+d（v）>=n
则G中存在哈密顿回路，即G为哈密顿图。【哈密顿图存在的充分条件】
其中d（u），d（v）分别代表顶点u，v的度数。
 *
 *
 *
 * */