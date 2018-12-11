#include <iostream>
#include <map>
using namespace std;
/*
 * 一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙跳上一个n级的台阶总共有多少种跳法
 *
 * 指数级的复杂度递归：
 * 1.第一步先找这个函数与下一个函数之间的关系：

假如有n个台阶，跳上一个n级的台阶的跳法总数为f(n).

我们在跳的过程中，每一次有两种跳法，即跳一个或两个台阶。

 第一种跳法：第一次我跳了一个台阶，那么还剩下n-1个台阶还没跳，剩下的n-1个台阶的跳法有f(n-1)种。

或者用

第二种跳法：第一次跳了两个台阶，那么还剩下n-2个台阶还没，剩下的n-2个台阶的跳法有f(n-2)种。

由此不难得出递归公式：f(n) = f(n-1) + f(n-2);



2.第二步，找出递归的结束条件

    当n <= 0时，跳法为0，即此时f(n) = 0

    当只剩下一个台阶n = 1时，那么只有一种跳法，即f(1) = 1;

    当n = 2时，此时跳法为2种，即f(2) = 2;
 * */

int f1(int n){
    if(n<=0){
        return 0;
    }
    else if(n<=2){
        return n;
    }
    else{
        return f1(n-1)+f1(n-2);
    }
}

/*优化：对于计算过的f(n)，保存在一个map容器里面，n作为key,f(n)作为value;
 * 每次递归时，先查看一下f(n)是否已经计算过了，若，直接取出，否，计算并put into map;
 * */
map<int,int> map_f2;//查找复杂度logn
int f2(int n){
    if(n<=0){
        return 0;
    }
    else if(n<=2){
        return n;
    }
    else{
        if(map_f2.count(n)==1){
            return map_f2[n];
        }
        else{
            int m = f2(n-1)+f2(n-2);
            map_f2.insert(pair<int, int>(n,m));
            return m;
        }

    }
}

/*
 * 对于f(n) = f(n-1) + f(n-2)这样的形式，和斐波拉契相似
 *
 */

int f3(int n){
    if(n<=0){
        return 0;
    }
    else if(n<=2){
        return n;
    }
    //斐波拉契的做法，循环嵌套，自下而上
    int fa = 0;
    int fb = 1;
    int sum = 0;
    for(int i = 1; i <= n; ++i){
        sum = fa + fb;
        fa = fb;
        fb = sum;
    }
    return sum;
}



/*
 * 问题2： 一只青蛙一次可以跳上1级台阶，也可以跳上2级……它也可以跳上n级。
 * 求该青蛙跳上一个n级的台阶总共有多少种跳法。
 * */
map<int,int> map_f4;
int f4(int n){
    if(n<=0){
        return 0;
    }
    else if(n<=2){
        return n;
    }
    else{
        int m = 0;
        //int m = f4(n-1)+f4(n-2);
        for(int i = 1; i <= n; ++i){
            m += f4(n-i);
        }
        map_f4.insert(pair<int, int>(n,m)); // f（n） = f(n-1) + f(n-2) +......+f(1)
        return m;
    }

}

int main() {
    int num;
    while(scanf("%d",&num)&&num){
        cout<<"递归:"<<f1(num)<<endl;
        cout<<"map优化"<<f2(num)<<endl;
        cout<<"斐波拉契"<<f3(num)<<endl;
        cout<<"变式："<<f4(num)<<endl;
    }



    return 0;
}