/*������ 
 	��i������� 2��i-1�����
	 ���Ϊk�Ľ�㣬�����2��k�η�-1�����
	 Ҷ�ӽڵ��� = ����Ϊ2�Ľ����+1
 �������� 
 	ȫ��������, �ڵ��� = 2��k�η�-1 
��ȫ������
    �������� һ������ 
*/ 

//˳�����飬��������ȫ������ �ͱȽϲ��˷ѿշ��䣩����ʽ 


//����ʵ����ʽ��
#include<iostream>
#include<string>
#include<queue>
#include<stack>
using namespace std;
struct Node{
	char  data;
	Node * l_child,*r_child;
}; 

class Binary{
private :
	Node * root  = NULL;
public:
	Binary(){
		root  = new Node;
		root->l_child = NULL;
		root->r_child = NULL;
		root->data = ' ';
	};
	
	~Binary(){ //using  BFS to release  all nodes 
	    queue<Node*> L;
	    Node * t = root;
 		L.push(t); //L is a queue.
 		while(!L.empty()){
 			t = L.front();  //������Ԫ�� 
 			L.pop(); 
 			if(t == NULL){
 				continue;
			 }  
 			L.push(t->l_child);  //������Ԫ�� ���������߽����� 
 			L.push(t->r_child);
 			delete t;  
		}
 
    }
	 


//����һ���������У�����Ѿ����������ĵ���û��ȷ�����Ҷ��ӵĽ�� 
//ÿ�δ��������ж�����Ԫ��,������Ԫ�ؾ�Ӧ���Ƕ��׽������Ҷ��� 
 //����������� 
void CreateTree(string s){
    queue<Node*> L ;
	int idx = 0;				
	
 	root->data = s[idx++] ;
 	L.push(root);   //L is a queue.
 	while( idx <s.length()){
	 	Node* node = L.front();  //ȡ����ǰ����Ԫ�� 
	 	L.pop();
	 	if (node == NULL) {    //������Ԫ���ǿյ� 
		 	idx += 2;           //��������������ŵ����������ǿյ� 
			continue;           //�����˴�ѭ�� 
		 }
		 
		 //node������ ��node ������� 
		
	 	char a = s[idx++];
	 	if ( a != '#'){//node ������Ӳ�Ϊ�� 
	 		node->l_child = new Node;
	 		node->l_child->data = a;
	 		node ->l_child-> l_child = NULL;
	 		node->l_child->r_child = NULL;
		}
	 	L.push(node->l_child);//�յ�ҲҪpush��ȥ����������idx+=2�����ս��������ն��� �� 
	 	
	 	if ( idx >=s.length()) break;//��ȡ��� 
	 	
	 	//��ȡδ��ϣ��������Ҷ��� 
	 
	 	a = s[idx++];
	 	if ( a != '#'){//node ���Ҷ��Ӳ�Ϊ�� 
	 		node->r_child = new Node;
	 		node->r_child->data = a;
	 		node ->r_child-> l_child = NULL;
	 		node->r_child ->r_child = NULL;
		}
	 	L.push(node->r_child);
	} 	
	cout<<"create finished!"<<endl; 
} 


void visit(Node *node){
	cout<<node->data<<" ";
} 

Node *GetRoot(){
	return root;
}





/*������
	BFS������� 
	DFS��ȱ���
		1.�ݹ飨Ч�ʵͣ� 
		2.�ǵݹ� 	 
*/ 


//BFS ������ʵ�֣� 
void LevelOrderTraverse(){
	queue<Node*> L ;
	if (root ==NULL){
		return;
	} 
	L.push(root); // L is a queue
	while(!L.empty()){
 		Node * node = L.front(); //ȡ������ 
 		L.pop();
 		if(node == NULL) continue;
 		L.push(node->l_child);
 		L.push(node->r_child);
 		visit(node); //����node��������
 	}
}

 //DFS
	 //1�ݹ� ��˼�룺ֻ�ǻ�visitλ�ã�ϵͳջ���ã� 
	 void  PreOrderTraverse( Node *p){
	 	if (p ==NULL) {
	 		return;
		 }
	 	visit(p);
	 	PreOrderTraverse(p->l_child);
	 	PreOrderTraverse(p->r_child);
	 }
	 void  InOrderTraverse( Node *p){
	 	if (p ==NULL) return;
	 	InOrderTraverse(p->l_child);
	 	visit(p);
	 	InOrderTraverse(p->r_child);
	 }
	void  PostOrderTraverse( Node *p){
	 	if (p ==NULL) return;
	 	PostOrderTraverse(p->l_child);
	 	PostOrderTraverse(p->r_child);
	 	visit(p);
	 }
	 

