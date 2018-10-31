/*
	一棵N个节点的二叉树,会有N+1个空指针.（填上一个NULL,就会多两个NULL） 
利用这些空指针把某个节点的前驱和后继记录下来：对于 一 
个结点,如果左儿子为空,那么做左儿子指向中序前驱(线索指针),
如果右儿子为空,则让它指向中序后继(线索指针)


这样就避免了像三叉链表中,需要临时计算某个结点的中序后
继的过程.但代价是每个节点需要额外的2个变量来指左右儿子 的指针是否为线索 ，还有
线索树中, 线索直接指后继结点. 但是线索需要单独建且一旦树的结构变了(如增删结点了),线索要重新建. （只要树的结构不改变，就一劳永逸） 
三叉中新鲜计算，不关乎结构 


 

1.某个结点没有左儿子右儿子时,才成为线索指针;
2.一个结点,如果有左线索,那么其指向该结点的前驱; 右线索(如果有)则指向其后继;
3.第1个结点和最后1个结点没有前驱和后继(或者说他们的前驱和后继是NULL)
*/ 

#include<iostream>
#include<string>
#include<queue>
using namespace std;

enum STATUS{THREAD,LINK};//枚举类型，个数有限 。默认依次赋值0，1，2，3.。。。。，赋值某个健，其后的值在它的基础上+1

struct Node{
	char data;
	STATUS l_thread = THREAD,r_thread = THREAD;//要初始化，因为在遍历中要 判断区分儿子和线索，开始初始化为 LINK,只要 创建中没改成THREAD,说明该指针域非空，非空即指向儿子 
	Node * l_child,*r_child; 
};

class Threaded_Binary_Tree{
private:
	Node* root = NULL;
public:
	Threaded_Binary_Tree(){
		root = new Node;
		root->l_child = NULL;
		root->r_child==NULL;
	}

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
	 		node->l_thread = LINK ;//******** 
		}
	 	L.push(node->l_child);
	 	
	 	if ( idx >=s.length()) break;
	 	
	
	 
	 	a = s[idx++];
	 	if ( a != '#'){
	 		node->r_child = new Node;
	 		node->r_child->data = a;
	 		node ->r_child-> l_child = NULL;
	 		node->r_child ->r_child = NULL;
	 		node->r_thread = LINK  ;  //******* 
		}
	 	L.push(node->r_child);
	} 	
	cout<<"create finished!"<<endl; 
}

/*********************************************前序线索二叉树的建立******************************************/
void preOrder_threading(Node * p,Node *& pre){

	 if(p){     	 
	 	///////////////////////////////////// 
		if(p->l_child == NULL) {//建立 p 前驱   
			 p->l_thread = THREAD;
			 p->l_child = pre;    
		 }
		 if(pre != NULL && pre->r_child == NULL){//建立pre 的后继
			 pre->r_thread = THREAD;
			 pre->r_child = p;
		 }
		 /////////////////////////////////////// 
		 pre = p;               //pre  更新 
		 
		 
		  //注意这要判断一下，只有是真儿子LINK才能递归，否则，根据线索进入其前驱，前驱再访问到它，进入死循环 
		 //p的左边建立为线索就不能进入递归
		 if(p->l_thread==LINK){              
		 	preOrder_threading(p->l_child, pre); 
		 }      
		 if(p->r_thread==LINK){
		 	 preOrder_threading(p->r_child, pre);
		 }
		
	 }
}

 //前序线索遍历的建立,主调函数
void preOrder_threading() {
	 if(root){    
		 Node * pre = NULL;
		 preOrder_threading(root, pre);
		 pre->r_child = NULL;
		 pre->r_thread = THREAD;//线索化最后一个结点,最后一个节点的 后继线索为空 
		 
	 }
}
/*********************************************前序线索二叉树的建立******************************************/


/*********************************************前序线索二叉树的遍历******************************************/	
void preOrder_thread() {
	 if(root == NULL) {
	 	return;
	 }
	 Node * cur = root;
	 do{
		 visit(cur);
		 cur = preOrder_successor_thread(cur);
	 }while(cur != NULL);
 }
 
 Node * preOrder_successor_thread(Node *p){
 	if(p){
 		if(p->l_thread==LINK){
			return  p->l_child;	
		} 
		else if(p->r_thread==LINK||p->r_thread==THREAD){
			return p->r_child;
		}
		return NULL;
	} 
 
	
}
/*********************************************前序线索二叉树的遍历******************************************/	




/*********************************************中序线索二叉树的建立******************************************/	
/*	思路：通过1次递归的中序遍历来建线索, 因为结点的先后
	顺序是在递归中维护的. 递归时, 只需要把上次访问的结点一 
	并递归即可. 初始时, pre = NULL,即第1个结点没有前驱
	
	且每种遍历的线索不一样，一但建立好了，遍历的顺序也就确定 
*/	


 //中序线索遍历的建立,递归, 即仅把    /////////   内的     原visit()换成建线索即可 
