#define MAX 10000
#include <string>
#include <queue>
#include <iostream>
#include <stdio.h>
using namespace std;
struct huffman_node{
    char c;
    float weight;
    string code ;
    huffman_node *left;
    huffman_node *right;
    int position ;
};

huffman_node** Print = new huffman_node*[MAX];

huffman_node* A[MAX];

class MinHeap {

public:

    int effective;
    int number_of_leaves;
    MinHeap(){};
    ~MinHeap(){

    };



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
        char cc[MAX];
        cin>>size;
        effective = size;
        number_of_leaves = effective;

        for(int i = 1; i <= size; i ++){
            A[i] = new huffman_node;

            scanf(" %c%c%f", &A[i]->c, &cc[i], &A[i]->weight);
            getchar();
            A[i]->right = NULL;
            A[i]->left = NULL;
            A[i]->position = i;
        }
        memcpy(Print,A,MAX);
    }



    int Heap_Minmum(){
        return A[effective]->weight;
    }


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

        if(small!=i){
            huffman_node* t = A[i];
            A[i] = A[small];
            A[small] = t;
            Min_Heapify(small);
        }
    }


    void Build_Min_Heap(){
        int length = effective/2;
        for(int i = length;i >= 1;i--){
            Min_Heapify(i);
        }
    }




    huffman_node* Heap_Extract_Min(){

        huffman_node* min  = A[MAX];
        if(effective<1){
            cout<<"underflow!"<<endl;
            return min;
        }

        min  = A[1];
        A[1] = A[effective];
        effective--;
        Min_Heapify(1);
        return min;
    }



    void Min_Heap_Insert(huffman_node *node ){
        effective ++;

        A[effective] = node;

        int i = effective;
        while(i>1 && A[PARENT(i)]->weight>A[i]->weight){
            huffman_node* t = A[i];
            A[i] = A[PARENT(i)];
            A[PARENT(i)] = t;
            i = PARENT(i);
        }

    }



    void HeapSort(){
        int length = effective;
        Build_Min_Heap();
        cout<<"build heap finished ";
        this->print();
        for(int i = effective; i >= 2; i --){
            huffman_node* t = A[1];
            A[1] = A[i];
            A[i] = t;
            effective--;
            Min_Heapify(1);
        }
        effective = length;
    }


    void print(){
        for(int i = 1;i<=effective;i++){
            cout<<A[i]->c<<"-"<<A[i]->weight<<" ";
        }
        cout<<endl;
    }


};

class Huffman {
public:
    huffman_node *root;
    MinHeap Heap;



    Huffman(){};
    ~Huffman(){
        destroy(root);
    }


    void create_huffman_tree(){
        Heap.create_huffman_node();
        Heap.Build_Min_Heap();


        while(Heap.effective>1){
            huffman_node *node1 = Heap.Heap_Extract_Min();
            huffman_node *node2 = Heap.Heap_Extract_Min();
            huffman_node * newNode = new huffman_node;
            newNode->weight = node1->weight+node2->weight;
            newNode->c = '*';
            newNode->left = node1;
            newNode->right = node2;
            Heap.Min_Heap_Insert(newNode);
            root = newNode;
        }
    }


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


    void order_for_coding(huffman_node *t) {
        if(!t){
            return;
        }

        coding(t);
        order_for_coding(t->left);
        order_for_coding(t->right);
    }




    void Huffman_code(){
        if(root==NULL){
            cout<<"树空！"<<endl;
            return;
        }

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

    void destroy(huffman_node *t){
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