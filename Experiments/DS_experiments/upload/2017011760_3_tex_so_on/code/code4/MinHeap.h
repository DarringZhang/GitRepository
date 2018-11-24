//
// Created by Darring on 2018/11/21.
//

#ifndef INC_4_MINHEAP_H
#define INC_4_MINHEAP_H


#define MAX 10000
#include <string>
#include <queue>
#include <iostream>
#include <stdio.h>
using namespace std;
struct huffman_node{
    char c;    //结点代号
    float weight; //节点的权值
    string code = "" ;
    huffman_node *left;
    huffman_node *right;
    int position ;
};



//1.声明指针但是没有分配空间 int *p//（即没有指向固定区域）若是int *p = new int;p指向new出来的空间

/*即int *A = new int[Max]//A是一个数组，里面有Max个int 型的数据，要delete[] A
和 int A[Max]，//数组名A实质为一个指针，自动new,自动delete//不需要显式delete*/

//huffman_node **Print = new huffman_node*[MAX];//全局变量，存储结点的信息，main中按输入顺序打印
//Print是一个数组,里面有Max个huffman_node*类型的数据,已经new 出了Max个空间

//错误：huffman_node* A = new huffman_node[MAX];
//huffman_node* A[MAX];//这是一个叫A的数组，里面存放的类型是huffman_node*，还没有为这些Max个指针new空间
//错误：huffman_node* Print[MAX];



//广义小顶堆（每个数组里面放哈夫曼的结点，根据结点权值大小排序）
class MinHeap {

public:

    int effective = 0;
    int number_of_leaves;
    huffman_node *A[MAX];
    huffman_node *Print[MAX];


    MinHeap(){
    }
    ~MinHeap(){
        DestroyPrint();
    }


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


    void create_huffman_node(){
        int size;
        char cc;
        //char maohao;
        cout<<"输入你要编码的字母个数：";
        cin>>size;
        effective = size;
        number_of_leaves = effective;
        cout<<"输入字母和权值"<<endl;
        for(int i = 1; i <= size; i ++){
            A[i] = new huffman_node;
            Print[i] = new huffman_node;
            //cin>>A[i]->c;
            //   cin>>A[i]->weight;
            scanf(" %c%c%f", &A[i]->c,&cc, &A[i]->weight);
            Print[i] ->c = A[i]->c;
            Print[i]->weight = A[i]->weight;
            //cin>>A[i]->c>>maohao>>A[i]->weight;
            // fflush(stdin);

            A[i]->right = NULL;
            A[i]->left = NULL;
            A[i]->position = i;
        }

        memcpy(Print,A,MAX);
    }


    //找堆中最小元素
    int Heap_Minmum(){
        return A[effective]->weight;
    }


    //堆化操作：将一棵完全二叉树(array)变成最小堆：该函数假设Left(i) 和 Right(i)都是最小堆，然后调整A[i]，使得以数组A的第i个节点为堆顶的堆是?个最小堆.
    //复杂度O(logn) = O(h)
    void Min_Heapify(int i){
        int small;
        int l = LEFT(i);
        int r = RIGHT(i);
        if(l<=effective&&A[l]->weight<A[i]->weight){
            small = l;
        }
        else{
            small = i;
        }
        if(r<=effective&&A[r]->weight<A[small]->weight){
            small = r;
        }

        if(small!=i){//孩子比父亲小，需要调整，将小孩子向上调整
            huffman_node* t = A[i];
            A[i] = A[small];
            A[small] = t;
            Min_Heapify(small);//递归向下 调整
        }
    }

    //建堆，自底向上将数组调整为一个最小堆,从第一个非叶子结点开始查它和它儿子的关系
    //复杂度O（h）
    void Build_Min_Heap(){
        int length = effective/2;
        for(int i = length;i >= 1;i--){  //1-based
            Min_Heapify(i);
        }
    }



    //拿出二叉堆中最小元素O(h)
    huffman_node* Heap_Extract_Min(){

        huffman_node* min  = A[MAX];
        if(effective<1){
            cout<<"underflow!"<<endl;//下限溢位
            return min;
        }

        min  = A[1];
        A[1] = A[effective];
        effective--;
        Min_Heapify(1);
        return min;
    }


    //最小堆插入O(h)
    void Min_Heap_Insert(huffman_node *node ){
        effective ++;

        A[effective] = node;

        int i = effective;
        while(i>1 && A[PARENT(i)]->weight>A[i]->weight){//新插入的比父权值小
            huffman_node* t = A[i];
            A[i] = A[PARENT(i)];
            A[PARENT(i)] = t;
            i = PARENT(i);//上位
        }

    }


    //应用之 堆排序（将数组中的元素从小到大排列），同时逐渐瓦解二叉堆的二叉树结构
    void HeapSort(){
        int length = effective;
        Build_Min_Heap();//建立好一个二叉堆
        cout<<"build heap finished ";
        this->print();
        for(int i = effective; i >= 2; i --){
            huffman_node* t = A[1];
            A[1] = A[i];
            A[i] = t;
            effective--;
            Min_Heapify(1);
        }
        effective = length;//还原有效长度，便于打印
    }

    void DestroyPrint(){
        for(int i = 0; i<number_of_leaves; i++){
            delete [] Print[i];
        }
    }


    void print(){
        for(int i = 1;i<=effective;i++){
            cout<<A[i]->c<<"-"<<A[i]->weight<<" ";
        }
        cout<<endl;
    }


};
#endif //INC_4_MINHEAP_H
