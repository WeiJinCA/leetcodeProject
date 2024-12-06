//
//  BacktrackingBasic.cpp
//  leetcodeProject
//
//  Created by WeiJin on 2024-11-16.
//

#include "BacktrackingBasic.hpp"

#include <stdio.h>
#include <vector>
#include <unordered_map>

using namespace std;

//77 给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合
// 当搜索达到叶子节点，即找到符合条件的组合
//for循环每次从startIndex开始遍历，然后用path保存取到的节点i； startIndex 是避免重复搜索
void BacktrackingBasic::backtracking77(int n, int k, int startIndex){
    if(static_cast<int>(path.size()) == k){//到达叶子节点
        result.push_back(path);
        return;
    }
    //剪枝操作：当可取的元素不足时，则不需要递归了
    for(int i = startIndex; i <= n - (k - path.size()) + 1; i++){// i为本次搜索的起始位置;剪枝操作：提高效率
        path.push_back(i);//处理节点
        backtracking77(n,k,i + 1);//递归
        path.pop_back();//回溯，撤销处理的节点
    }
}
vector<vector<int>> BacktrackingBasic::combine77(int n, int k){
    result.clear();
    path.clear();
    backtracking77(n, k, 1);
    return result;
}
//216:找出所有相加之和为 n 的 k 个数的组合。组合中只允许含有 1 - 9 的正整数，并且每种组合中不存在重复的数字
void BacktrackingBasic::backtracking216(int targetSum, int k, int sum, int startIndex){
    if(static_cast<int>(path.size()) == k){//到达叶子节点
        if(sum == targetSum) result.push_back(path);//满足条件则保存
        return;//不满足条件则返回
    }
    //剪枝操作：当可取的元素不足时，则不需要递归了
    for(int i = startIndex; i <= 9 - (k - path.size()) + 1; i++){// i为本次搜索的起始位置;剪枝操作：提高效率
        sum += 1;
        path.push_back(i);//处理节点
        
        if (sum > targetSum) { // 剪枝操作
                sum -= i; // 剪枝之前先把回溯做了
                path.pop_back(); // 剪枝之前先把回溯做了
                return;
            }
        
        backtracking216(targetSum,k,sum,i + 1);// 注意i+1调整startIndex
        sum -= i;//回溯
        path.pop_back();//回溯，撤销处理的节点
    }
}
vector<vector<int>> BacktrackingBasic::combinationSum3(int k, int n){
    result.clear();
    path.clear();
    backtracking216(n, k, 0,1);
    return result;
}
//17
void BacktrackingBasic::backtracking17(const string& digits, int index){
    if(index == digits.size()){//当递归层数 == 数字位数时，说明递归层数刚好
        res17.push_back(s);
        return ;
    }
    
    int digit = digits[index] - '0';// 将index指向的数字转为int
    string letters = letterMap[digit];      // 取数字对应的字符集;注意，每个数字对应的letters不一样，和之前的题目有差异
    for (int i = 0; i < letters.size(); i++) {
        s.push_back(letters[i]);            // 处理
        backtracking17(digits, index + 1);    // 递归，注意index+1，一下层要处理下一个数字了
        s.pop_back();                       // 回溯
    }
}
vector<string> BacktrackingBasic::letterCombinations(string digits){
    s.clear();
    res17.clear();
    if (digits.size() == 0) {
        return res17;
    }
    backtracking17(digits, 0);
    return res17;
}
//39 给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。candidates 中的数字可以无限制重复被选取。
// 不同之处： 组合没有数量要求； 元素可无限重复选取
void BacktrackingBasic::backtracking39(vector<int>& candidates, int target, int sum, int startIndex){
    if(sum > target) return;
    
    if(sum == target) {
        result.push_back(path);//保存结果
        return;
    }
    // 剪枝优化：如果 sum + candidates[i] > target 就终止遍历
    for(int i = startIndex; i < candidates.size() && sum + candidates[i] <= target;i++){
        sum += candidates[i];
        path.push_back(candidates[i]);
        backtracking39(candidates, target, sum, i);// 不用i+1了，表示可以重复读取当前的数
        sum -= candidates[i];
        path.pop_back();
    }
}
vector<vector<int>> BacktrackingBasic::combinationSum(vector<int>& candidates, int target){
    result.clear();
    path.clear();
    sort(candidates.begin(), candidates.end()); // 剪枝优化，需要排序
    backtracking39(candidates, target, 0, 0);
    return result;
}
//40 给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。candidates 中的每个数字在每个组合中只能使用一次。
//与39的区别： 数组元素有重复； 每个数字在每个组合中只能用一次
//去重，其实就是使用过的元素不能重复选取
//要求：不能有重复的组合，但组合内可以有重复的数字
//树枝去重：组合内重复元素； 树层去重：组合间去重（同一树层相同两个重复元素不可以重复选取），且需要排序
void BacktrackingBasic::backtracking40(vector<int>& candidates, int target, int sum, int startIndex) {
    if (sum == target) {
        result.push_back(path);
        return;
    }
    for (int i = startIndex; i < candidates.size() && sum + candidates[i] <= target; i++) {
        // 要对同一树层使用过的元素进行跳过
        if (i > startIndex && candidates[i] == candidates[i - 1]) {//直接使用startIndex来去重
            continue;
        }
        sum += candidates[i];
        path.push_back(candidates[i]);
       
        backtracking40(candidates, target, sum, i + 1); // 和39.组合总和的区别1，这里是i+1，每个数字在每个组合中只能使用一次

        sum -= candidates[i];
        path.pop_back();
    }
}

