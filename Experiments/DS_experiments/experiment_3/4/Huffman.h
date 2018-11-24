//
// Created by Darring on 2018/11/21.
//

#ifndef INC_4_HUFFMAN_H
#define INC_4_HUFFMAN_H

#include "MinHeap.h"

class Huffman {
public:
    huffman_node *root;
    MinHeap Heap ;//堆中存放哈夫曼树结点的内容（权值和叶子字母）
    string AllTheCodes = "";

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
            newNode->weight = node1->weight + node2->weight;//node1总比node2小，即符合哈夫曼权值小为左结点的规则，反之
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
        //遍历一遍哈夫曼树，将每个节点编码
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

    void Huffman_Decoding(string s){//传进来一串编码
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


#endif //INC_4_HUFFMAN_H
