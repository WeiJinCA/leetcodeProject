//
//  GraphBasic.cpp
//  leetcodeProject
//
//  Created by WeiJin on 2024-12-07.
//

#include "GraphBasic.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <queue>
#include <unordered_set>
#include <unordered_map>
using namespace std;

//邻接矩阵的写法，带构造图的代码
void GraphBasic::includeInput797Matrix(){
    
    int n,m,s,t;
    //测试用例：
    //5 5
    //1 3
    //3 5
    //1 2
    //2 4
    //4 5
    cin >> n >> m;
    
    // 节点编号从1到n，所以申请 n+1 这么大的数组
    vector<vector<int>> graph(n + 1, vector<int>(n + 1, 0));
    
    while (m--) {
            cin >> s >> t;
            // 使用邻接矩阵 表示无线图，1 表示 s 与 t 是相连的
            graph[s][t] = 1;
        }

    path.push_back(1); // 无论什么路径一定是从0节点出发
    dfs797Matrix(graph, 1, n); // 开始遍历

        // 输出结果
        if (result.size() == 0) cout << -1 << endl;
        for (const vector<int> &pa : result) {
            for (int i = 0; i < pa.size() - 1; i++) {
                cout << pa[i] << " ";
            }
            cout << pa[pa.size() - 1]  << endl;
        }
}
//力扣797只包含搜索，没有构造图的代码
void GraphBasic::dfs797Matrix (const vector<vector<int>>& graph, int x, int n){
    // 当前遍历的节点x 到达节点n
        if (x == n) { // 找到符合条件的一条路径
            result.push_back(path);
            return;
        }
        for (int i = 1; i <= n; i++) { // 遍历节点x链接的所有节点
            if (graph[x][i] == 1) { // 找到 x链接的节点
                path.push_back(i); // 遍历到的节点加入到路径中来
                dfs797Matrix(graph, i, n); // 进入下一层递归
                path.pop_back(); // 回溯，撤销本节点
            }
        }
}
void GraphBasic::includeInput797List(){
    int n, m, s, t;
        cin >> n >> m;

        // 节点编号从1到n，所以申请 n+1 这么大的数组
        vector<list<int>> graph(n + 1); // 邻接表
        while (m--) {
            cin >> s >> t;
            // 使用邻接表 ，表示 s -> t 是相连的
            graph[s].push_back(t);

        }

        path.push_back(1); // 无论什么路径已经是从0节点出发
    dfs797List(graph, 1, n); // 开始遍历

        // 输出结果
        if (result.size() == 0) cout << -1 << endl;
        for (const vector<int> &pa : result) {
            for (int i = 0; i < pa.size() - 1; i++) {
                cout << pa[i] << " ";
            }
            cout << pa[pa.size() - 1]  << endl;
        }
}
void GraphBasic::dfs797List (const vector<list<int>>& graph, int x, int n){
    if (x == n) { // 找到符合条件的一条路径
            result.push_back(path);
            return;
        }
        for (int i : graph[x]) { // 找到 x指向的节点
            path.push_back(i); // 遍历到的节点加入到路径中来
            dfs797List(graph, i, n); // 进入下一层递归
            path.pop_back(); // 回溯，撤销本节点
        }
}
//广搜的实例代码
// grid 是地图，也就是一个二维数组
// visited标记访问过的节点，不要重复访问
// x,y 表示开始搜索节点的下标
void GraphBasic::bfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int x, int y){
    queue<pair<int, int>> que; // 定义队列
    que.push({x, y}); // 起始节点加入队列
    visited[x][y] = true; // 只要加入队列，立刻标记为访问过的节点
    while(!que.empty()) { // 开始遍历队列里的元素
            pair<int ,int> cur = que.front(); que.pop(); // 从队列取元素
            int curx = cur.first;
            int cury = cur.second; // 当前节点坐标
            for (int i = 0; i < 4; i++) { // 开始想当前节点的四个方向左右上下去遍历
                int nextx = curx + dir[i][0];
                int nexty = cury + dir[i][1]; // 获取周边四个方向的坐标
                if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;  // 坐标越界了，直接跳过
                if (!visited[nextx][nexty]) { // 如果节点没被访问过
                    que.push({nextx, nexty});  // 队列添加该节点为下一轮要遍历的节点
                    visited[nextx][nexty] = true; // 只要加入队列立刻标记，避免重复访问
                }
            }
    }
}
//Kama99:岛屿问题：求陆地数量
//解法：只要碰到未访问的陆地，result++; 同时搜索与之相连的陆地，标记为访问过即可
void GraphBasic::includeInputKama99Dfs(){
    int n, m;
    //测试用例
    //4 5
    //1 1 0 0 0
    //1 1 0 0 0
    //0 0 1 0 0
    //0 0 0 1 1
        cin >> n >> m;
    
        vector<vector<int>> grid(n, vector<int>(m, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> grid[i][j];
            }
        }

        vector<vector<bool>> visited(n, vector<bool>(m, false));

        int result = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!visited[i][j] && grid[i][j] == 1) {
                    result++; // 遇到没访问过的陆地，+1
                    dfsKama99(grid, visited, i, j); // 将与其链接的陆地都标记上 true
                }
            }
        }
        cout << result << endl;
}
void GraphBasic::dfsKama99(const vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) {
    for (int i = 0; i < 4; i++) {
            int nextx = x + dir[i][0];
            int nexty = y + dir[i][1];
            if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;  // 越界了，直接跳过
            if (!visited[nextx][nexty] && grid[nextx][nexty] == 1) { // 没有访问过的 同时 是陆地的;隐形终止条件

                visited[nextx][nexty] = true;
                dfsKama99(grid, visited, nextx, nexty);
            }
        }
}
void GraphBasic::includeInputKama99Bfs(){
    int n, m;
        cin >> n >> m;
        vector<vector<int>> grid(n, vector<int>(m, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> grid[i][j];
            }
        }

        vector<vector<bool>> visited(n, vector<bool>(m, false));

        int result = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!visited[i][j] && grid[i][j] == 1) {
                    result++; // 遇到没访问过的陆地，+1
                    bfsKama99(grid, visited, i, j); // 将与其链接的陆地都标记上 true
                }
            }
        }


        cout << result << endl;
}
void GraphBasic::bfsKama99(const vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y){
    queue<pair<int, int>> que;
        que.push({x, y});
        visited[x][y] = true; // 只要加入队列，立刻标记
        while(!que.empty()) {
            pair<int ,int> cur = que.front(); que.pop();
            int curx = cur.first;
            int cury = cur.second;
            for (int i = 0; i < 4; i++) {
                int nextx = curx + dir[i][0];
                int nexty = cury + dir[i][1];
                if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;  // 越界了，直接跳过
                if (!visited[nextx][nexty] && grid[nextx][nexty] == 1) {
                    que.push({nextx, nexty});
                    visited[nextx][nexty] = true; // 只要加入队列立刻标记;提高效率，而非在取出时标记
                }
            }
        }
}
//Kama100: 岛屿问题：求岛屿的最大面积,计算最大陆地的格子数
void GraphBasic::includeInputKama100Dfs(){
    int n, m;
        cin >> n >> m;
        vector<vector<int>> grid(n, vector<int>(m, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> grid[i][j];
            }
        }
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        int result = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!visited[i][j] && grid[i][j] == 1) {
                    count = 1;  // 因为dfs处理下一个节点，所以这里遇到陆地了就先计数，dfs处理接下来的相邻陆地
                    visited[i][j] = true;
                    dfsKama100(grid, visited, i, j); // 将与其链接的陆地都标记上 true
                    result = max(result, count);
                }
            }
        }
        cout << result << endl;
}
//此处：dfs只处理下一个节点，即在主函数遇到岛屿就计数为1，dfs处理接下来的相邻陆地；
//还有一种写法，所有计数都在dfs中处理，此时没有if语句，但在函数开始要加终止条件，并且count++写在for循环前面
//if (visited[x][y] || grid[x][y] == 0) return; // 终止条件：访问过的节点 或者 遇到海水
void GraphBasic::dfsKama100(const vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) {
    for (int i = 0; i < 4; i++) {
            int nextx = x + dir[i][0];
            int nexty = y + dir[i][1];
            if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;  // 越界了，直接跳过
            if (!visited[nextx][nexty] && grid[nextx][nexty] == 1) { // 没有访问过的 同时 是陆地的
                visited[nextx][nexty] = true;
                count++;
                dfsKama100(grid, visited, nextx, nexty);
            }
        }
}
//广度优先
int GraphBasic::maxAreaOfIslandKama100(vector<vector<int>>& grid) {
    int n = static_cast<int>(grid.size()) , m = static_cast<int>(grid[0].size());
        vector<vector<bool>> visited = vector<vector<bool>>(n, vector<bool>(m, false));
        int result = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!visited[i][j] && grid[i][j] == 1) {
                    count = 0;
                    bfsKama100(grid, visited, i, j); // 将与其链接的陆地都标记上 true
                    result = max(result, count);
                }
            }
        }
        return result;
}
void GraphBasic::bfsKama100(const vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) {
    queue<int> que;
    que.push(x);
    que.push(y);
    visited[x][y] = true; // 加入队列就意味节点是陆地可到达的点
    count++;
    while(!que.empty()) {
                int xx = que.front();que.pop();
                int yy = que.front();que.pop();
                for (int i = 0 ;i < 4; i++) {
                    int nextx = xx + dir[i][0];
                    int nexty = yy + dir[i][1];
                    if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue; // 越界
                    if (!visited[nextx][nexty] && grid[nextx][nexty] == 1) { // 节点没有被访问过且是陆地
                        visited[nextx][nexty] = true;
                        count++;
                        que.push(nextx);
                        que.push(nexty);
                    }
                }
    }
}
//孤岛的总面积
//孤岛：位于矩阵内部，所有边都不接触边缘的岛屿，
//解法：只要从周边找到陆地然后 通过 dfs或者bfs 将周边靠陆地且相邻的陆地都变成海洋，然后再去重新遍历地图 统计此时还剩下的陆地就可以了
void GraphBasic::includeInputKama101Dfs(){
    int n, m;
        cin >> n >> m;
        vector<vector<int>> grid(n, vector<int>(m, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> grid[i][j];
            }
        }

        // 从左侧边，和右侧边 向中间遍历
        for (int i = 0; i < n; i++) {
            if (grid[i][0] == 1) dfsKama101(grid, i, 0);
            if (grid[i][m - 1] == 1) dfsKama101(grid, i, m - 1);
        }
        // 从上边和下边 向中间遍历
        for (int j = 0; j < m; j++) {
            if (grid[0][j] == 1) dfsKama101(grid, 0, j);
            if (grid[n - 1][j] == 1) dfsKama101(grid, n - 1, j);
        }
        count = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) dfsKama101(grid, i, j);
            }
        }
        cout << count << endl;
}
void GraphBasic::dfsKama101(vector<vector<int>>& grid, int x, int y) {
    grid[x][y] = 0;//访问过的置0
    count++;
    for (int i = 0; i < 4; i++) { // 向四个方向遍历
            int nextx = x + dir[i][0];
            int nexty = y + dir[i][1];
            // 超过边界
            if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;
            // 不符合条件，不继续遍历
            if (grid[nextx][nexty] == 0) continue;

            dfsKama101 (grid, nextx, nexty);
    }
    return;
}
int GraphBasic::includeInputKama101Bfs(){
    int n, m;
        cin >> n >> m;
        vector<vector<int>> grid(n, vector<int>(m, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> grid[i][j];
            }
        }
        // 从左侧边，和右侧边 向中间遍历
        for (int i = 0; i < n; i++) {
            if (grid[i][0] == 1) bfsKama101(grid, i, 0);
            if (grid[i][m - 1] == 1) bfsKama101(grid, i, m - 1);
        }
        // 从上边和下边 向中间遍历
        for (int j = 0; j < m; j++) {
            if (grid[0][j] == 1) bfsKama101(grid, 0, j);
            if (grid[n - 1][j] == 1) bfsKama101(grid, n - 1, j);
        }
        count = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) bfsKama101(grid, i, j);
            }
        }

        cout << count << endl;
    return count;
}
void GraphBasic::bfsKama101(vector<vector<int>>& grid, int x, int y) {
    queue<pair<int, int>> que;
        que.push({x, y});
        grid[x][y] = 0; // 只要加入队列，立刻标记
        count++;
        while(!que.empty()) {
            pair<int ,int> cur = que.front(); que.pop();
            int curx = cur.first;
            int cury = cur.second;
            for (int i = 0; i < 4; i++) {
                int nextx = curx + dir[i][0];
                int nexty = cury + dir[i][1];
                if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;  // 越界了，直接跳过
                if (grid[nextx][nexty] == 1) {
                    que.push({nextx, nexty});
                    count++;
                    grid[nextx][nexty] = 0; // 只要加入队列立刻标记
                }
            }
        }
}
//沉没孤岛：将孤岛的值1反转为0
//思路：从地图周边出发，将周边空格相邻的陆地都做上标记，然后在遍历一遍地图，遇到 陆地 且没做过标记的，那么都是地图中间的陆地，全部改成水域就行
//做法：将周边陆地改为2(遍历)，将中间陆地改为0，然后再将2改为1
void GraphBasic::includeInputKama102Dfs(){
    int n, m;
        cin >> n >> m;
        vector<vector<int>> grid(n, vector<int>(m, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> grid[i][j];
            }
        }

        // 步骤一：
        // 从左侧边，和右侧边 向中间遍历
        for (int i = 0; i < n; i++) {
            if (grid[i][0] == 1) dfsKama102(grid, i, 0);
            if (grid[i][m - 1] == 1) dfsKama102(grid, i, m - 1);
        }

        // 从上边和下边 向中间遍历
        for (int j = 0; j < m; j++) {
            if (grid[0][j] == 1) dfsKama102(grid, 0, j);
            if (grid[n - 1][j] == 1) dfsKama102(grid, n - 1, j);
        }
        // 步骤二、步骤三
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) grid[i][j] = 0;
                if (grid[i][j] == 2) grid[i][j] = 1;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
}
void GraphBasic::dfsKama102(vector<vector<int>>& grid, int x, int y){
    grid[x][y] = 2;
        for (int i = 0; i < 4; i++) { // 向四个方向遍历
            int nextx = x + dir[i][0];
            int nexty = y + dir[i][1];
            // 超过边界
            if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;
            // 不符合条件，不继续遍历
            if (grid[nextx][nexty] == 0 || grid[nextx][nexty] == 2) continue;
            dfsKama102 (grid, nextx, nexty);
        }
        return;
}
//Kama103水流问题：找格子中雨水可以同时流出左上边界和右下边界的格子
//思路：从左上格子、右下格子出发，逆流而上，分别标记两种出发点的格子；当该格子同时被标记，则说明它满足要求
void GraphBasic::includeInputKama103Dfs(){
    int n,m;
    cin >> n >> m;
        vector<vector<int>> grid(n, vector<int>(m, 0));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> grid[i][j];
            }
        }
        // 标记从第一组边界上的节点出发，可以遍历的节点
        vector<vector<bool>> firstBorder(n, vector<bool>(m, false));

        // 标记从第一组边界上的节点出发，可以遍历的节点
        vector<vector<bool>> secondBorder(n, vector<bool>(m, false));

        // 从最上和最下行的节点出发，向高处遍历
        for (int i = 0; i < n; i++) {
            dfsKama103 (grid, firstBorder, i, 0); // 遍历最左列，接触第一组边界
            dfsKama103 (grid, secondBorder, i, m - 1); // 遍历最右列，接触第二组边界
        }

        // 从最左和最右列的节点出发，向高处遍历
        for (int j = 0; j < m; j++) {
            dfsKama103 (grid, firstBorder, 0, j); // 遍历最上行，接触第一组边界
            dfsKama103 (grid, secondBorder, n - 1, j); // 遍历最下行，接触第二组边界
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // 如果这个节点，从第一组边界和第二组边界出发都遍历过，就是结果
                if (firstBorder[i][j] && secondBorder[i][j]) cout << i << " " << j << endl;;
            }
        }
}
void GraphBasic::dfsKama103(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y){
    int n = static_cast<int>(grid.size()) , m = static_cast<int>(grid[0].size());
    if (visited[x][y]) return;

        visited[x][y] = true;

        for (int i = 0; i < 4; i++) {
            int nextx = x + dir[i][0];
            int nexty = y + dir[i][1];
            if (nextx < 0 || nextx >= n || nexty < 0 || nexty >= m) continue;
            if (grid[x][y] > grid[nextx][nexty]) continue; // 注意：这里是从低向高遍历;方法与要求相反

            dfsKama103 (grid, visited, nextx, nexty);
        }
        return;
}
//Kama104:建立最大人工岛：反转一个格子的水域为陆地，以获得最大面积的陆地岛屿
void GraphBasic::includeInputKama104Dfs(){
    int n,m;
    cin >> n >> m;
        vector<vector<int>> grid(n, vector<int>(m, 0));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> grid[i][j];
            }
        }
        vector<vector<bool>> visited(n, vector<bool>(m, false)); // 标记访问过的点
        unordered_map<int ,int> gridNum;
        int mark = 2; // 记录每个岛屿的编号
        bool isAllGrid = true; // 标记是否整个地图都是陆地
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 0) isAllGrid = false;
                if (!visited[i][j] && grid[i][j] == 1) {
                    count = 0;
                    dfsKama104(grid, visited, i, j, mark); // 将与其链接的陆地都标记上 true
                    gridNum[mark] = count; // 记录每一个岛屿的面积
                    mark++; // 记录下一个岛屿编号
                }
            }
        }
        if (isAllGrid) {
            cout << n * m << endl; // 如果都是陆地，返回全面积
            return ; // 结束程序
        }

        // 以下逻辑是根据添加陆地的位置，计算周边岛屿面积之和
        int result = 0; // 记录最后结果
        unordered_set<int> visitedGrid; // 标记访问过的岛屿;存放的是mark值；后面用count()函数判断mark区域是否已经累加过
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                count = 1; // 记录连接之后的岛屿数量
                visitedGrid.clear(); // 每次使用时，清空
                if (grid[i][j] == 0) {
                    for (int k = 0; k < 4; k++) {
                        int neari = i + dir[k][1]; // 计算相邻坐标
                        int nearj = j + dir[k][0];
                        if (neari < 0 || neari >= n || nearj < 0 || nearj >= m) continue;
                        if (visitedGrid.count(grid[neari][nearj])) continue; // 添加过的岛屿不要重复添加
                        // 把相邻四面的岛屿数量加起来
                        count += gridNum[grid[neari][nearj]];
                        visitedGrid.insert(grid[neari][nearj]); // 标记该岛屿已经添加过
                    }
                }
                result = max(result, count);//对每个水域格子，将其变为陆地1时的最大岛屿面积的最大值
            }
        }
        cout << result << endl;
}
void GraphBasic::dfsKama104(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y, int mark) {
    int n = static_cast<int>(grid.size()) , m = static_cast<int>(grid[0].size());
    if (visited[x][y] || grid[x][y] == 0) return; // 终止条件：访问过的节点 或者 遇到海水
        visited[x][y] = true; // 标记访问过
        grid[x][y] = mark; // 给陆地标记新标签
        count++;
        for (int i = 0; i < 4; i++) {
            int nextx = x + dir[i][0];
            int nexty = y + dir[i][1];
            if (nextx < 0 || nextx >= n || nexty < 0 || nexty >= m) continue;  // 越界了，直接跳过
            dfsKama104(grid, visited, nextx, nexty, mark);
        }
}
//Kama110 : 字符串接龙: 从起始字符串 转换为结尾字符串，每次变换一个字母，且转换过程中的字符串必须在List中，求最短转换字符串数目
void GraphBasic::includeInputKama110Bfs(){
    //输入录入
    string beginStr, endStr, str;
        int n;
        cin >> n;
        unordered_set<string> strSet;
        cin >> beginStr >> endStr;
        for (int i = 0; i < n; i++) {
            cin >> str;
            strSet.insert(str);
        }
    
    // 记录strSet里的字符串是否被访问过，同时记录路径长度
        unordered_map<string, int> visitMap; // <记录的字符串，路径长度>

        // 初始化队列
        queue<string> que;
        que.push(beginStr);

        // 初始化visitMap
        visitMap.insert(pair<string, int>(beginStr, 1));
    
    while(!que.empty()) {
            string word = que.front();
            que.pop();
            int path = visitMap[word]; // 这个字符串在路径中的长度

            // 开始在这个str中，挨个字符去替换
            for (int i = 0; i < word.size(); i++) {
                string newWord = word; // 用一个新字符串替换str，因为每次要置换一个字符

                // 遍历26的字母
                for (int j = 0 ; j < 26; j++) {
                    newWord[i] = j + 'a';
                    if (newWord == endStr) { // 发现替换字母后，字符串与终点字符串相同
                        cout <<  path + 1 << endl; // 找到了路径
                        return ;
                    }
                    // 字符串集合里出现了newWord，并且newWord没有被访问过
                    if (strSet.find(newWord) != strSet.end()
                            && visitMap.find(newWord) == visitMap.end()) {
                        // 添加访问信息，并将新字符串放到队列中
                        visitMap.insert(pair<string, int>(newWord, path + 1));
                        que.push(newWord);
                    }
                }
            }
        }

        // 没找到输出0
        cout << 0 << endl;
}
//105 有向图的完全可达性：从某个节点可以达到其他任意节点：有向图搜索全路径的问题
void GraphBasic::includeInputKama105Dfs1(){
    int n,m,s,t;
    cin >> n >> m;
    
    // 节点编号从1到n，所以申请 n+1 这么大的数组
    vector<list<int>> graph(n+1);//邻接表
    while(m--){
        cin >> s >> t;
        //使用邻接表 ，表示 s -> t 是相连的
        graph[s].push_back(t);
    }
    vector<bool> visited(n+1,false);
    
    dfs1Kama105(graph,1,visited);
    //检查是否都访问到了
    for (int i = 1; i <= n; i++) {
        if(visited[i] == false){
            cout << -1 << endl;
            return;
        }
    }
    cout << 1 << endl;
}
// 写法一：dfs 处理当前访问的节点：即标记当前节点visited为true
// key 当前得到的可以； visited 记录访问过的房间
void GraphBasic::dfs1Kama105(const vector<list<int>>& graph, int key, vector<bool>& visited) {
    if(visited[key]){
        return;//已访问过就返回
    }
    
    visited[key] = true;//如果最后还有没访问到的（还有节点为false）,说明不完全可达
    list<int> keys = graph[key];
    for (int key : keys) {
        //深度优先搜索遍历
        dfs1Kama105(graph,key,visited);
    }
}
//写法二：dfs处理下一个要访问的节点
void GraphBasic::includeInputKama105Dfs2(){
    int n,m,s,t;
    cin >> n >> m;
    
    // 节点编号从1到n，所以申请 n+1 这么大的数组
    vector<list<int>> graph(n+1);//邻接表
    while(m--){
        cin >> s >> t;
        //使用邻接表 ，表示 s -> t 是相连的
        graph[s].push_back(t);
    }
    vector<bool> visited(n+1,false);
    
    visited[1] = true; // 节点1 预先处理；dfs处理下一个节点
    dfs2Kama105(graph,1,visited);
    //检查是否都访问到了
    for (int i = 1; i <= n; i++) {
        if(visited[i] == false){
            cout << -1 << endl;
            return;
        }
    }
    cout << 1 << endl;
}
void GraphBasic::dfs2Kama105(const vector<list<int>>& graph, int key, vector<bool>& visited){

    list<int> keys = graph[key];
    for (int key : keys) {
        if (visited[key] == false) {// 确认下一个是没访问过的节点;如果是访问过的，则跳过，所以不需要终止条件
            visited[key] = true;
            //深度优先搜索遍历
            dfs2Kama105(graph,key,visited);
        }
    }
}
//广度优先搜索，使用队列
void GraphBasic::bfsKama105() {
    int n, m, s, t;
        cin >> n >> m;

        vector<list<int>> graph(n + 1);
        while (m--) {
            cin >> s >> t;
            graph[s].push_back(t);

        }
        vector<bool> visited(n + 1, false);
        visited[1] = true; //  1 号房间开始
        queue<int> que;
        que.push(1); //  1 号房间开始
    
    //广度优先搜索的过程
    while (!que.empty()) {
        int key = que.front();que.pop();
        list<int> keys = graph[key];
        for(int key:keys){
            if(!visited[key]){//如果没访问过，则加入队列访问
                que.push(key);
                visited[key] = true;
            }
        }
    }
    
    for (int i = 1; i <= n; i++) {
            if (visited[i] == false) {
                cout << -1 << endl;
                return ;
            }
        }
    cout << 1 << endl;
}
//Kama106 岛屿的周长，2种思路
//思路1: 如果格子的上下左右的格子是水域或出界了，说明该边是边界
void GraphBasic::includeInputKama106_1(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> grid(n,vector<int>(m,0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; i < m; j++){
            cin >> grid[i][j];
        }
    }
    
    int direction[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};
    int result = 0;//记录边数
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if(grid[i][j] == 1){
                for (int k = 0; k < 4; k++) {//遍历4个方向
                    int x = i + direction[k][0];
                    int y = i + direction[k][1];//计算周边坐标x,y
                    if(x < 0 || x >= grid.size() //x在边界上
                       || y < 0 || y >= grid[0].size() //y在边界上
                       || grid[x][y] == 0){ //x,y位置是水域
                        result++;
                    }
                }
            }
        }
    }
    cout << result << endl;
}
//思路2:边的数量 = 陆地格子数 * 4 - 相邻格子的个数 * 2；相邻格子的边是内边，应排除
void GraphBasic::includeInputKama106_2(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> grid(n,vector<int>(m,0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; i < m; j++){
            cin >> grid[i][j];
        }
    }
    
    int sum = 0;//陆地数量
    int cover = 0;//相邻数量
    for (int i =0; i< n; i++) {
        for (int j =0; i< m; j++){
            if (grid[i][j] == 1) {
                sum++;//统计总的陆地数量
                //统计上边相邻陆地
                if(i - 1 >= 0 && grid[i - 1][j] == 1) cover++;//如果上方的格子为陆地，则说明共边
                //统计左边相邻陆地
                if(j - 1 >= 0 && grid[i][j - 1] == 1) cover++;//如果左方的格子为陆地，则说明共边
                //没有统计下边和右边，因为避免重复计算
            }
        }
        
    }
    
    cout << sum * 4 - cover * 2 << endl;
}

