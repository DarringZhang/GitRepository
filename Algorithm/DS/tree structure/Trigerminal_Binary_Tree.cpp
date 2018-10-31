//���ڶ�������ʵ�ֵ�2����������Ҫ�������ռ�: ����(�ݹ�) ���� ����.
//��������,�Ȳ��ø���ջҲ���õݹ� ��ϵͳջ�� 


                 /*ָ�򸸽ڵ��ָ�� */
				 
				 
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
	
	
	
	//ֻ�Ǳȶ������Ĵ���   ��ÿ������ڶ���parent =NULL ��ָ�򸸽ڵ��ָ�� 
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


//�����������ȱ�������Ȼ���Եݹ�����ɡ��������̺Ͷ�������汾û���κ�����
//���Ƿǵݹ�汾   ���ø���ջҲ���õݹ�
/********************************************* ����ǰ�� ******************************************/ 
void preOrder_No_Stack() {
	 if(root == NULL) {
	     return;
	 }
	 Node* cur = root; //������
	 do{
		 visit(cur) ;//�ȷ��ʵ�ǰ 
		 cur = preOrder_Successor(cur);//���Һ�� 
	 }while(cur != NULL);
 }
 
Node *preOrder_Successor(Node* p){
	//p����ж��ӣ����һ����ֱϵ���� 
	if(p->l_child){
		return  p->l_child;	
	} 
	else if(p->r_child){
		return p->r_child;
	}
	//p ΪҶ�ӽ�� ���Ϊ���׽����Ҷ��ӡ����Ҷ���Ϊ�� ���� p��Ϊ���׵��Ҷ��ӣ�Ϊ���������Ǹ�ת�۵���Ҷ��� 
	Node *y = p->parent; 
	while(y->r_child==NULL||p == y->r_child){//��������ֱ��  ָ������->���� 
		p = y;
		y = y->parent;
		if(y==NULL){ //y������Ϊ���ڵ��ˣ������yҪôû����������Ҫôy�������Ǵ��ұ��������ģ�y�Ķ��� p�ĺ�̾���NULL 
			return NULL;
		} 
	} 
	return y->r_child;   
}

/********************************************* ����ǰ�� ******************************************/ 

/********************************************* �������� ******************************************/ 
/* �������� 
	1) �ҵ������������µĽ��p;
	2) visit(p); p = inorder_successor(p);
	3) ����2),ֱ�� p û�к��(p == NULL).
*/ 
 void inOrder_No_Stack() {
	 if(root == NULL) {
	     return;
	 }
	 Node* cur = find_most_left_node(root); //�����ң��ȴ������µĽ�� 
	 do{
		 visit(cur) ;//���ȷ��������µĵ� 
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
	 if(x->r_child != NULL){//���x���ҽ�㣬����������x���������������µĵ�
	 	return find_most_left_node(x->r_child);
	 }
 
 //�������x�����Ƚ���е�ĳ���� 
     Node *p = x->parent;
	 while(p != NULL && x == p->r_child){//������Ѱ��һֱ��x �������� ����p������� Ϊ���� 
		 x = p;                         //��x ������ӣ���̾������ĸ��ס�
		 p = p->parent;            		 //��x ���Ҷ��ӣ�������ָ�����Ѿ�����һ�����ʣ� ��Ҫ˳�����ϣ�ֱ������ ����->���� 
	 }
	 return p;
 }
  /********************************************* �������� ******************************************/ 
  
  
  
  /********************************************* ������� ******************************************/ 
  void postOrder_No_Stack() {
	 if(root == NULL) {
	     return;
	 }
	 Node* cur  = find_first_node_postOrder(root); //�����У����ʱ���һ���Ͳ�һ���������µĵ㣨�������� �����ң� 
	 do{                                       //�����������ӿգ�������ѭ���������Լ�����һ��Ҫ�����Լ� 
		 visit(cur);                          // ��������ӿգ������ܷ����Լ������Ҷ��Ӿ�Ҫ���Ҷ����� 
		 cur = postOrder_Successor(cur);                //�����Ҷ��Ӻ͸��������ߵ�   ���ȼ� �����仯 
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
	 
	 	//p Ϊ�Ҷ��ӣ���̼���ǰ���ĸ��� 
	 if(p == p->parent->r_child){
	 	return p->parent;
	 } 
	 // pΪ����ӣ� ˵���丸�� �͸��׵��Ҷ��Ӷ���û���ʣ��ȷ��ʸ��׵��Ҷ��� 
	 Node *cur = p->parent;
	 //���׵��Ҷ���Ϊ�գ�����ֻ�ܷ��ʸ��� 
	 if(cur->r_child==NULL){
	 	return cur;
	 } 
	 cur = cur->r_child;
	 return  find_first_node_postOrder(cur);
 }
 
  /********************************************* ������� ******************************************/ 	
  
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
    printf("                     ������ʵ���������Ļ���������\n");  
    printf("���Խ��н������������ǵݹ鲻�ø���ջ��������, �������������\n");  
  
    while(flag)  
    {  
        printf("\n");  
        printf("|--------------------------------------------------------------|\n");  
        printf("|                    �������Ļ�����������:                     |\n");  
        printf("|                        0.����������                          |\n");  
        printf("|                        4.�ǵݹ鲻�ø���ջ�������                      |\n");  
        printf("|                        5.�ǵݹ鲻�ø���ջ�������                      |\n");  
        printf("|                        6.�ǵݹ鲻�ø���ջ�������                      |\n");   
        printf("|                        8.�˳�����                            |\n");  
        printf("|--------------------------------------------------------------|\n");  
        printf("                        ��ѡ���ܣ�");  
        scanf("%d",&k);  
        switch(k)  
        {  
	        case 0:{
	        	printf("�뽨��������������һ�������ַ�����ABD#C#F##E��");
	            string s;
	            cin>>s; 
	            a.CreateTree(s);
				break;
			}  
	        
	        case 4:  {
	        	 if(a.GetRoot())  
	            {  
	                printf("�ǵݹ鲻�ø���ջ���������������");  
	                a.preOrder_No_Stack(); 
	                printf("\n");  
	            }  
	            else  
	                printf("          ������Ϊ�գ�\n");  
	            break;  
			}
	           
	        case 5:  {
	        
	            if(a.GetRoot())  
	            {  
	                printf("�ǵݹ鲻�ø���ջ���������������");  
	                a.inOrder_No_Stack();
	                printf("\n");  
	            }  
	            else  
	                printf("          ������Ϊ�գ�\n");  
	            break;  
			}
	        case 6: {
	        if(a.GetRoot())  
	            {  
	                printf("�ǵݹ鲻�ø���ջ���������������");  
	                a.postOrder_No_Stack()  ;
	                printf("\n");  
	            }  
	            else  
	                printf("          ������Ϊ�գ�\n");  
	            break;  
			} 
	        
			case 8:{
				flag=0;  
	            printf("�����������У���������˳���\n");  
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

