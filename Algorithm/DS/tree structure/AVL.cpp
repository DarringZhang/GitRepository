//AVL�ڶ���������Ļ������������ת�㷨��������ת���������ı�����ָ���ָ�򣬺ķѳ���ʱ�䣬���Ӷ�ֻ��n�й� 
//�Ա�BST��ʱ�����ȶ��˺ܶ�,BST ������˳��ͬ �����Ľṹ��ͬ������ һ�ߵ������������Ӷ��������й� 

/*AVL��(�߶�ƽ����)���Ǹ�BST�������㣬�����κ�1�����еĽڵ�x���������Ⱥ������ȵĲ����1.
ÿ�β��½ڵ�󣬵ݹ��ͨ������תrotation�������������ڵ㣬ʹ������AVL���Ļ���Ҫ��
	
	Υ��AVL����Ҫ�������������
1) ��ĳ���ڵ�����ӵ��������в�ڵ�
2) ��ĳ���ڵ�����ӵ��������в�ڵ�
3) ��ĳ���ڵ��Ҷ��ӵ��������в�ڵ�
4) ��ĳ���ڵ��Ҷ��ӵ��������в�ڵ�
     ���ܽ�����Ҳ��������������� and ���ң���������Գƣ� 
*/ 
#include<iostream>
using namespace std;

struct Node { 
	int key;
	Node *left ,*right;
	int height;//��¼�˽�����߶ȣ��ս�㣬�߶���0 

	Node* parent;
};


class BST{
protected:
	Node *root = NULL;
public:
	
	BST(){	
	}


	
 //����������BST	
void Create_BST( int n){ 
	int value;                   
	cout<<"please input the keys:";
	for(int i=0; i<n; ++i){
		cin>>value;
		BST_Insert_NonRecur(root,value);
	}	
}



//������½��һ����ĳ��Ҷ��㣬��Ϊһ�ֶ�̬�ṹ���Ȳ�����ֵ���ظ����ٲ���	
//�ݹ����	
int BST_Insert(Node*T, int k, Node* l_parent = NULL){
	if(T == NULL)
	{
		T = new Node;
		T->key = k;
		T->left = NULL;
		T->right = NULL;
		T->parent = l_parent;
		return 1;  // ����1��ʾ�ɹ�
	}
	else if(k == T->key)
		return 0;  // ���д�����ͬ�ؼ���
	else if(k < T->key)
		return BST_Insert(T->left, k, T);
	else
		return BST_Insert(T->right, k, T);
}
 	
//�ǵݹ���루Ч�ʸߣ�	
int BST_Insert_NonRecur(Node* T, int k){
	Node* pre = NULL;  // ��¼��һ�����
	Node* t = T;
	//�ƶ�������λ�� 
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
		root = node; //��������Ǹ��ڵ� 
	else
	{
		if(k < pre->key)  //�жϲ���߻����ұ� 
			pre->left = node;
		else
			pre->right = node;
	}
	return 1;
}



//BST Search
/*
	Search sth�����⣬�������������֧���� Minimum����Сֵ����Maximum�����ֵ����
	Predecessor��ǰ������Successor����̣��Ȳ�ѯ�����ڸ߶�Ϊ h ��������Щ������������ ��(h) ʱ������ɡ�
*/ 

 
 //�ݹ� search ĳ��ֵ 
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
//�ǵݹ� search ĳ��ֵ 
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
 * ��Сֵ�����Ҷ���������йؼ�����С�Ľ��
 */
Node* BST_Minimum(Node* T)
{
	while(T->left != NULL)
		T = T->left;
	return T;
}

/**
 * ���ֵ�����Ҷ���������йؼ������Ľ��
 */
Node* BST_Maximum(Node* T)
{
	while(T->right != NULL)
		T = T->right;
	return T;
}


/**
 * ��̣����Ҹ����������������еĺ�̽��
 */
Node* BST_Successor(int k)
{
	Node *node = BST_Search_NonRecur(root, k);
	if(node->right != NULL){//x ����������Ϊ�գ��� x �ĺ�̾��������������������µĵ㣨���ؼ���ֵ��С�Ľ�㣩��
		return BST_Minimum(node->right);
	} 
	
	//�ҽڵ�Ϊ��	
	Node* p = node->parent;
	while(p!=NULL && p->right == node)//ֻҪ��û�����ڵ㣬����node ����p ���Ҷ��ӣ������ң�˵�����ĸ����Ѿ������ʣ���Ҫ˳�� 
	{                                 // ֱ�����p ���Ҷ��� 
		node = p;
		p = p->parent;
	}
	return p;
}

/**
 * ǰ�������Ҹ����������������е�ǰ�����
 */
Node* BST_Predecessor(int k)//���Һ�̾���Գ� 
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
�����������ɾ����������Ը���һ�㣬��Ҫ�� 3 �����������ɾ��(Deletion):��T��ɾ��?���ڵ�z,�������
1) zû�к���, �򵥽��丸�ڵ��ָ�� z��ָ���滻ΪNIL;
2) zֻ��1������ ��z�������������Ϊz�ĸ��׵ĺ���,ȡ��z��λ��;
3) z�������� ����z��������y(��Ȼ��z��������), yȡ��z��λ��, z��������ʣ�µĲ��ֳ�Ϊy����������,z����
   �����y��������. (����������Ƚϸ��ӣ�ȡ����y�ǲ���z���Һ�)
