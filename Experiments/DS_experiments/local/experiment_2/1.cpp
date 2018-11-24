/*
	stack 类继承LinkList类的部分方法，其中Append 为push,DeleteIltem(a.size()-1)为pop
	只有getTop（）和clear_stack 是在stack 类新加的，其他依靠继承
*/
#include<iostream>
using namespace std;
struct Node{
		int data;
		Node * next = NULL;
	};

class LinkList{
protected:
	int len = 0;
	Node *phead = NULL;
	Node *ptail = NULL;
public:
	LinkList (){
		phead = new Node;
		ptail = new Node;
		ptail = phead;
	}
	
	void Destrory(){//相当于显式调用LinkList的析构函数:~LinkList()，程序结束后delete每个new出来的结点
			Node *pdelete,*ptemp;
			pdelete = phead->next;
			while(pdelete!=NULL){ 
				ptemp = phead->next->next;//总是让头指针指向要删结点的下一个结点
				phead->next = ptemp;//ptemp存储下一个要删的结点
				delete pdelete;//删除本次要删的结点
				pdelete = ptemp;	
			}

			//tip：用 DeleteIltem and isEmpty() 两个函数结合来destroy更简洁，就像下述stack类中~stack（）析构函数
			
			delete phead;//头结点也要释放
		   	ptail = phead = NULL;

			this->len = 0;
	
		}
	
	//销毁栈之后，头结点也被销毁，需要重新构造
	Node *buildPhead(){
		phead = new Node;
		return phead; 
	}
	
	//创建链表的新结点：直接在ptail后new一个新结点接上
	void Create_List(int num){
		ptail->data = num;
		ptail->next = new Node;
		ptail = ptail->next;
		ptail->next = NULL;
		len++;
	}
	
	//找
	int  Getltem(int idx){ 
		Node* p = phead;
		if(idx>=len){//输入下标不合法
			return -1;
		}
		
		for(int i=0;i<idx;i++){//遍历到目标位置
			p = p->next;
		}
		return p->data;
	} 

	//增（push）
	 void Append(int num){
	 	//栈被销毁就不能push：需要重新构造栈再push
		if(phead==NULL){
				cout<<"stack is non_exist,now build it!"<<endl;
				buildPhead();
				Create_List(num);
				cout<<"push successfully!"<<endl; 
				return;
			}
			ptail->data = num;//直接在尾结点ptail后面追加
			ptail->next = new Node;
			ptail = ptail->next;
			len++;
			cout<<"push successfully!"<<endl; 
	}
	
	//定位
	int LocateItem(int num){
		Node* p = phead; 
		int i=0;
		while(p->next!=NULL){
			if(p->data == num){//遍历，找到目标值为止，返回位置
				return i;
			}
			p = p->next;
			i++;
		}
		
		return -1;//遍历完都没找到，返回负数
		
	}
	
	void InsertBefore(int idx,int num){
		Node* p = phead;

		if(idx<0||idx>len){//输入下标不合法的情况
			cout<<"insert illegal!"<<endl;
			return;
		}
		else if(idx==0) {//插入头结点
			Node* newphead =new Node;
			newphead->next = phead;
			newphead->data = num;
			phead = newphead;//更换头结点
			len++;
		}
		else if(idx==len){//插入尾结点
			ptail->data = num;
			ptail->next = new Node;
			ptail = ptail->next;
			ptail->next = NULL;
			len++;
		}
		else //插入中间结点需要遍历
		{
			for(int i=0;i<idx-1;++i){
				p = p->next;
			}
			//遍历到idx-1,找到要插入位置的前一个元素，插入
			Node *newnode = new Node;
			newnode->next =NULL; 
			newnode->data = num;
			
			newnode->next = p->next;
			p->next = newnode;
			len++;
			
		}
		cout<<"insert successfully!"<<endl;
		
}
	 int DeleteIltem(int k){
		int datatemp;
		Node* p= phead;
		
		if(k<0||k>=len){//删除不合格
			return -1; 
		} 
		else if(k==0){//删除头结点
			Node* ptemp = phead;
			int datatemp = phead->data;
			phead = phead->next;
			delete ptemp;
			ptemp = NULL;
			len--;	
			return datatemp;
		}
		else if(k==len-1){//删除尾结点（即pop）
			Node *p = phead; 
			for(int i =0;i<k-1;++i){
					p = p->next;
			}
			
			Node * ptemp = p->next;
			datatemp = ptemp->data;
			p->next = ptail; //越过最后一个元素，指向尾指针（这里的ptail并没有存值）
			delete ptemp;
			ptemp = NULL;	
			len--;
			return datatemp;
		}
		else{                //删除一般结点，需要遍历
				for(int i =0;i<k-1;++i){ 
					p = p->next;
				}
			Node* ptemp;
			ptemp = p->next;
			datatemp = ptemp->data;
			p->next = ptemp->next;
			delete ptemp;
			ptemp=NULL;
			len--; 
			return datatemp;
		}


		
	}
	
