//
// Created by Darring on 2018/11/18.
//

#ifndef INC_3_BST_H
#define INC_3_BST_H

/*ǰ��� �������������������������� ��ֻ�ǽ��������ˣ�������һ�飬��û�� ����
�ʽ��� ��, �ܲ������������ջ�Ƚṹ����/ɾ/��/�� ĳ����?


BST
1) T �Ƕ�����,
2) �����н�㣬��������������������С���� (����һ���Ĵ洢˳��)�����Խ��в�����
3���� ���� ���պ��Ǵ�С���� ����
*/

#include<iostream>
#include<queue>
using namespace std;

struct Node
{
    int key;
    Node* left;
    Node* right;
    Node* parent;
    int height = 0;//��¼���ĸ߶�
};

class BST{
public:
    Node *root = NULL;


    BST(){
    }
    ~BST(){
        destroy(root);
    }


    //����������BST
    void Create_BST( int n){
        int value;
        cout<<"please input the keys:";
        for(int i=0; i<n; ++i){
            cin>>value;
            BST_Insert(root,value);

        }
    }



    int Tree_Height(Node *p){//�������ĸ߶�
        if (p == NULL){
            return 0;
        }

        return p->height;
    }

    int MAX(int a,int b){
        if(a<b){
            return b;
        }
        return a;
    }


    //������½��һ����ĳ��Ҷ��㣬��Ϊһ�ֶ�̬�ṹ���Ȳ�����ֵ���ظ����ٲ���
//�ݹ����
    Node* BST_Insert(Node*T, int k){
        if(T == NULL)
        {
            T = new Node;
            T->key = k;
            T->left = NULL;
            T->right = NULL;
            T->height = 1;
        }
        else if(k == T->key){
            cout<<"insert failed!"<<endl;
            return 0;  // ���д�����ͬ�ؼ���
        }

        else if(k < T->key){
            T->left  = BST_Insert(T->left, k);
            T->left->parent = T;
        }
        else{
            T->right  = BST_Insert(T->right, k);
            T->right->parent = T;
        }

        T->height = MAX(Tree_Height(T->left), Tree_Height(T->right)) + 1;
        this->root = T;
        root->parent = NULL;
        return T;
    }

//�ǵݹ���루Ч�ʸߣ�
    int BST_Insert_NonRecur(Node *T,int k){
        Node* pre = NULL;  // ��¼��һ�����
        Node* t = T;
        //�ƶ�������λ��
        while(t != NULL)
        {
            pre = t;
            if(k < t->key)
                t = t->left;
            else if(k > t->key)
                t = t->right;
            else
                return 0;

        }

        Node* node = new Node;
        node->key = k;
        node->left = NULL;
        node->right = NULL;
        node->parent = pre;
        node->height = 1;

        if(pre == NULL){
            root = node; //��������Ǹ��ڵ�
            return 1;
        }

        else
        {
            if(k < pre->key){//�жϲ���߻����ұ�
                pre->left = node;
            }

            else{
                pre->right = node;
            }
        }

//        //��������
//        t = node;
//        while(t->parent!=NULL){
//            if(t->height+1 == t->parent->height){//���ø���
//                break;
//            }
//            else if(t->height+1 > t->parent->height){ //t֮ǰ��Ҷ�ڵ�
//                t ->parent->height++;
//                t = t->parent;
//            }
//        }


        return 1;
    }


//BST Search
/*
	Search sth�����⣬�������������֧���� Minimum����Сֵ����Maximum�����ֵ����
	Predecessor��ǰ������Successor����̣��Ȳ�ѯ�����ڸ߶�Ϊ h ��������Щ������������ ��(h) ʱ������ɡ�
*/