void inOrder_threading(Node * p,Node *& pre){ //这里用*& ：*&为两个意义相反的符号 ，像普通变量一样传递这个指针，只不过别的地方改变了值，需要反馈回来
	 if(p){            //p不是空的
		 inOrder_threading(p->l_child, pre); //递归左树  //这里不需要像前序遍历一样判断，因为这里建立线索在 递归之后 
		 
		 ///////////////////////////////////// 
		 //因现在已知 pre 和p  的关系: 即pre 的后继p 和 p 的前驱 pre ,根据这两个关系可以分别对 pre 和 p 建立一条线索 
		 if(p->l_child == NULL) {//建立 p 前驱   
			 p->l_thread = THREAD;
			 p->l_child = pre;   //对于第一个结点，pre = NULL; 
		 }
		 if(pre != NULL && pre->r_child == NULL){//建立pre 的后继
			 pre->r_thread = THREAD;
			 pre->r_child = p;
		 }
		 /////////////////////////////////////// 
		 pre = p;               //pre  更新，记住跟踪上次访问的结点 
		 inOrder_threading(p->r_child, pre);
	 }
}

 //中序线索遍历的建立,主调函数
void inOrder_threading() {
	 if(root){    
		 Node * pre = NULL;
		 inOrder_threading(root, pre);
		 pre->r_child = NULL;
		 pre->r_thread = THREAD;//线索化最后一个结点,最后一个节点的 后继线索为空 
		 
	 }
}

/*********************************************中序线索二叉树的建立******************************************/	


/*********************************************中序线索二叉树的遍历******************************************/	
//对非空的结点p，找其最左下的结点，左儿子不是线索，则一定有左儿子 
Node* find_most_left_node_thread(Node *p){
	 while(p->l_thread ==LINK){
	 	p = p->l_child;
	 }
     return p;
}

/*对非空的结点x，找其中序遍历下的后继结点 
	如果x的右子不是线索，则x的中序后继定是其右子树最左下的点
    否则x的右子是线索指针，正好指向x的中序后继、
*/ 
Node * inOrder_successor_thread(Node *x){
 	if(x->r_thread ==LINK){
 		return find_most_left_node_thread(x->r_child);
	 } 
	
	 return x->r_child;
}


 //中序线索遍历,不递归,不用辅助栈，不用三叉 
void inOrder_thread() {
	 if(root == NULL) {
	 	return;
	 }
	 Node * cur = find_most_left_node_thread(root);
	 do{
		 visit(cur);
		 cur = inOrder_successor_thread(cur);
	 }while(cur != NULL);
 }
/*********************************************中序线索二叉树的遍历******************************************/	


/*********************************************后序线索二叉树的建立******************************************/
void postOrder_threading(Node * p,Node *& pre){

	 if(p){     	 
		postOrder_threading(p->l_child, pre); 
		postOrder_threading(p->r_child, pre);
		
		///////////////////////////////////// 
		if(p->l_child == NULL) {//建立 p 前驱   
			 p->l_thread = THREAD;
			 p->l_child = pre;    
		 }
		 if(pre != NULL && pre->r_child == NULL){//建立pre 的后继
			 pre->r_thread = THREAD;
			 pre->r_child = p;
		 }
		 /////////////////////////////////////// 
		 pre = p;               //pre  更新 
		 
		             
	 }
}

 //后序线索遍历的建立,主调函数
void postOrder_threading() {
	 if(root){    
		 Node * pre = NULL;
		 postOrder_threading(root, pre);
		 pre->r_child = NULL;
		 pre->r_thread = THREAD;//线索化最后一个结点,最后一个节点的 后继线索为空 
		 
	 }
}
/*********************************************后序线索二叉树的建立******************************************/
/*********************************************后序线索二叉树的遍历******************************************/	
//后序遍历要使用带双亲的三叉链表


void postOrder_thread() {
	 if(root == NULL) {
	 	return;
	 }
	 Node * cur = find_first_node_postOrder(root);
	 do{
		 visit(cur);
		 cur = postOrder_successor_thread(cur);
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
 
 Node * postOrder_successor_thread(Node *p){
 ///////////////
 	if(p->parent==NULL){
 		return NULL;
	 } 
	 
	 
	 if(p->r_thread==THREAD){
			return p->r_child;
	}
	 // p为左儿子， 说明其父亲 和父亲的右儿子都还没访问，先访问父亲的右儿子 
	 Node *cur = p->parent;       //后序遍历要使用带双亲的三叉链表
	 //父亲的右儿子为空，接下只能访问父亲 
	 if(cur->r_child==NULL){
	 	return cur;
	 } 
	 cur = cur->r_child;
	 return  find_first_node_postOrder(cur);
 
 
 
 
 
	
}
/*********************************************后序线索二叉树的遍历******************************************/


	void visit(Node *node){
		cout<<node->data<<" ";
	} 
	
}; 


int main(void)  
{  
    Threaded_Binary_Tree a;
    cout<<"输入一串创建字符（如ABD#C#F##E）";
    string s;
	cin>>s; 
    a.CreateTree(s);
//    cout<<"前序遍历:" ;
//    a.preOrder_threading();//建立 
//    a.preOrder_thread();//遍历 
	cout<<"中序遍历:" ;
	a.inOrder_threading();
	a.inOrder_thread() ; 

    return 0;
}
    











