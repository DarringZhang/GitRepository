/*前面的 二叉树，三叉树，线索二叉树 ，只是建立起来了，访问了一遍，并没有 操作 
问建立 后, 能不能像链表或是栈等结构，增/删/改/查 某个点?


BST 
1) T 是二叉树,
2) 对所有结点，左子树大于它，右子树小于它 (有了一定的存储顺序)，可以进行操作啦 
3）按 中序 ，刚好是从小到大 排序 
*/

#include<iostream>
using namespace std;

struct Node
{
    int key;
    Node* left;
    Node* right;
    Node* parent;
};

class BST{
private:
    Node *root = NULL;
public:

    BST(){
    }



    //插入来创建BST
    void Create_BST( int n){
        int value;
        cout<<"please input the keys:";
        for(int i=0; i<n; ++i){
            cin>>value;
            BST_Insert_NonRecur(root,value);
        }
    }



//插入的新结点一定是某个叶结点，作为一种动态结构，先查找若值不重复，再插入	
//递归插入	
    int BST_Insert(Node*T, int k, Node* l_parent = NULL){
        if(T == NULL)
        {
            T = new Node;
            T->key = k;
            T->left = NULL;
            T->right = NULL;
            T->parent = l_parent;
            return 1;  // 返回1表示成功
        }
        else if(k == T->key)
            return 0;  // 树中存在相同关键字
        else if(k < T->key)
            return BST_Insert(T->left, k, T);
        else
            return BST_Insert(T->right, k, T);
    }

//非递归插入（效率高）	
    int BST_Insert_NonRecur(Node* T, int k){
        Node* pre = NULL;  // 记录上一个结点
        Node* t = T;
        //移动到合适位置
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

        if(pre == NULL)
            root = node; //即插入的是根节点
        else
        {
            if(k < pre->key)  //判断插左边还是右边
                pre->left = node;
            else
                pre->right = node;
        }
        return 1;
    }



//BST Search
/*
	Search sth操作外，二叉查找树还能支持如 Minimum（最小值）、Maximum（最大值）、
	Predecessor（前驱）、Successor（后继）等查询。对于高度为 h 的树，这些操作都可以在 Θ(h) 时间内完成。
*/


    //递归 search 某个值
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
//非递归 search 某个值 
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
 * 最小值：查找二叉查找树中关键字最小的结点
 */
    Node* BST_Minimum(Node* T)
    {
        while(T->left != NULL)
            T = T->left;
        return T;
    }

/**
 * 最大值：查找二叉查找树中关键字最大的结点
 */
    Node* BST_Maximum(Node* T)
    {
        while(T->right != NULL)
            T = T->right;
        return T;
    }


/**
 * 后继：查找给定结点在中序遍历中的后继结点
 */
    Node* BST_Successor(int k)
    {
        Node *node = BST_Search_NonRecur(root, k);
        if(node->right != NULL){//x 的右子树不为空，则 x 的后继就是它的右子树中最左下的点（即关键字值最小的结点）；
            return BST_Minimum(node->right);
        }

        //右节点为空
        Node* p = node->parent;
        while(p!=NULL && p->right == node)//只要还没到根节点，或者node 还是p 的右儿子，左中右，说明它的父亲已经被访问，还要顺藤
        {                                 // 直到变成p 的右儿子
            node = p;
            p = p->parent;
        }
        return p;
    }

/**
 * 前驱：查找给定结点在中序遍历中的前驱结点
 */
    Node* BST_Predecessor(int k)//与找后继镜像对称
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
二叉查找树的删除操作是相对复杂一点，它要按 3 种情况来处理：删除(Deletion):从T中删除?个节点z,三种情况
1) z没有孩子, 简单将其父节点的指向 z的指针替换为NIL;
2) z只有1个孩子 将z的这个孩子提升为z的父亲的孩子,取代z的位置;
3) z有俩孩子 先找z的中序后继y(必然在z的右子树), y取代z的位置, z中右子树剩下的部分成为y的新右子树,z的左
   树变成y的新左树. (第三种情况比较复杂，取决于y是不是z的右孩)