//并查集：模版
// 并查集初始化
void GraphBasic::init() {
    for (int i = 0; i < n; ++i) {
        father[i] = i;
    }
}
// 并查集里寻根的过程：判断这个节点的祖先节点是哪个
int GraphBasic::find(int u) {
    return u == father[u] ? u : father[u] = find(father[u]); // 路径压缩;每次查下都将返回的根赋给父节点，即让父节点直接指向根节点
}

// 判断 u 和 v是否找到同一个根
bool GraphBasic::isSame(int u, int v) {
    u = find(u);
    v = find(v);
    return u == v;
}

// 将v->u 这条边加入并查集：将两个节点连在同一个根节点上
void GraphBasic::join(int u, int v) {
    u = find(u); // 寻找u的根
    v = find(v); // 寻找v的根
    
    //推荐 第1种方法：路径压缩，写在find()函数里
    //空间复杂度：O(n) ，申请一个father数组
    //时间复杂度：在O(logn)与O(1)之间
    //在第一次查询的时候，相当于是n叉树上从叶子节点到根节点的查询过程，时间复杂度是logn；但路径压缩后，后面的查询操作都是O(1)，而 join 函数 和 isSame函数 里涉及的查询操作也是一样的过程
    if (u == v) return ; // 如果发现根相同，则说明在一个集合，不用两个节点相连直接返回
    father[v] = u;//此时的u和v都是根，而不能直接用u,v链接，这保证了isSame查询结果的正确性
    
    //第2种方法：按rank合并时，find()函数中改为 return u == father[u] ? u : find(father[u]);不能路径压缩，因为rank[v]数值就不准了
//    if (rank[u] <= rank[v]) father[u] = v; // rank小的树合入到rank大的树
//    else father[v] = u;
//
//    if (rank[u] == rank[v] && u != v) rank[v]++; // 如果两棵树高度相同，则v的高度+1，因为上面 if (rank[u] <= rank[v]) father[u] = v; 注意是 <=
}

