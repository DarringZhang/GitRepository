#include <iostream>
#include <cstdio>
using namespace std;
/*
 * 数组名取地址得到的是数组名所指元素的地址。对指针取地址得到的是指针变量自身的地址
 * 因为指针是个变量指针，对一个变量取地址就是这个变量自身的地址
 * 而数组名字是个常量指针，指向首元素的地址，对它取地址，等于得到它所指向的值
 * */
int main(){
	int a[100];

	for (int i = 0; i < 100; i++){
		a[i] = 2 * i;
	}

	printf("数组名字代表的内容：%p\n", a);
	printf("数组名字指向的内容：%p\n", &a);
	printf("数组第一个元素的地址：%p\n", &a[0]);



	int *b = a;//b是指向a数组的名字（一块地址）的指针变量。
	printf("b指针指向的内容：%p\n", b);
	printf("b指针本身的地址：%p\n", &b);
	for (int i = 0; i < 5; i++){
		printf("%p %d\n", &b[i], b[i]);
	}
//	a[3] = *(a + 3);a指针往后偏移三个单位，再*取值

}