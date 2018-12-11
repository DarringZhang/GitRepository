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
//但是可以证明dijkstra的贪心是正确的：见笔记本

struct Node{
    int idx;
    int pai;
    int d;//距离初始点的距离
    bool visited ;
    Node(){
        pai = -1;
        visited = false;
        d = INT_MAX;
    }

};


bool operator < (const Node &a,const Node &b)
{
    return a.d > b.d;
}

class Dijkstra {
private:
    int AdjMatrix[101][101];
    Node NodeList[101];
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
        }
        cout << "finish" << endl;
    }

    void RELAX(Node u,Node v,int w){ //distance里面每个值都是start到v的路径过程中权值的累加
        if(NodeList[v.idx].d > NodeList[u.idx].d + w){//从u过来花费代价小,w = 无穷远，u v不可达，不考虑
            NodeList[v.idx].d = NodeList[u.idx].d + w;//更新u.d
            NodeList[v.idx].pai = u.idx;
        }
    }

//无负权重有向图，单源最短路径

    void Calculate_Dijkstra(int start){//开始
        Node t;
        int count = N-1;
        priority_queue<Node> Q;//存放所有节点，按照d值排序


        //初始化所有点到start 点的最短距离初始值
        for(int i = 1; i <= N; ++i){
            NodeList[i].d = AdjMatrix[start][i];
            if(NodeList[i].d != INT_MAX){
                NodeList[i].pai = start;
                Q.push(NodeList[i]);

            }
        }
        NodeList[start].d = 0;
        NodeList[start].visited = true;


        while(count>0){

            do{
                t = Q.top(); //距离start最近的下一个未被结点t
                Q.pop();
            }while(NodeList[t.idx].visited == true);

            if(NodeList[t.idx].pai!=-1 && NodeList[NodeList[t.idx].pai].visited == true){//它的前驱不能是未被松弛到的点且前驱一定已经在最短路径里面
                NodeList[t.idx].visited = true;//即保证了 下面所说的松弛的次序性
                count--;
            }
            else if(NodeList[t.idx].pai ==-1 ){
                continue;
            }



            //然后松弛start通过当前节点t这个点 到 其它点i的路径
            for(int i = 1; i <= N; ++ i){
                if(t.idx!=i && AdjMatrix[t.idx][i]!=INT_MAX){//t到自己就不用松弛了，且t到i无穷远，花费太大，也不用松弛
                    RELAX(NodeList[t.idx],NodeList[i],AdjMatrix[t.idx][i]);//start这个点通过t这个点访问其它结点，看是否可以松弛
                }//一定是按照最短路径的顺序来松弛，中间夹杂其他松弛也没关系，反正松弛了也不如按照最短路径松弛的程度大，还要再松弛一遍
            }

            for(int i = 1; i <= N; ++i){//和t相邻的， 且未加入最短路径的点 打入队列
                if(i!= t.idx&&AdjMatrix[t.idx][i] != INT_MAX && NodeList[i].visited == false ){
                    Q.push(NodeList[i]);
                }
            }

        }

    }

    void PrintShortestPath(){//倒序打印到任何两个可达点的最短路径
        int sum,j;
        for(int i = 2; i <= N; ++i){
            sum = NodeList[i].d;
            j = i;
            while(NodeList[j].pai != -1){
                cout<<NodeList[j].idx<<"<-"<<NodeList[j].pai<< " ";
                j = NodeList[j].pai;
            }
            cout<<"  sum = "<< NodeList[i].d <<endl;
        }
    }


};
#endif //DIJKSTRA_DIJKSTRA_H
