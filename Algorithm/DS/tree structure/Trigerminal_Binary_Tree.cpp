//对于二叉链表实现的2叉树，都需要利辅助空间: 或是(递归) 或是 队列.
//三叉链表,既不用辅助栈也不用递归 （系统栈） 


                 /*指向父节点的指针 */
				 
				 
#include<iostream>
#include<string>
#include<queue>
using namespace std;				  
struct Node {
 	char data;
 	Node* l_child ,*r_child, *parent = NULL;
}; 


class Trigerminal{
private:
	Node * root = NULL;
public:
	Trigerminal(){
		root  = new Node;
		root->l_child = NULL;
		root->r_child = NULL;
		root->data = ' ';
		root->parent = NULL;
	}
	
	
	
	//只是比二叉树的创建   在每个结点内多了parent =NULL 和指向父节点的指向 
	void CreateTree(string s){
    queue<Node*> L ;
	int idx = 0;				
	
 	root->data = s[idx++] ;
 	L.push(root);   
 	while( idx <s.length()){
	 	Node* node = L.front();   
	 	L.pop();
	 	if (node == NULL) {    
		 	idx += 2;            
			continue;          
		 }
		 
		
		
	 	char a = s[idx++];
	 	if ( a != '#'){
	 		node->l_child = new Node;
	 		node->l_child->data = a;
	 		node ->l_child-> l_child = NULL;
	 		node->l_child->r_child = NULL;
	 		node->l_child->parent = node;  //******** 
		}
	 	L.push(node->l_child);
	 	
	 	if ( idx >=s.length()) break;
	 	
	
	 
	 	a = s[idx++];
	 	if ( a != '#'){
	 		node->r_child = new Node;
	 		node->r_child->data = a;
	 		node ->r_child-> l_child = NULL;
	 		node->r_child ->r_child = NULL;
	 		node->r_child->parent = node;    //******* 
		}
	 	L.push(node->r_child);
	} 	
	cout<<"create finished!"<<endl; 
}


//三叉链表的深度遍历，依然可以递归来完成。整个过程和二叉链表版本没有任何区别。
//但是非递归版本   不用辅助栈也不用递归
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
	if(p->l_child){
		return  p->l_child;	
	} 
	else if(p->r_child){
		return p->r_child;
	}
	//p 为叶子结点 后继为父亲结点的右儿子。若右儿子为空 或者 p就为父亲的右儿子，为换方向后的那个转折点的右儿子 
	Node *y = p->parent; 
	while(y->r_child==NULL||p == y->r_child){//往上爬，直到  指向右上->左上 
		p = y;
		y = y->parent;
		if(y==NULL){ //y往上爬为根节点了，这个根y要么没有右子树，要么y本来就是从右边往上爬的，y的儿子 p的后继就是NULL 
			return NULL;
		} 
	} 
	return y->r_child;   
}

/********************************************* 三叉前序 ******************************************/ 