*/

    //其中1的情况可以合并到2 （因为可以用NULL取代z 的位置）



    //种树
    void Transplant(Node *T, Node *u,Node *v){ //在T中，以v为根的子树替换以u为根的子树。
        if(u->parent==NULL){ // u 就为 根 T , v 替换树根
            //T = v;
            root = v;// 这里更新 T 虽然传进来的是root，但 T是局部变量，函数结束后就消失，所以 得改该根节点
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

    void Delete(int k){
        Node *z = BST_Search_NonRecur(root,k);
        //如果为叶子节点
        if(z->left==NULL&&z->right==NULL){
            if(z==z->parent->left){
                z->parent->left = NULL;
            }
            else if(z==z->parent->right){
                z->parent->right = NULL;
            }
        }
            //左子树为空
        else if(z->left==NULL){
            Transplant(root,z,z->right);//如果没有上面的叶子节点的判断，这里 Transplant 非法访问，就会出现段错误
        }
            //右子树为空
        else if(z->right==NULL){
            Transplant(root,z,z->left);
        }
        else{//z左右都不为空
            Node *y = BST_Minimum(z->right);//拿出右边最小的树构造新树 ，转化成第一个if 的情况(也可以找右边最大的，第二个if)
            if(y->parent!=z){//最左下的点和 z不直接相连 （直接相连的话，y 就为叶子，直接接上z 左，替代z）
                Transplant(root,y,y->right);  //把新树的结点 y 分离出来
                y->right = z->right; // 将要删的结点z 右边 和z 断开，接到新结点上
                y->right->parent = y;//父亲结点指向
            }//构造新树成功
            Transplant(root,z,y);
            y->left = z->left;
            y->left->parent = y;
        }
    }


    void Modyfiy(int old,int newer){
        Node *oldnode = BST_Search_NonRecur(root, old);
        Node *newernode = BST_Search_NonRecur(root, newer);
        if(newernode==NULL){//说明没有原树中没有与之重复的结点
            //修改某个值后还要将它调整到合适位置, 仅 oldnode->key = newer改个值  行不通;
            Delete(old);
            BST_Insert_NonRecur(root,newer);
        }
        else{
            cout<<"there is already has such newer keys,can’t repeate！"<<endl;
        }

    }

    /********************************************* 中序遍历 ******************************************/
/* 中序 
	1) 找到二叉树最左下的结点p;
	2) visit(p); p = inorder_successor(p);
	3) 返回2),直到 p 没有后继(p == NULL).
*/
    void inOrder_No_Stack() {
        if(root == NULL) {
            return;
        }
        Node* cur = find_most_left_node(root); //左中右，先从最左下的结点
        do{
            visit(cur) ;//最先访问最左下的点
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
        if(x->right != NULL){//如果x有右结点，则所求定是其x的右子树中最左下的点
            return find_most_left_node(x->right);
        }

        //否则就是x的祖先结点中的某个。
        Node *p = x->parent;
        while(p != NULL && x == p->right){//向上搜寻，一直到x 变成左儿子 或者p到根结点 为空了
            x = p;                         //若x 是左儿子，后继就是它的父亲。
            p = p->parent;            		 //若x 是右儿子，它的左指向父亲已经先他一步访问， 就要顺藤向上，直到方向 左上->右上
        }
        return p;
    }
    /********************************************* 中序遍历******************************************/


    void visit(Node *node){
        cout<<node->key<<" ";
    }

    Node *GetRoot(){
        return root;
    }


};





int main(void)
{
    BST a;
    int flag=1,k;
    printf("                     本程序实现二叉搜索树的基本操作。\n");
    printf("可以进行建立BST,递归插入，非递归插入，递归查找某个特定的值，非递归查找某个特定的值，找最大，找最小，找后继，前驱，删除，,替换，中序遍历打印，退出等操作。\n");

    while(flag)
    {
        printf("\n");
        printf("|--------------------------------------------------------------|\n");
        printf("|                      BST的基本操作如下:                      |\n");
        printf("|                        0.创建BST                             |\n");
        printf("|                        1.递归插入                            |\n");
        printf("|                        2.非递归插入                          |\n");
        printf("|                        3.递归查找                            |\n");
        printf("|                        4.非递归查找                          |\n");
        printf("|                        5.最大                                |\n");
        printf("|                        6.最小                                |\n");
        printf("|                        7.前驱                                |\n");
        printf("|                        8.后继                                |\n");
        printf("|                        9.删除                                |\n");
        printf("|                        10.替换                               |\n");
        printf("|                        11.中序遍历打印                       |\n");
        printf("|                        12.退出                               |\n");
        printf("|--------------------------------------------------------------|\n");
        printf("                        请选择功能：");
        scanf("%d",&k);
        switch(k)
        {
            case 0:{
                printf("请建立BST，输入你想要创建的结点个数：");
                int s;
                cin>>s;
                a.Create_BST(s);
                a.inOrder_No_Stack();
                break;
            }
            case 1 :{
                if(a.GetRoot())
                {
                    printf("input the key you wanna recursive_insert:");
                    int k;
                    cin>>k;
                    a.BST_Insert_NonRecur(a.GetRoot(),k);
                    a.inOrder_No_Stack();
                }
                else
                    printf("          BST为空！\n");
                break;

            }
            case 2: {
                if(a.GetRoot())
                {
                    printf("input the key you wanna non_recursive_insert:");
                    int k;
                    cin>>k;
                    a.BST_Insert_NonRecur(a.GetRoot(),k) ;
                    a.inOrder_No_Stack();
                }
                else
                    printf("          BST为空！\n");
                break;
            }

            case 3: {
                if(a.GetRoot())
                {
                    printf("input the key you wannna recursive find:");
                    int k;
                    cin>>k;
                    Node * t = a.BST_Search(a.GetRoot(),k);
                    if(t==NULL){
                        cout<<"cant't find!";
                    }
                    else{
                        cout<<"find it !";
                    }
                    printf("\n");
                }
                else
                    printf("          BST为空！\n");
                break;
            }

            case 4:  {
                if(a.GetRoot())
                {
                    printf("input the key you wannna Non_recursive find:");
                    int k;
                    cin>>k;
                    Node * t = a.BST_Search_NonRecur(a.GetRoot(),k);
                    if(t==NULL){
                        cout<<"cant't find!";
                    }
                    else{
                        cout<<"find it !";
                    }
                    printf("\n");
                }
                else
                    printf("          BST为空！\n");
                break;
            }

            case 5:  {

                if(a.GetRoot())
                {
                    printf("Maxinum is ：");
                    cout<<a.BST_Maximum(a.GetRoot())->key;
                    printf("\n");
                }
                else
                    printf("          BST为空！\n");
                break;
            }
            case 6: {
                if(a.GetRoot())
                {
                    printf("Mininum is ：");
                    cout<<a.BST_Minimum(a.GetRoot())->key;
                    printf("\n");
                }
                else
                    printf("          BST为空！\n");
                break;
            }

            case 7:{
                if(a.GetRoot())
                {
                    printf("input the key you wanna find predecessor for:");
                    int k;
                    cin>>k;
                    if(a.BST_Search_NonRecur(a.GetRoot(),k)==a.BST_Minimum(a.GetRoot())){
                        cout<<"the predecessor is NULL"<<endl;
                        break;
                    }
                    cout<<"the predecessor is:";
                    cout<<a.BST_Predecessor(k)->key<<endl;
                    printf("\n");
                }
                else
                    printf("          BST为空！\n");
                break;
            }

            case 8:{
                printf("input the key you wanna find successor for:");
                int k;
                cin>>k;
                if(a.BST_Search_NonRecur(a.GetRoot(),k)==a.BST_Maximum(a.GetRoot())){
                    cout<<"the successor is NULL"<<endl;
                    break;
                }
                cout<<"the successor is:";
                cout<<a.BST_Successor(k)->key<<endl;
                printf("\n");
                break;
            }
            case 9:{
                printf("input the key you wanna delete:");
                int k;
                cin>>k;
                a.Delete(k);
                a.inOrder_No_Stack();
                break;
            }
            case 10:{
                printf("input the key you wanna modify and modify as:");
                int m,n;
                cin>>m>>n;
                a.Modyfiy(m,n);
                a.inOrder_No_Stack();
                break;
            }
            case 11:{
                a.inOrder_No_Stack();
                break;
            }
            case 12:{
                flag=0;
                printf("结束程序运行，按任意键退出！\n");
                break;
            }

            default:{
                cout<<"input error,please input again"<<endl;
                break;
            }

        }
    }

    system("pause");
    return 0;
}







