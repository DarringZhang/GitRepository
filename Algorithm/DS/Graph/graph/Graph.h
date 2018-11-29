//
// Created by Darring on 2018/11/26.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H
//在有向图G中，如果两个顶点vi,vj间（vi>vj）有一条从vi到vj的有向路径，同时还有一条从vj到vi的有向路径，则称两个顶点强连通(strongly connected)。如果有向图G的每两个顶点都强连通，
// 称G是一个强连通图。有向图的极大强连通子图，称为强连通分量(strongly connected components)。

/*
 * 极?(强)连通?图:?个图的(强)连通?图，并且加?任何?个不在它的点集中的点都会导致它不再(强)连通
 * 极小连通子树（最小生成树）
 * 连通?向图的极?连通?图就是它本?…
 * */
/*
 * 存储方式：
 * 邻接矩阵表示法（数组），邻接链表，十字链表，多重链表（表示无向图）
 * 显然,?向图的链接矩阵是对称的
 * */
/*
 * 图的遍历，宽度优先（BFS）:为了避免同一顶点被访问多次，遍历过程中必须记下被访问过的顶点，用辅助数组visited[0~n-1]
 * BFS是一种层次遍历，所以该算法需要借助队列来实现。利用一个队列，访问push 与它邻接的 所有从未访问过的结点
 *
 * */
#include <iostream>
#include <climits>
#include <queue>
#include <vector>
using namespace std;
enum color{WHITE,GRAY,BLACK};
#define N 5

//不可以再结构体内初始化，因为定义结构体时，并未给其分配内存，所以初值是无法存储的。应该声明结构体变量后，手工赋值。
struct Node{
    int idx;
    int color;//结点被标记的颜色
    int find;//BFS发现的时间
    int start_discover;//开始访问的时间DFS
    int end_discover;//结束访问的时间DFS
    int pai;//前驱的下标
    Node(){
        color = WHITE;  //未访问前都是白色的
        start_discover = INT_MAX;//初始化被发现的时间
        end_discover = INT_MAX;
        find = INT_MAX;
        pai = -1;
    }
};


class VisitedGraph{
private:
    Node *NodeList;//存放结点
    int clock;//计时

    int bfs[N][N] = {    //给定一张5×5的图
        { 0, 1, 1, 0, 0 },
        { 0, 0, 1, 1, 0 },
        { 0, 1, 1, 1, 0 },
        { 1, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 0 }
    };

    int dfs[5][5] = {
            { 0, 1, 1, 0, 0 },
            { 0, 0, 1, 0, 1 },
            { 0, 0, 1, 0, 0 },
            { 1, 1, 0, 0, 1 },
            { 0, 0, 1, 0, 0 }
    };

public:
    VisitedGraph(){
        NodeList = new Node[N];  //0-base
        for(int i = 0; i < N; ++i){
            NodeList[i].idx = i;//为了方便，就将结点下标作为结点信息
        }
    }

    ~VisitedGraph(){
        delete [] NodeList;
    }

    int *FindAdj(int u){
        int *Adj;
        Adj = new int(N);
        for(int i = 0; i < N; ++ i){
            Adj[i] = 0;
        }

       //why int Adj[N] = [0,]数组名取地址得到的是数组名所指元素的地址。
        //对指针取地址得到的是指针变量自身的地址
        for(int i = 0; i < N; ++ i){
//            if(bfs[u][i] == 1){
//                Adj[i] = 1;
//            }

            if(dfs[u][i] == 1){
                Adj[i] = 1;
           }

        }
        return Adj;
    }

    void BFS(int start){
        queue <int> Q;
        Q.push(start);
        NodeList[start].color = GRAY;//start号位置的结点已经被访问
        NodeList[start].find = 0;

        while(!Q.empty()){
            int front = Q.front();
            Q.pop();
            int *Adj = FindAdj(front);
            for(int i = 0; i < N; ++ i){
                if(Adj[i] == 1){//for each node in Adj[front]
                    if(NodeList[i].color == WHITE){
                        NodeList[i].color = GRAY;
                        NodeList[i].find = NodeList[front].find +1;
                        NodeList[i].pai = front;
                        Q.push(NodeList[i].idx);
                    }
                }
            }
            NodeList[front].color = BLACK;
            print_BFS(NodeList[front]);
        }

        Check_Cannot_reach(start);

    }


    void print_BFS(Node u){
        if(u.pai==-1){
            cout<< u.idx <<"号结点没有前驱";
        }
        else{
            cout<< u.idx <<"号结点的前驱是"<< u.pai <<"号结点";
        }
        cout<<", 发现时间为："<<u.find<<"s"<<endl;
    }


    void DFS(){
        clock = 0;
        for(int i = 0; i < N; ++ i ){
            if(NodeList[i].color == WHITE){
                DFS_VISIT(NodeList[i].idx);
            }
        }

    }

    void DFS_VISIT(int start){
        clock ++;
        NodeList[start].start_discover = clock;
        NodeList[start].color = GRAY;
        int *Adj = FindAdj(start);
        for(int i = 0; i < N; ++ i){
            if(Adj[i] == 1){//for e-ach node in Adj[front]
                if(NodeList[i].color == WHITE){
                    NodeList[i].pai = start;
                    DFS_VISIT(NodeList[i].idx);
                }
            }
        }

        NodeList[start].color = BLACK;
        clock++;
        NodeList[start].end_discover = clock;
        print_DFS(NodeList[start]);

    }


    void print_DFS(Node u){

        if(u.pai == -1){
            cout<< u.idx <<"号结点没有前驱";
        }
        else{
            cout<< u.idx <<"号结点的前驱是"<< u.pai <<"号结点";
        }
        cout<<", discover/finish："<<u.start_discover<<"/"<<u.end_discover<<endl;



    }

    void Check_Cannot_reach(int start){
        for(int i = 0 ;i < N; ++i){
            if(NodeList[i].color == WHITE){
                cout<<NodeList[start].idx<<"号结点不可到达"<<NodeList[i].idx<<"号结点！"<<endl;
            }
        }
    }
};




#endif //GRAPH_GRAPH_H
