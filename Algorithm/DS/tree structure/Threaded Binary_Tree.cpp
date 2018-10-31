/*
	һ��N���ڵ�Ķ�����,����N+1����ָ��.������һ��NULL,�ͻ������NULL�� 
������Щ��ָ���ĳ���ڵ��ǰ���ͺ�̼�¼���������� һ 
�����,��������Ϊ��,��ô�������ָ������ǰ��(����ָ��),
����Ҷ���Ϊ��,������ָ��������(����ָ��)


�����ͱ�����������������,��Ҫ��ʱ����ĳ�����������
�̵Ĺ���.��������ÿ���ڵ���Ҫ�����2��������ָ���Ҷ��� ��ָ���Ƿ�Ϊ���� ������
��������, ����ֱ��ָ��̽��. ����������Ҫ��������һ�����Ľṹ����(����ɾ�����),����Ҫ���½�. ��ֻҪ���Ľṹ���ı䣬��һ�����ݣ� 
���������ʼ��㣬���غ��ṹ 


 

1.ĳ�����û��������Ҷ���ʱ,�ų�Ϊ����ָ��;
2.һ�����,�����������,��ô��ָ��ý���ǰ��; ������(�����)��ָ������;
3.��1���������1�����û��ǰ���ͺ��(����˵���ǵ�ǰ���ͺ����NULL)
*/ 

#include<iostream>
#include<string>
#include<queue>
using namespace std;

enum STATUS{THREAD,LINK};//ö�����ͣ��������� ��Ĭ�����θ�ֵ0��1��2��3.������������ֵĳ����������ֵ�����Ļ�����+1

struct Node{
	char data;
	STATUS l_thread = THREAD,r_thread = THREAD;//Ҫ��ʼ������Ϊ�ڱ�����Ҫ �ж����ֶ��Ӻ���������ʼ��ʼ��Ϊ LINK,ֻҪ ������û�ĳ�THREAD,˵����ָ����ǿգ��ǿռ�ָ����� 
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

/*********************************************ǰ�������������Ľ���******************************************/
void preOrder_threading(Node * p,Node *& pre){

	 if(p){     	 
	 	///////////////////////////////////// 
		if(p->l_child == NULL) {//���� p ǰ��   
			 p->l_thread = THREAD;
			 p->l_child = pre;    
		 }
		 if(pre != NULL && pre->r_child == NULL){//����pre �ĺ��
			 pre->r_thread = THREAD;
			 pre->r_child = p;
		 }
		 /////////////////////////////////////// 
		 pre = p;               //pre  ���� 
		 
		 
		  //ע����Ҫ�ж�һ�£�ֻ���������LINK���ܵݹ飬���򣬸�������������ǰ����ǰ���ٷ��ʵ�����������ѭ�� 
		 //p����߽���Ϊ�����Ͳ��ܽ���ݹ�
		 if(p->l_thread==LINK){              
		 	preOrder_threading(p->l_child, pre); 
		 }      
		 if(p->r_thread==LINK){
		 	 preOrder_threading(p->r_child, pre);
		 }
		
	 }
}

 //ǰ�����������Ľ���,��������
void preOrder_threading() {
	 if(root){    
		 Node * pre = NULL;
		 preOrder_threading(root, pre);
		 pre->r_child = NULL;
		 pre->r_thread = THREAD;//���������һ�����,���һ���ڵ�� �������Ϊ�� 
		 
	 }
}
/*********************************************ǰ�������������Ľ���******************************************/


/*********************************************ǰ�������������ı���******************************************/	
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
/*********************************************ǰ�������������ı���******************************************/	




/*********************************************���������������Ľ���******************************************/	
/*	˼·��ͨ��1�εݹ�����������������, ��Ϊ�����Ⱥ�
	˳�����ڵݹ���ά����. �ݹ�ʱ, ֻ��Ҫ���ϴη��ʵĽ��һ 
	���ݹ鼴��. ��ʼʱ, pre = NULL,����1�����û��ǰ��
	
	��ÿ�ֱ�����������һ����һ���������ˣ�������˳��Ҳ��ȷ�� 
*/	


