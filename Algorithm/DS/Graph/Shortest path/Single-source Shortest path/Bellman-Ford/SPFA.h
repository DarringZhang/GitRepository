//
// Created by lenovo on 2018/12/11.
//

#ifndef BELLMAN_FORD_SPFA_H
#define BELLMAN_FORD_SPFA_H
/*
 * Bellman-Ford算法的正确性保证依赖于路径松弛性质，我们只要能够保证最短路径中的边的松弛顺序即可，
 * Bellman-Ford算法属于一种暴力的算法，即，每次将所有的边都松弛一遍，这样肯定能保证顺序
 * 其实，实际应用中，SPFA的时间复杂度是很不稳定的，因此我们能用Dijkstra+优先队列，就用Dijkstra+优先队列为好。
 * */

/*！！！源点s到达其他的点的最短路径中的第一条边，必定是源点s与s的邻接点相连的边，因此，第一次松弛，
 * 我们只需要将这些边松弛一下即可。第二条边必定是第一次松弛的时候的邻接点与这些邻接点的邻接点相连的边
 * ！！！
 *
 *
 * 因此我们可以这样进行优化：设置一个队列，初始的时候将源点s放入，然后s出队，松弛s与其邻接点相连的边，将松弛成功的点放入队列中，
 * 然后再次取出队列中的点，松弛该点与该点的邻接点相连的边，如果松弛成功，看这个邻接点是否在队列中，没有则进入，有则不管，这里要说明一下，
 * 如果发现某点u的邻接点v已经在队列中，那么将点v再次放到队列中是没有意义的，这个v还没更新松弛，和已经在队列中的顶点一样，从队列中取出来才要松弛更新。
 * 因为即时你不放入队列中，点v的邻接点相连的边也会被松弛，
 * 只有松弛成功的边相连的邻接点，且这个点没有在队列中，这时候稍后（入队列后再出队列）对其进行松弛才有意义。因为该点已经更新，需要重新松弛。
 *
 * 优化思想和Dijkstra优化的while循环里面continue执行一样，即松弛的相对次序不变性
 *
 * 关于其判断负环，我们可以认为，在某个节点入队次数达到n的时候，就可以说明遇到了负环。
 *
 * */
#include "BellmanFord.h"

class SPFA: public BellmanFord{
public:
    SPFA(){
    }
    void Caluculate_SPFA(int s) {
        queue<int> Q;
        int u;
        for (int i = 1; i <= N; ++i) {
            distance[i] = INT_MAX;
        }
        distance[s] = 0;

        Q.push(s);
        NodeList[s].visited = true;

        while (!Q.empty()) {
            u = Q.front();
            Q.pop();

            NodeList[u].visited = false;//从队列里面出来，说明这个点要更新松弛了，那么它的邻接点也要稍后更新，所以visited = false，下次pop出它时更新松弛它的邻接点

            for (int i = 1; i <= N; ++i) {
                if (AdjMatrix[u][i] != INT_MAX) {//松弛所有和u邻接的顶点

                    if( distance[u] + AdjMatrix[u][i]< distance[i]) {//判断要放取mind前面，因为取min缩短路径后，if判断总是成立的
                        NodeList[i].pai = u;
                        if (!NodeList[i].visited) {//只将更新松弛成功的点打入队列，因为这个时候它的邻接点随着等待松弛
                            Q.push(i);
                            NodeList[i].visited = true;
                        }
                    }


                    distance[i] = min(distance[i],distance[u]+AdjMatrix[u][i]);//通过 u -> i 这条边 到达i点是否比较近


                }

            }

        }
    }
};

#endif //BELLMAN_FORD_SPFA_H