vector<vector<int>> BacktrackingBasic::combinationSum2(vector<int>& candidates, int target){
    
            path.clear();
            result.clear();
            // 首先把给candidates排序，让其相同的元素都挨在一起。
            sort(candidates.begin(), candidates.end());
            backtracking40(candidates, target, 0, 0);
            return result;
}
//131 给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串
//分割问题也是组合问题
void BacktrackingBasic::backtracking131 (const string& s, int startIndex){
    // 如果起始位置已经大于s的大小，说明已经找到了一组分割方案了
    if(startIndex >= s.size()){
        res131.push_back(path131);
        return;
    }
    
    for(int i = startIndex; i < s.size();i++){
        if(isPalindrome131(s, startIndex, i)){// 是回文子串
            // 获取[startIndex,i]在s中的子串
            string str = s.substr(startIndex, i - startIndex + 1);
            path131.push_back(str);
        }else{
            continue;//不是回文
        }
        backtracking131(s, i+1);
        path131.pop_back();
    }
}
bool BacktrackingBasic::isPalindrome131(const string& s, int start, int end){
    for(int i = start,j=end;i<j;i++,j--){
        if(s[i] != s[j]){
            return false;
        }
    }
    return true;
}
//熟悉动态规划这种算法的话, 我们可以高效地事先一次性计算出, 针对一个字符串s, 它的任何子串是否是回文字串, 然后在我们的回溯函数中直接查询即可, 省去了双指针移动判定这一步骤
void BacktrackingBasic::computePalindrome(const string& s) {
        // isPalindrome[i][j] 代表 s[i:j](双边包括)是否是回文字串
    isPalindrome.resize(s.size(), vector<bool>(s.size(), false)); // 根据字符串s, 刷新布尔矩阵的大小
    for (int i = static_cast<int>(s.size()) - 1; i >= 0; i--) {
            // 需要倒序计算, 保证在i行时, i+1行已经计算好了
            for (int j = i; j < s.size(); j++) {
                if (j == i) {isPalindrome[i][j] = true;}
                else if (j - i == 1) {isPalindrome[i][j] = (s[i] == s[j]);}
                else {isPalindrome[i][j] = (s[i] == s[j] && isPalindrome[i+1][j-1]);}
            }
        }
    }
//可以利用动态规划提前计算出字符串的子字符串的回文特性，然后需要判断时去查询该数组isPalindrome
vector<vector<string>> BacktrackingBasic::partition(string s){
    res131.clear();
    path131.clear();
    //computePalindrome(s);//对应backtracking131的代码要更改，见随想录网站
    backtracking131(s, 0);
    return res131;
}
//93 复原IP地址 -- 切割问题
void BacktrackingBasic::backtracking93(string& s, int startIndex, int pointNum) {
    if(pointNum == 3) {
        if(isValid(s,startIndex,static_cast<int>(s.size()) - 1)){
            res17.push_back(s);
        }
        return;
    }
    
    for(int i = startIndex; i < s.size();i++){
        if(isValid(s,startIndex,i)){// 判断 [startIndex,i] 这个区间的子串是否合法
            s.insert(s.begin() + i + 1,'.');//在i的后面插入一个逗点
            pointNum++;
            backtracking93(s, i+2, pointNum);// 插入逗点之后下一个子串的起始位置为i+2
            pointNum--;
            s.erase(s.begin() + i + 1);
        }else break;//不合法，直接结束本层循环
    }
}
bool BacktrackingBasic::isValid(const string& s, int start, int end){
    if(start > end) return false;
    
    if(s[start] == '0' && start != end) return false;// 0开头的数字不合法
    
    int num = 0;
    for(int i = start;i <= end;i++){
        if(s[i] > '9' || s[i] < '0') return false;//非法字符不合法
        num = num * 10 + (s[i] - '0');
        if(num > 255 ) return false;//大于255不合法
    }
    
    return true;
}
vector<string> BacktrackingBasic::BacktrackingBasic::restoreIpAddresses(string s){
    res17.clear();
    if (s.size() < 4 || s.size() > 12) return res17; // 算是剪枝了
    backtracking93(s, 0, 0);
    return res17;
}
//78 子集问题：找树的所有节点；所以不需要剪枝
void BacktrackingBasic::backtracking78(vector<int>& nums, int startIndex) {
    result.push_back(path);//// 收集子集，要放在终止添加的上面，否则会漏掉自己
    if(startIndex >= nums.size()){// 终止条件可以不加, for循环中有
        return;
    }
    for(int i = startIndex; i < nums.size();i++){
        path.push_back(nums[i]);
        backtracking78(nums, i + 1);
        path.pop_back();
    }
}

