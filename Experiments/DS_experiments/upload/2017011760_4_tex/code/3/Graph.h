//
// Created by Darring on 2018/11/26.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

/*
 * //DFS  BFS  邻接矩阵存储方式：复杂度O(n^2)，最坏空间复杂度O(V*V)
 *
 * */
/*DFS具有许多重要性质，DFS产生的图形成一个有多棵树构成的森林,结点v是深度优
先森林结点u的后代 当且仅当 结点v在结点u的灰阶段被发现，结点的发现时间和完成时间具有括号化结构
无向图的连通分量：如下DFS所述
 有向图的强连通分量：G 与G^T中都能到达的点
 对逆图按照结束时间从大到小的顺序进行DFS.  DFS产生的图形成有多棵树构成的森林。 森林中的每棵树表表一个强连通分量
 （即DFS中那个判断进去的次数）

 */
#include <iostream>
#include <climits>
#include <queue>
#include <vector>
using namespace std;
enum color{WHITE,GRAY,BLACK};
#define N 5

//结构体内初始化，因为定义结构体时，并未给其分配内存，所以初值是无法存储的。应该声明结构体变量后，在Node()构造函数内赋值。
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

    int bfs[N][N] = {    //给定一张5×5的图 用于BFS
        { 0, 1, 1, 0, 0 },
        { 0, 0, 1, 1, 0 },
        { 0, 1, 1, 1, 0 },
        { 1, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 0 }
    };

    int dfs[5][5] = {         ////给定一张5×5的图 用于DFS
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

    int *FindAdj(int u){//找结点u的邻接一维数组
        int *Adj;
        Adj = new int(N);
        for(int i = 0; i < N; ++ i){//初始化邻接一维数组，若不邻接，Adj[i] = 0;邻接就等于1
            Adj[i] = 0;
        }

       //why int Adj[N] = [0,]//如果没有new,出了这个函数，有关数组Adj的指针就会丢失，而new出来的空间，专门有一块内存存储它，不显示delete,就不会被释放
       // 数组名取地址得到的是数组名所指元素的地址。//对指针取地址得到的是指针变量自身的地址，详情请见GitRepository/other/pointer
        for(int i = 0; i < N; ++ i){

//进行DFS遍历时，将这个if注释,避免返回邻接数组产生冲突.
            if(bfs[u][i] == 1){
                Adj[i] = 1;
            }

//进行BFS遍历时，将这个if注释,避免返回邻接数组产生冲突.
 /*           if(dfs[u][i] == 1){
               Adj[i] = 1;
           }
*/

        }
        return Adj;
    }

    void BFS(int start){
        queue <int> Q;//利用辅助队列，先访问初始结点，再初始节点的邻居，再邻居的邻居
        Q.push(start);
        NodeList[start].color = GRAY;//start号位置的结点已经被访问
        NodeList[start].find = 0; //标记访问时间

        int *Adj;
        while(!Q.empty()){
            int front = Q.front();
            Q.pop();
             Adj = FindAdj(front);  //寻找存放当前节点的  所有邻接结点的一维数组
            for(int i = 0; i < N; ++ i){//将当前结点  所有未访问过的邻接结点 push
                if(Adj[i] == 1){//for each node in Adj[front]
                    if(NodeList[i].color == WHITE){//该邻接点未访问
                        NodeList[i].color = GRAY;
                        NodeList[i].find = NodeList[front].find +1;//该结点的访问时间在父亲节点的基础上++
                        NodeList[i].pai = front;
                        Q.push(NodeList[i].idx);
                    }
                }
            }
            NodeList[front].color = BLACK;//父亲结点访问完毕
            print_BFS(NodeList[front]);//BFS特点的打印，只有一个访问时间，即每个节点只经过一次（区别于DFS）
            delete [] Adj;//释放邻接一维数组的空间
            Adj = NULL;
        }

        //检查是否还有BFS不能遍历到的
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
            if(NodeList[i].color == WHITE){//无向图的连通分量：这个判断进去多少次，就有几个连通分量
                DFS_VISIT(NodeList[i].idx);
            }
        }

    }

    /*首先访问出发点start, 从出发点依次搜索出发点的每个邻接点w,
    若w未访问，则以 w 未新的出发点，直到最深层次的点所有邻接点都被访问了为止，再回溯到上一结点--------递归*/
    void DFS_VISIT(int start){
        clock ++;
        NodeList[start].start_discover = clock;
        NodeList[start].color = GRAY;
        int *Adj = FindAdj(start);
        for(int i = 0; i < N; ++ i){
            if(Adj[i] == 1){            //for each node in Adj[front]
                if(NodeList[i].color == WHITE){
                    NodeList[i].pai = start;
                    DFS_VISIT(NodeList[i].idx);//该结点没有访问，再从该结点出发，深入访问
                }
            }
        }

        NodeList[start].color = BLACK;
        clock++;
        NodeList[start].end_discover = clock;//记录访问完成的时间
        print_DFS(NodeList[start]);
        delete [] Adj;
        Adj = NULL;
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
