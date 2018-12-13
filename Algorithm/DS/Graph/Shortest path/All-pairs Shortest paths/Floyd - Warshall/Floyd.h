//
// Created by Darring on 2018/12/13.
//

#ifndef FLOYD_WARSHALL_FLOYD_H
#define FLOYD_WARSHALL_FLOYD_H
/*
 * Floyd算法只能在不存在负权环的情况下使用，因为其并不能判断负权环，上面也说过，如果有负权环，那么最短路将无意义，
 * 因为我们可以不断走负权环，这样最短路径值便成为了负无穷。但是其可以处理带负权边但是无负权环的情况。
 * 以上就是求多源最短路的Floyd算法，基于动态规划，十分优雅。
 * 但是其复杂度确实是不敢恭维，因为要维护一个路径矩阵，因此空间复杂度达到了O(n^2)，时间复杂度达到了O(n^3)，只有在数据规模很小的时候，才适合使用这个算法，
 * 但是在实际的应用中，求单源最短路是最常见的，因此，非负权重的Dijkstra更好
 * */
#include <iostream>
#include <climits>
#include <cmath>
#include <string>
using namespace std;

class Floyd {
protected:
    int AdjMatrix[201][201];
    int N, M;
    int Path[201][201];

public:
    Floyd() {

    }

    void CreateGraph(int n, int m) {
        N = n;//n个顶点
        M = m;//m条路径

        for (int j = 0; j < n; ++j) {//初始化邻接矩阵 0-base
            for (int i = 0; i < n; ++i) {
                if(i==j){
                    AdjMatrix[j][i] = 0;
                }
                else{
                    AdjMatrix[j][i] = INT_MAX;
                }
            }
        }

        //初始化路径
        for (int j = 0; j < n; ++j) {//初始化邻接矩阵 0-base
            for (int i = 0; i < n; ++i) {
                Path[j][i] = -1;
            }
        }



        cout << "输入结点和权值" << endl;
        int a, b, cost;
        for (int i = 1; i <= m; ++i) {
            cin >> a >> b >> cost;
            AdjMatrix[a][b] = cost;
        }
        cout << "finish" << endl;
        Print();
    }

    /*我们从动态规划的角度考虑，解动态规划题目的重点就是合理的定义状态，划分阶段，我们定义 f[k][i][j]为经过前k的节点，
     * 从i到j所能得到的最短路径，f[k][i][j]可以从f[k-1][i][j]转移过来，即不经过第k个节点，也可以从f[k-1][i][k]+f[k-1][k][j]转移过来，
     * 即经过第k个节点。观察一下这个状态的定义，满足不满足最优子结构和无后效性原则。

     1.最优子结构：图结构中一个显而易见的定理：最短路径的子路径仍然是最短路径
    2.无后效性：状态f[k][i][j]由f[k-1][i][j]，f[k-1][i,k] 以及f[k-1][k][j]转移过来，很容易可以看出，
        f[k] 的状态完全由f[k-1]转移过来，只要我们把k放倒最外层循环中，就能保证无后效性。
        //即子状态都优化好了，保证当前状态的最优性
     * */
    void Calculate_floyd(){
        int flag = 0;
        for (int k = 0; k < N; ++k) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if(i!=j&&AdjMatrix[i][k]!=INT_MAX&&AdjMatrix[k][j]!=INT_MAX&&AdjMatrix[i][j] > AdjMatrix[i][k] + AdjMatrix[k][j]){
                    //注意这里的if判断AdjMatrix[i][k]!=INT_MAX&&AdjMatrix[k][j]!=INT_MA//
                    //因为两个INT_MAX 相加可能等于一个很小的的负数，是个不定结果，况且其中一个等于INT_MAX，不能松弛if也不成立
                        AdjMatrix[i][j] =  AdjMatrix[i][k] + AdjMatrix[k][j];
                        cout<<"=="<<++flag<<"=="<<endl;
                        Print();
                        Path[i][j] = k;

                    }
                    //AdjMatrix[i][j] = min(AdjMatrix[i][j], AdjMatrix[i][k] + AdjMatrix[k][j]);

                }
            }
        }
        Print();
    }

    // 打印中间结果
    void Print(){
        for(int i = 0; i < N; ++ i){
            for(int j = 0; j < N; ++ j){
                if(AdjMatrix[i][j]!=INT_MAX){
                    printf("%d\t",AdjMatrix[i][j]);
                }
                else{
                    printf("∞\t");
                }
            }
            cout<<endl;
        }
        printf("\n--------------------------------\n");
    }


    /*
     * 上面仅仅是知道了最短路径的长度，实际应用中我们常常是需要知道具体的路径，在Floyd算法中怎么求具体路径呢，
     *只需要记录下来在更新f[i][j]的时候，用到的中间节点是哪个就可以了。假设我们用path[i][j]记录从i到j松弛的节点k，
     * 那么从i到j,肯定是先从i到k，然后再从k到j， 那么我们在找出path[i][k] , path[k][j]即可，\
     * 即 i到k的最短路是 i -> path[i][k] -> k -> path[k][j] -> k 然后求path[i][k]和path[k][j] ，一直到某两个节点没有中间节点为止
     *
     * /

 //求具体路径:怎么返回递归字符串
    string getPath(int[][] Path, int i, int j) {
        if (Path[i][j] == -1) {
            return " "+i+" "+j;
        } else {
            int k = Path[i][j];
            return getPath(Path, i, k)+" "+getPath(Path, k, j)+" ";
        }
    }
*/
};
#endif //FLOYD_WARSHALL_FLOYD_H
