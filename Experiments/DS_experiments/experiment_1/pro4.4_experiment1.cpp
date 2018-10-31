/*
	subject：Data Structure 
	To: experiment1_problem4.3
	Creator: 张丹颖2017011760
	date:2018.10.08
*/ 

#include<iostream>
using namespace std;

double Polynomail(double *a,double x,int n){
	double sum = a[0];
	double multy = 1;
	for(int i=1;i<n+1;++i){//对于系数数组每个数，都和其对应的x的几次方相乘，再相加
		multy*=x;      //不用pow函数，由于x指数递增，本次直接上一次的x基础上再乘以x
		sum+=a[i]*multy;
	}
	return sum;
}

int main(){
	int T,N,M;
	cin>>T;
	while(T-->0){
		double coef[1001],x[10];
		cin>>N;
		for(int i=0;i<N+1;++i){//输入指数
			cin>>coef[i];
		}
		cin>>M;
		for(int i=0;i<M;++i){//输入要计算的不同的x的值
			cin>>x[i];
		}
		
		for(int i=0;i<M;++i){
			printf("%.10e\n",Polynomail(coef,x[i],N));//%.10e代表精确到小数点后10位，用科学记数法表示结果
		}
	
	}
	
	return 0;
}


