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

huffman_node** Print = new huffman_node*[MAX];
//huffman_node* A = new huffman_node[MAX];
huffman_node* A[MAX];
//huffman_node* Print[MAX];
//����С���ѣ�ÿ����������Ź������Ľ�㣬���ݽ��Ȩֵ��С����    ��BinaryHeap ������ֻ�����ִ󶥶ѣ�
class MinHeap {

public:

    int effective = 0;
    int number_of_leaves;
    MinHeap(){};
    ~MinHeap(){

    };


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
        //char cc;
        char maohao;
        cout<<"������Ҫ�ı������ĸ������";
        cin>>size;
        effective = size;
        number_of_leaves = effective;
        cout<<"������ĸ����Ȩֵ��"<<endl;
        for(int i = 1; i <= size; i ++){
            A[i] = new huffman_node;
           //cin>>A[i]->c;
         //   cin>>A[i]->weight;
          // scanf(" %c%c%f", &A[i]->c,&cc, &A[i]->weight);//ƽ̨��%c��ǰ��û�пո�
            cin>>A[i]->c>>maohao>>A[i]->weight;
           // fflush(stdin);

            A[i]->right = NULL;
            A[i]->left = NULL;
            A[i]->position = i;
        }
        memcpy(Print,A,MAX);//������size�н�С�������ƵĹ�ģ
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
//////////////////////////////////////////////////////////////
class Huffman {
public:
    huffman_node *root;
    MinHeap Heap;//���д�Ź��������������ݣ�Ȩֵ��Ҷ����ĸ��



    Huffman(){};
    ~Huffman(){
        destroy(root);
    }


    void create_huffman_tree(){//������������
        Heap.create_huffman_node();//�������������
        Heap.Build_Min_Heap();     //������С��
        cout<<"������ɣ�";
        Heap.print();
        while(Heap.effective>1){
            huffman_node *node1 = Heap.Heap_Extract_Min();//�����ó�������С����Ԫ��
            huffman_node *node2 = Heap.Heap_Extract_Min();
            huffman_node * newNode = new huffman_node;
            newNode->weight = node1->weight+node2->weight;//node1�ܱ�node2С�������Ϲ�����ȨֵСΪ����Ĺ��򣬷�֮
            newNode->c = '*';
            newNode->left = node1;
            newNode->right = node2;
            Heap.Min_Heap_Insert(newNode);
            root = newNode;
        }
    }

    //ǰ�к����������������ֻ��ӡ����
    void preOrder(huffman_node *t) {
        if(!t){
            return;
        }

        print(t);
        preOrder(t->left);
        preOrder(t->right);
    }

    void inOrder(huffman_node *t){
        if(!t){
            return;
        }

        inOrder(t->left);
        print(t);
        inOrder(t->right);
    }

    void postOrder(huffman_node *t){
        if(!t){
            return;
        }

        postOrder(t->left);
        postOrder(t->right);
        print(t);
    }

    //(ǰ��)���������б���
    void order_for_coding(huffman_node *t) {
        if(!t){
            return;
        }

        coding(t);
        order_for_coding(t->left);
        order_for_coding(t->right);
    }



    //ʵ�ֹ��������룺·��Խ��������Խ�������ò�α�����queue�������ձ��볤�̵�˳�� ��ӡҶ�ӽڵ��code
    void Huffman_code(){
        if(root==NULL){
            cout<<"���գ�"<<endl;
            return;
        }
        //����һ�����������������������
        order_for_coding(root);



    }



    bool isLeaf(huffman_node*t){
        if(t->c=='*'){
            return false;
        }
        return true;
    }

    void coding(huffman_node *t){
        if(!isLeaf(t)){
            if(t->left!=NULL){
                t->left->code = t->code+"0";
            }
            if(t->right!=NULL){
                t->right->code = t->code +"1";
            }
        }

    }

    void destroy(huffman_node *t){          //���ٹ�����
        if(t){
            destroy(t->left);
            destroy(t->right);
            delete t;
            t = NULL;
        }

    }

    void print(huffman_node *t){
        cout<<t->c<<"-"<<t->weight<<" ";
    }


    huffman_node * GetRoot(){
        return root;
    }



};




int main() {

    Huffman huff;
    huff.create_huffman_tree();
    cout<<"ǰ���ӡ��������:";
    huff.preOrder(huff.GetRoot());
    cout<<"�����ӡ����������:"<<endl;
    huff.Huffman_code();
    for(int i = 1;i <= huff.Heap.number_of_leaves; i++){
        cout<<Print[i]->c<<":"<<Print[i]->code<<endl;
    }
    cout<<endl;

    for(int i = 0;i<huff.Heap.number_of_leaves;i++){
        delete  A[i];
    }

    delete []Print;
    return 0;
}