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
	
	Node* BST_Minimum(Node* T)
	{
		while(T->left != NULL){
			T = T->left;
		} 
			
		return T;
	}
 /********************************************旋转****************************************/	
 	//某个结点的左儿子的左子树中插入一个结点，以这个结点的左儿子为轴，顺时针 旋转 
 	Node* Left_Left_Rotation(Node *p){
 		Node* k1 = p->left;//k1为轴，p折下来 
 		p->left = k1->right;//k1原来右边的东西给p 的左边（k1原来的位置），k1右边就空出来的
 		k1->right = p;      //k1右边就接 p 
 		p->height = MAX(Tree_Height(p->left),Tree_Height(p->right)) + 1;
 		k1->height = MAX(Tree_Height(k1->left), p->height) + 1;//更新p 和 k1的高度 
 			
			 return k1; //返回新根 
	 }
 	
 	//某个结点的右儿子的右子树中插入一个结点，以这个结点的右儿子为轴，逆时针 旋转 
 	Node* Right_Right_Rotation(Node *p){
 		Node* k1 = p->right;
 		p->right = k1->left;
 		k1->left = p;      
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
	Node *AVL_Insert(Node *T,int v){
		if(T==NULL){
			T = Create_Node(v);
		}
		else if(v < T->key){
			T->left = AVL_Insert(T->left, v);//为 v的插入位置寻找新结点 
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
		return T;
	}
/*************************************************插入******************************************/



			
/********************************删除******************************************/ 
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
		
		return p;
	
	}
 
	
	Node *AVL_Delete(Node *p,int v){
		if(p == NULL){
			cout<<"delete failed!"<<endl; 
		}
 		else if(v == p->key){ //删掉 “根 ”结点 
 			Node*t = NULL; 
		 	if(p->right == NULL){//右子树为空，直接拿它的左子树上去替换 
		 		t = p;          //因其这个点 一定大于 左子树 所有值，可以划分为一类 
		 		p = p->left;    //左子树空不空，划分为另一类 （此分类依据是下面的Tree_Minimum，也可镜像对称分类） 
		 		delete t;
		 	}
		 	else {
			 	t = BST_Minimum(p->right);//找右子树最左下的点（这个点提上去，不会破坏BST 大小构造） 
			 	p->key = t->key;//赋给 要删的 p  (这时p 和 p 右子中最左下点值相同，删去p 右子中最左下点)
			 	p->right = AVL_Delete(p->right,p->key);//达到删除 p 的目的 
			 }
		 }
		 else if(v < p->key){
		 	 p->left = AVL_Delete(p->left, v);
		 }
		
		 else{
		 	p->right = AVL_Delete(p->right, v);
		 }
		 
		 p->height = MAX(Tree_Height(p->left), Tree_Height(p->right)) + 1;
		 if(p == NULL){//删除了 原p 后 看剩余的是不是空树，即原来是不是只有一个结点  
		 	 return p;
		 }

		 //do necessary rotate p->left, p->right and p, if they are not NIL，因为删除一个结点，很可能不平衡 
		 //一层一层纠正 
		 if(p->left) {p->left = AVL_Delete_Fixup(p->left);} 
		 if(p->right){ p->right = AVL_Delete_Fixup(p->right);} 
		 if(p) {p = AVL_Delete_Fixup(p);} 
		 return p;
	
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
		printf("|                        10.替换                                |\n");  
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








