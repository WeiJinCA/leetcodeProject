//
//  GreedyBasic.hpp
//  leetcodeProject
//
//  Created by WeiJin on 2024-11-18.
//  贪心算法： 选择每一阶段的局部最优，从而达到全局最优
//  如何验证：常识性推导 + 举反例；数学归纳法；反证法
//  贪心算法一般分为如下四步：1.将问题分解为若干个子问题；2.找出适合的贪心策略；3.求解每一个子问题的最优解；4.将局部最优解堆叠成全局最优解
//  Tip: 如果局部最优是可以推出全局最优，并且找不出反例，则可以尝试贪心算法

//  摆动序列: 如果连续数字之间的差严格地在正数和负数之间交替，则数字序列称为 摆动序列
#ifndef GreedyBasic_hpp
#define GreedyBasic_hpp

#include <stdio.h>
#include <vector>
#include <unordered_map>

using namespace std;

class GreedyBasic {
private:
    int result;
public:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
    
    int findContentChildren(vector<int>& g, vector<int>& s);//2
    //3摆动序列
    int wiggleMaxLength(vector<int>& nums);//376
    //4
    int maxSubArray(vector<int>& nums);//53
    //6
    int maxProfit(vector<int>& prices);//122
    //7
    bool canJump(vector<int>& nums);//55
    //8
    int jump(vector<int>& nums);//45
    //9
    int largestSumAfterKNegations(vector<int>& nums, int k);//1005
    //11加油站
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost);//134
    //12分发糖果
    int candy(vector<int>& ratings);//135
    //13
    bool lemonadeChange(vector<int>& bills);//860
    //14根据身高重建队列406
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people);
    static bool cmpHelper(const vector<int>& a, const vector<int>& b);
    //17
    int findMinArrowShots(vector<vector<int>>& points);//452
    //18
    int eraseOverlapIntervals(vector<vector<int>>& intervals);//435
    //19
    vector<int> partitionLabels(string s);//763
    //20
    vector<vector<int>> merge56(vector<vector<int>>& intervals);//56
    //22
    int monotoneIncreasingDigits(int n);//738
    //23
    int minCameraCover(TreeNode* root);//968
    int traversalHelper(TreeNode* cur);
    //649**
    string predictPartyVictory(string senate);//649 dota2参议院
    int balancedStringSplit1221(string s);//1221
    
    
};
#endif /* GreedyBasic_hpp */
