//
// Created by Darring on 2018/11/21.
//

#ifndef INC_4_HUFFMAN_H
#define INC_4_HUFFMAN_H

#include "MinHeap.h"

class Huffman {
public:
    huffman_node *root;
    MinHeap Heap ;//���д�Ź��������������ݣ�Ȩֵ��Ҷ����ĸ��
    string AllTheCodes = "";

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
            newNode->weight = node1->weight + node2->weight;//node1�ܱ�node2С�������Ϲ�����ȨֵСΪ����Ĺ��򣬷�֮
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
        //����һ�������������ÿ���ڵ����
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

    string find_code_for_letter(char c ){
        for(int i = 1; i <= Heap.number_of_leaves; i++){
            if(c == Heap.Print[i]->c){
                return Heap.Print[i]->code;
            }
        }
    }
    void Huffman_Encoding(string s){
        for(int i = 0; i < s.size(); i++){
            string t;
            t= find_code_for_letter(s[i]);

            cout << t;
            AllTheCodes += t;
        }
        cout<<endl;
    }



    char find_letter_for_code(string ss){
        for(int i = 1; i <= Heap.number_of_leaves; i++){
            if(ss == Heap.Print[i]->code){
                return Heap.Print[i]->c;
            }
        }
        return '#';
    }

    void Huffman_Decoding(string s){//������һ������
        string t = "";
        for(int i =0; i< s.size(); i++){
            t += s[i];
            char findChar = find_letter_for_code(t);
            if( findChar != '#'){
                cout << findChar <<" ";
                t = "";
            }
        }
        cout << endl;

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


#endif //INC_4_HUFFMAN_H
