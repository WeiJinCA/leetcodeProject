//
//  BacktrackingBasic.hpp
//  leetcodeProject
//
//  Created by WeiJin on 2024-11-16.
// 回溯：一种搜索方式（暴力查找），递归的副产品； 本质：穷举所有可能，然后选出我们想要的答案，效率不高
// 适合用回溯的常见的问题
    // 1.组合问题（元素没有顺序）：N个数里面按一定规则找出k个数的集合
    // 2.切割问题：一个字符串按一定规则有几种切割方式
    // 3.子集问题：一个N个数的集合里有多少符合条件的子集
    // 4.排列问题（有序）：N个数按一定规则全排列，有几种排列方式
    // 5.棋盘问题：N皇后，解数独等等
// 回溯法解决的问题都可以抽象为树形结构；回溯法解决的都是在集合中递归查找子集，集合的大小就构成了树的宽度，递归的深度就构成了树的深度；递归就要有终止条件，所以必然是一棵高度有限的树（N叉树）
// for循环可以理解是横向遍历，backtracking（递归）就是纵向遍历

#ifndef BacktrackingBasic_hpp
#define BacktrackingBasic_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

class BacktrackingBasic {
private:
    const string letterMap[10] = {
            "", // 0
            "", // 1
            "abc", // 2
            "def", // 3
            "ghi", // 4
            "jkl", // 5
            "mno", // 6
            "pqrs", // 7
            "tuv", // 8
            "wxyz", // 9
        };
    vector<string> res17;
    string s;
public:
    vector<vector<int>> result; // 存放符合条件结果的集合
    vector<int> path; // 用来存放符合条件结果
    //131
    vector<vector<string>> res131;
    vector<string> path131; // 放已经回文的子串
    vector<vector<bool>> isPalindrome; // 放事先计算好的是否回文子串的结果
    
    //332 unordered_map<出发机场, map<到达机场, 航班次数>> targets
    unordered_map<string, map<string, int>> targets;
    
    //2 组合问题
    void backtracking77(int n, int k, int startIndex);
    vector<vector<int>> combine77(int n, int k);//77
    
    //4组合总和III
    void backtracking216(int targetSum, int k, int sum, int startIndex);
    vector<vector<int>> combinationSum3(int k, int n);//216
    
    //5电话号码的字母组合
    void backtracking17(const string& digits, int index);
    vector<string> letterCombinations(string digits);
    //7 组合总和
    void backtracking39(vector<int>& candidates, int target, int sum, int startIndex);
    vector<vector<int>> combinationSum(vector<int>& candidates, int target);//39
    //8
    void backtracking40(vector<int>& candidates, int target, int sum, int startIndex) ;
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target);//40
    //9 分割回文串
    void backtracking131 (const string& s, int startIndex);
    bool isPalindrome131(const string& s, int start, int end);
    void computePalindrome(const string& s);
    vector<vector<string>> partition(string s);//131
    //10 复原IP地址
    vector<string> restoreIpAddresses(string s);
    bool isValid(const string& s, int start, int end);
    void backtracking93(string& s, int startIndex, int pointNum);
    
    //11子集问题
    vector<vector<int>> subsets(vector<int>& nums);//78
    void backtracking78(vector<int>& nums, int startIndex) ;
    //13
    vector<vector<int>> subsetsWithDup(vector<int>& nums) ;//90
    void backtracking90(vector<int>& nums, int startIndex);
    //14递增子序列
    vector<vector<int>> findSubsequences(vector<int>& nums);//491
    void backtracking491(vector<int>& nums, int startIndex);
    //15全排列
    vector<vector<int>> permute46(vector<int>& nums);//46
    void backtracking46 (vector<int>& nums, vector<bool>& used);
    //16全排列II
    void backtracking47 (vector<int>& nums, vector<bool>& used);
    vector<vector<int>> permuteUnique47(vector<int>& nums);//47
    //19重新安排行程
    vector<string> findItinerary(vector<vector<string>>& tickets);//332**
    bool backtracking332(int ticketNum, vector<string>& result);
    //20 N皇后问题
    vector<vector<string>> solveNQueens(int n);//51 //52
    void backtracking51(int n, int row, vector<string>& chessboard);
    bool isValid51(int row, int col, vector<string>& chessboard, int n);
    //21解数独
    void solveSudoku(vector<vector<char>>& board);//37
    bool backtracking37(vector<vector<char>>& board);
    bool isValid37(int row, int col, char val, vector<vector<char>>& board);
};
#endif /* BacktrackingBasic_hpp */
