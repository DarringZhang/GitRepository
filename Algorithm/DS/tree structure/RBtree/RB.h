//
// Created by DarringZhang on 2018/11/6.
//参考：https://github.com/hoohack/KeepCoding/tree/master/DataStructure/RBTree

using namespace std;
#ifndef RBTREE_RB_H
#define RBTREE_RB_H

//BST根据插入顺序的不同，可能会退化成链表
// BST 派生出来 AVL, RB ,其中，BST 效率远不如AVL RB，RB树 时间比 AVL 少个常数项

/*  红黑树（平衡二叉树）
		1.每个节点不是红色就是黑色；
		2.根节点是黑色；
		3.每个叶子节点是黑色；
		4.如果节点是红色，那么它的两个孩子节点都是黑色的；
		5.对每个节点来说，从节点到叶子节点的路径包含相同数目的黑色节点。
		6.一颗有n个节点的RB树,其高度最多是2log(n+1)
		7.黑高：某个结点到达 一个叶结点的任意一条简单路径上的黑色结点个数称为该结点的黑高（black-height），记作 bh(x)。
		8.红黑树的所有操作的算法复杂度都是 O(lgn)
		9.旋转的操作只是做了修改指针的操作，因此算法复杂度是 O(1)。
		10.BST的标准插入和删除操作对于红黑树也是O(lgn)的，但是这两个操作不保证操作之后还是颗RB树.



AVL and RB
首先红黑树是不符合AVL树的平衡条件的，即每个节点的左子树和右子树的高度最多差1的二叉查找树。
但是提出了为节点增加颜色，红黑是用非严格的平衡来换取增删节点时候旋转次数的降低，
任何不平衡都会在三次旋转之内解决，而AVL是严格平衡树，
RB-Tree在需要大量插入和删除node的场景下，效率更高。自然，由于AVL高度平衡，因此AVL的search效率更高

红黑树的查询性能略微逊色于AVL树，因为他比avl树会稍微不平衡最多一层，
也就是说红黑树的查询性能只比相同内容的avl树最多多一次比较，但是
红黑树在插入和删除上完爆avl树，avl树每次插入删除会进行大量的平衡度计算,
而红黑树为了维持红黑性质所做的红黑变换和旋转的开销，相较于avl树为了维持平衡的开销要小得多

*/

#define RED 1
#define BLACK 0

#define LEFT 1
#define RIGHT 2

#define IS_NULL(node) ((node) == NULL)
#define IS_RED(node) ((node) != NULL && (node)->color == RED)

struct RBNode {
    int color;
    int key;
    struct RBNode *left;
    struct RBNode *right;
    struct RBNode *parent;
};

struct RBTree{
    RBNode *root;
};

RBTree *RB_INIT(){
    RBTree *tree = new RBTree;
    tree->root = NULL;
    if (tree == NULL) {
        printf("malloc tree failed\n");
        exit(1);
    }
    return tree;
}

//某个结点的左儿子的左子树中插入一个结点，以这个结点的左儿子为轴，顺时针 旋转
RBNode* Left_Left_Rotation(RBNode *p){//右旋
    RBNode* k1 = p->left;//k1为轴，p折下来
    p->left = k1->right;//k1原来右边的东西给p 的左边（k1原来的位置），k1右边就空出来的
    if(k1->right){
        k1->right->parent = p;
    }

    k1->right = p;      //k1右边就接 p
    p->parent = k1;


    return k1; //返回新根
}

//某个结点的右儿子的右子树中插入一个结点，以这个结点的右儿子为轴，逆时针 旋转
RBNode* Right_Right_Rotation(RBNode *p){//左旋
    RBNode* k1 = p->right;
    p->right = k1->left;
    if(k1->left){
        k1->left->parent = p;
    }

    k1->left = p;
    p->parent = k1;


    return k1;
}


//**************************************RB树的插入*******************************************************//
//红黑树的插入:先找到要新节点插入的位置，将节点赋予红色，然后插入新节点。最后做红黑树性质的修复。
/* 为什么新结点赋红
 可能违反2，直接将根节点变黑即可 。若插入黑，影响黑高，反5，若插红，只需要处理2 4，即根红 或连续两个红结点
 */

