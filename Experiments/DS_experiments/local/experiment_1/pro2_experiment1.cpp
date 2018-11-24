/*
	subject：Data Structure 
	To: experiment1_problem2
	Creator: 张丹颖2017011760
	date:2018.10.08
*/ 

#include<iostream>
using namespace std;

struct Node{
		int data;
		Node * next = NULL;
	};
	
class LinkList{
private:
	int len  ;
	Node *phead = NULL;
	Node *ptail = NULL;
	
public:
	LinkList (){//构造 
		phead = new Node;
		ptail = phead;
	}
	
	~LinkList (){//析构 
		delete phead ;
		phead = NULL;	
	}
	
	Node* getHead(){
		return phead;
	}
	
	//初始化链表		
	void Create_List(){//头结点不存放有效数据 ，尾结点的指针域指向空  
		len = 0;
		Node *p = phead;
		cout<<"create a LinkList(5)"<<endl;
		for(int i=0;i<5;++i){
			Node *pnew = new Node;
			cin>>pnew->data;
			pnew->next = NULL;
			
		 	p->next = pnew;
			p = p->next;
			len++;
		}
	
		ptail = p;//尾指针
	}
	
	//第一个元素之前插入
	void InsertHead(int d){//即在phead后插入一个结点
		Node* newphead =new Node;
		newphead->next = phead->next;//新结点指向原来的phead的下一个结点
		phead->next = newphead;//更新phead的下一个结点为这个新结点
		newphead->data = d;
		len++;
	}
	
   //最后一个元素之后插入新数据 
	void InsertTail(int d){//定义了ptail不需要再遍历
		Node * newPtail  = new Node;
		newPtail->next = NULL;	
		newPtail->data = d;
		ptail->next = newPtail;//直接在结尾ptail后追加新结点
		ptail = newPtail;//更新ptail
		len++;
	}
	
	//删除头结点，即删除phead紧接的那个结点
	int DeleteHead(){
		int datatemp;
		Node* p;
		datatemp = phead->next->data ;//存储删除那个结点的数据域
		p = phead->next;
		phead->next = phead->next->next;//断开phead和它的直接后继
	
		delete p;
		p = NULL;
		
		len--; 
		return datatemp; 
		
	}
	
	//删除尾结点
	int DeleteTail(){
		Node* p = phead->next;
		for(int i =0;i<len-2;++i){//遍历到尾结点的上一个结点
			p = p->next;
		}
		int datatemp = p->next->data;	

		ptail = p;//更新ptail
		p = p->next;
		ptail->next = NULL;//注意！ 更新尾结点的指针域
		delete p;
		p = NULL;
		len--;
		return datatemp;
	}
	
	//查找表中是否有特定元素
	int LocateItem(int num){
		Node* p = phead->next; 
		int i=0;
		for( i=0;i<len;++i){  //遍历寻找
			if(p->data == num){
				
				return i;
			}
			p = p->next;
		}
		
			return -1;
		
	}
	
	
	//表中特定元素之前插入 （包含在第一个元素之前插入） 
	void InsertBefore(int idx,int num){
		if(idx==0) {				//判断是不是再第一位插入（即替换phead的后继） 
			Node* newphead =new Node;
			newphead->next = phead->next;//newphead指向原phead的后继
			phead->next = newphead;		//phead指向newphead
			newphead->data = num;
			len++;
			cout<<"insert  Before successfully!"<<endl;
		}
		else if(idx>=0&&idx<len)//除了插入第一位后的任意位置插入 
		{
			Node* p = phead->next; 
				for(int i=0;i<idx-1;++i){//遍历到指定结点的上一个结点
				p = p->next;
			}
			
			Node *newnode = new Node; 
			newnode->next =NULL; 
			newnode->data = num;
			
			newnode->next = p->next ;//新结点的指针域指向指定结点上一个结点的指针域
			p->next = newnode; //更新指定结点上一个结点的指针域
			
			len++;
			cout<<"insert  Before successfully!"<<endl;
		}
		else{
			cout<<"input illegal!"<<endl;
		}
		
	}
	
