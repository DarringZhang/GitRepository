//
// Created by Darring on 2018/12/3.
//

#ifndef INC_4_3_BUILDPATHTOMERGE_H
#define INC_4_3_BUILDPATHTOMERGE_H
/*
 * 把所有的城镇都看作一个点，每一条路都会与两个点相连接，把每个相连通的分量看成一个集合，
 * 然后用树来表示集合。我们只需要求出根结点的个数，就能求出有多少个集合，
 * 进而求出需要多少条路使它们联通，因此就可以用到并查集。
 * 如果是1个连通分支，说明整幅图上的点都连起来了，不用再修路了；如果是2个连通分支，
 * 则只要再修1条路，从两个分支中各选一个点，把它们连起来，那么所有的点都是连起来的了；
 * 如果是3个连通分支，则只要再修两条路……
 * */
#include <iostream>
using namespace std;
class UnionFind{
private:
    int N,M;//N结点，M条路径
    int * parent;//parent[i] 元素 i 父节点的索引
    int * rank;// rank[i] 以i为根 的集合所表示的树的层数
public:
    UnionFind(int _N,int _M ){
        this->M = _M;
        this->N = _N;

        parent = new int[N+1];
        rank = new int[N+1];

        //开始每个节点独立， 每个节点的根都是自己；
        //开始 树高 都是1
        for(int i = 1; i <= N; i++){
            parent[i] = i;
            rank[i] = 1;
        }
    }

    int * getParent(){
        int *p;
        p = parent;
        return p;
    }
    void deleteUnionFind(){
        delete[] parent;
        delete [] rank;
    }

    int normal_find(int i){//普通单纯查找根，不压缩路径
        int j = i;
        while(parent[j]>0){
            j = parent[j];//根据索引，向上查找
        }
        return j;
    }

//大名鼎鼎的路径压缩，就是在“查找”的过程中，将树的高度压缩成 2 层

//路径压缩方式查找：递归
    int fix_find_recursion(int i){
        if( i != parent[i]){//i 不是 i所在集合的根
            parent[i] = fix_find_recursion(parent[i]);//往上一级找根；一直向上，直到返回值到根为止
        }
        return parent[i];
    }
//非递归
    int fix_find_non_recursion(int x){
        int k,j,r;
        r = x;
        while(r != parent[r]){//查找根节点
            r = parent[r];
        }

        k = x;
        while(k != r){//x!= x的根节点r
            j = parent[k]; //j 暂时存储k 的父节点
            parent[k] = r; //k的父节点 指向根节点
            k = j;    //k 移到父节点的位置，下一步 压缩父节点的路径，以此类推
        }//总体思想：底层逐步向上压缩路径
        return r;//返回根节点是那哪个
    }

    bool is_connected(int p,int q){
        return fix_find_recursion (p) == fix_find_recursion(q);
    }


//合并索引分别为p和q的元素到同一个索引
    void Merge(int p,int q){
        int p_root = fix_find_recursion(p);
        int q_root = fix_find_recursion(q);
        if(p_root ==q_root){return;}

        //为了不增加树的高度，合并时将树的高度低的 指向 树高 高的
        if(rank[p_root] < rank[q_root]){//q  的树高 高
            parent[p_root] = q_root;
        }
        else if(rank[p_root] < rank[q_root]){
            parent[q_root] = p_root;
        }
        else{
            parent[p_root] = q_root;//p的树指向q的树
            rank[q_root] += 1;
        }

    }
};

#endif //INC_4_3_BUILDPATHTOMERGE_H
