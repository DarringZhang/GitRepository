//
// Created by Darring on 2018/12/13.
//

#ifndef FLOYD_WARSHALL_SCROLLINGARRAYTOOPTIMIZATION_H
#define FLOYD_WARSHALL_SCROLLINGARRAYTOOPTIMIZATION_H
/*滚动数组是一种动态规划中常见的降维优化的方式，应用广泛（背包dp等），可以极大的减少空间复杂度。
 * 但也仅限于减少空间的复杂度
 *
 * 在我们求出的状态转移方程中，我们在更新f[k]层状态的时候，用到f[k-1]层的值，f[k-2] f[k-3]层的值就直接废弃了。
 * 所以我们大可让第一层的大小从n变成2,再进一步，我们在f[k]层更新f[k][i][j]的时候，f[k-1][i][k] 和 f[k-1][k][j] 我们如果能保证，
 * 在更新k层另外一组路径m->n的时候，不受前面更新过的f[k][i][j]的影响，就可以把第一维度去掉了。我们现在去掉第一个维度，
 * 写成我们在代码中的那样，就是f[i][j] 依赖 f[i][k] + f[k][j] 我们在更新f[m][n]的时候，用到了f[m][k] + f[k][n]
 * 假设f[i][j]的更新影响到了f[m][k] 或者 f[k][m] 即 {m=i,k=j} 或者 {k=i,n=j} 这时候有两种情况，j和k是同一个点，或者i和k是同一个点，
 * 那么 f[i][j] = f[i][j] + f[j][j]，或者f[i][j] = f[i][i]+f[i][j] 这时候，我们所谓的“前面更新的点对”还是这两个点本来的路径，
 * 也就是说，唯一两种在某一层先更新的点，影响到后更新的点的情况，是完全合理的，所以说，我们即时把第一维去掉，也满足无后效性原则。因此可以用滚动数组优化。
 * 优化之后的状态转移方程即为：f[i][j] = min(f[i][j],f[i][k]+f[k][j])。
 * */
#include "Floyd.h"
#define SIZE 50
class Scroll :public Floyd{
private:
    int[][][] f = new int[ SIZE+ 1][SIZE][SIZE];
    Scroll(){

    }

    ~Scroll(){
        for (i = 0; i < SIZE; i ++) {//学会释放三维数组
            for (j = 0; j < SIZE; j ++) {//这个for循环释放三维
                delete[] f[i][j];
            }
            delete[] f[i];//这个for循环释放二维
        }
        delete[] f;//释放一维
    }

    void Calculate_Scroll(){
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k <= N; k++) {
                    f[k][i][j] = INT_MAX;
                }
                f[0][i][j] = AdjMatrix[i][j];//在不经过任何一个点的时候，这两点的最短路径就是其初始路径
            }
        }

        for (int k = 1; k <= N; k++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    f[k][i][j] = min(f[k - 1][i][j], f[k - 1][i][k - 1] + f[k - 1][k - 1][j]);
                }//第一维k代表前k个节点，由于数组下标不能为-1，所以在第一维中，统一加上1，在更新的时候，还是通过k-1这个节点。
            }
        }
    }

//怎么打印出结果？
    void Print_Scroll(){

    }
};

#endif //FLOYD_WARSHALL_SCROLLINGARRAYTOOPTIMIZATION_H