 //�������������Ľ���,�ݹ�, ������    /////////   �ڵ�     ԭvisit()���ɽ��������� 
void inOrder_threading(Node * p,Node *& pre){ //������*& ��*&Ϊ���������෴�ķ��� ������ͨ����һ���������ָ�룬ֻ������ĵط��ı���ֵ����Ҫ��������
	 if(p){            //p���ǿյ�
		 inOrder_threading(p->l_child, pre); //�ݹ�����  //���ﲻ��Ҫ��ǰ�����һ���жϣ���Ϊ���ｨ�������� �ݹ�֮�� 
		 
		 ///////////////////////////////////// 
		 //��������֪ pre ��p  �Ĺ�ϵ: ��pre �ĺ��p �� p ��ǰ�� pre ,������������ϵ���Էֱ�� pre �� p ����һ������ 
		 if(p->l_child == NULL) {//���� p ǰ��   
			 p->l_thread = THREAD;
			 p->l_child = pre;   //���ڵ�һ����㣬pre = NULL; 
		 }
		 if(pre != NULL && pre->r_child == NULL){//����pre �ĺ��
			 pre->r_thread = THREAD;
			 pre->r_child = p;
		 }
		 /////////////////////////////////////// 
		 pre = p;               //pre  ���£���ס�����ϴη��ʵĽ�� 
		 inOrder_threading(p->r_child, pre);
	 }
}

 //�������������Ľ���,��������
void inOrder_threading() {
	 if(root){    
		 Node * pre = NULL;
		 inOrder_threading(root, pre);
		 pre->r_child = NULL;
		 pre->r_thread = THREAD;//���������һ�����,���һ���ڵ�� �������Ϊ�� 
		 
	 }
}

/*********************************************���������������Ľ���******************************************/	


/*********************************************���������������ı���******************************************/	
//�ԷǿյĽ��p�����������µĽ�㣬����Ӳ�����������һ��������� 
Node* find_most_left_node_thread(Node *p){
	 while(p->l_thread ==LINK){
	 	p = p->l_child;
	 }
     return p;
}

/*�ԷǿյĽ��x��������������µĺ�̽�� 
	���x�����Ӳ�����������x�������̶����������������µĵ�
    ����x������������ָ�룬����ָ��x�������̡�
*/ 
Node * inOrder_successor_thread(Node *x){
 	if(x->r_thread ==LINK){
 		return find_most_left_node_thread(x->r_child);
	 } 
	
	 return x->r_child;
}


 //������������,���ݹ�,���ø���ջ���������� 
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
/*********************************************���������������ı���******************************************/	


/*********************************************���������������Ľ���******************************************/
void postOrder_threading(Node * p,Node *& pre){

	 if(p){     	 
		postOrder_threading(p->l_child, pre); 
		postOrder_threading(p->r_child, pre);
		
		///////////////////////////////////// 
		if(p->l_child == NULL) {//���� p ǰ��   
			 p->l_thread = THREAD;
			 p->l_child = pre;    
		 }
		 if(pre != NULL && pre->r_child == NULL){//����pre �ĺ��
			 pre->r_thread = THREAD;
			 pre->r_child = p;
		 }
		 /////////////////////////////////////// 
		 pre = p;               //pre  ���� 
		 
		             
	 }
}

 //�������������Ľ���,��������
void postOrder_threading() {
	 if(root){    
		 Node * pre = NULL;
		 postOrder_threading(root, pre);
		 pre->r_child = NULL;
		 pre->r_thread = THREAD;//���������һ�����,���һ���ڵ�� �������Ϊ�� 
		 
	 }
}
/*********************************************���������������Ľ���******************************************/
/*********************************************���������������ı���******************************************/	
//�������Ҫʹ�ô�˫�׵���������


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
	 // pΪ����ӣ� ˵���丸�� �͸��׵��Ҷ��Ӷ���û���ʣ��ȷ��ʸ��׵��Ҷ��� 
	 Node *cur = p->parent;       //�������Ҫʹ�ô�˫�׵���������
	 //���׵��Ҷ���Ϊ�գ�����ֻ�ܷ��ʸ��� 
	 if(cur->r_child==NULL){
	 	return cur;
	 } 
	 cur = cur->r_child;
	 return  find_first_node_postOrder(cur);
 
 
 
 
 
	
}
/*********************************************���������������ı���******************************************/


	void visit(Node *node){
		cout<<node->data<<" ";
	} 
	
}; 


int main(void)  
{  
    Threaded_Binary_Tree a;
    cout<<"����һ�������ַ�����ABD#C#F##E��";
    string s;
	cin>>s; 
    a.CreateTree(s);
//    cout<<"ǰ�����:" ;
//    a.preOrder_threading();//���� 
//    a.preOrder_thread();//���� 
	cout<<"�������:" ;
	a.inOrder_threading();
	a.inOrder_thread() ; 

    return 0;
}
    











