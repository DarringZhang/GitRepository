//
// Created by Darring on 2018/12/5.
//

#ifndef TOPOLOGICAL_SORT_AND_AOE_TOPOLOGICAL_H
#define TOPOLOGICAL_SORT_AND_AOE_TOPOLOGICAL_H
/*
 * 拓扑排序：活动间的先后次序依赖关系，主要是为解决一个工程能否顺序进行的问题, 每个步骤（结点）的依赖关系
 * 指对一个有向无环图(Directed Acyclic Graph)，G=(V,E)的所有顶点v线性排序,排序的结果是如果G有一条边(u,v),那么顶点u会排在顶点v的前面
 *要进行拓扑排序，前提是图中不存在环,检测：DFS探索
 *拓扑排序步骤：if  DFS检测有环，返回 错误   else 有向图中选择一个没有前驱的节点输出它，删除该节点及其它发出的边
 * 重复else ,直到全部顶点已经输出 或者 当前图不存在没有前驱的节点（入度为0的节点）
 * 若图中顶点未被全部输出，剩余的顶点的入度均不为0，则说明网中存在有向环
 *
 *
 * 方法一：只需要使?DFS就可以获得?个DAG的拓扑排序结果:一个链表DFS_VISIT(Node u)函数里面 链表Q.push_front(u);
 * 方法二：还可以通过计算每个顶点的入度拓扑排序，若网中所有顶点都在拓扑排序的序列中，则不存在环
 *
 *
 * 拓扑排序的结果不唯一， 但先后相对顺序都不变
 * */
#include <iostream>
#include <string>
#include <stack>
using namespace std;
#define  N 100
struct Node{
    int idx;//节点代号
    int indegree;
    bool has_been_pushed;
    Node(){
        indegree = 0;
        has_been_pushed = false;
    }
};

 class AOV{ //AOV Activity On Vertex Network 顶点表示活动的网
 private:
     Node* NodeList;//顶点矩阵
     int AdjMatrix[N+1][N+1];//邻接矩阵
     int n;//顶点个数
     int e;//边的条数
     stack <int> s;// stack不能遍历，所以没有迭代器！
 public:
     AOV(){
         NodeList = new Node[N+1];
     }

     ~AOV(){
         delete [] NodeList;
     }

     void createGraph(){
         //邻接矩阵
         //更改顶点矩阵中每个点的入度
         int _n;
         int _e;
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


         cout << "输入每条边的信息（对应每条边输入邻接的两个点的下标 1-base，下标输入有序）:";
         int index1;
         int index2;
         for (int j = 0; j < e; ++j) {
             cin >> index1 >> index2;
             AdjMatrix[index1][index2] = 1;
             NodeList[index2].indegree ++;
         }
     }

     //修改删除掉一个点之后的各个点的入度，并//将所有度为0的顶点打入辅助栈S中
     void Fix_Node_Indegree(int dele){
         s.pop();
        for(int i = 1; i <= n; ++i){
            if(AdjMatrix[dele][i] != 0){//删除掉的这个节点delete 有 入度到 i 结点
                NodeList[i].indegree--;
                if (NodeList[i].indegree == 0 ) {
                    s.push(i);
                }
            }
        }
     }

     void TopoSort(){
             int count = 0;//计数已经输出了多少个

             for (int i= 1; i <= n; ++i){//将所有度为0的顶点打??个辅助栈S中
                 if (NodeList[i].indegree == 0) {
                     s.push(i);
                 }
             }

             while (!s.empty()){
                 cout << s.top() << " ";
                 Fix_Node_Indegree(s.top());
                 count++;

             }

         if (count < n) {
             cout << "该图有环,，不能求关键路径" << endl;
         } else {
             cout << "该图无环" << endl;
         }

     }

 };
#endif //TOPOLOGICAL_SORT_AND_AOE_TOPOLOGICAL_H
