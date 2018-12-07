//
// Created by Darring on 2018/11/29.
//

#ifndef INC_4_1_ARTICULATION_H
#define INC_4_1_ARTICULATION_H
/*
 * 关键节点：无向连通图中，去掉顶点v 及其所连接的边后，G不连通，v is articulation points
 * 不是关键结点：当前结点 的相邻白色节点 与 当前结点的前驱之一 之间 有一条路径， 当前结点不是key
 * 寻找关节节点：计算结点的low 值
 * low值：隐藏最早发现时间
 * 比较有三，取min：1.该结点v的访问时间d;   2.v的有回边相连的邻接灰色节点（已经访问的祖先k）的d   3.v的下一个邻接白色孩子结点的w的low值
 * 若v存在孩子结点w,使 w.low>v.d(即w的最早访问时间在访问父亲v之后），v就是关键节点
 * */
#include <iostream>
#include <string>
#include <climits>
#define SIZE 100
using namespace std;
enum color{WHITE,GRAY,BLACK};


struct Node{
    int idx;
    int degree;
    int low;
    int color;//结点被标记的颜色
    int d;
    bool key;//判断是否为关键节点
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
    Node *NodeList;//顶点矩阵
    int AdjMatrix[SIZE+1][SIZE+1];//邻接矩阵
    int n;//顶点个数
    int e;//边的条数
    int clock;//计时
    int count;//记录当前已经访问的结点个数
public:
    UnDirectedGraph() {
        NodeList = new Node[SIZE+1];
    }

    ~UnDirectedGraph() {

        delete [] NodeList;

    }
    int GetN(){
        return n;
    }
    Node* GetNodeList(){
        Node *p ;
        p = NodeList;
        return p;
    }
    void createAdjGraph() {
        int _n, _e;
        cout << "输入图的顶点数和边数:";
        cin >> _n >> _e;
        this->e = _e;
        this->n = _n;
        //初始化邻接矩阵
        for(int i = 1; i <= n; ++i){
            for(int j = 1; j <=n; ++j ){
                AdjMatrix[i][j] = 0;
            }
        }

        //初始化顶点矩阵
        for(int i = 1; i <=n; ++i ){
            NodeList[i].idx = i;
        }


        cout << "输入每条边的信息（对应每条边输入邻接的两个点的下标 1-base，下标输入无序）:";
        int index1;
        int index2;
        for (int j = 0; j < e; ++j) {
            cin >> index1 >> index2;
            AdjMatrix[index1][index2] = 1;
            AdjMatrix[index2][index1] = 1;
            NodeList[index1].degree ++;
            NodeList[index2].degree ++;
        }
    }

    /*对DFS稍加修改即可，因为DFSArticul 生成的结果：由所有标灰的节点构成的深度优先生成树具有两类特性
        1.若树根有两棵或者两棵以上的子树，此根必为Articulation.即下面的 count < n
        2.生成树中某个非叶子节点v ，v 所有子树 的节点均没有指向 v 的 祖先的回边，v为Articulation
     */
    void FindArticulation(){
        int flag;
        clock = 1;
        NodeList[1].d = clock;//选择1号点作为起始点
        count = 1;

        for(int i = 1; i <= n; ++i){//寻找一号结点的第一个邻接点
            if(AdjMatrix[1][i] ==1){
                flag = i;
                break;
            }
        }
        NodeList[1].color = GRAY;
        DFSArticul(NodeList[flag]);//从1号结点作为生成树的根，访问它的第一个邻接点
        if(count < n){//访问完1号结点的第一个邻接结点的所有邻接结点后，回到一号节点，发现count < n总，说明访问v的另外一边一定要经过v,则一号节点一定是关键节点
            NodeList[1].key = true;//根节点单独处理
            for(int i = 1; i <= n; ++i){
                if(AdjMatrix[1][i] == 1){//访问一号节点的其他邻接结点
                    if(NodeList[i].color == WHITE){
                        DFSArticul(NodeList[i]);
                    }
                }
            }
        }

    }

    void DFSArticul(Node u){
        NodeList[u.idx].color = GRAY;
        clock++;
        int min = clock;
        NodeList[u.idx].d = clock;//此时  min = u.d
        count++;//又访问了一个结点
        for(int i = 1; i <= n; ++i){
            if(AdjMatrix[u.idx][i] == 1) {// u 的所有邻接结点
                if (NodeList[i].color == WHITE) {
                    DFSArticul(NodeList[i]);//递归计算u的邻接孩子的low
                    if (NodeList[i].low < min) {//计算出了邻接孩子的low,比较
                        min = NodeList[i].low;
                    }
                    if (NodeList[i].low >= NodeList[u.idx].d) {//u的白孩子low > u.d，符合关键节点的条件
                        NodeList[u.idx].key = true;
                    }
                }
                else if(NodeList[i].d < min){//比较前驱的d和当前min，看是否可以有捷径，直接过来
                    min = NodeList[i].d;
                }
            }

        }

        NodeList[u.idx].low = min;

    }


};
#endif //INC_4_1_ARTICULATION_H