	Node* getPtail(){//得到真正存有效数字的尾部，遍历
		Node*p = phead;
		while(p->next->next!=NULL){
			p = p->next;
		}
		return p;
	}
	
	
	bool isEmpty(){
			if(phead==NULL||phead->next==NULL){
				return true;
			}
			return false;
	} 
	
	int size(){
		 int n = 0;
		 Node *p = phead;
		 while(p->next!=NULL){ //依赖指针的空指针域判断size，不单单是len=0
		 	n++;
		 	p = p->next;
		 } 
		 return n; 
	}
	
	void printAll() {
			Node *p= phead;
			while(p->next!= NULL){ 
			cout<<p->data<<" ";
			p = p->next;
		}
		cout<<endl;
	}
};



class Stack :public LinkList{
	public:
		Stack(){//构造函数
		}
		~Stack(){//析构
			int length = size();
			while(!isEmpty()){
			DeleteIltem(length-1);
				length--;
			}
			delete phead;
		   	phead = NULL;
			len = 0;
		}
			
		int getTop(){
			if(isEmpty()){
				return -1;
			} 
			return getPtail()->data;//直接调用父类获得有意义数值“尾”指针
		} 
		
		void ClearStack(){//与destroy 区别：clear 不回收头指针
			while(phead->next!=NULL){//始终删除头结点后面的结点
				Node *pdelete = phead->next;
				phead->next = pdelete->next;
				delete pdelete; 
			}
			ptail = phead;
			this->len = 0;
			cout<<"clear successfully!"<<endl;
		} 
		
		
		 
};


int main(){
	char ch; 
	int geshu,in;
	Stack a;
	cout<<"input the stack height:";
	cin>>geshu;
	cout<<"please input numbers"<<endl;
	for(int i=0;i<geshu;i++){
		cin>>in;
		a.Create_List(in);
	} 	
	bool flag = 1;
	while(flag){
		cout<<"a(push),b(pop),c(top),d(size),e(clear),f(print),g(quit)"<<endl; 
		cin>>ch;	
			switch(ch){
			case 'a':{
				int ina;
				cout<<"input the num you wanna push:";
				cin>>ina;
				a.Append(ina);
				break;
			}
				
			case 'b':{
				int inb = a.DeleteIltem(a.size()-1);
				if(inb==-1){
					cout<<"delete illegal!"<<endl;
					break;
				} 
				else{
					cout<<"pop " << inb <<" successfully!"<<endl;
				}
				break;
			}
				
			case 'c':{
				int ans = a.getTop();
				if(ans==-1){
					cout<<"stack is empty,can't get top!"<<endl;
					break;
				}
				cout<<"the top element is:"<<ans<<endl;
				break;
			}
				
			case 'd':{
				cout<<"the height of stack is:"<<a.size()<<endl;
				break;
			}
			case 'e':{
				a.ClearStack();
				break;
			}
			case 'f':{
				a.printAll();
				break;
			}
			case 'g':{
				flag = 0;
				break;
			}	
			default:{
				cout<<"input illegal.please input again!"<<endl; 
				break;
			}
			
		}
	}
	

	return 0;
} 



	
