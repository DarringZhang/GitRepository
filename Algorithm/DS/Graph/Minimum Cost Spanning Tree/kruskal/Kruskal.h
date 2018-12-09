
#ifndef KRUSKAL_KRUSKAL_H
#define KRUSKAL_KRUSKAL_H



//
// Created by Darring on 2018/12/4.
//

/*
图的最??成树(Minimum Cost Spanning Tree)
 对于?个带权的连通?向图G(V,E), w:(u,v)—>R, 我们希望找到E的?个?环的?集T,使得每?个v都能被连起来\
 且总权值最?.

*/

/*求最小生成树：kruskal算法：
Kruskal算法是基于贪心的思想得到的。首先我们把所有的边按照权值先从小到大排列，
 接着按照顺序选取每条边，如果这条边的两个端点不属于同一集合，那么就将它们合并，
 直到所有的点都属于同一个集合为止。至于怎么合并到一个集合，
 那么这里我们就可以用到一个工具——-并查集
 换而言之，Kruskal算法就是基于并查集的贪心算法。

 (1)将图G看做一个森林，每个顶点为一棵独立的树
(2)将所有的边加入集合S，即一开始S = E
(3)从S中拿出一条最短的边(u,v)此处使用优先队列，如果(u,v)不在同一棵树内，则连接u,v合并这两棵树，同时将(u,v)加入生成树的边集E'
(4)重复(3)直到所有点属于同一棵树，边集E'就是一棵最小生成树


*/
#include <iostream>
#include <queue>
using namespace std;

struct edge{
    int point1,point2,cost;
    bool operator < (const edge& n) const {
        return cost > n.cost;//重载优先队列的小于号，因为默认优先队列是最大堆，比较边的cost
    }
};

class MinimumSpanningTree{
private:
    int *parent;
    int N;
public:
    MinimumSpanningTree(int n){
        this->N = n;
        parent = new int[n+1];
        for(int i = 1; i <= n; ++i ){
            parent[i] = i;
        }
    }

    void Destroy(){
        delete [] parent;
    }

    //并查集
    /*
     * 采用rank和路径压缩算法实现的并查集最坏时间复杂度是O(m α(n) )。其中α是Ackerman函数的某个反函数，
     * 这个函数的值可以看成是不大于4。所以，并查集的三种典型操作（makeset,merge,findset）的时间复杂度是线性的。
     * n>2048后  α（n）就是个<=4的常数
     * */
    int fix_find_recursion(int i){
        if( i != parent[i]){//i 不是 i所在集合的根
            parent[i] = fix_find_recursion(parent[i]);//往上一级找根；一直向上，直到返回值到根为止
        }
        return parent[i];
    }

    bool Merge(int a,int b){
        a = fix_find_recursion(a);
        b = fix_find_recursion(b);//找到各自个祖先，顺便压缩一遍路径
        if(a == b){
            return false;
        }
        else{//不是一棵树的，合并
            parent[a] = b;
            return true;
        }
    }

    void kruskal(){
        edge e;
        int ans = 0;
        int flag = 0;
        priority_queue<edge> Q;//此处使用优先队列（二叉堆实现），使算法复杂度控制在O（elogv）
        //如果这里就用普通数组，需要使用sort函数（分段采用不同的排序方法）事先排好，存在一个数组里面，O（eloge）
        int m = N*(N-1)/2;//m条边（这里任意两点之间都有边）
        cout<<"输入边信息"<<endl;
        while(m--){//利用优先队列将 边 依权重 递增排列
            cin>>e.point1>>e.point2>>e.cost;
            Q.push(e);
        }

        while(!Q.empty()){//e
            e = Q.top();//logv
            Q.pop();
            if(Merge(e.point1,e.point2)){//如果两个点不在同一个集合,就需要增加一条路径
                flag ++;
                ans += e.cost;
            }

            if(flag == N-1){//已经成一棵最小生成树，再多一条边就成环了
                break;
            }
        }

        cout<<ans;
    }
};


#endif //KRUSKAL_KRUSKAL_H
