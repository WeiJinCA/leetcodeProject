//
//  GraphBasic.hpp
//  leetcodeProject
//
//  Created by WeiJin on 2024-12-07.
//  图论
//  图：多个点连成线构成图;
//  分类：有向图 和 无向图
//  度：连接节点的边的条数；有向图中分出度和入度
//  连通性：节点的连通情况； 连通图：无向图中，任意两个节点都是可以达到的；非连通图：有节点不能到达其他节点
//  强连通图：在有向图中，任何两个节点是可以相互到达的；
//  连通分量：在无向图中的极大连通子图
//  强连通分量：在有向图中极大强连通子图
//  图的构造：一般使用邻接表、邻接矩阵 或者用类来表示；主要是 朴素存储、邻接表和邻接矩阵
//  邻接矩阵 使用 二维数组来表示图结构。 邻接矩阵是从节点的角度来表示图，有多少节点就申请多大的二维数组;适用于边数接近顶点数的平方的图中
//  邻接表：使用数组+链表的方式；有多少边申请对应大小的链表节点
//  遍历方式：
//    深度优先dfs:沿一个方向搜，直到搜不下去了，然后回溯
//    广度优先bfs：先把本节点的所有链接节点搜一遍，然后搜下一个节点；适合于解决两个点之间的最短路径问题

//  查并集： 判断两个元素是否在同一个集合里；2个作用：1.将两个元素添加到一个集合中;2.判断两个元素在不在同一个集合
//  解决的问题：连通性问题：元素在同一个集合中，即将三个元素连通在一起；用father[A] = B，father[B] = C表示
//  路径压缩：return u == father[u] ? u : father[u] = find(father[u]);
//  路径压缩：第2种方法：按秩(rank)合并；rank表示树的高度，即树中结点层次的最大值；
//     两棵树的合并原则：rank小的树合并到rank大的树，保证合成的树rank最小（层次最少），降低在树上的查询路径长度

//  最小生成树：所有节点的最小连通子图：以最小的成本（边的权值）将图中所有节点链接到一起
//  边数量较少为稀疏图，接近或等于完全图（所有节点皆相连）为稠密图
//  Prim算法：从节点的角度 采用贪心的策略 每次寻找距离 最小生成树最近的节点 并加入到最小生成树中。minDist数组 用来记录 每一个节点距离最小生成树的最近距离；可以负权值
//  Kruskal算法:维护边的集合；如果求解题目中边少节点多，用kruskal算法比较好（稀疏图）

//  拓扑排序：如打印文件依赖问题；
//  拓扑排序：给出一个 有向图，把这个有向图转成线性的排序；
//    要检测是否有环，如果存在循环依赖的情况，是不能做线性排序的；方法：当找不到入度为0的节点时，结果集中的节点小于总节点数，说明剩下的是环
//    图论中判断有向无环图的常用方法
//  节点的入度表示 有多少条边指向它，节点的出度表示有多少条边 从该节点出发。
//  出发节点：优先找 入度为 0 的节点，只有入度为0，它才是出发节点
//  步骤：1. 找到入度为0的节点，加入结果集；2.将该节点从图中移除；3. 循环步骤1和2，直到所有节点都被移除

//  dijkstra算法：在有权图（权值非负数）中求从起点到其他节点的最短路径算法；和Prim类似，但不能有负权值
//  dijkstra 算法可以同时求 起点到所有节点的最短路径；权值不能为负数
//  minDist数组的含义：记录所有节点到源点的最短路径

//  Bellman_ford算法： 允许权值为负
//  核心思想是 对所有边进行松弛n-1次操作（n为节点数量），从而求得目标最短路
//  放松：relax the edge：if (minDist[B] > minDist[A] + value) minDist[B] = minDist[A] + value
//  采用了动态规划的思想，即：将一个问题分解成多个决策阶段，通过状态之间的递归关系最后计算出全局最优解。
#ifndef GraphBasic_hpp
#define GraphBasic_hpp

#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <list>
#include <queue>

using namespace std;

class GraphBasic {
private:
    static  int bitCount1356(int n);
    static  bool cmp1356(int a, int b);
public:
    //797
    vector<vector<int>> result; // 收集符合条件的路径
    vector<int> path; // 0节点到终点的路径
    
