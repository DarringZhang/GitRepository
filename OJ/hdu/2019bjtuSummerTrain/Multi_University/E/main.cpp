#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    int n,m;
    cin >> T;
    while(T--){
        cin >> n >> m;
        int path[n][n];

        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                path[i][j] = -1;
            }
        }

        int x,y,c;
        for(int i = 0; i < m; ++i){
            cin >>x>>y>>c;
            path[x][y] = c;
        }

    }
    return 0;
}

/*不知道已知终点和起点最短路径怎么求。复习prim,dijstra,krustal
 *
 * 找最短路径，然后毁掉其中代价最小的一段。
 * 问题是
 * 1.只有一条最短路径，答案即代价最小的一段
 * 2.最短路径不止一条，比如有三条总路径长度都是9，
 * 分为这三条路径重叠和不重叠的情况
 *   ①不重叠，各自砍最小的一节，再相加。
 *   ②重叠，比较砍掉重叠部分还是一条一条地看每个最短路径中代价最小的一节
 *
 *
 * */