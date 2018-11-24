
/*
	subject：Data Structure 
	To: experiment1_problem4.2
	Creator: 张丹颖2017011760
	date:2018.10.08
*/ 

#include<iostream>
using namespace std;

struct scoreNode{       //定义链表，存储这个数的相关信息
	int data ;          //这个数的数值
	int times;			//这个数出现的次数
	scoreNode *next;    //用链表这一结构存储这些不同的数字
}; 
int main(){
	int N ,find_score;
	cin>>N;
	while(N!=0){
		scoreNode * phead = new scoreNode;
		phead->next = NULL;
		phead->data = -1;
		phead->times = 1;
		scoreNode *p,*ptail;
		
		while(N-->0){    //对于每个测试用例
			int temp,flag=0 ;
			cin>>temp;
			p = phead;
			while(p!=NULL){  
				if(temp==p->data){//对于每个输出的成绩，检查在链表中是否有相同的成绩
					p->times++;//有，出现的次数++
					flag++;
				}
				ptail = p;
				p = p->next;
			}
			if(flag == 0){  //遍历完链表后发现都没有这个数，则在链表后面追加新成绩结点
					scoreNode* ScoreBox = new scoreNode;
					ptail->next = ScoreBox;
					ScoreBox->data = temp;;
					ScoreBox->next = NULL;
					ScoreBox->times = 1;
					ptail = ScoreBox;
			} 
		}
		
		cin>>find_score;//输入目标成绩
		p = phead->next;
		int star=0;	
		while(p!=NULL){
			if(find_score==p->data){  //遍历寻找
				cout<<p->times<<endl;//找到就输入对应输入的次数
				star++;
				break;	
			}
			p = p->next;
		}
		
		if(star==0){//若找不到，就输出0
			cout<<star<<endl;
		}
		cin>>N;
	}

	return 0;
}
