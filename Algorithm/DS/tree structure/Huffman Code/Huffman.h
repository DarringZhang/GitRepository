//
// Created by Darring on 2018/11/8.
//

#ifndef HUFFMAN_HUFFMAN_H
#define HUFFMAN_HUFFMAN_H
/*哈夫曼又称最优二叉树。是一种带权路径长度最短的二叉树
 * 利用字符出现频率代表权值，出现频率较高的源符号采用较短的编码，出现频率较低的符号采用较长的编码
 *无损压缩数据
 *利用小顶堆，取出堆中最小的两个元素，组成新的结点
 *
 * */

#define MAX 10000
#include "MinHeap.h"
#include <queue>


class Huffman {
private:
    huffman_node *root;
    MinHeap Heap;//堆中存放哈夫曼树结点的内容（权值和叶子字母）

public:

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
        //遍历一遍哈夫曼树，将哈夫曼编码 按从短到长，打印出来
        order_for_coding(root);

        huffman_node* p;
        queue<huffman_node*> q;
        q.push(root);
        while(!q.empty()){
            p = q.front();//拿出队列q 中第一个元素
            q.pop();
            if(p==NULL){
                continue;
            }
            q.push(p->left);
            q.push(p->right);
            if(isLeaf(p)){
                cout<<p->c<<" "<<p->code<<endl;
            }
        }
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






#endif //HUFFMAN_HUFFMAN_H
