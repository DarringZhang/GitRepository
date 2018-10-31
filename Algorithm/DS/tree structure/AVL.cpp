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
};

class AVL{
private:
	Node *root = NULL;
public:
	AVL(){	
	}
	
	
	Node *Create_Node(int v){
		Node *t = new Node;
		t->key = v ;
		t->left = NULL;
		t->right = NULL;
		return t;
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
	
	Node* BST_Minimum(Node* T)
	{
		while(T->left != NULL){
			T = T->left;
		} 
			
		return T;
	}
 /********************************************��ת****************************************/	
 	//ĳ����������ӵ��������в���һ����㣬��������������Ϊ�ᣬ˳ʱ�� ��ת 
 	Node* Left_Left_Rotation(Node *p){
 		Node* k1 = p->left;//k1Ϊ�ᣬp������ 
 		p->left = k1->right;//k1ԭ���ұߵĶ�����p ����ߣ�k1ԭ����λ�ã���k1�ұ߾Ϳճ�����
 		k1->right = p;      //k1�ұ߾ͽ� p 
 		p->height = MAX(Tree_Height(p->left),Tree_Height(p->right)) + 1;
 		k1->height = MAX(Tree_Height(k1->left), p->height) + 1;//����p �� k1�ĸ߶� 
 			
			 return k1; //�����¸� 
	 }
 	
 	//ĳ�������Ҷ��ӵ��������в���һ����㣬����������Ҷ���Ϊ�ᣬ��ʱ�� ��ת 
 	Node* Right_Right_Rotation(Node *p){
 		Node* k1 = p->right;
 		p->right = k1->left;
 		k1->left = p;      
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
	Node *AVL_Insert(Node *T,int v){
		if(T==NULL){
			T = Create_Node(v);
		}
		else if(v < T->key){
			T->left = AVL_Insert(T->left, v);//Ϊ v�Ĳ���λ��Ѱ���½�� 
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
		return T;
	}
/*************************************************����******************************************/



			
/********************************ɾ��******************************************/ 
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
		
		return p;
	
	}
 
	
	Node *AVL_Delete(Node *p,int v){
		if(p == NULL){
			cout<<"delete failed!"<<endl; 
		}
 		else if(v == p->key){ //ɾ�� ���� ����� 
 			Node*t = NULL; 
		 	if(p->right == NULL){//������Ϊ�գ�ֱ����������������ȥ�滻 
		 		t = p;          //��������� һ������ ������ ����ֵ�����Ի���Ϊһ�� 
		 		p = p->left;    //�������ղ��գ�����Ϊ��һ�� ���˷��������������Tree_Minimum��Ҳ�ɾ���ԳƷ��ࣩ 
		 		delete t;
		 	}
		 	else {
			 	t = BST_Minimum(p->right);//�������������µĵ㣨���������ȥ�������ƻ�BST ��С���죩 
			 	p->key = t->key;//���� Ҫɾ�� p  (��ʱp �� p �����������µ�ֵ��ͬ��ɾȥp �����������µ�)
			 	p->right = AVL_Delete(p->right,p->key);//�ﵽɾ�� p ��Ŀ�� 
			 }
		 }
		 else if(v < p->key){
		 	 p->left = AVL_Delete(p->left, v);
		 }
		
		 else{
		 	p->right = AVL_Delete(p->right, v);
		 }
		 
		 p->height = MAX(Tree_Height(p->left), Tree_Height(p->right)) + 1;
		 if(p == NULL){//ɾ���� ԭp �� ��ʣ����ǲ��ǿ�������ԭ���ǲ���ֻ��һ�����  
		 	 return p;
		 }

		 //do necessary rotate p->left, p->right and p, if they are not NIL����Ϊɾ��һ����㣬�ܿ��ܲ�ƽ�� 
		 //һ��һ����� 
		 if(p->left) {p->left = AVL_Delete_Fixup(p->left);} 
		 if(p->right){ p->right = AVL_Delete_Fixup(p->right);} 
		 if(p) {p = AVL_Delete_Fixup(p);} 
		 return p;
	
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
		printf("|                        10.�滻                                |\n");  
        printf("|                        11.���������ӡ                       |\n");  
        printf("|                        12.�˳�                               |\n");  
        printf("|--------------------------------------------------------------|\n");  
        printf("                        ��ѡ���ܣ�");  
        scanf("%d",&k);  
        switch(k)  
        {  
	        case 0:{
	        	printf("�뽨��BST����������Ҫ�����Ľ�������");
	            int s;
	            cin>>s; 
	            a.Create_Tree(s);
	            a.inOrder_No_Stack();
				break;
			}  
	        case 1 :{
	        	if(a.GetRoot())  
	            {  
	                printf("input the key you wanna insert:"); 
					int k;
					cin>>k; 
	                a.AVL_Insert(a.GetRoot(),k) 
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








