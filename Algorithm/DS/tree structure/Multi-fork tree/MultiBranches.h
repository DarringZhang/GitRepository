//
// Created by Darring on 2018/11/13.
//

#ifndef MULTI_FORK_TREE_MULTIBRANCHES_H
#define MULTI_FORK_TREE_MULTIBRANCHES_H
/*
 * 多叉树：与二叉树定义类似，只是每个节点可以有大于等于2个儿子（B,B+tree）
 * 存储结构：双亲法（数组）
 *         链表法(下面实现)
 *         左子右兄
 * */



/**********************************
//双亲法：⽤数组存放每个结点,通过下标访问,每个结点内还包括其⽗亲结点的下标
#include <vector>//向量是一个能够存放任意类型的动态数组。
struct ParentTreeNode{
    char data;
    int parent;
};

struct ParentNode{
    vector <ParentTreeNode> nodes;
    int root;
 };

//双亲法适用于Parent(T,i)找树根，链表法适合孩子操作，两者结合：链表数组
***********************************/

/*******************************
//链表法：每个结点⽤⼀个链表来存放其所拥有的孩⼦结点
struct MLTreeNode {
    char *data;
    //list<MLTreeNode*> child_list; //一个链表list，里面存MLTreeNode型的指针
    struct MLTreeNode *first_child *next_sibling;
}tree;


struct MLTree {
    MLTreeNode* root;
    //各种遍历BFS,先(根)序,后(根)序
    //只有先根，后根遍历。而这里的前序后序遍历可以唯一确定一棵树，因后序可以转化为左子右兄（二叉树）的中序

};
*******************************/

//左子右兄法：利用二叉树表示多叉树（左上指向的全部拉水平就还原为多叉树）
//给定⼀棵树，⼀定能找到⼀棵唯⼀的⼆叉树与之对应.
//先根遍历:如果采⽤⼆叉树表达,则等价于⼆叉树的前序遍历
//后根遍历:如果采⽤⼆叉树表达,则等价于⼆叉树的中序遍历

#include <string>
struct node_t{
    string name;   //结点名字
    int NO_child;  //子结点个数
    int level;    //该结点再多叉树中的层数
    struct node_t **child; //child 是一个数组，里面存放node_n*类型的指针，还没有为这些指针开辟空间
};//重命名结构体

class MultiBranches{
public:
    node_t *root;
    MultiBranches(){

    }
    ~MultiBranches(){
        destroy(root);
    }
};

//生成结点
node_t *create_node(){
    node_t *q;
    q = new Node;
    q->NO_child = 0;
    q->level = -1;
    q->child = NULL;
    return q;
}

//建立多叉树
void create_tree(){
    cout<<"你要输入几条信息？";
    int
}
#endif //MULTI_FORK_TREE_MULTIBRANCHES_H