*/ 
      
	  //����1��������Ժϲ���2 ����Ϊ������NULLȡ��z ��λ�ã� 
      
      
      
      //����
    void Transplant(Node *T, Node *u,Node *v){ //��T�У���vΪ���������滻��uΪ����������
    	if(u->parent==NULL){ // u ��Ϊ �� T , v �滻���� 
    		//T = v; 
    		root = v;// ������� T ��Ȼ����������root���� T�Ǿֲ��������������������ʧ������ �øĸø��ڵ� 
		}
		else if(u = u->parent->left){//u�� ����� 
			u->parent->left = v;//v�滻����� 
		}
		else{
			u->parent->right = v; 
		} 
		if(v!=NULL){
			v->parent = u->parent; //��������ÿ���������v�ĸ��׽��Ҫ������ 
		}
	}
	
	void Delete(int k){
		 Node *z = BST_Search_NonRecur(root,k); 
		 //���ΪҶ�ӽڵ� 
		 if(z->left==NULL&&z->right==NULL){
		 	if(z==z->parent->left){
		 		z->parent->left = NULL;
			 }
			 else if(z==z->parent->right){
			 	z->parent->right = NULL;
			 }
		 }
		 //������Ϊ�� 
		 else if(z->left==NULL){
		 	Transplant(root,z,z->right);//���û�������Ҷ�ӽڵ���жϣ����� Transplant �Ƿ����ʣ��ͻ���ֶδ��� 
		 } 
		 //������Ϊ�� 
		 else if(z->right==NULL){
		 	Transplant(root,z,z->left);
		 }
		 else{//z���Ҷ���Ϊ�� 
		 	Node *y = BST_Minimum(z->right);//�ó��ұ���С������������ ��ת���ɵ�һ��if �����(Ҳ�������ұ����ģ��ڶ���if) 
		 	if(y->parent!=z){//�����µĵ�� z��ֱ������ ��ֱ�������Ļ���y ��ΪҶ�ӣ�ֱ�ӽ���z �����z�� 
		 		Transplant(root,y,y->right);  //�������Ľ�� y ������� 
		 		y->right = z->right; // ��Ҫɾ�Ľ��z �ұ� ��z �Ͽ����ӵ��½����
				 y->right->parent = y;//���׽��ָ�� 
			 }//���������ɹ� 
			 Transplant(root,z,y);
			 y->left = z->left;
			 y->left->parent = y; 
		 } 
	} 
	
	
	void Modyfiy(int old,int newer){
		Node *oldnode = BST_Search_NonRecur(root, old);
		Node *newernode = BST_Search_NonRecur(root, newer);
		if(newernode==NULL){//˵��û��ԭ����û����֮�ظ��Ľ�� 
			//�޸�ĳ��ֵ��Ҫ��������������λ��, �� oldnode->key = newer�ĸ�ֵ  �в�ͨ;
			Delete(old);
			BST_Insert_NonRecur(root,newer);
		}
		else{
			cout<<"there is already has such newer keys,can��t repeate��"<<endl;
		} 
		
	}
	
	/********************************************* ������� ******************************************/ 
