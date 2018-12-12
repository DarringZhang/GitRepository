//
// Created by Darring on 2018/12/11.
//

#ifndef BELLMAN_FORD_BELLMANFORD_H
#define BELLMAN_FORD_BELLMANFORD_H
/*该算法就比较暴力
 * 算法对每条边做松弛操作，并且重复|V|-1次，所以算法可以在于|V|·|E|成正比的时间内解决单源最短路径问题
 * 对边的情况没有要求，不仅可以处理负权边，还能处理负环
 * 对于一个图G(v,e)(v代表点集，e代表边集)，执行|v|-1次边集的松弛操作，所谓松弛操作，就是对于每个边e1(v,w)，
 * 将源点到w的距离更新为：原来源点到w的距离 和 源点到v的距离加上v到w的距离 中较小的那个。v-1轮松弛操作之后，
 * 判断是否有源点能到达的负环，判断的方法就是，再执行一次边集的松弛操作，如果这一轮松弛操作，有松弛成功的边，那么就说明图中有负环。算法复杂度为O(ne)
 * */
#include <iostream>
#include <queue>
#include <climits>
#include <cmath>
using namespace std;
#define SIZE 101
//注意这里要顾及到AdjMatrix二维数组大小，数组元素太多会出现栈空间的溢出，编译的时候没问题，但栈空间的分配是在运行的时候分配的。解决问题的最好办法是进行堆内存分配，堆内存就很大，栈空间的大小只有K数量级，
// 而堆空间的大小可以达到G的数量级（当然是有虚拟内存了）堆空间分配就是用new，用了之后要注意delete来释放

struct Node{
    int idx;
    int pai;
    bool visited;//给SPFA判断是否在队列中
    Node(){
        pai = -1;
        visited = false;
    }
};


class BellmanFord {
protected:
    int AdjMatrix[SIZE][SIZE];
    Node NodeList[SIZE];
    int distance[SIZE];//存储所有点到begin 点的最短距离初始值
    int N, M;


public:
    BellmanFord() {

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



    //返回一个bool值，bool值为true则图中没有源点可达的负环，false即为图中有源点可达的负环。
    bool Violence_Calculate_BellmanFord(int s){

        for(int i = 1; i <= N; ++i){
            distance[i] = AdjMatrix[s][i];
            if( AdjMatrix[s][i]!=INT_MAX){
                NodeList[i].pai = s;
            }
        }
        distance[s] = 0;


        for(int i = 1; i <= N-1; ++i){//对最短路径上的每一条边都做一次松弛，即 N-1 次

            for(int j = 1; j <= N; ++j){//遍历的整个邻接矩阵，判断是否两点间存在边，如果存在，则进行松弛操作
                for(int k = 1; k <= N; ++k){
                    if(AdjMatrix[j][k]!=INT_MAX){//其实这个地方可以存一份边集,存储start和end，代表某条边的两个端点，初始化图的时候，构造出来所有的边，存储在一个集合中。在进行Bellman-Ford的时候，直接遍历这个边集即可，免去了额外的判断。

                        if(distance[j]+AdjMatrix[j][k] < distance[k]){
                            NodeList[k].pai = j;
                        }

                        distance[k] = min(distance[k],distance[j]+AdjMatrix[j][k]);//通过 j -> k 这条边 到达k点是否比较近

                    }

                }

            }
        }

        //判断是否有负环，再比较一次 已经松弛好的边， 再通过 j -> k 这条边 到达k点是否比较近，若，则有负权重环
        for(int j=1 ;j <= N ; j++) {
            for (int k = 1; k <= N; k++) {
                if (AdjMatrix[j][k] != INT_MAX) {
                    if(distance[k] > distance[j]+AdjMatrix[j][k]){
                        return false;
                    }
                }
            }
        }

        return true;
    }


    void PrintShortestPath(){//倒序打印从起始点到任何一个可达点的最短路径
        int sum,j;
        for(int i = 2; i <= N; ++i){
            sum = distance[i];
            j = i;
            //有环，输出具体路径没意义
            /*while(NodeList[j].pai != -1){
                cout<<NodeList[j].idx<<"<-"<<NodeList[j].pai<< " ";
                j = NodeList[j].pai;
            }*/
            cout<<"  sum = "<< sum <<endl;
        }
    }


};

#endif //BELLMAN_FORD_BELLMANFORD_H