//Kama107 寻找存在的路径
void GraphBasic::includeInputKama107(){
    int m,s,t,source,destination;
    cin >> n >> m;
    init();
    while(m--){
        cin >> s >> t;
        join(s,t);
    }
    
    cin >> source >> destination;
    if(isSame(source,destination)) cout << 1 << endl;
    else cout << 0 << endl;
}
//kama108 返回冗余边
void GraphBasic::includeInputKama108(){
    int s,t;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s >> t;
        if(isSame(s,t)){
            cout << s << " " << t << endl;
            return ;
        }else {
            join(s,t);
        }
    }
}
//kama109 返回冗余边，得到有向树：该树只有一个根节点，除了根节点，其他节点只有一个父节点
//有向树的特点：只有根节点入度为0，其他节点入度都为1
//情况1:有节点入度为2，此时删除一条边后，它是一个树，满足要求；从后向前遍历，因为优先删除后面那一条边
//情况2:没有入度为2的节点，此时包含有向环，删除构成环的边即可
void GraphBasic::includeInputKama109(){
    int s,t;
    vector<vector<int>> edges;
    cin >> n;
    vector<int> inDegree(n + 1, 0); // 记录节点入度
    for (int i = 0; i < n; i++) {
        cin >> s >> t;
        inDegree[t]++;
        edges.push_back({s,t});
    }
    
    vector<int> vec; // 记录入度为2的边（如果有的话就两条边）
        // 找入度为2的节点所对应的边，注意要倒序，因为优先删除最后出现的一条边
        for (int i = n - 1; i >= 0; i--) {
            if (inDegree[edges[i][1]] == 2) {
                vec.push_back(i);
            }
        }
    
    // 情况一、情况二
        if (vec.size() > 0) {
            // 放在vec里的边已经按照倒叙放的，所以这里就优先删vec[0]这条边
            if (isTreeAfterRemoveEdge(edges, vec[0])) {
                cout << edges[vec[0]][0] << " " << edges[vec[0]][1];
            } else {
                cout << edges[vec[1]][0] << " " << edges[vec[1]][1];
            }
            return ;
        }

        // 处理情况三
        // 明确没有入度为2的情况，那么一定有有向环，找到构成环的边返回就可以了
        getRemoveEdge(edges);
}
// 在有向图里找到删除的那条边，使其变成树
void GraphBasic::getRemoveEdge(const vector<vector<int>>& edges){
    init();
    for (int i = 0; i < n; i++) {
        if(isSame(edges[i][0], edges[i][1])){// 构成有向环了，就是要删除的边,
            cout << edges[i][0] << " " << edges[i][1];
            return;
        }else{
            join(edges[i][0] , edges[i][1]);
        }
    }
}
// 删一条边之后判断是不是树
bool GraphBasic::isTreeAfterRemoveEdge(const vector<vector<int>>& edges, int deleteEdge){
    init();
    for (int i = 0; i < n; i++) {
        if(i == deleteEdge) continue;
        if(isSame(edges[i][0],edges[i][1])){//加入的边的两端点已经在集合中，说明此时构成环了，一定不是树
            return false;
        }
        join(edges[i][0],edges[i][1]);
    }
    return true;
}
//Kama53 用最小权值的边将所有节点连通：最小路径总距离
//Prim算法思路：1.选取非生成树中距离生成树最近的点作为当前节点；2.将当前节点加入生成树 3.更新minDist表，即更新当前节点与非生成树所有节点的距离比minDist中小的值
//minDist数组 用来记录最小生成树的边的权值；即每一个节点距离最小生成树的最近距离；每加入一个新节点，更新该节点与非生成树节点的距离中比minDist小的值，这样生成树中所有点与非生成树节点的最小距离都存在minDist中
//累加minDist中的值即是最小总路径
//时间复杂度为 O(n^2)，n为节点数量
void GraphBasic::includeInputKama53Prim(){
    int v,e;//输入顶点数，边数
    int x, y, k;//输入坐标和权值k
    cin >> v >> e;
    // 填一个默认最大值，题目描述val最大为10000
    vector<vector<int>> grid(v + 1, vector<int>(v + 1, 10001));//求最小值，所以设置默认值为大数
    while(e--){
        cin >> x >> y >> k;
        // 因为是双向图，所以两个方向都要填上
        grid[x][y] = k;
        grid[y][x] = k;
    }
    
    //所有节点到最小生成树的最小距离
    vector<int> minDist(v + 1, 10001);

    // 这个节点是否在树里
    vector<bool> isInTree(v + 1, false);
    
    //加上初始化
    vector<int> parent(v + 1, -1);
    
    // 我们只需要循环 n-1次，建立 n - 1条边，就可以把n个节点的图连在一起
    for (int i = 1; i < v; i++) {
        //1.prim三部曲，第一步：选距离生成树最近节点
        int cur = -1;//选中哪个节点，加入最小生成树
        int minVal = INT_MAX;
        for (int j = 1; j <= v; j++) {// 1 - v，顶点编号，这里下标从1开始
            //  选取最小生成树节点的条件：
            //  （1）不在最小生成树里
            //  （2）距离最小生成树最近的节点
            if(!isInTree[j] && minDist[j] < minVal){
                minVal = minDist[j];
                cur = j;
            }
        }
        // 2、prim三部曲，第二步：最近节点（cur）加入生成树
        isInTree[cur] = true;
        
        // 3、prim三部曲，第三步：更新非生成树节点到生成树的距离（即更新minDist数组）
                // cur节点加入之后， 最小生成树加入了新的节点，那么所有节点到 最小生成树的距离（即minDist数组）需要更新一下
                // 由于cur节点是新加入到最小生成树，那么只需要关心与 cur 相连的 非生成树节点 的距离 是否比 原来 非生成树节点到生成树节点的距离更小了呢
                for (int j = 1; j <= v; j++) {
                    // 更新的条件：
                    // （1）节点是 非生成树里的节点
                    // （2）与cur相连的某节点的权值 比 该某节点距离最小生成树的距离小
                    // 很多录友看到自己 就想不明白什么意思，其实就是 cur 是新加入 最小生成树的节点，那么 所有非生成树的节点距离生成树节点的最近距离 由于 cur的新加入，需要更新一下数据了
                    if (!isInTree[j] && grid[cur][j] < minDist[j]) {
                        minDist[j] = grid[cur][j];
                        
                        parent[j] = cur; // 记录边；不能写反，否则多个j的边容易覆盖
                    }
                }
    }
    
    // 统计结果
        int result = 0;
        for (int i = 2; i <= v; i++) { // 不计第一个顶点，因为统计的是边的权值，v个节点有 v-1条边
            result += minDist[i];
        }
        cout << result << endl;
    
    // 输出 最小生成树边的链接情况
    for (int i = 1; i <= v; i++) {
            cout << i << "->" << parent[i] << endl;
        }
}
//Kama53: Kruskal算法:维护边的集合
//思路：1.将边的权值从小到大排序 2.按权值从小到大将边加入边集合，如果两个节点出现在同一个集合，说明成环，不满足要求；如果不成环，则加入最小生成树，直到最后
//时间复杂度：nlogn; 快排nlogn + logn(并查集)
void GraphBasic::includeInputKama53Kruskal(){
    int v,e;
    int v1,v2,val;
    vector<Edge> edges;//最小生成树，维护边
    vector<Edge> result; // 存储最小生成树的边
    
    int result_val = 0;
    cin >> v >> e;
    while(e--){
        cin >> v1 >> v2 >> val;
        edges.push_back({v1,v2,val});
    }
    
    // 执行Kruskal算法
    // Step1:按边的权值对边进行从小到大排序
    sort(edges.begin(),edges.end(),[](const Edge& a,const Edge& b){
        return a.val < b.val;
    });
    
    //并查集初始化
    init();
    
    //从头开始遍历边
    for(Edge edge:edges){
        //并查集，搜出两个节点的祖先
        int x = find(edge.l);
        int y = find(edge.r);
        
        //如果祖先不同，则不在同一个集合
        if(x != y){
            result_val += edge.val;// 这条边可以作为生成树的边
            result.push_back(edge);//记录生成树的边
            join(x, y);// 两个节点加入到同一个集合
        }
    }
    cout << result_val << endl;
    
    // 打印最小生成树的边
        for (Edge edge : result) {
            cout << edge.l << " - " << edge.r << " : " << edge.val << endl;
        }
    
}
//Kama117:软件构件：拓扑排序
//  步骤：1. 找到入度为0的节点，加入结果集；2.将该节点从图中移除；3. 循环步骤1和2，直到所有节点都被移除
void GraphBasic::includeInputKama117(){
    int n,m,s,t;
    cin >> n >> m;
    vector<int> inDegree(n,0);//记录每个文件的入度
    
    unordered_map<int, vector<int>> umap;//记录文件的依赖关系
    vector<int> result;//记录结果
    
    while(m--){
        //s->t: 现有s才有t
        cin >> s >> t;
        inDegree[t]++;//t的入度+1
        umap[s].push_back(t);//记录s指向哪些文件
    }
    
    queue<int> que;
    for (int i = 0 ; i < n ; i++) {
        //入度为0的文件，可以作为开头，先加入队列；可能有多个
        if (inDegree[i] == 0) que.push(i);
                //cout << inDegree[i] << endl;
    }
    
    // int count = 0;
    while (que.size()) {
        int  cur = que.front(); // 当前选中的文件
        que.pop();
        //count++;
        
        result.push_back(cur);
        vector<int> files = umap[cur];//获取该文件指向的文件
        if(files.size()){// cur有后续文件
            for(int i = 0;i<files.size();i++){
                inDegree[files[i]] --;// cur的指向的文件入度-1;删除入度为0的节点的目的
                if(inDegree[files[i]] == 0) que.push(files[i]);
            }
        }
    }
    //判断是否有环
    if (result.size() == n) {
        for (int i = 0; i < n - 1; i++) cout << result[i] << " ";
        cout << result[n - 1];
    } else cout << -1 << endl;
}
//Kama47: 从起点到终点，用时最短的路径：Dijkstra
//步骤：1.选源点到哪个节点近且该节点未被访问过 2. 该最近节点被标记访问过 3.更新非访问节点到源点的距离（即更新minDist数组）
//时间和空间复杂度：n^2
//和Prim算法的区别：prim是求 非访问节点到最小生成树的最小距离，而 dijkstra是求 非访问节点到源点的最小距离
void GraphBasic::includeInputKama47(){
    int n,m,p1,p2,val;
    cin >> n >> m;
    
    vector<vector<int>> grid(n+1, vector<int>(n+1,INT_MAX));
    for(int i = 0;i < m ;i++){
        cin >> p1 >> p2 >> val;
        grid[p1][p2] = val;
    }
    
    int start  = 1;
    int end = n;
    
    // 存储从源点到每个节点的最短距离
    std::vector<int> minDist(n + 1, INT_MAX);

    // 记录顶点是否被访问过
    std::vector<bool> visited(n + 1, false);

    minDist[start] = 0;  // 起始点到自身的距离为0
    
    //打印最短路径：加上初始化
    vector<int> parent(n + 1, -1);
    
    for (int i =0; i <= n; i++) {// 遍历所有节点
        int minVal = INT_MAX;
        int cur = 1;
        
        //1.选距离源点最近且未被访问过的
        for(int v = 1;v <= n;++v){
            if(!visited[v] && minDist[v] < minVal){
                minVal = minDist[v];
                cur = v;
            }
        }
        
        //2、标记该节点已被访问
        visited[cur] = true;  // 2、标记该节点已被访问
        
        //3，更新非访问节点到源点的距离（即更新minDist数组）
        for (int v=1; v <= n; v++) {
            if(!visited[v] && grid[cur][v] != INT_MAX && minDist[cur] + grid[cur][v] < minDist[v]){
                minDist[v] = minDist[cur] + grid[cur][v];//此处是和Prim算法的区别
                parent[v] = cur; // 记录边
            }
        }
    }
    
    if (minDist[end] == INT_MAX)
        cout << -1 << endl; // 不能到达终点
    else {
        cout << minDist[end] << endl; // 到达终点最短路径
        
        // 输出最短情况
        for (int i = 1; i <= n; i++) {
            cout << parent[i] << "->" << i << endl;
        }
    }
}
//Kama47算法优化：堆优化版dijkstra
//当节点数n较大时，普通版dijkstra可以优化
//方法：1.使用邻接表描述图；2.使用小顶堆的自动排序功能，获得权值小的边，自动找到距离源点最近的顶点，省去循环
//时间复杂度：O(ElogE) E 为边的数量；空间复杂度：O(N + E) N 为节点的数量
void GraphBasic::includeInputKama47_v2(){
    int n, m, p1, p2, val;
        cin >> n >> m;

        vector<list<Edge1>> grid(n + 1);

        for(int i = 0; i < m; i++){
            cin >> p1 >> p2 >> val;
            // p1 指向 p2，权值为 val
            grid[p1].push_back(Edge1(p2, val));

        }

        int start = 1;  // 起点
        int end = n;    // 终点

        // 存储从源点到每个节点的最短距离
        std::vector<int> minDist(n + 1, INT_MAX);

        // 记录顶点是否被访问过
        std::vector<bool> visited(n + 1, false);
        
        // 优先队列中存放 pair<节点，源点到该节点的权值>
        priority_queue<pair<int, int>, vector<pair<int, int>>, mycomparison> pq;


        // 初始化队列，源点到源点的距离为0，所以初始为0
        pq.push(pair<int, int>(start, 0));
        
        minDist[start] = 0;  // 起始点到自身的距离为0
    
    while(!pq.empty()){
        // 1. 第一步，选源点到哪个节点近且该节点未被访问过 （通过优先级队列来实现）
        // <节点， 源点到该节点的距离>
        pair<int,int> cur = pq.top();pq.pop();//自动找最小的边
        
        if (visited[cur.first]) {
            continue;
        }
        // 2. 第二步，该最近节点被标记访问过
        visited[cur.first] = true;

        // 3. 第三步，更新非访问节点到源点的距离（即更新minDist数组）
                for (Edge1 edge : grid[cur.first]) { // 遍历 cur指向的节点，cur指向的节点为 edge
                    // cur指向的节点edge.to，这条边的权值为 edge.val
                    if (!visited[edge.to] && minDist[cur.first] + edge.val < minDist[edge.to]) { // 更新minDist
                        minDist[edge.to] = minDist[cur.first] + edge.val;
                        pq.push(pair<int, int>(edge.to, minDist[edge.to]));// 由于cur节点的加入，而新链接的边，加入到优先级队里中
                    }
                }

            }

            if (minDist[end] == INT_MAX) cout << -1 << endl; // 不能到达终点
            else cout << minDist[end] << endl; // 到达终点最短路径
}
//Kama94: 城市间货物运输:负权值最低权值路径
//minDist数组来表达 起点到各个节点的最短距离
//对所有边松弛一次，相当于计算 起点到达 与起点一条边相连的节点 的最短距离;
//对所有边松弛n-1次，相当于计算 起点到达 与起点n-1条边相连的节点 的最短距离,即到达终点的松弛次数;
//时间复杂度： O(N * E) , N为节点数量，E为图中边的数量；空间复杂度： O(N) ，即 minDist 数组所开辟的空间
//题目中说不存在负权回路：（在有向图中出现有向环 且环的总权值为负数）
void GraphBasic::includeInputKama94(){
    int n, m, p1, p2, val;
    cin >> n >> m;

    vector<vector<int>> grid;

    // 将所有边保存起来
    for(int i = 0; i < m; i++){
            cin >> p1 >> p2 >> val;
            // p1 指向 p2，权值为 val
            grid.push_back({p1, p2, val});

    }
    int start = 1;  // 起点
    int end = n;    // 终点

    vector<int> minDist(n + 1 , INT_MAX);
    minDist[start] = 0;
    
    for(int i = 0; i < n;i++){// 对所有边 松弛 n-1 次
        for(vector<int> &side : grid){// 每一次松弛，都是对所有边进行松弛
            int from = side[0]; // 边的出发点
            int to = side[1]; // 边的到达点
            int price = side[2]; // 边的权值
            // 松弛操作
            // minDist[from] != INT_MAX 防止从未计算过的节点出发
            if (minDist[from] != INT_MAX && minDist[to] > minDist[from] + price) {
                minDist[to] = minDist[from] + price;
            }
        }
    }
    
    if (minDist[end] == INT_MAX) cout << "unconnected" << endl; // 不能到达终点
    else cout << minDist[end] << endl; // 到达终点最短路径
}
//Kama94:城市间货物运输:负权值最低权值路径
//Bellman_ford 队列优化算法Queue improved Bellman-Ford（又名SPFA:Shortest Path Faster Algorithm）
//Bellman_ford 算法 每次都是对所有边进行松弛，其实是多做了一些无用功；只需对上一次松弛时候更新过的节点作为出发点所连接的边 进行松弛
//方法：使用队列记录上次松弛的时候更新过的节点
//用visited数组记录已经在队列里的元素，已经在队列的元素不用重复加入
//图越稀疏，SPFA的效率就越高;越密越接近Bellman_ford（O(N * E) N 为节点数量，E为边的数量）
//一般来说，SPFA 的时间复杂度为 O(K * N) K 为不定值，因为 节点需要计入几次队列取决于 图的稠密度
void GraphBasic::includeInputKama94_v2(){
    int n,m,p1,p2,val;
    cin >> n >> m;
    
    vector<list<Edge1>> grid(n+1);
    
    vector<bool> isInQueue(n+1);//已经在过队列的节点不可以重复添加
    
    //将所有边保存起来
    for (int i =0; i < m; i++) {
        cin >> p1 >> p2 >> val;
        // p1 指向 p2，权值为 val
        grid[p1].push_back(Edge1(p2, val));
    }
    
    int start = 1;//起点
    int end = n;//终点
    
    vector<int> minDist(n+1,INT_MAX);
    minDist[start] = 0;
    
    queue<int> que;
    que.push(start);
    
    while(!que.empty()){
        int node = que.front();que.pop();
        isInQueue[node] = false; // 从队列里取出的时候，要取消标记，我们只保证已经在队列里的元素不用重复加入
        for (Edge1 edge : grid[node]) {
            int from = node;
            int to = edge.to;
            int value = edge.val;
            if(minDist[to] > minDist[from] + value){
                minDist[to] = minDist[from] + value;
                if (isInQueue[to] == false) { // 已经在队列里的元素不用重复添加
                    //当minDist数组不在变化时，就没有新节点加入队列，循环结束
                    que.push(to);
                    isInQueue[to] = true;
                }
            }
        }
    }
        if (minDist[end] == INT_MAX) cout << "unconnected" << endl; // 不能到达终点
            else cout << minDist[end] << endl; // 到达终点最短路径
}
//Kama95:城市货物运输：带负权值回路
//负权回路是指一系列道路的总权值为负，这样的回路使得通过反复经过回路中的道路，理论上可以无限地减少总成本或无限地增加总收益
//用 bellman_ford 算法来判断 负权回路：松弛n次以上，minDist有变化，说明有负权回路
void GraphBasic::includeInputKama95(){
    int n, m, p1, p2, val;
    cin >> n >> m;

    vector<vector<int>> grid;

    // 将所有边保存起来
    for(int i = 0; i < m; i++){
            cin >> p1 >> p2 >> val;
            // p1 指向 p2，权值为 val
            grid.push_back({p1, p2, val});

    }
    int start = 1;  // 起点
    int end = n;    // 终点

    vector<int> minDist(n + 1 , INT_MAX);
    minDist[start] = 0;
    bool flag = false;
    
    for(int i = 0; i <= n;i++){// 这里我们松弛n次，最后一次判断负权回路
        for(vector<int> &side : grid){// 每一次松弛，都是对所有边进行松弛
            int from = side[0]; // 边的出发点
            int to = side[1]; // 边的到达点
            int price = side[2]; // 边的权值
            // 松弛操作
            // minDist[from] != INT_MAX 防止从未计算过的节点出发
            if(i < n){
                if (minDist[from] != INT_MAX && minDist[to] > minDist[from] + price) {
                    minDist[to] = minDist[from] + price;
                }
            }else{// 多加一次松弛判断负权回路
                if (minDist[from] != INT_MAX && minDist[to] > minDist[from] + price) flag = true;
            }
        }
    }
    
    if (flag) cout << "circle" << endl;
    else if (minDist[end] == INT_MAX) cout << "unconnected" << endl; // 不能到达终点
    else cout << minDist[end] << endl; // 到达终点最短路径
}
//对于SPFA算法，在极端情况下，即：所有节点都与其他节点相连，每个节点的入度为 n-1 （n为节点数量），所以每个节点最多加入 n-1 次队列
//所以如果节点加入队列的次数超过n-1次，那么就一定有负权回路
void GraphBasic::includeInputKama95_SPFA(){
    int n,m,p1,p2,val;
    cin >> n >> m;
    
    vector<list<Edge1>> grid(n+1);//邻接表
    
    vector<bool> isInQueue(n+1);//已经在过队列的节点不可以重复添加
    
    //将所有边保存起来
    for (int i =0; i < m; i++) {
        cin >> p1 >> p2 >> val;
        // p1 指向 p2，权值为 val
        grid[p1].push_back(Edge1(p2, val));
    }
    
    int start = 1;//起点
    int end = n;//终点
    
    vector<int> minDist(n+1,INT_MAX);
    minDist[start] = 0;
    
    queue<int> que;
    que.push(start);
    
    vector<int> count(n+1, 0); // 记录节点加入队列几次
    count[start]++;
    
    bool flag = false;
    while(!que.empty()){
        int node = que.front();que.pop();
        isInQueue[node] = false; // 从队列里取出的时候，要取消标记，我们只保证已经在队列里的元素不用重复加入
        for (Edge1 edge : grid[node]) {
            int from = node;
            int to = edge.to;
            int value = edge.val;
            if(minDist[to] > minDist[from] + value){
                minDist[to] = minDist[from] + value;
                que.push(to);
                count[to]++;
                if(count[to] == n){// 如果加入队列次数超过 n-1次 就说明该图与负权回路
                    flag = true;
                    while(!que.empty()) que.pop();
                    break;
                }
               
            }
        }
    }
    if (flag) cout << "circle" << endl;
    else if (minDist[end] == INT_MAX) cout << "unconnected" << endl; // 不能到达终点
    else cout << minDist[end] << endl; // 到达终点最短路径
}
//Kama96:单源有限最短路：最多经过k个城市，从起始城市到目的地的最低运输成本（最短路径）
//起点最多经过k + 1 条边到达终点的最短距离：只需松弛k+1次
//当节点中包含负权回路时，每次更新都会更新所有minDist的值，所以要用minDist_copy数组来记录上一次更新完的数组，用于本次计算
void GraphBasic::includeInputKama96(){
    int src, dst,k ,n, m, p1, p2, val;
    cin >> n >> m;

    vector<vector<int>> grid;

    // 将所有边保存起来
    for(int i = 0; i < m; i++){
            cin >> p1 >> p2 >> val;
            // p1 指向 p2，权值为 val
            grid.push_back({p1, p2, val});

    }
    
    cin >> src >> dst >>k;

    vector<int> minDist(n + 1 , INT_MAX);
    minDist[src] = 0;
    vector<int> minDist_copy(n + 1); // 用来记录上一次遍历的结果
    
    for(int i = 1; i <= k + 1 ;i++){// 对所有边 松弛 k + 1 次
        minDist_copy = minDist; // 获取上一次计算的结果
        for(vector<int> &side : grid){// 每一次松弛，都是对所有边进行松弛
            int from = side[0]; // 边的出发点
            int to = side[1]; // 边的到达点
            int price = side[2]; // 边的权值
            // 松弛操作
            // minDist[from] != INT_MAX 防止从未计算过的节点出发
            // 注意使用 minDist_copy 来计算 minDist
            if (minDist_copy[from] != INT_MAX && minDist[to] > minDist_copy[from] + price) {
                minDist[to] = minDist_copy[from] + price;
            }
        }
    }
    
    if (minDist[dst] == INT_MAX) cout << "unconnected" << endl; // 不能到达终点
    else cout << minDist[dst] << endl; // 到达终点最短路径
}
//使用SPFA，由于进出栈的耗时比较高，所以不一定效率高
void GraphBasic::includeInputKama96_SPFA(){
    int n,m,p1,p2,val;
    cin >> n >> m;
    
    vector<list<Edge1>> grid(n+1);//邻接表
    
    //将所有边保存起来
    for (int i =0; i < m; i++) {
        cin >> p1 >> p2 >> val;
        // p1 指向 p2，权值为 val
        grid[p1].push_back(Edge1(p2, val));
    }
    int start, end, k;
    cin >> start >> end >> k;

    k++;
    
    vector<int> minDist(n+1,INT_MAX);
    vector<int> minDist_copy(n + 1); // 用来记录每一次遍历的结果
    minDist[start] = 0;
    
    queue<int> que;
    que.push(start);
    
    int que_size;
    
    while(k-- && !que.empty()){
        vector<bool> visited(n + 1, false); // 每一轮松弛中，控制节点不用重复入队列
        minDist_copy = minDist;
        que_size = static_cast<int>(que.size()) ;
        while (que_size--) {
            int node = que.front();que.pop();
            
            for (Edge1 edge : grid[node]) {
                int from = node;
                int to = edge.to;
                int value = edge.val;
                if(minDist[to] > minDist[from] + value){
                    minDist[to] = minDist[from] + value;
                    
                    if(visited[to])continue;// 不用重复放入队列，但需要重复松弛，所以放在这里位置
                    visited[to] = true;
                    que.push(to);
                    
                    
                }
            }
        }
    }
    
    if (minDist[end] == INT_MAX) cout << "unconnected" << endl; // 不能到达终点
    else cout << minDist[end] << endl; // 到达终点最短路径
}
//Kama97 逛公园：多源最短路问题：求多个起点到多个终点的多条最短路径
//Floyd算法：可以处理权值为负的情况；核心是动态规划;时间复杂度相对较高，适合 稠密图且源点较多的情况
//grid[i][j][k] = m，表示 节点i 到 节点j 以[1...k] 集合为中间节点的最短距离为m
//时间复杂度： O(n^3);空间复杂度：O(n^2)
void GraphBasic::includeInputKama97(){
    int n, m, p1, p2, val;
    cin >> n >> m;
    
    vector<vector<vector<int>>> grid(n+1,vector<vector<int>>(n+1,vector<int>(n+1,10005)));// 因为边的最大距离是10^4
    for(int i = 0; i < m; i++){
            cin >> p1 >> p2 >> val;
            grid[p1][p2][0] = val;
            grid[p2][p1][0] = val; // 注意这里是双向图

    }
    
    //Floyd：k为中间节点集合的个数；当k遍历到n时，即完成整个地图的计算
    for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    grid[i][j][k] = min(grid[i][j][k-1], grid[i][k][k-1] + grid[k][j][k-1]);//递推公式
                }
            }
    }
    
    //输出结果
    int z, start, end;
    cin >> z;
    while (z--) {
            cin >> start >> end;
            if (grid[start][end][n] == 10005) cout << -1 << endl;
            else cout << grid[start][end][n] << endl;
    }
}
//使用二维数组，因为k的状态仅依赖于k-1
void GraphBasic::includeInputKama97_2D(){
    int n, m, p1, p2, val;
    cin >> n >> m;
    
    vector<vector<int>> grid(n+1,vector<int>(n+1,10005));// 因为边的最大距离是10^4
    for(int i = 0; i < m; i++){
            cin >> p1 >> p2 >> val;
            grid[p1][p2] = val;
            grid[p2][p1] = val; // 注意这里是双向图

    }
    
    //Floyd：k为中间节点集合的个数；当k遍历到n时，即完成整个地图的计算
    for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    grid[i][j] = min(grid[i][j], grid[i][k] + grid[k][j]);//递推公式
                }
            }
    }
    
    //输出结果
    int z, start, end;
    cin >> z;
    while (z--) {
            cin >> start >> end;
            if (grid[start][end] == 10005) cout << -1 << endl;
            else cout << grid[start][end] << endl;
    }
}

