//
// Created by Darring on 2018/11/18.
//

//AVL在二叉查找树的基础上添加了旋转算法，但是旋转操作仅仅改变少数指针的指向，耗费常数时间，复杂度只与n有关
//对比BST，时间上稳定了很多,BST 输入点的顺序不同 ，树的结构不同（出现 一边倒的树），复杂度与树高有关

/*AVL树(高度平衡树)：是个BST，且满足，对于任何1个树中的节点x，其左树度和右树度的差不超过1.
每次插新节点后，递归地通过“旋转rotation”来调整各个节点，使其满足AVL树的基本要求

	违反AVL树的要求有四种情况：
1) 往某个节点左儿子的左子树中插节点
2) 往某个节点左儿子的右子树中插节点
3) 往某个节点右儿子的左子树中插节点
4) 往某个节点右儿子的右子树中插节点
     （总结起来也就两种情况，左左 and 左右，其他镜像对称）
*/



#ifndef INC_3_AVL_H
#define INC_3_AVL_H
#include "BST.h"
//除了 插入 和 删除，其他继承BST
class AVL :public BST {
public:
    AVL(){
    }
    ~AVL() {
        destroy(root);
    }

    Node *Create_Node(int v){
        Node *t = new Node;
        t->key = v ;
        t->left = NULL;
        t->right = NULL;
        t->height = 1;
        return t;
    }

    void Create_AVL(int n){
        int value;
        cout<<"please input the keys:";
        for(int i=0; i<n; ++i){
            cin>>value;
            this->AVL_Insert(root,value);
        }
    }


