//
// Created by Darring on 2018/12/2.
//

#ifndef INC_4_2_SINGLESOURCESHORTESTPATHS_H
#define INC_4_2_SINGLESOURCESHORTESTPATHS_H

#include <iostream>
#include <queue>
#include <climits>
using namespace std;


struct Node{
    int idx;
    int pai;
    bool visited ;
    Node(int _pai = -1){
        pai = _pai;
        visited = false;
    }

};

class Dijkstra{
private:
    int AdjMatrix[101][101];
    Node NodeList[101];
    int distance[10001];//存储所有点到begin 点的最短距离初始值
    int N,M;


public:
    Dijkstra(){

    }

    void CreateGraph(int n,int m){
        N = n;//n个顶点
        M = m;//m条路径

        for(int i = 1; i <= n; ++i ){//初始化结点列表
            NodeList[i].idx = i;
        }

        for(int j = 1; j <= n; ++j ){//初始化邻接矩阵
            for(int i = 1; i <= n; ++i){
                AdjMatrix[j][i] = INT_MAX;
            }
        }
        cout<<"输入结点和花费"<<endl;
        int a,b,cost;//输入 a b 的花费
        for(int i = 1; i <= m; ++i ){
            cin>>a>>b>>cost;
            AdjMatrix[a][b] = cost;
            AdjMatrix[b][a] = cost;
        }
        cout<<"finish"<<endl;
    }

    void RELAX(Node u,Node v,int w){ //distance里面每个值都是start到v的路径过程中权值的累加
        if(distance[v.idx] > distance[u.idx] + w){//从u过来花费代价小,w = 无穷远，u v不可达，不考虑
            distance[v.idx] = distance[u.idx] + w;//更新u.d
            v.pai = u.idx;
        }
    }

//无负权重有向图，单源最短路径

    void Calculate_Dijkstra(int start){//开始
        int t;
        int count = N-1;
        NodeList[start].visited = true;
        //初始化所有点到start 点的最短距离初始值
        for(int i = 1; i <= N; ++i){
            distance[i] = AdjMatrix[start][i];
        }
        distance[start] = 0;//自己到自己


        while(count-->0){
            t = FindMinDistance();//每次取出一个距离start点权值最小的未访问的点
            NodeList[t].visited = true;

            //然后松弛start通过t这个点到其它点j的路径
            for(int i = 1; i <= N; ++ i){
                if(t!=i && AdjMatrix[t][i]!=INT_MAX){//t到自己就不用松弛了，且t到i无穷远，花费太大，也不用松弛
                    RELAX(NodeList[t],NodeList[i],AdjMatrix[t][i]);//start这个点通过t这个点访问其它结点，看是否可以松弛
                }

            }
        }

    }

    int SumDistance(){
        return distance[N];
    }

    int FindMinDistance(){//找到未标记的最小结点下标
        int min_idx = N;
        for( int i = 1; i <= N; ++i){
            if(distance[min_idx] > distance[i] && NodeList[i].visited == false ){
                min_idx = i;
            }
        }
        return min_idx;
    }

};
#endif //INC_4_2_SINGLESOURCESHORTESTPATHS_H