//Astar 关键在于 启发式函数， 也就是 影响 广搜或者 dijkstra 从 容器（队列）里取元素的优先顺序；不适合多个目标找最短路径
//启发式函数 要影响的就是队列里元素的排序
//F = G + H; G：起点达到目前遍历节点的距离; H：目前遍历的节点到达终点的距离; 起点达到目前遍历节点的距离 + 目前遍历的节点到达终点的距离 就是起点到达终点的距离。
//使用队列，保证每次弹出的是F最小的，即保证搜索方向是朝着目标去的
//计算两点距离的方式：每种方式会导致结果不同
//1.曼哈顿距离，计算方式： d = abs(x1-x2)+abs(y1-y2)
//2.欧氏距离（欧拉距离） ，计算方式：d = sqrt( (x1-x2)^2 + (y1-y2)^2 )
//3.切比雪夫距离，计算方式：d = max(abs(x1 - x2), abs(y1 - y2))
//x1, x2 为起点坐标，y1, y2 为终点坐标 ，abs 为求绝对值，sqrt 为求开根号，
//最坏情况下，A * 退化成广搜，算法的时间复杂度 是 O(n * 2)，n 为节点数量。最佳情况，是从起点直接到终点，时间复杂度为 O(dlogd)，d 为起点到终点的深度。
//因为在搜索的过程中也需要堆排序，所以是 O(dlogd)。
//效率高，但结果不唯一，也可能是次短路径，适合工程应用，不适合算法题
void GraphBasic::includeInputKama126(){
    int n,a1,a2;
    cin >> n;
    while(n--){
        cin >> a1 >> a2 >> b1 >> b2;
        memset(moves,0,sizeof(moves));
        Knight start;
        start.x = a1;
        start.y = a2;
        start.g = 0;
        start.h = Heuristic(start);
        start.f = start.g + start.h;
        astar(start);
        while(!que.empty()) que.pop(); // 队列清空
        cout << moves[b1][b2] << endl;
    }
}
int GraphBasic::Heuristic(const Knight& k) { // 欧拉距离
    return (k.x - b1) * (k.x - b1) + (k.y - b2) * (k.y - b2); // 统一不开根号，这样可以提高精度
}
void GraphBasic::astar(const Knight& k){
    Knight cur,next;
    que.push(k);
    while(!que.empty()){
        cur = que.top();que.pop();
        if(cur.x == b1 && cur.y == b2) break;
        
        for (int i = 0; i < 8; i++) {
            next.x = cur.x + dir[i][0];
            next.y = cur.y + dir[i][1];
            if(next.x < 1 || next.x > 1000 || next.y < 1 || next.y > 1000)continue;
            if(!moves[next.x][next.y]){
                moves[next.x][next.y] = moves[cur.x][cur.y] + 1;
                
                //开始计算F
                next.g = cur.g + 5;// 统一不开根号，这样可以提高精度，马走日，1 * 1 + 2 * 2 = 5
                next.h = Heuristic(next);
                next.f = next.g + next.h;
                que.push(next);//将可能的下一个格子加入队列，利用自动排序，下一次去目标方向的点走
            }
        }
    }
}