    int Tree_Height(Node *p){//返回树的高度
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


    /********************************************旋转****************************************/
    //某个结点的左儿子的左子树中插入一个结点，以这个结点的左儿子为轴，顺时针 旋转
    Node* Left_Left_Rotation(Node *p){
        Node* k1 = p->left;//k1为轴，p折下来
        p->left = k1->right;//k1原来右边的东西给p 的左边（k1原来的位置），k1右边就空出来的
        if(k1->right){
            k1->right->parent = p;
        }

        k1->right = p;      //k1右边就接 p
        p->parent = k1;
        p->height = MAX(Tree_Height(p->left),Tree_Height(p->right)) + 1;
        k1->height = MAX(Tree_Height(k1->left), p->height) + 1;//更新p 和 k1的高度

        return k1; //返回新根
    }

    //某个结点的右儿子的右子树中插入一个结点，以这个结点的右儿子为轴，逆时针 旋转
    Node* Right_Right_Rotation(Node *p){
        Node* k1 = p->right;
        p->right = k1->left;
        if(k1->left){
            k1->left->parent = p;
        }

        k1->left = p;
        p->parent = k1;
        p->height = MAX(Tree_Height(p->right),Tree_Height(p->left)) + 1;
        k1->height = MAX(Tree_Height(k1->right), p->height) + 1;

        return k1;
    }


    //往某个结点左儿子的右树中插结点(LR)以该结点左儿子的右子树为轴，逆时针旋转;折线变成直线，再以该结点的新左儿子（即插入的点，即刚刚转上来的点）为轴，顺时针旋转;
    Node* Left_Right_Rotation(Node *p){
        p->left = Right_Right_Rotation(p->left);
        return Left_Left_Rotation(p);
    }

    //往某个结点右儿子的左树中插结点(RL)
    Node* Right_Left_Rotation(Node *p){
        p->right = Left_Left_Rotation(p->right);
        return Right_Right_Rotation(p);
    }
/********************************************旋转*******************************************/


/*************************************************递归插入******************************************/
    Node *AVL_Insert(Node * T,int v){
        if(T==NULL){
            T = Create_Node(v);
        }
        else if(v < T->key){
            T->left = AVL_Insert(T->left, v);//为 v的插入位置寻找新结点
            T->left->parent = T;
            if(Tree_Height(T->left) - Tree_Height(T->right) == 2){//左边插入后 重了
                if(T->left!=NULL){
                    if(v < T->left->key){     //插入到左边了，左左式不平衡
                        T = Left_Left_Rotation(T);
                    }

                    else{    //左右式不平衡
                        T = Left_Right_Rotation(T);
                    }
                }
            }
        }
        else if(v > T->key){
            T->right = AVL_Insert(T->right, v);//为 v的插入位置寻找新结点
            T->right->parent = T;
            if(Tree_Height(T->right) - Tree_Height(T->left) == 2){//右边插入后 重了
                if(T->right!=NULL){
                    if(v < T->right->key){ //右左式不平衡
                        T = Right_Left_Rotation(T);
                    }
                    else{   // 右右式不平衡
                        T = Right_Right_Rotation(T);
                    }
                }


            }
        }
        else{
            //v == Root->key, insert failed->
            cout<<"Already have this element!"<<endl;
        }

        T->height = MAX(Tree_Height(T->left), Tree_Height(T->right)) + 1;
        this->root = T;
        root->parent = NULL;
        return T;
    }
/*************************************************递归插入******************************************/


/*************************************************非递归插入******************************************/
    void AVL_Insert_Nonrecur(Node * T,int v){
        Node *NewNode = Create_Node(v);
        Node *t = NULL;
        Node *x = T;
        while(x!=NULL){//为插入结点寻找合适父亲t
            t = x;
            if(NewNode->key < x->key){
                x =  x->left;
            }
            else if(NewNode->key > x->key){
                x = x->right;
            }
            else{
                //v == Root->key, insert failed->
                cout<<"Already have this element!"<<endl;
            }
        }

        NewNode->parent = t;
        if(t==NULL){
            root = NewNode;
            return ;
        }
        else if(NewNode->key<t->key){
            t->left = NewNode;
        }
        else{
            t->right = NewNode;
        }
        AVL_Insert_Fixup(NewNode->parent);
    }


    void AVL_Insert_Fixup(Node *T){
        T->height = MAX(Tree_Height(T->left), Tree_Height(T->right)) + 1;//插入结点，更新树高
        Node *y = T;
        while(T->parent!=NULL){
            y = T->parent;
            int old_height = MAX(Tree_Height(y->left), Tree_Height(y->right)) + 1;//插入新结点，祖父高度更新
            Node *t = AVL_Delete_Fixup(y);//修正不平衡的祖父y,修正后新根为t
            t->height = MAX(Tree_Height(t->left), Tree_Height(t->right)) + 1;
            if(t!=y){//确实需要修正
                if(t->parent == NULL){
                    root = t;
                }
                else if(y == t->parent->left){//调整新树根与外界的联系
                    t->parent->left = t;
                }

                else if(y == t->parent->right){
                    t->parent->right = t;
                }

            }
            if(t->height < old_height){//新树根高度修正好了，没有出现不平衡
                break;
            }

            T = t;//往上遍历
        }

    }
/*************************************************非递归插入******************************************/




/********************************删除******************************************/
//AVL的树的删除策略与二叉查找树的删除策略相似，只是删除节点后造成树失去平衡性，需要做平衡处理。




    Node *AVL_Delete_Fixup(Node *p){//修正不平衡的树
        if(Tree_Height(p->left) - Tree_Height(p->right) == 2){//左树重
            if(Tree_Height(p->left->left) >= Tree_Height(p->left->right)){//左左型
                p = Left_Left_Rotation(p);
            }

            else{//左右型
                p = Left_Right_Rotation(p);
            }
        }

        else if(Tree_Height(p->right) - Tree_Height(p->left) == 2) {//右树重
            if(Tree_Height(p->right->left) >= Tree_Height(p->right->right)){// 右左型
                p = Right_Left_Rotation(p);
            }

            else{//右右型
                p = Right_Right_Rotation(p);
            }
        }
        this->root = p;
        root->parent = NULL;
        return p;

    }


    void *AVL_Delete(Node *p,int v){
        if(p == NULL){//空树报错
            cout<<"delete failed!"<<endl;
        }
        if(v< p->key){//在左子树中查找
            AVL_Delete(p->left,v);
            AVL_Delete_Fixup(p);
        }
        else if(v>p->key){
            AVL_Delete(p->right,v);
            AVL_Delete_Fixup(p);
        }
        else{//找到要删除的元素
            if(p->left==NULL){ //左子树为空
                Node* t = p;
                if(p==p->parent->left){
                    p->parent->left = NULL;
                }
                else if(p==p->parent->right){
                    p->parent->right = NULL;
                }
                p = p->right;         //用右孩子代替此节点
                delete t;            //释放内存
                t = NULL;
            }
            else if(p->right==NULL){  //右子树为空
                Node* t = p;
                if(p==p->parent->left){//不置空，就会随机指向，导致p->parent->left 永远 不为空，所以要置空
                    p->parent->left = NULL;
                }
                else if(p==p->parent->right){
                    p->parent->right = NULL;
                }
                p = p->left;       //用左孩子代替此节点
                delete t;
                t = NULL;
            }
            else {  //左右子树都不为空
                //一般的删除策略是左子树的最大数据 或 右子树的最小数据 代替该节点, 才符合BST的大小顺序
                Node * t = this->BST_Maximum(p->left);
                p->key = t->key;
                AVL_Delete(p->left,t->key);//递归地删除该结点
            }

        }
        //更新节点的高度
        if(p){
            p->height = MAX(Tree_Height(p->left), Tree_Height(p->right)) + 1;
        }


    }
    /********************************删除******************************************/



};
#endif //INC_3_AVL_H