/* ���� 
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
	 	cout<<endl;
 }
 
 Node* find_most_left_node(Node *p){
	 while(p->left != NULL){
	 	p = p->left;
	 }
    return p;
}
 
 Node* inOrder_Successor(Node *x){
	 if(x->right != NULL){//���x���ҽ�㣬����������x���������������µĵ�
	 	return find_most_left_node(x->right);
	 }
 
 //�������x�����Ƚ���е�ĳ���� 
     Node *p = x->parent;
	 while(p != NULL && x == p->right){//������Ѱ��һֱ��x �������� ����p������� Ϊ���� 
		 x = p;                         //��x ������ӣ���̾������ĸ��ס�
		 p = p->parent;            		 //��x ���Ҷ��ӣ�������ָ�����Ѿ�����һ�����ʣ� ��Ҫ˳�����ϣ�ֱ������ ����->���� 
	 }
	 return p;
 }
  /********************************************* �������******************************************/
  
  
	void visit(Node *node){
		cout<<node->key<<"-��"<<node->height<<" ";
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
	
	
	int Tree_Height(Node *p){//�������ĸ߶� 
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
	

 /********************************************��ת****************************************/	
 	//ĳ����������ӵ��������в���һ����㣬��������������Ϊ�ᣬ˳ʱ�� ��ת 
 	Node* Left_Left_Rotation(Node *p){
 		Node* k1 = p->left;//k1Ϊ�ᣬp������ 
 		p->left = k1->right;//k1ԭ���ұߵĶ�����p ����ߣ�k1ԭ����λ�ã���k1�ұ߾Ϳճ�����
 		if(k1->right){
 			k1->right->parent = p;
		 }
 	
 		k1->right = p;      //k1�ұ߾ͽ� p 
 		p->parent = k1;
 		p->height = MAX(Tree_Height(p->left),Tree_Height(p->right)) + 1;
 		k1->height = MAX(Tree_Height(k1->left), p->height) + 1;//����p �� k1�ĸ߶� 
 			
			 return k1; //�����¸� 
	 }
 	
 	//ĳ�������Ҷ��ӵ��������в���һ����㣬����������Ҷ���Ϊ�ᣬ��ʱ�� ��ת 
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
	 
	 
	 //��ĳ���������ӵ������в���(LR)�Ըý������ӵ�������Ϊ�ᣬ��ʱ����ת;���߱��ֱ�ߣ����Ըý���������ӣ�������ĵ㣬���ո�ת�����ĵ㣩Ϊ�ᣬ˳ʱ����ת;
	Node* Left_Right_Rotation(Node *p){
		p->left = Right_Right_Rotation(p->left);
 		return Left_Left_Rotation(p);
	}
 
	//��ĳ������Ҷ��ӵ������в���(RL)
	Node* Right_Left_Rotation(Node *p){
		p->right = Left_Left_Rotation(p->right);
 		return Right_Right_Rotation(p);
	}
/********************************************��ת*******************************************/		
	

/*************************************************����******************************************/	
	Node *AVL_Insert(Node * T,int v){
		if(T==NULL){
			T = Create_Node(v);
		}
		else if(v < T->key){
			T->left = AVL_Insert(T->left, v);//Ϊ v�Ĳ���λ��Ѱ���½�� 
			T->left->parent = T;
			if(Tree_Height(T->left) - Tree_Height(T->right) == 2){//��߲���� ���� 
				if(v < T->left->key){     //���뵽����ˣ�����ʽ��ƽ�� 
					T = Left_Left_Rotation(T);
				}
			
				else{    //����ʽ��ƽ�� 
					T = Left_Right_Rotation(T);
				}
			
		 	}
		}
		else if(v > T->key){
			T->right = AVL_Insert(T->right, v);//Ϊ v�Ĳ���λ��Ѱ���½�� 
			T->right->parent = T;
			if(Tree_Height(T->right) - Tree_Height(T->left) == 2){//�ұ߲���� ���� 
				if(v < T->left->key){ //����ʽ��ƽ�� 
					T = Right_Left_Rotation(T);
				}
			
				else{   // ����ʽ��ƽ�� 
					T = Right_Right_Rotation(T);
				}
			
		 	}
		}	
		else{
			//v == Root->key, insert failed->
			cout<<"insert failed��"<<endl;
		} 
			
		T->height = MAX(Tree_Height(T->left), Tree_Height(T->right)) + 1;
		this->root = T;
		root->parent = NULL;
		return T;
	}
/*************************************************����******************************************/



			
/********************************ɾ��******************************************/ 
//AVL������ɾ������������������ɾ���������ƣ�ֻ��ɾ���ڵ�������ʧȥƽ���ԣ���Ҫ��ƽ�⴦��




	Node *AVL_Delete_Fixup(Node *p){//������ƽ����� 
		if(Tree_Height(p->left) - Tree_Height(p->right) == 2){//������ 
			if(Tree_Height(p->left->left) >= Tree_Height(p->left->right)){//������ 
				p = Left_Left_Rotation(p);
			}
		 
		 	else{//������ 
		 	 	p = Left_Right_Rotation(p);
		 	}	
		}
		 
		else if(Tree_Height(p->right) - Tree_Height(p->left) == 2) {//������ 
		 	if(Tree_Height(p->right->left) >= Tree_Height(p->right->right)){// ������ 
				p = Right_Left_Rotation(p);
			}
		 
		 	else{//������ 
		 	 	p = Right_Right_Rotation(p);
		 	}	
		}
		this->root = p;
		root->parent = NULL;
		return p;
	
	}
 
	
	void *AVL_Delete(Node *p,int v){
		if(p == NULL){//�������� 
			cout<<"delete failed!"<<endl;
		}
 		if(v< p->key){//���������в��� 
 			AVL_Delete(p->left,v);
 			AVL_Delete_Fixup(p);
		}
		else if(v>p->key){
			AVL_Delete(p->right,v);
 			AVL_Delete_Fixup(p);
		}
		else{//�ҵ�Ҫɾ����Ԫ��
			if(p->left==NULL){ //������Ϊ��	
				Node* t = p;
				if(p==p->parent->left){
					p->parent->left = NULL;
				}
				else if(p==p->parent->right){
					p->parent->right = NULL;
				}
				p = p->right;         //���Һ��Ӵ���˽ڵ�
				delete t;            //�ͷ��ڴ�
				t = NULL;
			}
			else if(p->right==NULL){  //������Ϊ��
				Node* t = p;
				if(p==p->parent->left){//���ÿգ��ͻ����ָ�򣬵���p->parent->left ��Զ ��Ϊ�գ�����Ҫ�ÿ� 
					p->parent->left = NULL;
				}
				else if(p==p->parent->right){
					p->parent->right = NULL;
				}
				p = p->left;       //�����Ӵ���˽ڵ�
				delete t;  
				t = NULL;  
			}
			else {  //������������Ϊ��
				//һ���ɾ����������������������� �� ����������С���� ����ýڵ�, �ŷ���BST�Ĵ�С˳�� 
				Node * t = this->BST_Maximum(p->left); 
				p->key = t->key;
				AVL_Delete(p->left,t->key);//�ݹ��ɾ���ý�� 
			} 
			
		}
	//���½ڵ�ĸ߶�
	if(p){
		p->height = MAX(Tree_Height(p->left), Tree_Height(p->right)) + 1;
	}
	
	
	}
 /********************************ɾ��******************************************/ 
 
 	
 
};


//���۲���BST�Ƚ���Щ������ʱ�䣩������ ���� �� ɾ���������̳�BST 
int main(void)  
{  
    AVL a; 
    int flag=1,k;  
    printf("                         ������ʵ��AVL�Ļ���������\n");  
    printf("���Խ��� ����AVL����ת���룬�ݹ���ң��ǵݹ���ң����������С����ǰ�����Һ�̣�ɾ�����滻�������ӡ������\n");  
  
    while(flag)  
    {  
        printf("\n");  
        printf("|--------------------------------------------------------------|\n");  
        printf("|                      AVL�Ļ�����������:                      |\n");  
        printf("|                        0.����AVL                             |\n");  
        printf("|                        1.����                                |\n");  
        printf("|                        3.�ݹ����                            |\n");  
        printf("|                        4.�ǵݹ����                          |\n");  
        printf("|                        5.���                                |\n");  
        printf("|                        6.��С                                |\n");  
        printf("|                        7.ǰ��                                |\n");  
        printf("|                        8.���                                |\n");  
        printf("|                        9.ɾ��                                |\n");
		printf("|                        10.�滻                               |\n");  
        printf("|                        11.���������ӡ                       |\n");  
        printf("|                        12.�˳�                               |\n");  
        printf("|--------------------------------------------------------------|\n");  
        printf("                        ��ѡ���ܣ�");  
        scanf("%d",&k);  
        switch(k)  
        {  
	        case 0:{
	        	printf("�뽨��AVL����������Ҫ�����Ľ�������");
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
	                printf("          BSTΪ�գ�\n");  
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
	                printf("          BSTΪ�գ�\n");  
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
	                printf("          BSTΪ�գ�\n");  
	            break;  
			}
	           
	        case 5:  {
	        
	            if(a.GetRoot())  
	            {  
	                printf("Maxinum is ��");  
	                cout<<a.BST_Maximum(a.GetRoot())->key;
	                printf("\n");  
	            }  
	            else  
	                printf("          BSTΪ�գ�\n");  
	            break;  
			}
	        case 6: {
	        if(a.GetRoot())  
	            {  
	                printf("Mininum is ��");  
	                cout<<a.BST_Minimum(a.GetRoot())->key;
	                printf("\n");  
	            }  
	            else  
	                printf("          BSTΪ�գ�\n");  
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
	                printf("          BSTΪ�գ�\n");  
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








