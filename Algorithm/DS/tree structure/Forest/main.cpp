#include <iostream>
#include <ctime>
#include "union_find.h"
using namespace std;

#define N 100000000
//测试样例 一亿次合并操作和 1 亿次检查是否属于同一集合的操作
int main() {
    srand(time(NULL));//根据时间随机化种子
    register int a,b;//a b变量的值 放到CPU寄存器中，不必再内存中去取，提高效率

    UnionFind uf  = UnionFind(N);

    time_t start_time = clock();//开始计时
    //合并
    for(int i = 0; i < N; ++ i) {
        a = rand() % N; //rand()产生0到最大随机数（32767 (2^16-1)）的任意整数，%N 对N取余，产生0~N的随机数
        b = rand()% N;
        uf.Merge(a,b);//将随机产生的a 和 b 合并
     }
    //检查
    //第一次查找 O（n）,压缩完路径后 查找都是O(1)
    for (int i = 0; i < N; ++ i){
        a = rand()%N;
        b = rand()%N;
        uf.is_connected(a,b);
    }
    time_t  end_time = clock();//clock()是以毫秒为单位，要正确输出时间差需要把它换成秒，因此需要除以CLOCKS_PER_SEC
    cout << double(end_time - start_time) / CLOCKS_PER_SEC<<" s"<<endl;
    return 0;
}

