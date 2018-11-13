//
// Created by Darring on 2018/11/8.
//

#ifndef HUFFMAN_MINHEAP_H
#define HUFFMAN_MINHEAP_H
#define MAX 10000
#include <string>
using namespace std;
struct huffman_node{
    char c;    //������
    int weight; //�ڵ��Ȩֵ
    string code = "" ;
    huffman_node *left;
    huffman_node *right;
};



//����С���ѣ�ÿ����������Ź������Ľ�㣬���ݽ��Ȩֵ��С����    ��BinaryHeap ������ֻ�����ִ󶥶ѣ�
class MinHeap {

public:
    huffman_node* A[MAX];
    int effective = 0;

    MinHeap(){};
    ~MinHeap(){};


    //��λ���������Ӷ�O(1)
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
        cout<<"������Ҫ�ı������ĸ������";
        int size;
        cin>>size;
        effective = size;
        cout<<"������ĸ����Ȩֵ��"<<endl;
        for(int i = 1; i <= size; i ++){
            A[i] = new huffman_node;
            cin>>A[i]->c;
            cin>>A[i]->weight;
            A[i]->right = NULL;
            A[i]->left = NULL;
        }
    }


    //�Ҷ�����СԪ��
    int Heap_Minmum(){
        return A[effective]->weight;
    }


    //�ѻ���������һ����ȫ������(array)�����С�ѣ��ú�������Left(i) �� Right(i)������С�ѣ�Ȼ�����A[i]��ʹ��������A�ĵ�i���ڵ�Ϊ�Ѷ��Ķ���?����С��.
    //���Ӷ�O(logn) = O(h)
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

        if(small!=i){//���ӱȸ���С����Ҫ��������С�������ϵ���
            huffman_node* t = A[i];
            A[i] = A[small];
            A[small] = t;
            Min_Heapify(small);//�ݹ����� ����
        }
    }

    //���ѣ��Ե����Ͻ��������Ϊһ����С��,�ӵ�һ����Ҷ�ӽ�㿪ʼ�����������ӵĹ�ϵ
    //���Ӷ�O��h��
    void Build_Min_Heap(){
        int length = effective/2;
        for(int i = length;i >= 1;i--){  //1-based
            Min_Heapify(i);
        }
    }



    //�ó����������СԪ��O(h)
    huffman_node* Heap_Extract_Min(){

        huffman_node* min  = A[MAX];
        if(effective<1){
            cout<<"underflow!"<<endl;//������λ
            return min;
        }

        min  = A[1];
        A[1] = A[effective];
        effective--;
        Min_Heapify(1);
        return min;
    }


    //���Ѳ���O(h)
    void Min_Heap_Insert(huffman_node *node ){
        effective ++;

        A[effective] = node;

        int i = effective;
        while(i>1 && A[PARENT(i)]->weight>A[i]->weight){//�²���ıȸ�ȨֵС
            huffman_node* t = A[i];
            A[i] = A[PARENT(i)];
            A[PARENT(i)] = t;
            i = PARENT(i);//��λ
        }

    }


    //Ӧ��֮ �����򣨽������е�Ԫ�ش�С�������У���ͬʱ���߽����ѵĶ������ṹ
    void HeapSort(){
        int length = effective;
        Build_Min_Heap();//������һ�������
        cout<<"build heap finished ";
        this->print();
        for(int i = effective; i >= 2; i --){
            huffman_node* t = A[1];
            A[1] = A[i];
            A[i] = t;
            effective--;
            Min_Heapify(1);
        }
        effective = length;//��ԭ��Ч���ȣ����ڴ�ӡ
    }


    void print(){
        for(int i = 1;i<=effective;i++){
            cout<<A[i]->c<<"-"<<A[i]->weight<<" ";
        }
        cout<<endl;
    }



};


#endif //HUFFMAN_MINHEAP_H
