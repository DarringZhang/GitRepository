//
// Created by Darring on 2018/11/29.
//

#ifndef INC_4_1_ARTICULATION_H
#define INC_4_1_ARTICULATION_H
/*
 * 关键节点：无向连通图中，去掉顶点v 及其所连接的边后，G不连通，v is articulation points
 * 不是关键结点：当前结点 的相邻白色节点 与 当前结点的前驱之一 之间 有一条路径， 当前结点不是key
 * 寻找关节节点：计算结点的low 值
 * low值：其祖先最早能发现的时间
 * */
#include <iostream>
#include <string>
#include <climits>
#define SIZE 100
using namespace std;
enum color{WHITE,GRAY,BLACK};


struct Node{
    int degree;
    int low;//发现时间最早的祖先结点
    int color;//结点被标记的颜色
    int d;
    bool key;//判断是否为关键节点
    struct Node *AdjList;
    Node(){
        degree = 0;
        color = WHITE;
        d = INT_MAX;
        low = INT_MAX;
        key = false;
    }

};


class UnDirectedGraph {
private:
    Node *NodeList;
    int n;//顶点个数
    int e;//边的条数
    int clock;//计时
    int count;//记录当前已经访问的结点个数
public:
    UnDirectedGraph() {
        NodeList = new Node[SIZE+1];
    }

    ~UnDirectedGraph() {
        delete[] NodeList;
        for (int i = 1; i <= n; ++i) {
            delete[] NodeList[i].AdjList;
        }
    }

    void createAdjGraph() {
        int _n, _e;
        cout << "输入图的顶点数和边数:";
        cin >> _n >> _e;
        this->e = _e;
        this->n = _n;

        for (int i = 1; i <= n; ++i) {
            NodeList[i].AdjList = new Node[n+1];
        }//为每个节点的邻接结点数组开辟空间

        cout << "输入每条边的信息（对应每条边输入邻接的两个点的下标 1-base，下标输入无序）:";
        int index1;
        int index2;
        int de1;//该点的度数
        int de2;
        for (int j = 0; j < e; ++j) {
            cin >> index1 >> index2;
            NodeList[index1].degree++;//度是几，就有几个邻接点
            de1 = NodeList[index1].degree;
            NodeList[index1].AdjList[de1] = NodeList[index2];

            NodeList[index2].degree++;
            de2 = NodeList[index2].degree;
            NodeList[index2].AdjList[de2] = NodeList[index1];
        }
    }

    void FindArticulation(){
        clock = 1;
        NodeList[1].d = 1;
        count = 1;
        DFSArticul(NodeList[1].AdjList[1]);//从1号结点的第一个邻接结点开始计算low值
        if(count < n){//访问完1号结点的第一个邻接结点的所有邻接结点后，回到一号节点，发现count < n总，则一号节点一定是关键节点
            NodeList[1].key = true;
            for(int i = 1; i <= NodeList[1].degree; ++i){//访问一号节点的其他邻接结点
                if(NodeList[1].AdjList[i].color = WHITE){
                    DFSArtical(NodeList[1].AdjList[i]);
                }
            }
        }

    }

    DFSArticul(Node u){
        u.color = GRAY;
        clock++;
        int min = clock;//计算最小的low值
        u.d = clock;
        count++;
        for(int i = 1; i <= u.degree; ++i){// u 的所有 u邻接结点
            if(u.AdjList[i].color = WHITE){
                DFSArtical(u.AdjList[i]);
                if(u.AdjList[i].low < min){
                    min = v.low;
                }
                if(u.AdjList[i].low > u.d){
                    u.key = true;
                }
            }
            else if(u.AdjList[i].d < min){
                min = u.AdjList[i].d;
            }
        }

        u.low = min;
    }


};
#endif //INC_4_1_ARTICULATION_H
