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

#ifndef GraphBasic_hpp
#define GraphBasic_hpp

#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

class GraphBasic {
    
public:
    //797
    vector<vector<int>> result; // 收集符合条件的路径
    vector<int> path; // 0节点到终点的路径
    
    int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1}; // 表示四个方向；左右上下
    int count;
    
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

    
    
    
    
};


#endif /* GraphBasic_hpp */
