//
// Created by Darring on 2018/12/7.
//
/*
(1)   AOE网
    *导语：
     AOE，AOV都是带权的有向无环图。
    拓扑排序实际上对应着AOV网络(Activity on Vertex),它描述的是一张图中，结点之间的相互制约关系，即结点间的先后顺序或是依赖关系.
    而在实际大型工程或项目中，除了每个步骤间的依赖关系外，我们还比较关心整个路程是否能够顺利进行以及完成整个路程的最短时间.
    哪些活动的延期将会影响整个工程的进度，而加速这些活动是否会提高整个工程的效率。

     *AOE(Activity On Edge netword)网络就是专??来找出整个?程当中哪些步骤不能被延误的?种?段
     *                      1.哪些活动是工程进度的关键   2.完成整项工程最少需要多长时间
     *AOE网的性质：

                只有在某顶点所代表的事件发生后，从该顶点出发的各活动才能开始；

                只有在进入某顶点的各活动都结束，该顶点所代表的事件才能发生。

     * AOV网的顶点表示活动， 边表示活动之间的优先关系
       AOE网的边表示活动，边也表示优先关系，边上的权值表示活动持续的时间
        AOE网是建立在活动之间制约关系(先后关系)没有矛盾的基础上，再来分析完成整个工程至少需要多少时间
        所以，关键路径要建立在拓扑排序好的基础上

 (2)  关键路径：开始点到完成点 活动所持续的 时间之和 叫路径长度，其中路径最长的路叫关键路径，一个工程可能会有多条关键路径，。关键路径上的活动叫关键活动
 （最早开始时间 = 最迟开始时间），提前完成非关键活动并不能加快工程进度。反之，要缩短工期，只能缩短关键路径上的活动（缩短后可能出现之前的关键路径变成了非关键路径）

    特点：　前面定义过，关键路径就是图中从源点到汇点最长（权值最大）的路径。

　　　　　　　　这条路径就决定了整个工程的工期，这说明一个什么问题？

　　　　　　　　关键路径上的顶点与顶点之间的活动的应该最早开始和最迟开始时间是相等的，

　　　　　　　　如果不等那么说明活动还有余额时间（在最早开始时间和最迟开始时间之间可以任选一个时间点开始），这说明还有其他活动是决定这个工程时间的，那就不是关键路径了。


（3）关键路径算法实现
  在整个AOE网上寻找所有活动的最早开始时间和最晚开始时间，并比较它们，如果而二者相等，则表明该活动是关键活动（当然也就是关键路径上的一段了


    1.结点事件的最早发生时间etv(earliest time of vertex)：即顶点vk的最早发生时间
        注意：etv[i]的求解必须在所有前驱的最早发生时间求得之后才能确定，因此是在拓扑有序的基础上进行的

    2.结点事件的最晚发生时间ltv：即在不推迟整个工程的前提下，顶点vk的最晚发生时间
        注意：ltv[i]必须在其所有后继的最晚发生时间求得之后才能确定，因此是在逆拓扑有序的基础上进行的
    3.边活动<Vi,Vj>所需的时间：t(i,j),即AOE网上的边的权值
    4.边活动<Vi,Vj>最早开工时间ete(earliest time of edge)：即弧ak的最早发生时间
        ete(i,j) = etv[i];
    5.边活动<Vi,Vj>最晚开工时间lte：即在不推迟整个工程的前提下，弧ak的最晚发生时间
        lte(i,j) = ltv[j] - t(i,j)

    由 etv 和 ltv 求得ete, lte
    当 ete[k] == lte[k] 时，该活动为关键活动



*/

#ifndef TOPOLOGICAL_SORT_AND_AOE_CRITICAL_PATH_H
#define TOPOLOGICAL_SORT_AND_AOE_CRITICAL_PATH_H


#include <iostream>
#include <string>
#include <stack>
using namespace std;
#define  N 100

struct Node{
    int idx;      //节点代号
    int indegree; //入度域
    int earliest_happen_v;//结点最早发生时间
    int latest_happen_v;//结点最晚发生时间  （由逆 拓扑 求得）
    Node(){
        indegree = 0;
        earliest_happen_v = 0;//初始化为非常早
    }
};


struct Edge{
    int earliest_happen_e;//边最早动工时间
    int latest_happen_e;
    Edge(){
    }
};

class AOE{
private:
    Node* NodeList;//顶点矩阵
    int AdjMatrix[N+1][N+1];//邻接矩阵
    int n;//顶点个数
    int e;//边的条数
    stack <int> StoreToPo;//存储逆拓扑的栈
    stack <int> s;//拓扑排序的辅助栈
public:
    AOE(){
        NodeList = new Node[N+1];
    }

