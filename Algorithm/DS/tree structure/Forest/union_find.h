//
// Created by Darring on 2018/11/26.
//

#ifndef FOREST_UNION_FIND_H
#define FOREST_UNION_FIND_H
//森林的存储方式：1.双亲法
// 2.左子右兄法：假想有一个虚拟根，转化为二叉树，再去虚拟根

/*森林的应?, 并查集(?双亲表?法实现)
       并查：一些有 N 个元素的集合应用问题中，我们通常是在开始时让每个元素构成一个单元素的集合，
       然后按一定顺序将属于同一组的元素所在的集合合并，其间要反复查找一个元素在哪个集合中。
       这个过程就涉及到：“合并”和“查找”这两个操作。查找和合并操作其实都是建立在从叶节点向上递归查找根节点的操作上。
       利用并查集，可以实现用数组存储数据，并且查找操作和合并操作的时间复杂度近乎$O(1)$。
 */
/*实现 大致思路：并查集是一种树形数据结构。在这些数据中，每个集合是一棵树，所有的集合在一起就形成了“森林”。
节省空间，借助数组就可以实现。为了方便说明，这里数组的索引值就是数据本身，而索引 i 对应的数组的值arr[i]就是i的根节点。

 合并优化：在“合并操作”的更改根节点指向的这步中，检测两棵树的高度，将高度较低的那颗树指向高度较高的树的根节点。
 所以，在初始化的时候，需要多一个数组rank[]，用来记录以 i 为根节点的树的高度。
 */
#include <iostream>

class UnionFind{
private:
     int count;
     int * parent;//parent[i] 元素 i 父节点的索引
     int * rank;// rank[i] 以i为根 的集合所表示的树的层数
public:
    UnionFind(int count){
        this->count = count;
        parent = new int[count];
        rank = new int[count];

        //开始每个节点独立， 每个节点的根都是自己；
        //开始 树高 都是1
        for(int i = 0; i<count; i++){
            parent[i] = i;
            rank[i] = 1;
        }
    }

    ~UnionFind(){
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
            rank[q_root]  +=1;
        }

    }
};



#endif //FOREST_UNION_FIND_H
