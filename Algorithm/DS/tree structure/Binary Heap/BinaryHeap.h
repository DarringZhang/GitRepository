//
// Created by Darring on 2018/11/7.
//

#ifndef BINARY_HEAP_BINARYHEAP_H
#define BINARY_HEAP_BINARYHEAP_H

/*二叉堆Binary Heap 首先是一棵完全二叉树（树高h = logn,与数组一一对应,Parent(i) : return i / 2 ; Left(i) : return 2 * i ;Right(i) : return 2 * i + 1;）
 *完全二叉树可以是一个满二叉树，也可以是比满二叉树“少几个叶节点“（有顺序地少）
 * 只关乎父子，不关乎子间的关系（与BST区别）
 * 最大堆：儿子结点都小于父结点，最小堆~
 *优点： 二叉堆是专门为取出最大或最小节点而设计点数据结构，O（1），取出后调整(从第一个非叶子开始调)O（logn）)
 *应用：霍夫曼编码（数据压缩），优先队列，堆排序（优化了选择排序）
 *堆排序相对于选择排序优点：各元素间相对位置不变，
 */
#include <iostream>
using namespace std;
#define MAX 10000
class BinaryHeap{
public:
    int A[MAX];
    int effective = 0;

    BinaryHeap(){};
    ~BinaryHeap(){};


    //定位操作，复杂度O(1)
    int PARENT(int i){
        return i/2;
    }

    int LEFT(int i){
        return 2*i;
    }
    int RIGHT(int i){
        return 2*i+1;
    }


    //堆化操作：将一棵完全二叉树变成最大堆：该函数假设Left(i) 和 Right(i)都是最⼤堆，然后调整A[i]，使得以数组A的第i个节点为堆顶的堆是⼀个最⼤堆.
    //复杂度O(logn) = O(h)
    void MAX_Heapify(int i){
        int large;
        int l = LEFT(i);
        int r = RIGHT(i);
        if(l<=effective&&A[l]>A[i]){
            large = l;
        }
        else{
            large = i;
        }
        if(r<=effective&&A[r]>A[large]){
            large = r;
        }

        if(large!=i){//孩子比父亲大，需要调整，将父亲向下调整
            int t = A[i];
            A[i] = A[large];
            A[large] = t;
            MAX_Heapify(large);//递归向下 调整
        }
    }

    //建堆，自底向上将数组调整为一个最大堆,从第一个非叶子结点开始查它和它儿子的关系
    //复杂度O（nh）
    void Build_Max_Heap(){
        int length = effective/2;
        for(int i = length;i >= 1;i--){//1-based
            MAX_Heapify(i);
        }
    }


    //找堆中最大元素
    int Heap_Maximum(){
        return A[1];
    }



    //拿出二叉堆中最大元素O(h)
    int Heap_Extract_Max(){

        Build_Max_Heap();//建立好一个二叉堆
        cout<<"build heap finished ";
        this->print();

        if(effective<1){
            cout<<"underflow!"<<endl;//下限溢位
            return -1;
        }
        int max = A[1];
        A[1] = A[effective];
        effective--;
        MAX_Heapify(1);//向下调整
        return max;
    }


    //最大堆插入O(h)
    void Max_Heap_Insert(int key){
        Build_Max_Heap();//建立好一个二叉堆
        cout<<"build heap finished ";
        this->print();

        effective++;
        A[effective] = key;//插到最后，再调整
        int i = effective;
        while(i>1 && A[PARENT(i)]<A[i]){//新插入的比父大
            int t = A[i];
            A[i] = A[PARENT(i)];
            A[PARENT(i)] = t;
            i = PARENT(i);//上位
        }

    }


    //应用之 堆排序（将数组中的元素从小到大排列），同时逐渐瓦解二叉堆的二叉树结构
    void HeapSort(){
        int length = effective;
        Build_Max_Heap();//建立好一个二叉堆
        cout<<"build heap finished ";
        this->print();
        for(int i = effective;i>=2;i--){
            int t = A[1];
            A[1] = A[i];
            A[i] = t;
            effective--;
            MAX_Heapify(1);
        }
        effective = length;
    }


    void print(){
        for(int i = 1;i<=effective;i++){
            cout<<A[i]<<" ";
        }
        cout<<endl;
    }


    /*应用之 （最大）优先队列Priority_Queue 类包含方法
     * 1.取得优先级最高的元素Heap_Maximum()
     * 2.删除优先级最高的元素Heap_Extract_Max()
     * 3.将插入的元素放到合适位置Max_Heap_Insert(int key)
     * /


     /*应用之 霍夫曼编码*/


};
#endif //BINARY_HEAP_BINARYHEAP_H