    ~AOE(){
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
            NodeList[i].idx = i ;
        }


        cout << "输入每条边的信息（对应每条边输入邻接的两个点的下标 1-base，下标输入有序）:";
        int index1;
        int index2;
        int weight;
        for (int j = 1; j <= e; ++j) {
            cin >> index1 >> index2 >> weight;
            AdjMatrix[index1][index2] = weight;
            NodeList[index2].indegree ++;
        }
    }





    /**********************************************************/
   //寻找关键路径是建立在拓扑排序的基础上，修改原来的拓扑排序：
    /*1. 初始化每个节点的最早发生时间 =0
     * 2.计算后继节点最早发生时间的操作 if v1.earliest_time_v  + weigth(v1, v2) > v2.earliest_time_v; 更新v2的最早发现时间
    * 3.为了方便计算逆拓扑，栈存 拓扑排序各节点

     */
    bool TopoSort(){
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
            return false;

        } else {
            return true;

        }

    }

    //修改删除掉一个点之后的各个点的入度，并将所有度为0的顶点打入辅助栈S中
    void Fix_Node_Indegree(int dele){
        StoreToPo.push(s.top());  //准备逆拓扑的顺序
        s.pop();
        for(int i = 1; i <= n; ++i){
            if(AdjMatrix[dele][i] != 0){//如果 有  入度邻接
                NodeList[i].indegree--;
                if (NodeList[i].indegree == 0 ) {//如果 入度 由不是 0 减到 0 了
                    s.push(i);
                }
                ///更新最早发现该结点的时间，所有前驱的最早发生时间求得之后才能确定
                if(NodeList[dele].earliest_happen_v + AdjMatrix[dele][i] > NodeList[i].earliest_happen_v){
                    NodeList[i].earliest_happen_v = NodeList[dele].earliest_happen_v + AdjMatrix[dele][i];
                }
            }
        }
    }


    //求关键路径
    bool CriticalPath(){
        if(!TopoSort()){
            cout << "该图有环，不能求关键路径" << endl;
            return false;
        }
        cout<<endl;
        //初始化每个顶点的最迟发生时间，
        for(int i = 1; i <= n; ++i){
            NodeList[i].latest_happen_v = NodeList[n].earliest_happen_v;//初始化为 汇点的最早开始时间
        }


        //按 逆拓扑排序求 顶点最晚发生时间
        //先将邻接矩阵变成逆矩阵,从最后一个点（原来拓扑正序的最后一个点）开始求
        Inverse_Matrix();


        while(!StoreToPo.empty()){
            int t = StoreToPo.top();
            StoreToPo.pop();
            for(int i = 1; i <= n; ++i){
                if(AdjMatrix[t][i] != 0){//  t->i   所有后继的最迟发生时间求得之后才能确定最迟发生时间
                    if(NodeList[i].latest_happen_v - AdjMatrix[t][i] < NodeList[t].latest_happen_v ){
                        NodeList[t].latest_happen_v = NodeList[i].latest_happen_v - AdjMatrix[t][i];
                    }
                }
            }
        }

        //将逆矩阵变回原图的邻接矩阵，便于求关键活动
        Inverse_Matrix();


        cout<<"关键节点有:";
        for(int j = 1; j <= n; ++j ){
            if(NodeList[j].latest_happen_v == NodeList[j].earliest_happen_v){
                cout<<"V"<<j<<" ";
            }

        }
        cout<<endl;
        cout<<"关键路径:";
        //求每条边的动工时间 和 关键 路径，关键路径上对应的点为关键节点
        //所为关键就是既不能提前又不能推后的点
        for(int i = 1; i <= n ;++i){
            for(int j = 1; j <= n; ++j){
                if(AdjMatrix[i][j] != 0){ // i->j
                    int ee = NodeList[i].earliest_happen_v;//边活动最早开始时间
                    int el = NodeList[j].latest_happen_v - AdjMatrix[i][j];//边活动最晚开始时间
                    if(ee == el){
                        cout<<"V"<<i<<"->V"<<j<<" ";
                    }
                }
            }
        }


    }


    void Inverse_Matrix(){
        for(int i = 1; i <= n; ++i){
            int temp;
            for(int j = 1; j <= n; ++j ){
                temp = AdjMatrix[i][j];
                AdjMatrix[i][j] = AdjMatrix[j][i];
                AdjMatrix[j][i] = temp;
            }
        }

    }


};
#endif //TOPOLOGICAL_SORT_AND_AOE_CRITICAL_PATH_H