	// 表中特定元素之后插入 (包含最后一个元素之后插入)
	void InsertBack(int idx,int num){
		if(idx==len-1){               //判断是不是在尾结点之后加入 
			Node * newPtail = new Node;
			newPtail->next = NULL;
			
			newPtail->data = num;
			ptail->next = newPtail;//尾结点后面追加
			ptail = newPtail;
			len++;
			cout<<"insert  Before successfully!"<<endl;
		}	
		else if(idx>=0&&idx<len){
			Node* p = phead->next; 
			for(int i=0;i<idx;++i){//遍历到指定结点，在下一个结点插入
				p = p->next;
			}
			
			Node *newnode = new Node; 
			newnode->next =NULL; 
			newnode->data = num;
			
			newnode->next = p->next; 
			p->next = newnode; 
			
			len++;
			cout<<"insert  Before successfully!"<<endl;		
		}
		else{
			cout<<"input illegal!"<<endl;
		}
	}
	

	

	
	//删除特定元素 （包含删除第一个元素和最后一个元素） 
	int DeleteIltem(int k){
		int datatemp;
		Node* p;
		
		if(k<0||k>=len){    //输入不合法
			return -1; 
		} 
		else if(k==0){   //删除第一个元素  
			datatemp = phead->next->data ;
			p = phead->next;
			phead->next = phead->next->next;
	
			delete p;
			p = NULL;
		}
		else if(k==len-1){//删除最后一个元素
			p = phead->next;
			for(int i =0;i<len-2;++i){
				p = p->next;
			}
			datatemp = p->next->data;	
			ptail = p;
			p = p->next;
			ptail->next = NULL;
			delete p;
			p = NULL;
		} 
		else{                      //其它
			p= phead->next;
			for(int i =0;i<k-1;++i){
				p = p->next;
			}
			Node* ptemp;
			ptemp = p->next;
			datatemp = ptemp->data;
			p->next = ptemp->next;
			delete ptemp;
			ptemp=NULL;
			// delete删除的只是该指针指向的内存，断开了指向，该指针变成一个野指针，可能指向某个重要变量的地址，需要重置为NULL
		} 
		cout<<"delete successfully!"<<endl;
		len--; 
		return datatemp; 	
	}
	
	
	//遍历整个链表，并输出 
	void printAll() {
		Node *p= phead->next;

		//两种方法判断遍历到尾结点


//		while(p!=NULL){
//			cout<<p->data<<" ";
//			p = p->next;
//		}

		for(int i=0;i<len;i++){
			cout<<p->data<<" ";
			p = p->next;
		}
		cout << endl;
	}
	
	//递归方式实现反转
	Node * ReverseLinkList_1(Node *head){
		if(head==NULL||head->next==NULL){//递归终止条件：找到最后一个节点 ，每次传的参数时head->next
			return head;
		}
		else{
			Node *newhead = ReverseLinkList_1(head->next);//先从末尾反转，从倒数第二个开始 
			head ->next ->next = head;//反转指向
			head->next = NULL;//断开原来的
			return newhead;
		} 
	} 
	
	//非递归方式,依次定义三个指针，时间复杂度O(n) 
	Node*ReverseLinkList_2(Node*head){
 	if(head==NULL||head->next==NULL){
		return head;
	}
	//定义三个紧邻的移动指针
	Node*pre = head;
	Node*cur = head->next;
	Node*temp = head->next->next;
	
	while(cur){
		temp = cur->next;//录当前节点cur下一个节点的位置
		cur->next = pre;//反转
		pre = cur;      //移位
		cur = temp; 	 
	}
	head->next = NULL;//反转后的最后一个结点（即反转前的第一个结点）置空 
	return pre; 
 	} 
};


int main(){
	char ch; 
	LinkList a; 

	a.Create_List();
	
	
	bool flag = 1;
	while(flag){
		cout<<"*******************************************************************************"<<endl;
		cout<<"a(InsertHead),b(InsertTail),c(DeleteHead),d(DeleteTail),e(find),f(insert_before)"<<endl;
		cout<<"g(insert_Back),h(delete),i(visit),j(Recursive_Reverse),k(General_Reverse),l(quit)"<<endl; 
		cout<<"*******************************************************************************"<<endl;
		cin>>ch;	
			switch(ch){
			case 'a':{
				int ina;
				cout<<"input the num:" ;
				cin>>ina;
				a.InsertHead(ina);
				cout<<"insert successfully!"<<endl;
				break;
			}
				
			case 'b':{
			int inb;
				cout<<"input the num:";
				cin>>inb; 
				a.InsertTail(inb);
				cout<<"insert successfully!"<<endl;
				break;
			}
				
			case 'c':{
				cout<<"the head_num you delete is "<<a.DeleteHead()<<endl;
				break;
			}
			
			case 'd':{
				cout<<"the tail_num you delete is "<<a.DeleteTail()<<endl;
				break;
			}
				
			case 'e':{
				int k;
				cout<<"input the num:";
				cin>> k;
				int ans = a.LocateItem(k);
				if(ans==-1){
					cout<<"not exist!"<<endl;
				}
				else{
					cout<<"the idx is "<<ans<<endl; 
				}
				break;
			}
			
			case 'f':{
				int idx,value;
				cout<<"input the idx and value:";
				cin>>idx>>value;
				a.InsertBefore(idx,value);
				break;
			}
				
			case 'g':{
				int idx,value;
				cout<<"input the idx and value:";
				cin>>idx>>value;
				a.InsertBack(idx,value);
				break;
			}
				
			case 'h':{
				int inh,ans;
				cout<<"input the idx you wanna delete:" ;
				cin>>inh;
				ans = a.DeleteIltem(inh);
				if(ans==-1){
					cout<<"delete illegal!"<<endl;
				}
				else{
					cout<<"the value you delete is "<<ans<<endl;
				}
				break;
			}
				
			case 'i':{
				a.printAll();
				break;
			}
				
			case 'j':{
				a.getHead()->next = a.ReverseLinkList_1(a.getHead()->next);
				cout<<"Recursion Reverse successfully!"<<endl;
				a.printAll();
				break;
			}
				
			case 'k':{
				a.getHead()->next = a.ReverseLinkList_2(a.getHead()->next);
				cout<<"General Reverse successfully!"<<endl;
				a.printAll();
				break;
			}
			
			case 'l':{
				flag =0;
				break;
			}
			
			default:{
				cout<<"input illegal! please input again"<<endl; 
				break;
			}
		}
	}
	
	return 0;
} 




