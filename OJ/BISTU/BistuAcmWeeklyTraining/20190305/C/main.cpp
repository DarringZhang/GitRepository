#include <iostream>
using namespace std;

/*用个结构体数组，结构体里面放出现的gram字符对和它出现的个数
难度在于 每次都要在结构体数组扫一遍，没有就添加
 还不如一开始就开26*26数组  表示A~Z 分别组合
 暴力扫描并找最大
 */
 int main() {
     long long n;
     char a[110];
     cin >> n >> a;
     int gram[27][27] = {0};//初始化每对可能的gram数 = 0

     for(int i = 0; i < 26 ; ++i){
         for(int j = 0 ; j < 26 ; ++j){
             for(int k = 1; a[k] != '\0'; k++){ //一直读到字符串末尾
                if(a[k-1] - 'A' == i && a[k] - 'A' == j){ //将char转换成数字和ij对应的A~Z字母比较
                    gram[i][j] ++;
                }
             }
         }
     }

     int big_count = 0;
     int i_index = 0;
     int j_index = 0;
     //暴力找出出现次数最多的gram
     for(int i = 0; i < 26; ++i){
         for(int j = 0; j < 26; j++){
             if(gram[i][j] > big_count){
                 big_count  =  gram[i][j];
                 //记载出现次数最多的 gram 字母下标
                 i_index = i;
                 j_index = j;
             }
         }
     }
     cout << (char) (i_index + 'A') << (char) (j_index + 'A');//将数字转换成字符
    return 0;
}