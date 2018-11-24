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
    char c;    //������
    float weight; //�ڵ��Ȩֵ
    string code = "" ;
    huffman_node *left;
    huffman_node *right;
    int position ;
};



//1.����ָ�뵫��û�з���ռ� int *p//����û��ָ��̶���������int *p = new int;pָ��new�����Ŀռ�

/*��int *A = new int[Max]//A��һ�����飬������Max��int �͵����ݣ�Ҫdelete[] A
�� int A[Max]��//������Aʵ��Ϊһ��ָ�룬�Զ�new,�Զ�delete//����Ҫ��ʽdelete*/

//huffman_node **Print = new huffman_node*[MAX];//ȫ�ֱ������洢������Ϣ��main�а�����˳���ӡ
//Print��һ������,������Max��huffman_node*���͵�����,�Ѿ�new ����Max���ռ�

//����huffman_node* A = new huffman_node[MAX];
//huffman_node* A[MAX];//����һ����A�����飬�����ŵ�������huffman_node*����û��Ϊ��ЩMax��ָ��new�ռ�
//����huffman_node* Print[MAX];



//����С���ѣ�ÿ����������Ź������Ľ�㣬���ݽ��Ȩֵ��С����
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
        int size;
        char cc;
        //char maohao;
        cout<<"������Ҫ�������ĸ������";
        cin>>size;
        effective = size;
        number_of_leaves = effective;
        cout<<"������ĸ��Ȩֵ"<<endl;
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
