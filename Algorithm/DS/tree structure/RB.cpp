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


struct RBNode {
     int color;
     void *key;
     void *value;
     struct RBNode *left;
     struct RBNode *right;
     struct RBNode *parent;
};

//红黑树的插入:先找到要新节点插入的位置，将节点赋予红色，然后插入新节点。最后做红黑树性质的修复。
/* 为什么新结点赋红 
 可能违反2，直接将根节点变黑即可 。若插入黑，影响黑高，反5，若插红，只需要处理2 4，即根红 或连续两个红结点 
 */ 
 
 RB_INSERT(RBNode* T, node){
 	RBNode *walk = T;
    RBNode *prev = NULL;
    while (walk != NULL)
        prev = walk;
        if (node.key < walk.key)
            walk = walk.left
        else walk = walk.right
    node.parent = walk
    if (walk == NULL)
        T.root = node
    else if (node.key < walk.key)
        walk.left = node
    else walk.right = node
    RB-INSERT-FIXUP(T, node)
 } 
    
    
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
