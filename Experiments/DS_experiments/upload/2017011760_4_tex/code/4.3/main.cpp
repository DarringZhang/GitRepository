#include "BuildPathToMerge.h"
int main() {
     int n,m,a,b,ans;
     while(scanf("%d",&n)!= EOF && n){
             scanf("%d",&m);
             UnionFind pa(n,m);
             ans = 0;
             for(int i = 1; i <= m; ++ i){
                 cin>>a>>b;
                 pa.Merge(a,b);
             }

             //先路径压缩一遍
             for(int i = 1; i <= n; ++ i){
                 pa.fix_find_non_recursion(i);
             }

             //寻找parent 数组中有多少个根 即 多少个
             for(int i = 1; i <= n; ++ i){
                 if(pa.getParent()[i]==i){
                     ans ++;
                 }
             }

             cout<<ans-1;

             pa.deleteUnionFind();


    }
    return 0;
}