/********************************************* 三叉中序 ******************************************/ 
/* 三叉中序 
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
 }
 
 Node* find_most_left_node(Node *p){
	 while(p->l_child != NULL){
	 	p = p->l_child;
	 }
    return p;
}
 
 Node* inOrder_Successor(Node *x){
	 if(x->r_child != NULL){//如果x有右结点，则所求定是其x的右子树中最左下的点
	 	return find_most_left_node(x->r_child);
	 }
 
 //否则就是x的祖先结点中的某个。 
     Node *p = x->parent;
	 while(p != NULL && x == p->r_child){//向上搜寻，一直到x 变成左儿子 或者p到根结点 为空了 
		 x = p;                         //若x 是左儿子，后继就是它的父亲。
		 p = p->parent;            		 //若x 是右儿子，它的左指向父亲已经先他一步访问， 就要顺藤向上，直到方向 左上->右上 
	 }
	 return p;
 }
  /********************************************* 三叉中序 ******************************************/ 
  
  
  
  /********************************************* 三叉后序 ******************************************/ 
  void postOrder_No_Stack() {
	 if(root == NULL) {
	     return;
	 }
	 Node* cur  = find_first_node_postOrder(root); //左右中，这个时候第一个就不一定是最左下的点（区别中序 左中右） 
	 do{                                       //中序，如果左儿子空，不进入循环，返回自己，下一个要访问自己 
		 visit(cur);                          // 后序，左儿子空，还不能返回自己，有右儿子就要让右儿子先 
		 cur = postOrder_Successor(cur);                //即左右儿子和父亲这三者的   优先级 发生变化 
	 }while(cur != NULL);
 }
 
 Node *find_first_node_postOrder(Node *p){
 	while(p) {
 		if(p->l_child){
 			p = p->l_child;
		 } 
		 else if(p->r_child){
		 	p = p->r_child;
		 }
		 else{
		 	break;
		 }
	 }
	 return p;
 } 
 
 Node * postOrder_Successor(Node *p){
 	if(p->parent==NULL){
 		return NULL;
	 } 
	 
	 	//p 为右儿子，后继即当前结点的父亲 
	 if(p == p->parent->r_child){
	 	return p->parent;
	 } 
	 // p为左儿子， 说明其父亲 和父亲的右儿子都还没访问，先访问父亲的右儿子 
	 Node *cur = p->parent;
	 //父亲的右儿子为空，接下只能访问父亲 
	 if(cur->r_child==NULL){
	 	return cur;
	 } 
	 cur = cur->r_child;
	 return  find_first_node_postOrder(cur);
 }
 
  /********************************************* 三叉后序 ******************************************/ 	
  
	void visit(Node *node){
		cout<<node->data<<" ";
	} 
	
	Node *GetRoot(){
		return root;
	}

};



int main(void)  
{  
    Trigerminal a; 
    int flag=1,k;  
    printf("                     本程序实现三叉树的基本操作。\n");  
    printf("可以进行建立三叉树，非递归不用辅助栈先序、中序, 后序遍历操作。\n");  
  
    while(flag)  
    {  
        printf("\n");  
        printf("|--------------------------------------------------------------|\n");  
        printf("|                    三叉树的基本操作如下:                     |\n");  
        printf("|                        0.创建三叉树                          |\n");  
        printf("|                        4.非递归不用辅助栈先序遍历                      |\n");  
        printf("|                        5.非递归不用辅助栈中序遍历                      |\n");  
        printf("|                        6.非递归不用辅助栈后序遍历                      |\n");   
        printf("|                        8.退出程序                            |\n");  
        printf("|--------------------------------------------------------------|\n");  
        printf("                        请选择功能：");  
        scanf("%d",&k);  
        switch(k)  
        {  
	        case 0:{
	        	printf("请建立二叉树，输入一串创建字符（如ABD#C#F##E）");
	            string s;
	            cin>>s; 
	            a.CreateTree(s);
				break;
			}  
	        
	        case 4:  {
	        	 if(a.GetRoot())  
	            {  
	                printf("非递归不用辅助栈先序遍历二叉树：");  
	                a.preOrder_No_Stack(); 
	                printf("\n");  
	            }  
	            else  
	                printf("          二叉树为空！\n");  
	            break;  
			}
	           
	        case 5:  {
	        
	            if(a.GetRoot())  
	            {  
	                printf("非递归不用辅助栈中序遍历二叉树：");  
	                a.inOrder_No_Stack();
	                printf("\n");  
	            }  
	            else  
	                printf("          二叉树为空！\n");  
	            break;  
			}
	        case 6: {
	        if(a.GetRoot())  
	            {  
	                printf("非递归不用辅助栈后序遍历二叉树：");  
	                a.postOrder_No_Stack()  ;
	                printf("\n");  
	            }  
	            else  
	                printf("          二叉树为空！\n");  
	            break;  
			} 
	        
			case 8:{
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

