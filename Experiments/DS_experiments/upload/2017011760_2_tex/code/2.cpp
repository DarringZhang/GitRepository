/*
	一般队列：
	操作和栈类似（也采用继承linklist and array 的方法），只是pop底，push头（数组的最后）------------这些都是单链表的插入和删除的特殊操作  
	双端队列：
	限定插入和删除在两端进行(输出输入等设限) ，限定某端插入只能从该端删除=两个栈底相连的栈 
  **循环队列 （以下实现） ：array and Queue  
	 tip1:   空队列rear=front = 0 
			 push_back:   rear++
	 		 pop_front:   front++
	  	     to save space, 循环队列 
	 tip2:   front=rear can't distinguish blank and full
	         way1:  记住队列元素的个数
			 way2:   少用一个空间，front = rear+1  is full!                       
	 
	 													注：添加头结点，空队列即头尾指针都指向头结点 
	 													
*/ 


#include<iostream>
#define MAXSIZE 5
using namespace std;

struct queue{
	int *base = NULL;
	int front= -100000;
	int rear = -200;
	//int count     ways1记录队列中元素总数， 判断empty ,下述采用ways2 
};


class QueueList{
	public:
		queue Q;
		QueueList(){	
			
		}
		void initeQueue(){//构造一个空队列 
		    Q.base = new int(MAXSIZE);//顺序存储，创建一个大小为MAXSIZE的数组 
			Q.front =  Q.rear= 0;//头尾标记指向一个地方 ，初始化
			cout<<"build queue successfully!"<<endl;
		}
		
		void DestroyQueue(){
			delete [] Q.base;
			Q.base=NULL;
			Q.front = Q.rear = -10000; //将front 和rear 置为负数，利于下面isEmpty()判断列表不存在的情况
			cout<<"destroy queue successfully!"<<endl;
		}
		
		int queueSize(){
			return (Q.rear-Q.front+MAXSIZE)%MAXSIZE;//rear 和front相对大小为size 
		}
		
		void EnQueue(int d){
			if((Q.rear+1)%MAXSIZE==Q.front){//队列满（要留出一个空位）,实际容量比MAXSIZE小1 
				cout <<"queue is full,can't push,please modify MAXSIZE"<<endl; 
				return;
			}
			else if(Q.base == NULL){
				cout<<"queue is non_exist，please inite first!"<<endl;
			}
			Q.base[Q.rear]=d;
			Q.rear = (Q.rear+1) %MAXSIZE;//rear 向后挪，对MAXSIZE 取余，保证了 rear 的最大值永远不会超过容量 
		}
		
		void DeQueue(){
			if(isEmpty()){
				return;
			} 
			if(Q.base==NULL){
				cout<<"queue is non_exist，please inite first!"<<endl;
				return ;
			}
			cout<<"the element out of queue is "<<Q.base[Q.front]<<endl;//出队列的永远为front标记所在的元素 
			Q.front = (Q.front+1) % MAXSIZE; //front向后挪
		} 
		
		bool isEmpty(){
			if(Q.front==Q.rear&&Q.front>0&&Q.base!=NULL){//只有front= rear 不够,不能判断 是empty or full 
				cout<<"queue is empty"<<endl;//empty(front=rear,才开始，元素还没入队列)
				return true;                 //full(size+1=MAXSIZE) 
			} 
			else if(Q.front<0){      //队列还没被初始化，不存在
				cout<<"queue is non_exist ,please inite first!"<<endl; 
				return true;
			}
			cout<<"queue is not empty"<<endl; 
			return false;
		}
		
		bool isNULL(){
			return Q.base==NULL;
		}
		void getHead(){
			if(queueSize()==0){
				cout<<"queue is empty,can't get head!'"<<endl;
				return ;
			}
			cout<<"the head is :"<<Q.base[Q.front]<<endl;
		}
		
		void Print(){
			if(queueSize()==0){
				cout<<"the queue is empty!  can't print!";
			}
			int co = Q.front;//临时存储front的原来位置，因为队列中留出一个空位，循环一圈后不会回到原来位置
			int length = this->queueSize();
			while(Q.base!=NULL&&length>0){//跟随front++遍历一遍
				cout<<Q.base[Q.front++]<<" ";
				 length--;
			}
			Q.front = co;//还原front标记的位置
			cout<<endl;
		}
		
};

int main(){
	char ch;
	int flag = 1;
	
	QueueList IQ;

	while(flag){
		cout<<"a(initie),b(destroy),c(size),d(in),e(out),f(empty)?,g(gethead),h(print),i(quit)"<<endl;
		cin>>ch; 
		switch(ch){
			case 'a':{
				IQ.initeQueue();
				break;
			}
			case 'b':{
				IQ.DestroyQueue();
				break;
			}
			case 'c':{
				cout<<"queue already has elements of "<<IQ.queueSize()<<endl;
				break;
			}
			case 'd':{
				if(IQ.queueSize()==MAXSIZE-1){//队列满的情况，这样不用rear=front混淆empty 和full
					cout<<"queue is full,please modify MAXSIZE!"<<endl;
					break; 
				}
				if(!IQ.isNULL()){
					int in;
					cout<<"input :";
					cin>>in; 
					IQ.EnQueue(in);
					break;
				}
				cout<<"queue is not exist,please inite first!"<<endl; 
				break;
			}
			case 'e':{
				IQ.DeQueue();
				break;
			}
			case 'f':{
				IQ.isEmpty();
				break;
			}
			case 'g':{
				IQ.getHead();
				break;
			}
			case 'h':{
				IQ.Print();
				break;
			}
			case 'i':{
				flag = 0;
				break;
			}
			default:{
				cout<<"input error!"<<endl;
				break;
			}
	
		}
			
	}
	
	return 0;
}