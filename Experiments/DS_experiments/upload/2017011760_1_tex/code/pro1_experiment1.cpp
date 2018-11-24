/*
	subject：Data Structure 
	To: experiment1_problem1
	Creator: 张丹颖2017011760
	date:2018.10.08
*/ 

#include<iostream>
//#include<cstring>
using namespace std;

struct MyArray{
	int *data;
	int size;

	MyArray(){//构造函数 
		data = NULL;	
		size = 0;
	}
	
	~MyArray(){//析构
		delete data; 
		data = NULL;	
		size = 0;
	}
	

	void Create_Array(){ 
		cout<<"please input the size:";
		cin>>size;
		data = new int[size];//存多少数，new多大空间 
		cout<<"please input number:";
		for(int i=0;i<size;++i){
			cin>>data[i];	
		}
		cout<<"create successfully!" <<endl;
	}
	
	//利用数组下标随机访问
	int &Getltem(int index){ 
		int m =-1,n = -2; 
		if(size==0){//返回-1表示空表  
			return m;
		}
		
		if(size>index&&index>=0){
			return (data)[index];
		}
		else{
			return n;//返回-2表示下标不合法  
		}
	} 
	//有引用&就可以实行右赋值操作getItem(s,4) = 6

	//表后添加 
	void Append(int d){ 
		size++;						
		int *temp = new int[size];//开辟新空间  
		temp[size-1]=d;
		for(int i=0;i<size-1;++i){//数据复制
			temp[i] = data[i];
		}
		delete [] data;//释放原来的data 
	    data = temp; //给data赋新值 
	    cout<<"append successfully!"<<endl;
	} 
	 
	//指定下标前面插入新数据  
	void InsertBefore(int d,int index){
		if(index<0){						//检查输入的下标
			cout<<"input illegal!"<<endl;	
			return;
		}
		
		size++;					
		int *temp = new int[size];			//开辟新空间  
		
		for(int i=0;i<index;++i){		//index前面的数据复制 
			temp[i] = data[i];
		}

		temp[index]=d;					//插入该数据

		for(int i=index+1;i<size;++i){	//index 后面的数据复制
			temp[i]=data[i-1];
		}
		
		delete [] data;
		data= temp;
		cout<<"insert successfully!"<<endl;
	}
	 
	  //将另外一张表的内容添加到这个表的后面
	 int AddTableBack(int table[] ,int l){
	 	//int NewSize = size+strlen(table);在c++的函数里面，如果把一个数组作为参数传进去，那么这个数组就会退化为一个指针，因而就不知道这个数组的长度, 此法不可行 
	 	
		int NewSize = size+l;
	 	int *temp = new int [NewSize];//开辟能容纳两个表大小的新空间
	 		//数据赋值 
	 		for(int i=0;i<size;++i){
	 			temp[i] = data[i];
			}
		 
		int j = 0;
		for(int i=size;i<NewSize;++i){//此处注意下标 
			temp[i] = table[j++];
		}
		 
		 delete [] data;
		 data = temp;
		 
		 size = NewSize;
		 return size;//返回新线性表的长度
	 }
	 
	 //查找表的特定元素
	int Locateltem(int d){
		int i=0;
		for( i=0;i<size;++i){
			if(data[i] == d){
				return i;//return直接结束该函数调用，与break有区别;	
			}
		}
			return -1;
		
	}
	
	//删除表中某特定元素 
	int DeleteIltem(int index){
		if(index<0){//检查下标合不合理 
			return -1;
		}
		size--;
		int ans = data[index];
		for(int i=index;i<size;++i){//从index位开始，后一位数覆盖前一位  
			data[i]=data[i+1];
		} 
		return ans;//返回删除的数 
	}
	
	//打印所有元素
	void printAll() {
		if(size==0){
			cout<<"Linear table is empty!, please create first!"<<endl;
			return;
		}
		
		for(int i=0;i<size;++i){
			cout<<data[i]<<' ';
		}
		cout<<endl;
	}	
	
}; 


int main(){
	char ch; 
	MyArray a;
	
	bool flag = 1;//退出界面标志
	while(flag){
		cout<<"a(create),b(visit),c(append),d(insert),e(addTable),f(find),g(delete),h(print),i(quit)"<<endl; 
		cin>>ch;	
			switch(ch){
				case 'a':{
					a.Create_Array();
					break;
				}
			
				case 'b':{
					int inb ;
					cout<<"input index that you want to visit:";
					cin>>inb;
					int outb = a.Getltem(inb);
					
					if(outb==-1){
						cout<<"Linear table is empty!, please create first!"<<endl;
					}
					else if(inb==-2){
						cout<<"input illegal!"<<endl;
					}
					else{
						cout<<"the number is "<<outb<<endl;
					} 
					break;
				}
				
				case 'c':{
					int inc;
					cout<<"input the num you want to append:";
					cin>>inc;
					a.Append(inc);
					break;
				}
				
				case 'd':{
					int dd,ind;
					cout<<"input the num and place(index)";
					cin>>dd>>ind; 
					a.InsertBefore(dd,ind);
					break;
				}
				
				case 'e':{
					int scale;
					
					cout<<"input the size of your  inserted array:";
					cin>>scale;
					int *array = new int[scale];
					cout<<"input its number:";
					for(int i=0;i<scale;++i){
						cin>>array[i]; 
					}
					
					cout<<"the length of combined table is "<<a.AddTableBack(array,scale)<<endl; 
					break;
				}
			
				case 'f':{
					if(a.size==0){
						cout<<"Linear table is empty!, please create first!"<<endl;
						break;;
					}
					int inf;
					cout<<"input the number you wanna find:";
					cin>>inf;
					
					int outf = a.Locateltem(inf);
					if(outf==-1){
						cout<<"can' t find!"<<endl; 
					}
					else{
						cout<<"the index is "<<outf<<endl;
					}
					break;
			}
					
				case 'g':{
					if(a.size==0){
						cout<<"Linear table is empty!, please create first!"<<endl;
						break;
					}
					
					int ing;
					cout<<"input the index you wanna delete:";
					cin>>ing;
					
					int outg = a.DeleteIltem(ing);
					if(outg==-1){
						cout<<"input illegal!"<<endl;
					}
					else{
						cout<<"the num you delete is "<<outg<<endl;
					} 
					break;
				}
					
				case 'h':{
					a.printAll();
					break;
				}
				
				case 'i':{
					flag =0;
					break;
				}
					
				default:{
					cout<<"input illegal£¡please input again!"<<endl; 
					break;
				}
				
		}
	}

	return 0;
} 









