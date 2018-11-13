//
// Created by Darring on 2018/11/8.
//

#ifndef HUFFMAN_HUFFMAN_H
#define HUFFMAN_HUFFMAN_H
/*�������ֳ����Ŷ���������һ�ִ�Ȩ·��������̵Ķ�����
 * �����ַ�����Ƶ�ʴ���Ȩֵ������Ƶ�ʽϸߵ�Դ���Ų��ý϶̵ı��룬����Ƶ�ʽϵ͵ķ��Ų��ýϳ��ı���
 *����ѹ������
 *����С���ѣ�ȡ��������С������Ԫ�أ�����µĽ��
 *
 * */

#define MAX 10000
#include "MinHeap.h"
#include <queue>


class Huffman {
private:
    huffman_node *root;
    MinHeap Heap;//���д�Ź��������������ݣ�Ȩֵ��Ҷ����ĸ��

public:

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
        //����һ����������������������� ���Ӷ̵�������ӡ����
        order_for_coding(root);

        huffman_node* p;
        queue<huffman_node*> q;
        q.push(root);
        while(!q.empty()){
            p = q.front();//�ó�����q �е�һ��Ԫ��
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






#endif //HUFFMAN_HUFFMAN_H
