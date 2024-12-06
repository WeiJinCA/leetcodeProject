//
//  DPBasic.hpp
//  leetcodeProject
//
//  Created by WeiJin on 2024-11-25.
//  Dynamic Programming 动态规划 ： 一个问题有很多个重叠的子问题，每个状态是由上一个状态推导来的；确定递推公式很重要
//  步骤：1.确定dp数组（dp table）以及下标的含义；2.确定递推公式；3.dp数组如何初始化；4.确定遍历顺序；5.举例推导dp数组

// 滚动数组：需要满足的条件是上一层可以重复利用，直接拷贝到当前层

//  背包问题：有多种背包方式，常见的有：01背包（每个物品1件）、完全背包(每个物品无限件，可重复放)、多重背包、分组背包和混合背包等等
// 完全背包理论：每个物品有无限个，物品可以添加多次，所以从小到大遍历
//  如果求组合数就是外层for循环遍历物品，内层for遍历背包;物品组合没有顺序，即多个物品组合的顺序固定，只算一次
//  如果求排列数就是外层for遍历背包，内层for循环遍历物品。多个物品组合顺序计算多次

//  多重背包：每件物品最多有M件可用；区别：01背包：每件物品只有1件可用；完全背包：每件物品有无数件可用
//  多重背包中，把每件物品都铺开，当作是独立的物品，即转化为01背包问题

#ifndef DPBasic_hpp
#define DPBasic_hpp

#include <stdio.h>
#include <vector>
#include <unordered_map>

using namespace std;

class DPBasic {
    
public:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
    
    //2
    int fib(int n);//509
    //3
    int climbStairs(int n) ;//70
    int climbStairsComplete(int n,int m) ;//卡码网57
    //4
    int minCostClimbingStairs(vector<int>& cost);//746
    //6
    int uniquePaths(int m, int n);//62
    //7
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid);//63
    int uniquePathsWithObstacles1(vector<vector<int>>& obstacleGrid);//63
    //8
    int integerBreak(int n);//343
    int integerBreakByGreedy(int n);//343
    //9
    int numTrees(int n);//96
    //12 01背包理论基础（滚动数组）
    int bag01(int bagweight,vector<int>& weight,vector<int>& value);//卡码网46
    int bag01ByOneDimensionalArray(int bagweight,vector<int>& weight,vector<int>& value);//卡码网46***
    //13
    bool canPartition(vector<int>& nums);//416
    //14
    int lastStoneWeightII(vector<int>& stones);
    //16
    int findTargetSumWays(vector<int>& nums, int target);
    int findTargetSumWaysByOneDimensionalArray(vector<int>& nums, int target);
    //17
    int findMaxForm(vector<string>& strs, int m, int n);//474
    //18
    void test_CompletePack();//卡码网52
    //19
    int change518(int amount, vector<int>& coins);//518
    //21
    int combinationSum4(vector<int>& nums, int target);//377
    //23
    int coinChange(vector<int>& coins, int amount);//322
    //24
    int numSquares(int n);//279
    //26
    bool wordBreak(string s, vector<string>& wordDict);
    //27
    int multiBags(vector<int>& nums,vector<int>& weight,vector<int>& value);//卡码网56
    
    //29
    int rob(vector<int>& nums);//198
    //30
    int robRange(vector<int>& nums, int start, int end);
    int rob213(vector<int>& nums);//213
    //31
    int rob337(TreeNode* root);//337
    vector<int> robTree(TreeNode* cur);
    //32
    int maxProfit(vector<int>& prices);//121
    int maxProfitWithRollingArray(vector<int>& prices);
    //34
    int maxProfit122(vector<int>& prices);
    //35
    int maxProfit123(vector<int>& prices);
    int maxProfit123WithRollingArray(vector<int>& prices);
    //36
    int maxProfit188(int k, vector<int>& prices);//188
    //37
    int maxProfit309(vector<int>& prices);
    //39
    int maxProfit714(vector<int>& prices, int fee);//714
    
    //41
    int lengthOfLIS(vector<int>& nums);//300
    //42
    int findLengthOfLCIS(vector<int>& nums) ;//674
    //43
    int findLength718(vector<int>& nums1, vector<int>& nums2);//718
    int findLength718WithRollingArray(vector<int>& A, vector<int>& B);
    //44
    int longestCommonSubsequence(string text1, string text2);//1143
    //45
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2);//1035
    //46
    int maxSubArray(vector<int>& nums);//53
    //47
    bool isSubsequence(string s, string t);//392
    //48
    int numDistinct115(string s, string t);
    //49
    int minDistance(string word1, string word2);//583
    int minDistance2(string word1, string word2);
    //50
    int minDistance72(string word1, string word2);
    //52
    int countSubstrings(string s);
    int countSubstringsWithTwoPointers(string s);
    int extend(const string& s, int i, int j, int n);
    //53
    int longestPalindromeSubseq(string s);//516
    
    
};
#endif /* DPBasic_hpp */