vector<vector<int>> BacktrackingBasic::subsets(vector<int>& nums){
    result.clear();
            path.clear();
            backtracking78(nums, 0);
            return result;
}
//90 要求：解集不包含重复集合，但集合内可以有重复元素
void BacktrackingBasic::backtracking90(vector<int>& nums, int startIndex){
    result.push_back(path);
    for(int i = startIndex;i<nums.size();i++){
        // 而我们要对同一树层使用过的元素进行跳过
        if(i > startIndex && nums[i] == nums[i-1]){// 注意这里使用i > startIndex
            continue;
        }
        path.push_back(nums[i]);
        backtracking90(nums, i + 1);
        path.pop_back();
    }
}
vector<vector<int>> BacktrackingBasic::subsetsWithDup(vector<int>& nums) {
    result.clear();
            path.clear();
            sort(nums.begin(), nums.end()); // 去重需要排序
            backtracking90(nums, 0);
            return result;
}
//491
vector<vector<int>> BacktrackingBasic::findSubsequences(vector<int>& nums){
    result.clear();
    path.clear();
    backtracking491(nums, 0);
    return result;
}
void BacktrackingBasic::backtracking491(vector<int>& nums, int startIndex){

    if(path.size() > 1){
        result.push_back(path);//收集所有长度大于等于2的节点
    }
    
    int used[201] = {0};// 这里使用数组来进行去重操作，题目说数值范围[-100, 100]
    for(int i = startIndex; i < nums.size();i++){
        if((!path.empty() && nums[i] < path.back()) || used[nums[i] + 100] == 1){
            continue;
        }
        
        used[nums[i] + 100] = 1; // 记录这个元素在本层用过了，本层后面不能再用了
        path.push_back(nums[i]);
        backtracking491(nums, i + 1);
        path.pop_back();
    }
}
//46
//used数组，其实就是记录此时path里都有哪些元素使用了，一个排列里一个元素只能使用一次
void BacktrackingBasic::backtracking46 (vector<int>& nums, vector<bool>& used){
    //此时说明找到了一组
    if(path.size() == nums.size()){
        result.push_back(path);
        return;
    }
    
    for(int i = 0;i < nums.size();i++){
        if(used[i] == true) continue;// path里已经收录的元素，直接跳过
        used[i] = true;
        path.push_back(nums[i]);
        backtracking46(nums, used);
        path.pop_back();
        used[i] = false;
    }
}
//TC:n!;SC:n
vector<vector<int>> BacktrackingBasic::permute46(vector<int>& nums){
    result.clear();
           path.clear();
           vector<bool> used(nums.size(), false);
           backtracking46(nums, used);
           return result;
}
//47 返回不重复的全排列
//去重逻辑：对同一树层，前一位（也就是nums[i-1]）如果使用过，那么就进行去重
//对于排列问题，树层上去重和树枝上去重，都是可以的，但是树层上去重效率更高
void BacktrackingBasic::backtracking47 (vector<int>& nums, vector<bool>& used){
    // 此时说明找到了一组
            if (path.size() == nums.size()) {
                result.push_back(path);
                return;
            }
            for (int i = 0; i < nums.size(); i++) {
                // used[i - 1] == true，说明同一树枝nums[i - 1]使用过
                // used[i - 1] == false，说明同一树层nums[i - 1]使用过
                // 如果同一树层nums[i - 1]使用过则直接跳过
                if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false) {// = false 说明是树层去重；此处也可以写成true,树枝去重也可以
                    continue;
                }
                if (used[i] == false) {
                    used[i] = true;
                    path.push_back(nums[i]);
                    backtracking47(nums, used);
                    path.pop_back();
                    used[i] = false;
                }
            }
}
vector<vector<int>> BacktrackingBasic::permuteUnique47(vector<int>& nums){
    result.clear();
            path.clear();
            sort(nums.begin(), nums.end()); // 排序
            vector<bool> used(nums.size(), false);
            backtracking47(nums, used);
            return result;
}
//332
bool BacktrackingBasic::backtracking332(int ticketNum, vector<string>& result) {
    if (result.size() == ticketNum + 1) {
        return true;
    }
    for (pair<const string, int>& target : targets[result[result.size() - 1]]) {
        if (target.second > 0 ) { // 记录到达机场是否飞过了
            result.push_back(target.first);
            target.second--;
            if (backtracking332(ticketNum, result)) return true;
            result.pop_back();
            target.second++;
        }
    }
    return false;
}
//332 unordered_map<出发机场, map<到达机场, 航班次数>> targets
//unordered_map<string, map<string, int>> targets;
vector<string> BacktrackingBasic::findItinerary(vector<vector<string>>& tickets){
    targets.clear();
            vector<string> result;
            for (const vector<string>& vec : tickets) {
                targets[vec[0]][vec[1]]++; // 记录映射关系
            }
    result.push_back("JFK"); // 起始机场
    backtracking332(static_cast<int>(tickets.size()) , result);
    return result;
}
//51
//要求：不能同行、同列、同斜线
//递归深度就是row控制棋盘的行，每一层里for循环的col控制棋盘的列，一行一列，确定了放置皇后的位置
void BacktrackingBasic::backtracking51(int n, int row, vector<string>& chessboard) {
    if (row == n) {
        res131.push_back(chessboard);
        return;
    }
    
    for (int col = 0; col < n; col++) {
        if (isValid51(row, col, chessboard, n)) { // 验证合法就可以放
            chessboard[row][col] = 'Q'; // 放置皇后
            backtracking51(n, row + 1, chessboard);
            chessboard[row][col] = '.'; // 回溯，撤销皇后
        }
    }
}
bool BacktrackingBasic::isValid51(int row, int col, vector<string>& chessboard, int n) {
    // 检查列
    for (int i = 0; i < row; i++) { // 这是一个剪枝
        if (chessboard[i][col] == 'Q') {
            return false;
        }
    }
    // 检查 45度角是否有皇后
    for (int i = row - 1, j = col - 1; i >=0 && j >= 0; i--, j--) {
        if (chessboard[i][j] == 'Q') {
            return false;
        }
    }
    // 检查 135度角是否有皇后
    for(int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
        if (chessboard[i][j] == 'Q') {
            return false;
        }
    }
    return true;
}
//TC:n!; SC:n
vector<vector<string>> BacktrackingBasic::solveNQueens(int n){
    res131.clear();
           std::vector<std::string> chessboard(n, std::string(n, '.'));
           backtracking51(n, 0, chessboard);
           return res131;
}
//37 9宫格填数字；每行、列、每个9宫格，数字1-9只能出现1次；
bool BacktrackingBasic::backtracking37(vector<vector<char>>& board) {
    for (int i = 0; i < board.size(); i++) {        // 遍历行
        for (int j = 0; j < board[0].size(); j++) { // 遍历列
            if (board[i][j] != '.') continue;
            for (char k = '1'; k <= '9'; k++) {     // (i, j) 这个位置放k是否合适
                if (isValid37(i, j, k, board)) {
                    board[i][j] = k;                // 放置k
                    if (backtracking37(board)) return true; // 如果找到合适一组立刻返回
                    board[i][j] = '.';              // 回溯，撤销k
                }
            }
            return false;                           // 9个数都试完了，都不行，那么就返回false
        }
    }
    return true; // 遍历完没有返回false，说明找到了合适棋盘位置了
}
//棋盘是否合法：同行、列、9宫格是否有重复数字
bool BacktrackingBasic::isValid37(int row, int col, char val, vector<vector<char>>& board) {
    for (int i = 0; i < 9; i++) { // 判断行里是否重复
        if (board[row][i] == val) {
            return false;
        }
    }
    for (int j = 0; j < 9; j++) { // 判断列里是否重复
        if (board[j][col] == val) {
            return false;
        }
    }
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int i = startRow; i < startRow + 3; i++) { // 判断9方格里是否重复
        for (int j = startCol; j < startCol + 3; j++) {
            if (board[i][j] == val ) {
                return false;
            }
        }
    }
    return true;
}
void BacktrackingBasic::solveSudoku(vector<vector<char>>& board){
    backtracking37(board);
}
