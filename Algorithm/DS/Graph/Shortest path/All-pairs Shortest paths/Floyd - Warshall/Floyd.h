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
#endif //FLOYD_WARSHALL_FLOYD_H
