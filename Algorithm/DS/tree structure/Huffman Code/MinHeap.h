//
// Created by Darring on 2018/11/8.
//

#ifndef HUFFMAN_MINHEAP_H
#define HUFFMAN_MINHEAP_H
#define MAX 10000
#include <string>
using namespace std;
struct huffman_node{
    char c;    //结点代号
    int weight; //节点的权值
    string code = "" ;
    huffman_node *left;
    huffman_node *right;
};



//广义小顶堆（每个数组里面放哈夫曼的结点，根据结点权值大小排序）    （BinaryHeap 里面是只存数字大顶堆）
class MinHeap {

public:
    huffman_node* A[MAX];
    int effective = 0;

    MinHeap(){};
    ~MinHeap(){};


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
        cout<<"输入你要的编码的字母个数：";
        int size;
        cin>>size;
        effective = size;
        cout<<"输入字母和其权值："<<endl;
        for(int i = 1; i <= size; i ++){
            A[i] = new huffman_node;
            cin>>A[i]->c;
            cin>>A[i]->weight;
            A[i]->right = NULL;
            A[i]->left = NULL;
        }
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


    //最大堆插入O(h)
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


    void print(){
        for(int i = 1;i<=effective;i++){
            cout<<A[i]->c<<"-"<<A[i]->weight<<" ";
        }
        cout<<endl;
    }



};


#endif //HUFFMAN_MINHEAP_H
