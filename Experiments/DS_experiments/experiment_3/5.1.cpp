#include<iostream>
using namespace std;

struct Node { 
	int key;
	Node *left ,*right;
	int height;

	Node* parent;
};



class AVL {
public:
	Node *root = NULL;
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
			T->left = AVL_Insert(T->left, v); 
			T->left->parent = T;
			if(Tree_Height(T->left) - Tree_Height(T->right) == 2){
				if(T->left!=NULL){	
					if(v < T->left->key){    
						T = Left_Left_Rotation(T);
					}
				
					else{    
						T = Left_Right_Rotation(T);
					}
				}
		 	}
		}
		else if(v > T->key){
			T->right = AVL_Insert(T->right, v);
			T->right->parent = T;
			if(Tree_Height(T->right) - Tree_Height(T->left) == 2){
			if(T->right!=NULL){	
				if(v < T->right->key){ 
					T = Right_Left_Rotation(T);
				}
				else{  
					T = Right_Right_Rotation(T);
				}
			}
			
				
		 	}
		}	
		else{
			
			cout<<"insert failed！"<<endl;
		} 
			
		T->height = MAX(Tree_Height(T->left), Tree_Height(T->right)) + 1;
		this->root = T;
		root->parent = NULL;
		return T;
	}

	
/*************************************************插入******************************************/

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
  
 	/********************************************* 三叉前序 ******************************************/ 
void preOrder_No_Stack() {
	 if(root == NULL) {
	     return;
	 }
	 Node* cur = root; //中左右
	 do{
		 visit(cur) ;//先访问当前 
		 cur = preOrder_Successor(cur);//再找后继 
	 }while(cur != NULL);
 }
 
Node *preOrder_Successor(Node* p){
	//p如果有儿子，后继一定是直系儿子 
	if(p->left){
		return  p->left;	
	} 
	else if(p->right){
		return p->right;
	}
	//p 为叶子结点 后继为父亲结点的右儿子。若右儿子为空 或者 p就为父亲的右儿子，为换方向后的那个转折点的右儿子 
	Node *y = p->parent; 
	while(y->right==NULL||p == y->right){//往上爬，直到  指向右上->左上 
		p = y;
		y = y->parent;
		if(y==NULL){ //y往上爬为根节点了，这个根y要么没有右子树，要么y本来就是从右边往上爬的，y的儿子 p的后继就是NULL 
			return NULL;
		} 
	} 
	return y->right;   
}

/********************************************* 三叉前序 ******************************************/ 


	void visit(Node *node){
		cout<<node->key<<" ";
	} 
	
	Node *GetRoot(){
		return root;
	}
	

 
};


int main(void)  
{
	AVL a;
	cout<<"INPUT:"<<endl; 
	int s;
	cin>>s; 
	a.Create_AVL(s);
	cout<<"OUTPUT:"<<endl;
	a.inOrder_No_Stack();
	a.preOrder_No_Stack();
	return 0; 
}