//插入的修复,包括旋转和使修复节点上升
void RB_INSERT_FIXUP(RBTree *tree, RBNode *node){
    while(IS_RED(node)){//插入的结点是 红色才合法
        RBNode *parent = node->parent;
        if (!IS_RED(parent)) {
            break;      //红结点不相邻，无冲突
        }
        //出现相邻的红结点 ，即红结点的儿子不全为黑色
        RBNode *grandparent = parent->parent;//修复的变化还要看父结点是祖父结点的左孩子还是右孩子


        if (parent == grandparent->left){       //左右两种情况是对称的，此处看父结点是祖父结点的左孩子的情况
            RBNode *uncle = grandparent->right;
            if (IS_RED(uncle)){//uncle的颜色也是红的，uncle 可以随兄弟变黑
                parent->color = BLACK;//要恢复红黑树的性质 ,就要将parent 变黑，黑高++，但是grandparent 破坏了性质5
                uncle->color = BLACK;//所以对应 uncle 也要黑高++(uncle符合变黑条件)
                grandparent->color = RED;//此种情况插入之前，parent 和 uncle 一定是红的，即这对兄弟的父亲即grandparent 黑，爷爷的儿子们黑高++，爷爷要变红来偿还爷爷的爸爸和爷爷的左兄弟性质5
                node = grandparent; //node 指向 grandparent，让修复结点上升两个 level，重复上述，直到遇到根结点为止。从底部慢慢向上调整
            }
            else{            //uncle is black,只能父子俩变自己了
                if(node == parent->right){//将node 变为parent 的左儿子，进入下面的else
                    RBNode *t ;
                    Right_Right_Rotation(parent);
                    t = node;
                    node = parent;
                    parent = t;
                }
                else{//node 是左儿子
                    parent->color = BLACK;//插入的红色的父亲白变黑，祖父黑变白，右转才能保证黑高不变
                    grandparent->color = RED;
                    Left_Left_Rotation(grandparent);
                }
            }
        }

        //父节点是祖父结点的右儿子
        // same as then clause with "right" and "left" exchanged
        if (parent == grandparent->right){
            RBNode *uncle = grandparent->left;
            if (IS_RED(uncle)){
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            }
            else{//uncle is black
                if(node == parent->left){
                    RBNode *t ;
                    Left_Left_Rotation(parent);
                    t = node;
                    node = parent;
                    parent = t;
                }
                else{
                    parent->color = BLACK;
                    grandparent->color = RED;
                    Right_Right_Rotation(grandparent);
                }
            }

        }

    }

    tree->root->color = BLACK; //根节点一定是黑色

}





void DO_RB_INSERT(RBTree *tree, RBNode *node){//复杂度：1找到新结点插入logn,2插入修复 （包括旋转O(1)和使结点上升O(logn)）,so:O(logn)
    RBNode *walk = tree->root;
    RBNode *pre = NULL;
    while (walk != NULL){//确定插入的位置
        pre = walk;
        if (node->key < walk->key){
            walk = walk->left;
        }

        else walk = walk->right;// 这里默认插入的不会重复
    }

    node->parent = pre;
    //插入pre的左边右边？
    if (pre == NULL){
        tree->root = node;
    }
    else if (node->key <pre->key){
        pre->left = node;
    }
    else {pre->right = node;}
    //插入修复
    RB_INSERT_FIXUP(tree, node);
}




void RB_INSERT(RBTree *tree, int val){
    RBNode *newNode = new RBNode;
    if(newNode==NULL){
        cout<<"new failed!"<<endl;
        return;
    }
    newNode->parent = NULL;
    newNode->key = val;
    newNode->right = NULL;
    newNode->left = NULL;
    newNode->color = RED;
    DO_RB_INSERT(tree,newNode);
}
//**************************************RB树的插入*******************************************************//


RBNode *_rbtree_minimum(RBNode *node)
{
    while (node->left) {
        node = node->left;
    }

    return node;
}

void Transplant(RBTree *T, RBNode *u,RBNode *v){ //在T中，以v为根的子树替换以u为根的子树。
    if(u->parent==NULL){ // u 就为 根 T , v 替换树根
        //T = v;
        T->root = v;// 这里更新 T 虽然传进来的是root，但 T是局部变量，函数结束后就消失，所以 得改该根节点
    }
    else if(u = u->parent->left){//u是 左儿子
        u->parent->left = v;//v替换左儿子
    }
    else{
        u->parent->right = v;
    }
    if(v!=NULL){
        v->parent = u->parent; //如果不是拿空树来换，v的父亲结点要更新了
    }
}


//***********************************************递归遍历***************************************************//
void rbtree_preorder( RBNode *node)
{
    if (node == NULL){
        return;
    }

    cout<<node->key<<"-";
    if (node->color == RED)
        printf("RED \n");
    else
        printf("BLACK \n");
    rbtree_preorder(node->left);
    rbtree_preorder(node->right);
}

void rbtree_inorder(RBNode *node)
{
    if (node == NULL)
        return;
    rbtree_inorder(node->left);

    cout<<node->key<<"-";
    if (node->color == RED)
        printf("RED \n");
    else
        printf("BLACK \n");

    rbtree_inorder(node->right);
}

void rbtree_postorder(RBNode *node)
{
    if (node == NULL)
        return;
    rbtree_postorder(node->left);
    rbtree_postorder(node->right);

    cout<<node->key<<"-";
    if (node->color == RED)
        printf("RED \n");
    else
        printf("BLACK \n");
}

//***********************************************递归遍历***************************************************//

















#endif //RBTREE_RB_H
