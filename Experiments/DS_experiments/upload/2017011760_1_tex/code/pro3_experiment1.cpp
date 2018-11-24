/*
	subject：Data Structure 
	To: experiment1_problem3
	Creator: 张丹颖2017011760
	date:2018.10.08
*/ 

#include<iostream>
using namespace std;

struct DoubleNode{
		int data;
		DoubleNode *next = NULL;
		DoubleNode *pre = NULL;
	};
	
class LinkList{
private:
	int len  ;
	DoubleNode *phead = NULL;
	DoubleNode *ptail = NULL;
	
public:
	LinkList (){//构造 
		phead = new DoubleNode;
		ptail = phead;
		phead->next = NULL;
		phead->pre = NULL;
	}
	
	~LinkList (){//析构 
		phead->next = NULL;
		phead->pre = NULL;
		delete phead ;
		phead = NULL;	
	}
	
	DoubleNode* getHead(){
		return phead;
	}
	
	//初始化链表		
	void Create_List(){ 
		len = 0;
		DoubleNode *p = phead;
		cout<<"create a LinkList(5)"<<endl;
		for(int i=0;i<5;++i){
			DoubleNode *pnew = new DoubleNode;
			cin>>pnew->data;
			pnew->next = NULL;

			pnew->pre = p;        //增加前指针
		 	p->next = pnew;
			p = p->next;
			len++;
		}
	
		ptail = p;
	}
	
	//第一个元素之前插入
	void InsertHead(int d){//即在phead后插入一个结点
		DoubleNode* newphead =new DoubleNode;
		//指针域操作
		newphead->next = phead->next;//新结点指向原来的phead的下一个结点
		phead->next->pre = newphead;//原来的phead的下一个结点指向新结点
		newphead->pre = phead;  //新结点的前一个结点为phead
		phead->next = newphead;//更新phead的下一个结点为这个新结点

		newphead->data = d;
		len++;
	}
	
   //最后一个元素之后插入新数据 
	void InsertTail(int d){
		DoubleNode * newPtail  = new DoubleNode;
		newPtail->next = NULL;	
		
		newPtail->data = d;
		ptail->next = newPtail;//直接在结尾ptail后追加新结点
		newPtail->pre = ptail; //新尾结点的前一个结点尾原尾结点
		ptail = newPtail;//更新ptail
		len++;
	}
	
	//删除第一位数，即删除phead紧接的那个结点
	int DeleteHead(){
		int datatemp;
		DoubleNode* p;
		datatemp = phead->next->data ;//存储删除那个结点的数据域
		p = phead->next;

		phead->next = phead->next->next;//断开phead和它的直接后继
		phead->next->next->pre = phead; //接上前指针
		delete p;
		p = NULL;
		
		len--; 
		return datatemp; 
		
	}
	
	//删除尾结点
	int DeleteTail(){
		DoubleNode* p = phead->next;
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
		DoubleNode* p = phead->next; 
		int i=0;
		for( i=0;i<len;++i){  
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
			DoubleNode* newphead =new DoubleNode;

			newphead->next = phead->next;
			phead->next->pre = newphead;
			newphead->pre = phead; 
			phead->next = newphead;	

			newphead->data = num;
			len++;
			cout<<"insert  Before successfully!"<<endl;
		}
		else if(idx>=0&&idx<len)//除了插入第一位后的任意位置之前插入 
		{
			DoubleNode* p = phead->next; 
				for(int i=0;i<idx-1;++i){//遍历到指定结点的上一个结点
				p = p->next;
			}
			
			DoubleNode *newDoubleNode = new DoubleNode; 
			newDoubleNode->next =NULL; 
			newDoubleNode->data = num;
			
			newDoubleNode->next = p->next ;//新结点的指针域指向指定结点上一个结点的指针域
			p->next->pre = newDoubleNode;//指定结点的前驱为这个新结点
			p->next = newDoubleNode; //更新指定结点上一个结点的指针域
			newDoubleNode->pre = p;//新结点的前驱为指定结点的前驱
			
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
			DoubleNode * newPtail = new DoubleNode;
			newPtail->next = NULL;
			
			newPtail->data = num;
			ptail->next = newPtail;
			newPtail->pre = ptail; //新尾结点的前一个结点尾原尾结点
			ptail = newPtail;
			len++;
			cout<<"insert  Before successfully!"<<endl;
		}	
		else if(idx>=0&&idx<len){
			DoubleNode* p = phead->next; 
			for(int i=0;i<idx;++i){//遍历到指定结点，在下一个结点插入
				p = p->next;
			}
			
			DoubleNode *newDoubleNode = new DoubleNode; 
			newDoubleNode->next = NULL; 
			newDoubleNode->data = num;
			
			newDoubleNode->next = p->next; 
			p->next->pre = newDoubleNode;
			p->next = newDoubleNode; 
			newDoubleNode->pre = p;
			
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
		DoubleNode* p;
		
		if(k<0||k>=len){   
			return -1; 
		} 
		else if(k==0){   //删除第一个元素  
			datatemp = phead->next->data ;
			p = phead->next;
			phead->next = phead->next->next;
			phead->next->next->pre = phead; //接上前指针
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
			DoubleNode* ptemp;
			ptemp = p->next;
			datatemp = ptemp->data;
			p->next = ptemp->next;
			ptemp->next->pre = p;
			delete ptemp;
			ptemp=NULL;
		} 
		cout<<"delete successfully!"<<endl;
		len--; 
		return datatemp; 	
	}
	
	
	//遍历整个链表，并输出 
	void printAll() {
		DoubleNode *p = phead->next;

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
	
	

	//非递归方式,时间复杂度O(n) 
	DoubleNode*ReverseLinkList(DoubleNode*head){
	 	if(head==NULL||head->next==NULL){ //处理空链表的情况
			return head;
		}
		
		DoubleNode*cur = head,*p;
		
		//开始反转
		while(cur->next!=NULL){//遍历到倒数第二个结点，新ptail和phead 单独处理
			p = cur->next;    //p记住cur的下一个结点
			cur->next = cur->pre;  //当前的结点下一个结点为其前一个结点
			cur->pre = p;      //当前结点的前一个结点=当前结点的下一个节点
			cur = cur->pre;	 //后移
		}
		
	
		head->next = NULL;//反转后的最后一个结点（即反转前的第一个结点）置空 
		
		ptail->next = ptail->pre; // 更新ptail 的下一个结点
		ptail->pre = phead;  //ptail前一个结点为头结点
		ptail = head;      //更新尾结点
		return cur; 
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
		cout<<"g(insert_Back),h(delete),i(visit),k(General_Reverse),l(quit)"<<endl; 
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
				
			case 'k':{
				a.getHead()->next= a.ReverseLinkList(a.getHead()->next);
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




