//
//  GraphBasic.cpp
//  leetcodeProject
//
//  Created by WeiJin on 2024-12-07.
//

#include "GraphBasic.hpp"
#include <iostream>
#include <vector>
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