	//2.�ǵݹ�	
 /*ǰ�� ˼�룺�����ұ�����visit��ǰ��㣬�ж��ӵĻ�������һ��visit ���ӣ�ͬʱ����������ջ��ע������˳��
	 ����ջ�ĺ���ȳ����ص�,��������visit��  
 */ 
	 void PreOrder_Stack( Node *p){
	  if (p ==NULL){
		   return;
		} 
		
	 stack<Node*> s;
	 s.push(p);
	 while(!s.empty()){
	 	Node *t = s.top();
	 	s.pop();
	    if(t ==NULL) {continue;}
	 	visit(t);
	 	s.push(t->r_child);
	 	s.push(t->l_child);//ע��������������Ϊջ�� 
	 }
 }
	 
/*
	//����˼�� �����ø���ջ �����ұ���.��һ·�ҵ������µĽ�� 
*/	 
void InOrder_Stack( Node *p){
	 if (p ==NULL){
	 	return;
	 }
	 
	 stack<Node*> s;
	 s.push(p);
	 while(!s.empty()){
	    Node *t = s.top();
		 while(t){//���һ·��ջֱ�������µĿս�㣬��Ϊʼ�����ȷ�������� 
		 	s.push(t->l_child);
		 	t = s.top();
		 } 
		 //���һ��һ���ǿս�㣬��ջ 
		 s.pop(); //����һ��ѭ��������һ��������ǿյģ��ս����ջ
		 
		 if(s.empty()) {break;}//�����������һ���������꣬ջ�յ�ʱ���õ������򣬽����ŵ�pop���� 
		 
		 t = s.top();
		 s.pop();
		 visit(t);//�����Լ�
		 s.push(t->r_child); //��ǰ��������һ��һ���� �Ҷ��� �����Ҷ����߽�ȥ 
	 }
}

/*
	***hard!!��ΪҪ���ø��ڵ��ȷ�������Ӻ��Ҷ���,���Ա����
¼�ϴη��ʵĽ���ջ�����Ĺ�ϵ:����ϴη��������,
��ô���ڵ㻹���ܳ�ջ,Ҫ�����Ҷ��ӷ��ʺ�ų�ջ; ����ϴ�
���ʵ����Ҷ���,��˵�������������Ѿ��������,���ڵ��ջ)
      
       �жϸ��ڵ������ջ���� 
*/
	 
void  PostOrder_Stack(Node *p){
	if(p ==NULL){
		return;
	} 
	
	stack<Node*> s;
	Node * cur = p;//��ǰҪ���Ľ�� 
	Node *LastVisited = NULL; //ǰһ�������ʵĽ��
	
	while(cur) {            //ջ��ʱ���� 
		s.push(cur);      //���ȱ��� ��ߣ� ȫ�� l_child ����ջ 
		cur = cur->l_child;
	}
	
	while(!s.empty()){
		cur = s.top(); 
		s.pop();   
	
	 
	    
		//�����ǰ�����Һ���Ϊ�ջ��� �Ѿ�������,�����������Լ� ����������������������Ҫ�������� 
		if(cur->r_child == NULL||cur->r_child==LastVisited){
			visit(cur);
			LastVisited = cur;
		} 
		 
		else{//��ǰ����Ҷ��Ӳ�����δ���ʣ� ˵����ʱ���Լ������ܷ��� 
		 	s.push(cur);//�ղ� pop�� ��cur�Լ�����Ϊ��û�ֵ������Լ���Ҫ�ȷ����Ҷ��ӵģ�������pop�Լ������ڼӻ�����//����if �������Ҫpop �Լ� 
			 cur = cur->r_child;
			 while(cur){//�Ҷ��ӵ�ȫ����������ջ 
			 	s.push(cur);
				cur = cur->l_child; 
			 } 
		 	
		 }
	} 
}
};




int main(void)  
{  
    Binary a; 
    int flag=1,k;  
    printf("                     ������ʵ�ֶ������Ļ���������\n");  
    printf("���Խ��н������������ݹ��������򡢺���������ǵݹ���������, ����������ǵݹ��������Ȳ�����\n");  
  
    while(flag)  
    {  
        printf("\n");  
        printf("|--------------------------------------------------------------|\n");  
        printf("|                    �������Ļ�����������:                     |\n");  
        printf("|                        0.����������                          |\n");  
        printf("|                        1.�ݹ��������                        |\n");  
        printf("|                        2.�ݹ��������                        |\n");  
        printf("|                        3.�ݹ�������                        |\n");  
        printf("|                        4.�ǵݹ��������                      |\n");  
        printf("|                        5.�ǵݹ��������                      |\n");  
        printf("|                        6.�ǵݹ�������                      |\n");  
        printf("|                        7.�ǵݹ�������                      |\n");  
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
	        case 1 :{
	        	if(a.GetRoot())  
	            {  
	                printf("�ݹ���������������Ľ��Ϊ��");  
	                a.PreOrderTraverse(a.GetRoot()) ; 
	                printf("\n");  
	            }  
	            else  
	                printf("          ������Ϊ�գ�\n");  
	            break;  
			
			}    
	        case 2: {
	        	if(a.GetRoot())  
	            {  
	                printf("�ݹ���������������Ľ��Ϊ��");  
	                a.InOrderTraverse(a.GetRoot()) ;
	                printf("\n");  
	            }  
	            else  
	                printf("          ������Ϊ�գ�\n");  
	            break;  
			} 
	            
	        case 3: {
	        	if(a.GetRoot())  
	            {  
	                printf("�ݹ��������������Ľ��Ϊ��");  
	                a.PostOrderTraverse(a.GetRoot()) ;
	                printf("\n");  
	            }  
	            else  
	                printf("          ������Ϊ�գ�\n");  
	            break;  
			} 
	            
	        case 4:  {
	        	 if(a.GetRoot())  
	            {  
	                printf("�ǵݹ����������������");  
	                a.PreOrder_Stack(a.GetRoot()) ; 
	                printf("\n");  
	            }  
	            else  
	                printf("          ������Ϊ�գ�\n");  
	            break;  
			}
	           
	        case 5:  {
	        
	            if(a.GetRoot())  
	            {  
	                printf("�ǵݹ����������������");  
	                a.InOrder_Stack(a.GetRoot());
	                printf("\n");  
	            }  
	            else  
	                printf("          ������Ϊ�գ�\n");  
	            break;  
			}
	        case 6: {
	        if(a.GetRoot())  
	            {  
	                printf("�ǵݹ���������������");  
	                a.PostOrder_Stack(a.GetRoot())  ;
	                printf("\n");  
	            }  
	            else  
	                printf("          ������Ϊ�գ�\n");  
	            break;  
			} 
	            
	        case 7:{
	        	if(a.GetRoot())  
	            {  
	                printf("�ǵݹ���������������");  
	 				a.LevelOrderTraverse();
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