    //�ݹ� search ĳ��ֵ
    Node* BST_Search(Node* T, int k)
    {
        if(T==NULL){
            return NULL;
        }
        else if(k == T->key){
            return T;
        }
        if(k < T->key)
            return BST_Search(T->left, k);
        else
            return BST_Search(T->right, k);
    }
//�ǵݹ� search ĳ��ֵ
    Node* BST_Search_NonRecur(Node* T, int k)
    {
        while(T != NULL&& k!=T->key)
        {
            if(k < T->key){
                T = T->left;
            }

            else if(k>T->key){
                T = T->right;
            }
        }
        return T;


    }

/**
 * ��Сֵ�����Ҷ���������йؼ�����С�Ľ��
 */
    Node* BST_Minimum(Node* T)
    {
        while(T->left != NULL)
            T = T->left;
        return T;
    }

/**
 * ���ֵ�����Ҷ���������йؼ������Ľ��
 */
    Node* BST_Maximum(Node* T)
    {
        while(T->right != NULL)
            T = T->right;
        return T;
    }


/**
 * ��̣����Ҹ����������������еĺ�̽��
 */
    Node* BST_Successor(int k)
    {
        Node *node = BST_Search_NonRecur(root, k);
        if(node->right != NULL){//node ����������Ϊ�գ��� node �ĺ�̾��������������������µĵ㣨���ؼ���ֵ��С�Ľ�㣩��
            return BST_Minimum(node->right);
        }

        //�ҽڵ�Ϊ��
        Node* p = node->parent;
        while(p!=NULL && p->right == node)//ֻҪ��û�����ڵ㣬����node ����p ���Ҷ��ӣ������ң�˵�����ĸ����Ѿ������ʣ���Ҫ˳��
        {                                 // ֱ�����p ���Ҷ���
            node = p;
            p = p->parent;
        }
        return p;
    }

/**
 * ǰ�������Ҹ����������������е�ǰ�����
 */
    Node* BST_Predecessor(int k)//���Һ�̾���Գ�
    {
        Node *node = BST_Search_NonRecur(root, k);
        if(node->left != NULL){
            return BST_Maximum(node->left);
        }

        Node* p = node->parent;
        while(p!=NULL && p->left == node)
        {
            node = p;
            p = p->parent;
        }
        return p;
    }

/*
�����������ɾ����������Ը���һ�㣬��Ҫ�� 3 �����������ɾ��(Deletion):��T��ɾ���ڵ�z,�������
1) zû�к���, �򵥽��丸�ڵ��ָ�� z��ָ���滻ΪNIL;
2) zֻ��1������ ��z�������������Ϊz�ĸ��׵ĺ���,ȡ��z��λ��;
3) z�������� ����z��������y(��Ȼ��z��������), yȡ��z��λ��, z��������ʣ�µĲ��ֳ�Ϊy����������,z����
   �����y��������. (����������Ƚϸ��ӣ�ȡ����y�ǲ���z���Һ�)
*/

    //����1��������Ժϲ���2 ����Ϊ������NULLȡ��z ��λ�ã�



    //����
    void Transplant(Node *T, Node *u,Node *v){ //��T�У���vΪ���������滻��uΪ����������
        if(u->parent==NULL){ // u ��Ϊ �� T , v �滻����
            //T = v;
            root = v;// ������� T ��Ȼ����������root���� T�Ǿֲ��������������������ʧ������ �øĸø��ڵ�
        }
        else if(u = u->parent->left){//u�� �����
            u->parent->left = v;//v�滻�����
        }
        else{
            u->parent->right = v;
        }
        if(v!=NULL){
            v->parent = u->parent; //��������ÿ���������v�ĸ��׽��Ҫ������
        }
    }

    void Delete(int k){
        Node *z = BST_Search_NonRecur(root,k);
        //���ΪҶ�ӽڵ�
        if(z->left==NULL&&z->right==NULL){
            if(z==z->parent->left){
                z->parent->left = NULL;
            }
            else if(z==z->parent->right){
                z->parent->right = NULL;
            }
        }
            //������Ϊ��
        else if(z->left==NULL){
            Transplant(root,z,z->right);//���û�������Ҷ�ӽڵ���жϣ����� Transplant �Ƿ����ʣ��ͻ���ֶδ���
        }
            //������Ϊ��
        else if(z->right==NULL){
            Transplant(root,z,z->left);
        }
        else{//z���Ҷ���Ϊ��
            Node *y = BST_Minimum(z->right);//�ó��ұ���С������������ ��ת���ɵ�һ��if �����(Ҳ�������ұ����ģ��ڶ���if)
            if(y->parent!=z){//�����µĵ�� z��ֱ������ ��ֱ�������Ļ���y ��ΪҶ�ӣ�ֱ�ӽ���z �����z��
                Transplant(root,y,y->right);  //�������Ľ�� y �������
                y->right = z->right; // ��Ҫɾ�Ľ��z �ұ� ��z �Ͽ����ӵ��½����
                y->right->parent = y;//���׽��ָ��
            }//���������ɹ�
            Transplant(root,z,y);
            y->left = z->left;
            y->left->parent = y;
        }
    }