    int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1}; // 表示四个方向；左右上下
    int count;
    
    //并查集
    int n = 1005; // n根据题目中节点数量而定，一般比节点数量大一点就好
    vector<int> father = vector<int> (n, 0); // C++里的一种数组结构
    vector<int> rank = vector<int> (n, 1); // 初始每棵树的高度都为1
    
    //20 Kama53
    // l,r为 边两边的节点，val为边的数值
    struct Edge {
        int l, r, val;
    };
    
    //23
    struct Edge1 {
        int to;  // 邻接顶点
        int val; // 边的权重

        Edge1(int t, int w): to(t), val(w) {}  // 构造函数
    };
    // 小顶堆
    class mycomparison {
    public:
        bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) {
            return lhs.second > rhs.second;
        }
    };
    
    //Kama126
    int moves[1001][1001];
    int dir1[8][2]={-2,-1,-2,1,-1,2,1,2,2,1,2,-1,1,-2,-1,-2};
    int b1, b2;
    // F = G + H
    // G = 从起点到该节点路径消耗
    // H = 该节点到终点的预估消耗

    struct Knight{
        int x,y;
        int g,h,f;
        bool operator < (const Knight & k) const{  // 重载运算符， 从小到大排序
         return k.f < f;
        }
    };

    priority_queue<Knight> que;
    
    //3
    void includeInput797Matrix();
    void dfs797Matrix (const vector<vector<int>>& graph, int x, int n);//797
    //Adjacency List写法
    void includeInput797List();
    void dfs797List (const vector<list<int>>& graph, int x, int n);//797
    //4
    void bfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int x, int y);
    //5
    void includeInputKama99Dfs();
    void dfsKama99(const vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) ;
    void includeInputKama99Bfs();
    void bfsKama99(const vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) ;
    //7
    void includeInputKama100Dfs();
    void dfsKama100(const vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) ;
    int maxAreaOfIslandKama100(vector<vector<int>>& grid);
    void bfsKama100(const vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) ;
    //8
    void includeInputKama101Dfs();
    void dfsKama101(vector<vector<int>>& grid, int x, int y) ;
    int includeInputKama101Bfs();
    void bfsKama101(vector<vector<int>>& grid, int x, int y) ;
    //9
    void includeInputKama102Dfs();
    void dfsKama102(vector<vector<int>>& grid, int x, int y) ;
    //10
    void includeInputKama103Dfs();
    void dfsKama103(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) ;
    //11
    void includeInputKama104Dfs();
    void dfsKama104(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y, int mark) ;
    //12
    void includeInputKama110Bfs();
    //13
    void includeInputKama105Dfs1();
    void dfs1Kama105(const vector<list<int>>& graph, int key, vector<bool>& visited) ;
    void includeInputKama105Dfs2();
    void dfs2Kama105(const vector<list<int>>& graph, int key, vector<bool>& visited) ;
    void bfsKama105() ;
    //14
    void includeInputKama106_1();
    void includeInputKama106_2();
    //15并查集
    // 并查集初始化
    void init() ;
    // 并查集里寻根的过程
    int find(int u) ;
    // 判断 u 和 v是否找到同一个根
    bool isSame(int u, int v);
    // 将v->u 这条边加入并查集
    void join(int u, int v);
    
    //16
    void includeInputKama107();//
    //17
    void includeInputKama108();
    //18
    void includeInputKama109();
    void getRemoveEdge(const vector<vector<int>>& edges);
    bool isTreeAfterRemoveEdge(const vector<vector<int>>& edges, int deleteEdge);
    //19
    void includeInputKama53Prim();
    //20
    void includeInputKama53Kruskal();
    //21
    void includeInputKama117();
    //22
    void includeInputKama47();
    //23
    void includeInputKama47_v2();
    //24
    void includeInputKama94();
    //25
    void includeInputKama94_v2();
    //26
    void includeInputKama95();
    void includeInputKama95_SPFA();
    //27
    void includeInputKama96();
    void includeInputKama96_SPFA();
    //28 Floyd 算法
    void includeInputKama97();
    void includeInputKama97_2D();
    //29 A star算法
    void includeInputKama126();
    int  Heuristic(const Knight& k);//欧拉距离
    void astar(const Knight& k);
    
    //额外题目
    bool canVisitAllRoomsByDfs(vector<vector<int>>& rooms);//841
    void dfs841(const vector<vector<int>>& rooms, int key, vector<bool>& visited);
    bool canVisitAllRoomsByBfs(vector<vector<int>>& rooms);//841
    int ladderLength127(string beginWord, string endWord, vector<string>& wordList);//127
    vector<int> findRedundantConnection684(vector<vector<int>>& edges);//684
    vector<int> findRedundantConnection685(vector<vector<int>>& edges);//685 类似kama109
    //非图题目
    bool judgeCircle657(string moves);
    void nextPermutation31(vector<int>& nums);//31
    vector<int> sortByBits1356(vector<int>& arr) ;//1356
    
};


#endif /* GraphBasic_hpp */
