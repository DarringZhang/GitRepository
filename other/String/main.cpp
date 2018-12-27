/*
 * 本程序理解字符串操作 背后的代价 以及优化
 * 复制和赋值运算符的区别：  赋值：传统 = （copy 没有重载之前，）  操作，没有开辟新空间，只是将指针复制，是指针指向同一片区域；
 *                  比如 a = b; 在以后修改a 或者b ，都会互相造成影响（指针指向同一片区域）
 *                  然而这并不是我们的常规
 *          拷贝： 新开辟空间，彼此之间没有影响（符合常规操作,copy一份文件,两份文件的操作独立）
 * */
#include <iostream>
#include <cstring>
using namespace std;

//struct 默认所有对象都是public,而class 默认private
struct MyString{
    char *str;
    size_t length; //size_t 当作比int 能存更大范围数的 int 型

    //不带参数的构造函数
    MyString() : str(NULL) , length(0) {
        cout<<" MyString()"<<endl;
    }

    //创建一个新字符串
    MyString(const char *s) : str(NULL), length(0){
        cout<<" MyString(const char *s)"<<endl;
        if(s == NULL){
            return;
        }
        length = strlen(s);
        str = new char [length + 1];
        strcpy(str,s);//将字符串s 复制给空的 str;
    }

    //字符串复制，拷贝构造
    MyString(const MyString &s) :str(NULL) , length(0){
        cout<<" MyString(const  MyString &S)"<<endl;
        if(s.length == 0)
            return;
        length = strlen(s.str);
        str = new char [length + 1];
        strcpy(str,s.str); //将字符串s.str 拷贝到 str;
    }

    //提高效率：移动构造 右值引用
    MyString(MyString &&s) : str(NULL),length(0){
        cout<<" MyString(const  MyString &&S)"<<endl;
        if(s.length == 0)
            return;
        str = s.str;
        length = s.length;
        s.str = NULL;//不需要new char空间, 只需要将指针指过来就行
    }

    ~MyString(){
        cout<<" ~MyString()"<<endl;
        delete [] str;
    }

    //重载各种符号
    MyString & operator = (const MyString &other){
        cout<<"  MyString & operator ="<<endl;
        if(this == &other){//处理other = other 自等的情况，否则报错
            return *this;//直接返回自己
        }
        delete [] str;
        length = 0;
        if(other.length == 0)//用空字符串 做 等号运算
            return *this;
        str = new char[other.length + 1];
        length  = other.length + 1;
        strcpy(str,other.str);
        return *this;
    }


    //s1 = s + s2  重载操作符 +    字符串拼接
    MyString operator + (const MyString &other) const{
        cout<<"  MyString & operator +"<<endl;
        //如果自己是空的
        if(length == 0)
            return other;
        if(other.length == 0)
            return  *this;
        MyString t;
        t.str = new char[length + other.length +1];
        strcpy(t.str,str);//把自己的那部分拷贝过去t
        strcpy(t.str + length , other.str);//将 other 的那部分拷贝过去
        t.length = length + other.length;
        return  t;
    }

};

int main() {
    MyString s("Hello");//调用有参的构造函数
    MyString s1; //调用无参的构造函数: 创建一个字符串
    MyString s2(" Darring!"); //调用字符串复制 的函数

    s1 = s + s2;


    return 0;
}