    void Modyfiy(int old,int newer){
        Node *oldnode = BST_Search_NonRecur(root, old);
        Node *newernode = BST_Search_NonRecur(root, newer);
        if(newernode==NULL){//˵��û��ԭ����û����֮�ظ��Ľ��
            //�޸�ĳ��ֵ��Ҫ��������������λ��, �� oldnode->key = newer�ĸ�ֵ  �в�ͨ;
            Delete(old);
            BST_Insert_NonRecur(root,newer);
        }
        else{
            cout<<"there is already has such newer keys,can��t repeate��"<<endl;
        }

    }

    /********************************************* ǰ����� ******************************************/
    void preOrder_No_Stack() {
        if(root == NULL) {
            return;
        }
        Node* cur = root; //������
        do{
            visit(cur) ;//�ȷ��ʵ�ǰ
            cur = preOrder_Successor(cur);//���Һ��
        }while(cur != NULL);
    }

    Node *preOrder_Successor(Node* p){
        //p����ж��ӣ����һ����ֱϵ����
        if(p->left){
            return  p->left;
        }
        else if(p->right){
            return p->right;
        }
        //p ΪҶ�ӽ�� ���Ϊ���׽����Ҷ��ӡ����Ҷ���Ϊ�� ���� p��Ϊ���׵��Ҷ��ӣ�Ϊ���������Ǹ�ת�۵���Ҷ���
        Node *y = p->parent;
        while(y->right==NULL||p == y->right){//��������ֱ��  ָ������->����
            p = y;
            y = y->parent;
            if(y==NULL){ //y������Ϊ���ڵ��ˣ������yҪôû����������Ҫôy�������Ǵ��ұ��������ģ�y�Ķ��� p�ĺ�̾���NULL
                return NULL;
            }
        }
        return y->right;
    }

/********************************************* ǰ����� ******************************************/

/********************************************* ������� ******************************************/
/* ����
	1) �ҵ������������µĽ��p;
	2) visit(p); p = inorder_successor(p);
	3) ����2),ֱ�� p û�к��(p == NULL).
*/
    void inOrder_No_Stack() {
        if(root == NULL) {
            return;
        }
        Node* cur = find_most_left_node(root); //�����ң��ȴ������µĽ��
        do{
            visit(cur) ;//���ȷ��������µĵ�
            cur = inOrder_Successor(cur);
        }while(cur != NULL);
        cout<<endl;
    }

    Node* find_most_left_node(Node *p){
        while(p->left != NULL){
            p = p->left;
        }
        return p;
    }

    Node* inOrder_Successor(Node *x){
        if(x->right != NULL){//���x���ҽ�㣬����������x���������������µĵ�
            return find_most_left_node(x->right);
        }

        //�������x�����Ƚ���е�ĳ����
        Node *p = x->parent;
        while(p != NULL && x == p->right){//������Ѱ��һֱ��x �������� ����p������� Ϊ����
            x = p;                         //��x ������ӣ���̾������ĸ��ס�
            p = p->parent;            		 //��x ���Ҷ��ӣ�������ָ�����Ѿ�����һ�����ʣ� ��Ҫ˳�����ϣ�ֱ������ ����->����
        }
        return p;
    }
    /********************************************* �������******************************************/

    void destroy(Node *T){//using BFS to realease all nodes;
        queue<Node*> L;
        Node *t = T;
        if(T!=NULL){
            L.push(T);
        }
        while(!L.empty()){
            t = L.front();//ȡ������Ԫ��
            L.pop();
            if(t==NULL){
                continue;
            }
            L.push(t->left);//������Ԫ�ص������������
            L.push(t->right);
            delete t;
            t = NULL;
        }
        //cout<<"free node finished!"<<endl;
        root = NULL;
    }



    void visit(Node *node){
        cout<<node->key<<"-��-"<<node->height<<" ";
    }

    Node *GetRoot(){
        return root;
    }
    void fixRoot(Node*t){
        root = t;
    }

};





#endif //INC_3_BST_H
