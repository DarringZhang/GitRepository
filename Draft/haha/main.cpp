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

huffman_node** Print = new huffman_node*[MAX];
//huffman_node* A = new huffman_node[MAX];
huffman_node* A[MAX];
//huffman_node* Print[MAX];
//广义小顶堆（每个数组里面放哈夫曼的结点，根据结点权值大小排序）    （BinaryHeap 里面是只存数字大顶堆）
class MinHeap {

public:

    int effective = 0;
    int number_of_leaves;
    MinHeap(){};
    ~MinHeap(){

    };


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
        //char cc;
        char maohao;
        cout<<"输入你要的编码的字母个数：";
        cin>>size;
        effective = size;
        number_of_leaves = effective;
        cout<<"输入字母和其权值："<<endl;
        for(int i = 1; i <= size; i ++){
            A[i] = new huffman_node;
           //cin>>A[i]->c;
         //   cin>>A[i]->weight;
          // scanf(" %c%c%f", &A[i]->c,&cc, &A[i]->weight);//平台上%c的前面没有空格
            cin>>A[i]->c>>maohao>>A[i]->weight;
           // fflush(stdin);

            A[i]->right = NULL;
            A[i]->left = NULL;
            A[i]->position = i;
        }
        memcpy(Print,A,MAX);//用两者size中较小的作复制的规模
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
//////////////////////////////////////////////////////////////
class Huffman {
public:
    huffman_node *root;
    MinHeap Heap;//堆中存放哈夫曼树结点的内容（权值和叶子字母）



    Huffman(){};
    ~Huffman(){
        destroy(root);
    }


    void create_huffman_tree(){//构建哈夫曼树
        Heap.create_huffman_node();//构建哈夫曼结点
        Heap.Build_Min_Heap();     //构建最小堆
        cout<<"建堆完成：";
        Heap.print();
        while(Heap.effective>1){
            huffman_node *node1 = Heap.Heap_Extract_Min();//连续拿出堆中最小两个元素
            huffman_node *node2 = Heap.Heap_Extract_Min();
            huffman_node * newNode = new huffman_node;
            newNode->weight = node1->weight+node2->weight;//node1总比node2小，即符合哈夫曼权值小为左结点的规则，反之
            newNode->c = '*';
            newNode->left = node1;
            newNode->right = node2;
            Heap.Min_Heap_Insert(newNode);
            root = newNode;
        }
    }

    //前中后序遍历哈夫曼树，只打印内容
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

    //(前序)遍历过程中编码
    void order_for_coding(huffman_node *t) {
        if(!t){
            return;
        }

        coding(t);
        order_for_coding(t->left);
        order_for_coding(t->right);
    }



    //实现哈夫曼编码：路径越长，编码越长，采用层次遍历（queue），按照编码长短的顺序 打印叶子节点的code
    void Huffman_code(){
        if(root==NULL){
            cout<<"树空！"<<endl;
            return;
        }
        //遍历一遍哈夫曼树，将哈夫曼编码
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

    void destroy(huffman_node *t){          //销毁哈夫曼
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
    cout<<"前序打印哈夫曼树:";
    huff.preOrder(huff.GetRoot());
    cout<<"层序打印哈夫曼编码:"<<endl;
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