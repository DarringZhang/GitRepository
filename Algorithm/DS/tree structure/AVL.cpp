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
#include<iostream>
using namespace std;

struct Node { 
	int key;
	Node *left ,*right;
	int height;//记录此结点二点高度，空结点，高度是0 

	Node* parent;
};


class BST{
protected:
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
		cout<<node->key<<"-高"<<node->height<<" ";
	} 
	
	Node *GetRoot(){
		return root;
	}
	
   
};













///////////////////////////////////////////////////////////////////////////////////////////

class AVL :public BST {
public:
	AVL(){	
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
	

/*************************************************插入******************************************/	
	Node *AVL_Insert(Node * T,int v){
		if(T==NULL){
			T = Create_Node(v);
		}
		else if(v < T->key){
			T->left = AVL_Insert(T->left, v);//为 v的插入位置寻找新结点 
			T->left->parent = T;
			if(Tree_Height(T->left) - Tree_Height(T->right) == 2){//左边插入后 重了 
				if(v < T->left->key){     //插入到左边了，左左式不平衡 
					T = Left_Left_Rotation(T);
				}
			
				else{    //左右式不平衡 
					T = Left_Right_Rotation(T);
				}
			
		 	}
		}
		else if(v > T->key){
			T->right = AVL_Insert(T->right, v);//为 v的插入位置寻找新结点 
			T->right->parent = T;
			if(Tree_Height(T->right) - Tree_Height(T->left) == 2){//右边插入后 重了 
				if(v < T->left->key){ //右左式不平衡 
					T = Right_Left_Rotation(T);
				}
			
				else{   // 右右式不平衡 
					T = Right_Right_Rotation(T);
				}
			
		 	}
		}	
		else{
			//v == Root->key, insert failed->
			cout<<"insert failed！"<<endl;
		} 
			
		T->height = MAX(Tree_Height(T->left), Tree_Height(T->right)) + 1;
		this->root = T;
		root->parent = NULL;
		return T;
	}
/*************************************************插入******************************************/



			
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


//（观察与BST比较这些操作的时间），除了 插入 和 删除，其他继承BST 
int main(void)  
{  
    AVL a; 
    int flag=1,k;  
    printf("                         本程序实现AVL的基本操作。\n");  
    printf("可以进行 建立AVL，旋转插入，递归查找，非递归查找，找最大，找最小，找前驱，找后继，删除，替换，中序打印操作。\n");  
  
    while(flag)  
    {  
        printf("\n");  
        printf("|--------------------------------------------------------------|\n");  
        printf("|                      AVL的基本操作如下:                      |\n");  
        printf("|                        0.创建AVL                             |\n");  
        printf("|                        1.插入                                |\n");  
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
	        	printf("请建立AVL，输入你想要创建的结点个数：");
	            int s;
	            cin>>s; 
	            a.Create_AVL(s);
	            a.inOrder_No_Stack();
				break;
			}  
	        case 1 :{
	        	if(a.GetRoot())  
	            {  
	                printf("input the key you wanna insert:"); 
					int k;
					cin>>k; 
	                a.AVL_Insert(a.GetRoot(),k) ;
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
					a.AVL_Delete(a.GetRoot(),k); 
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








