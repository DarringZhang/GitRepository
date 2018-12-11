//
// Created by Darring on 2018/12/10.
//
//实验4.2是普通实现，时间复杂度O(n^2)，下面基于最小堆的实现，复杂度ElgV。
//注释掉下面的distance（存储与出发点最小的距离值），改用优先队列

/*具体的实现跟Prim类似
 * 开始时将源点添加到SPT中，然后，每次增加一条边来构建SPT，
 * 所取的边总是可以给出从源点到尚未在SPT中某个定点的最短路径。这样，顶点按照到源点的距离由小到大逐个添加到SPT中
 *从SPT之外的顶点中选择一个顶点v，对应边的权值最小；然后对这条边进行松弛操作。算法迭代直至图中所有顶点都在SPT中为止。
 * */
#ifndef DIJKSTRA_DIJKSTRA_H
#define DIJKSTRA_DIJKSTRA_H


#include <iostream>
#include <queue>
#include <vector>
#include <memory.h>
#include <climits>
using namespace std;
#define SIZE 100000
//从堆中出一个距离源点路径最短的顶点。刚好符合堆的基本操作（删除堆顶元素），这里也体现了Dijkstra是个贪心算法。


struct Edge{int to,cost;};
typedef pair<int,int>P; //first是最短距离，second是顶点的编号



class Dijkstra {
private:
    int AdjMatrix[101][101];
    Node NodeList[101];
    vector<Edge>G[SIZE];
   // int distance[10001];//存储所有点到begin 点的最短距离初始值
    int N, M;


public:
    Dijkstra() {

    }

    void CreateGraph(int n, int m) {
        N = n;//n个顶点
        M = m;//m条路径

        for (int i = 1; i <= n; ++i) {//初始化结点列表
            NodeList[i].idx = i;
        }

        for (int j = 1; j <= n; ++j) {//初始化邻接矩阵
            for (int i = 1; i <= n; ++i) {
                AdjMatrix[j][i] = INT_MAX;
            }
        }
        cout << "输入结点和花费" << endl;
        int a, b, cost;//输入 a b 的花费
        for (int i = 1; i <= m; ++i) {
            cin >> a >> b >> cost;
            AdjMatrix[a][b] = cost;
            AdjMatrix[b][a] = cost;
        }
        cout << "finish" << endl;
    }

    void dijkstra(int s){
        priority_queue<P> Q;
        int *d = new int[SIZE];
        memset(d,INT_MAX,SIZE* sizeof(d));// 记得delete
        d[s] = 0;
        Q.push(P(0,s));
        while(!Q.empty()){
            P p = Q.top();
            Q.pop();
            int v = p.second;//获取该点的编号
            if(d[v]<p.first){//不需要松弛
                continue;
            }
            for(int i = 0; i <= )
        }
    }


};
#endif //DIJKSTRA_DIJKSTRA_H
