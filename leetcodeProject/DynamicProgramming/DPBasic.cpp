//
//  DPBasic.cpp
//  leetcodeProject
//
//  Created by WeiJin on 2024-11-25.
//
//  步骤：1.确定dp数组（dp table）以及下标的含义；2.确定递推公式；3.dp数组如何初始化；4.确定遍历顺序；5.举例推导dp数组

#include "DPBasic.hpp"
#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;
//509
int DPBasic::fib(int n){
    if(n <=1) return n;
    int dp[2];//不需要记录中间状态，所以可以用2个值来完成计算
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        int sum = dp[0] + dp[1];//dp[i] = dp[i - 1] + dp[i - 2]
        dp[0] = dp[1];
        dp[1] = sum;
     }
    return dp[1];
}
//70 爬楼梯：到第三层楼梯的状态可以由第二层楼梯 和 到第一层楼梯状态推导出来；dp[i] = dp[i - 1] + dp[i - 2]；
//类似于509，只是从dp[1]开始
int DPBasic::climbStairs(int n) {
    if (n <= 1) return n;
            int dp[3];
            dp[1] = 1;
            dp[2] = 2;
            for (int i = 3; i <= n; i++) {
                int sum = dp[1] + dp[2];
                dp[1] = dp[2];
                dp[2] = sum;
            }
            return dp[2];
}
//70题的拓展：卡码网57: 一步一个台阶，两个台阶，三个台阶，直到 m个台阶，有多少种方法爬到n阶楼顶。
int DPBasic::climbStairsComplete(int n,int m){
    vector<int> dp(n + 1, 0);
            dp[0] = 1;
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++) { // 把m换成2，就可以AC爬楼梯70这道题
                    if (i - j >= 0) dp[i] += dp[i - j];
                }
            }
            return dp[n];
}
//746 一但支付cost[i],可以选择向上爬1或2个台阶，可以从0或1层开始，直到楼顶；求最小花费
int DPBasic::minCostClimbingStairs(vector<int>& cost){
    vector<int> dp(static_cast<int>(cost.size()) + 1);//可以只用dp0,dp1，不需要记录中间状态
            dp[0] = 0; // 默认第一步都是不花费体力的
            dp[1] = 0;
            for (int i = 2; i <= cost.size(); i++) {
                dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
            }
            return dp[cost.size()];
}
//62 使用二位数组比较好理解；也可以使用一维数组
//还有使用计算组合的方法，但注意分子溢出
int DPBasic::uniquePaths(int m, int n){
    vector<vector<int>> dp(m, vector<int>(n, 0));
            for (int i = 0; i < m; i++) dp[i][0] = 1;
            for (int j = 0; j < n; j++) dp[0][j] = 1;
            for (int i = 1; i < m; i++) {
                for (int j = 1; j < n; j++) {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
            return dp[m - 1][n - 1];
    //使用一维数组，相当于每一行也累加
//    vector<int> dp(n);
//            for (int i = 0; i < n; i++) dp[i] = 1;
//            for (int j = 1; j < m; j++) {
//                for (int i = 1; i < n; i++) {
//                    dp[i] += dp[i - 1];
//                }
//            }
//            return dp[n - 1];
}
//63 网格不同路径，有障碍物的情况
//区别：因为有了障碍，dp(i, j)如果就是障碍的话应该就保持初始状态（初始状态为0）
int DPBasic::uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid){
    int m = static_cast<int>(obstacleGrid.size());
    int n = static_cast<int>(obstacleGrid[0].size());
    if(obstacleGrid[m-1][n-1] == 1 || obstacleGrid[0][0] == 1) return 0;//如果在起点或终点出现了障碍，直接返回0
    vector<vector<int>> dp(m,vector<int>(n,0));
    for(int i = 0;i < m && obstacleGrid[i][0] == 0;i++) dp[i][0] = 1;//对于第1行，如果中间有障碍，后序方格都不能走，所以后序都置0
    for(int j = 0;j < n && obstacleGrid[0][j] == 0;j++) dp[0][j] = 1;//对于第1列，如果中间有障碍，后序方格都不能走，所以后序都置0
    for(int i = 1;i < m;i++){
        for(int j = 1;j<n;j++){
            if(obstacleGrid[i][j] == 1) continue;
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }
    return dp[m-1][n-1];
}
//空间优化：只使用一维数组
int DPBasic::uniquePathsWithObstacles1(vector<vector<int>>& obstacleGrid){
    if (obstacleGrid[0][0] == 1)
                return 0;
            vector<int> dp(obstacleGrid[0].size());
            for (int j = 0; j < dp.size(); ++j)
                if (obstacleGrid[0][j] == 1)
                    dp[j] = 0;
                else if (j == 0)
                    dp[j] = 1;
                else
                    dp[j] = dp[j-1];

            for (int i = 1; i < obstacleGrid.size(); ++i)
                for (int j = 0; j < dp.size(); ++j){
                    if (obstacleGrid[i][j] == 1)
                        dp[j] = 0;
                    else if (j != 0)
                        dp[j] = dp[j] + dp[j-1];//遍历行时，列值累加
                }
            return dp.back();//返回最后一个值
}
//343: dp[i] = max({dp[i], (i - j) * j, dp[i - j] * j}); 2个数的乘积或多个数的乘积，并与自己比较，获得最大值
//注意：拆分一个数n 使之乘积最大，那么一定是拆分成m个近似相同的子数相乘才是最大的；所以遍历到n/2就可以了
int DPBasic::integerBreak(int n) {
    vector<int> dp(n+1);
    dp[2] = 1;
    for(int i = 3; i <= n; i++){
        for(int j = 1;j<= i / 2; j++){
            dp[i] = max(dp[i],max((i - j) * j, dp[i - j] * j));
        }
    }
    return dp[n];
}
//贪心算法：乘积最大要利用推论：一个正整数可以拆分为n个3和4的和；
int DPBasic::integerBreakByGreedy(int n){
    if (n == 2) return 1;
            if (n == 3) return 2;
            if (n == 4) return 4;
            int result = 1;
            while (n > 4) {
                result *= 3;
                n -= 3;
            }
            result *= n;
            return result;
}
//96
//找重叠子问题 dp[3] = 元素1为头结点搜索树的数量 + 元素2为头结点搜索树的数量 + 元素3为头结点搜索树的数量
//元素1为头结点搜索树的数量 = 右子树有2个元素的搜索树数量 * 左子树有0个元素的搜索树数量
//元素2为头结点搜索树的数量 = 右子树有1个元素的搜索树数量 * 左子树有1个元素的搜索树数量
//元素3为头结点搜索树的数量 = 右子树有0个元素的搜索树数量 * 左子树有2个元素的搜索树数量
//有2个元素的搜索树数量就是dp[2]。有1个元素的搜索树数量就是dp[1]。有0个元素的搜索树数量就是dp[0]
int DPBasic::numTrees(int n){
    vector<int> dp(n+1);
    dp[0] = 1;
    for(int i = 1; i <= n;i++){
        for(int j = 1;j <= i;j++){
            dp[i] += dp[j - 1] * dp[i - j];//以j为头节点，其左子树节点数量为dp[j - 1]， 右子树节点数量为dp[i - j]
        }
    }
    return dp[n];
}
//背包问题 //卡码网46
//dp[i][j] 表示从下标为[0-i]的物品里任意取，放进容量为j的背包，价值总和最大是多少。
//在一维dp数组中，dp[j]表示：容量为j的背包，所背的物品价值可以最大为dp[j]
int DPBasic::bag01(int bagweight,vector<int>& weight,vector<int>& value){
    int n = static_cast<int>(weight.size());
    // dp数组, dp[i][j]代表行李箱空间为j的情况下,从下标为[0, i]的物品里面任意取,能达到的最大价值
        vector<vector<int>> dp(weight.size(), vector<int>(bagweight + 1, 0));

        // 初始化, 因为需要用到dp[i - 1]的值
        // j < weight[0]已在上方被初始化为0
        // j >= weight[0]的值就初始化为value[0]
        for (int j = weight[0]; j <= bagweight; j++) {
            dp[0][j] = value[0];
        }

        for(int i = 1; i < weight.size(); i++) { // 遍历科研物品
            for(int j = 0; j <= bagweight; j++) { // 遍历行李箱容量
                if (j < weight[i]) dp[i][j] = dp[i - 1][j]; // 如果装不下这个物品,那么就继承dp[i - 1][j]的值
                else {
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
                }
            }
        }
        return dp[n - 1][bagweight];
}
//***
int DPBasic::bag01ByOneDimensionalArray(int N,vector<int>& weight,vector<int>& value){
    int M = static_cast<int>(weight.size());
    // 创建一个动态规划数组dp，初始值为0
        vector<int> dp(N + 1, 0);

        // 外层循环遍历每个类型的研究材料
        for (int i = 0; i < M; ++i) {
            // 内层循环从 N 空间逐渐减少到当前研究材料所占空间
            for (int j = N; j >= weight[i]; --j) {
                // 考虑当前研究材料选择和不选择的情况，选择最大值
                dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
            }
        }

        // 输出dp[N]，即在给定 N 行李空间可以携带的研究材料最大价值
        return dp[N];
}
//416 转换为01背包问题
//关键：dp[target] == target = sum / 2； 子集中有元素的和刚好可以凑够sum / 2，所以返回true
bool DPBasic::canPartition(vector<int>& nums){
    int sum = 0;

            // dp[i]中的i表示背包内总和
            // 题目中说：每个数组中的元素不会超过 100，数组的大小不会超过 200
            // 总和不会大于20000，背包最大只需要其中一半，所以10001大小就可以了
            vector<int> dp(10001, 0);
            for (int i = 0; i < nums.size(); i++) {
                sum += nums[i];
            }
            // 也可以使用库函数一步求和
            // int sum = accumulate(nums.begin(), nums.end(), 0);
            if (sum % 2 == 1) return false;
            int target = sum / 2;

            // 开始 01背包
            for(int i = 0; i < nums.size(); i++) {
                for(int j = target; j >= nums[i]; j--) { // 每一个元素一定是不可重复放入，所以从大到小遍历
                    dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
                }
            }
            // 集合中的元素正好可以凑成总和target
            if (dp[target] == target) return true;
            return false;
}
//1049 尽量让石头分成重量相同的两堆，相撞之后剩下的石头最小，这样就化解成01背包问题了；本题是求背包最多能装多少
//dp[j] = max(dp[j], dp[j - stones[i]] + stones[i])
//target是最大重量的一半：30 * 1000 / 2 = 15000
int DPBasic::lastStoneWeightII(vector<int>& stones){
    vector<int> dp(15001, 0);
            int sum = 0;
            for (int i = 0; i < stones.size(); i++) sum += stones[i];
            int target = sum / 2;
            for (int i = 0; i < stones.size(); i++) { // 遍历物品
                for (int j = target; j >= stones[i]; j--) { // 遍历背包
                    dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);
                }
            }
            return sum - dp[target] - dp[target];
}
//494
//既然为target，那么就一定有 left组合 - right组合 = target。left + right = sum，而sum是固定的。right = sum - left
//left - (sum - left) = target 推导出 left = (target + sum)/2 。target是固定的，sum是固定的，left就可以求出来。
//此时问题就是在集合nums中找出和为left的组合;即用nums装满容量为x的背包，有几种方法
int DPBasic::findTargetSumWays(vector<int>& nums, int target){
    int sum = 0;
    for(int i = 0;i < nums.size(); i++) sum += nums[i];
    if(abs(target) > sum) return 0;//此时没有方案
    if((target + sum) % 2 == 1) return 0;//此时没有方案
    int bagSize = (target + sum) / 2;
    
    vector<vector<int>> dp(nums.size(),vector<int>(bagSize + 1,0));
    
    //初始化最上行
    if(nums[0] <= bagSize) dp[0][nums[0]] = 1;
    //初始化最左列，最左列其他数值在递推公式中完成了赋值
    dp[0][0] = 1;
    
    int numZero = 0;
    for(int i = 0;i < nums.size(); i++){
        if(nums[i] == 0) numZero++;
        dp[i][0] = (int)pow(2.0, numZero);//组合数量
    }
    
    //以下遍历顺序行列可以颠倒
    for(int i = 1; i < nums.size();i++){
        for (int j = 0; j <= bagSize; j++) {
            if(nums[i] > j) dp[i][j] = dp[i - 1][j];//放不下i时
            else dp[i][j] = dp[i - 1][j] + dp[i - 1][j - nums[i]];//不放i和放i的方法种类
        }
    }
    return dp[nums.size() - 1][bagSize];
}
//使用一维数组  去掉维度i 之后，递推公式：dp[j] = dp[j] + dp[j - nums[i]] ，即：dp[j] += dp[j - nums[i]]
//dp[j]： 填满j（包括j）这么大容积的包，有dp[j]种方法；dp[j - nums[i]]：放i物品，先把其重量减下来，剩下的有多少种方法
int DPBasic::findTargetSumWaysByOneDimensionalArray(vector<int>& nums, int target){
    int sum = 0;
    for(int i = 0;i < nums.size(); i++) sum += nums[i];
    if(abs(target) > sum) return 0;//此时没有方案
    if((target + sum) % 2 == 1) return 0;//此时没有方案
    int bagSize = (target + sum) / 2;
    
    vector<int> dp(bagSize + 1, 0);
    dp[0] = 1;
    for(int i = 0; i < nums.size();i++){
        for (int j = bagSize; j >= nums[i]; j--) {
            dp[j] += dp[j - nums[i]];
        }
    }
    return dp[bagSize];
}
//474 dp[i][j]：最多有i个0和j个1的strs的最大子集的大小为dp[i][j];背包有2个维度
//递推公式：dp[i][j] = max(dp[i][j], dp[i - zeroNum][j - oneNum] + 1);
int DPBasic::findMaxForm(vector<string>& strs, int m, int n){
    vector<vector<int>> dp(m + 1, vector<int> (n + 1, 0)); // 默认初始化0
    for(string str:strs){
        int oneNum =0 , zeroNum = 0;
        for(char c : str){
            if(c == '0') zeroNum++;
            else oneNum++;
        }
        
        for(int i = m; i >= zeroNum;i--){//遍历背包容量且从后向前遍历
            for(int j = n;j >= oneNum;j--){
                dp[i][j] = max(dp[i][j],dp[i-zeroNum][j-oneNum]+1);
            }
        }
    }
    return dp[m][n];
}
//卡码网52
//物品和容量的循环可以颠倒；物品循环从0开始遍历：这是与01背包的区别
void DPBasic::test_CompletePack(){
    vector<int> weight = {1, 3, 4};
        vector<int> value = {15, 20, 30};
        int bagWeight = 4;

        vector<int> dp(bagWeight + 1, 0);

        for(int j = 0; j <= bagWeight; j++) { // 遍历背包容量
            for(int i = 0; i < weight.size(); i++) { // 遍历物品
                if (j - weight[i] >= 0) dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
            }
        }
}
//如果求组合数就是外层for循环遍历物品，内层for遍历背包。
//如果求排列数就是外层for遍历背包，内层for循环遍历物品。
int DPBasic::change518(int amount, vector<int>& coins){
    vector<int> dp(amount + 1, 0); // 防止相加数据超int
            dp[0] = 1; // 只有一种方式达到0
            for (int i = 0; i < coins.size(); i++) { // 遍历物品
                for (int j = coins[i]; j <= amount; j++) { // 遍历背包
                    if (dp[j] < INT_MAX - dp[j - coins[i]]) { //防止相加数据超int
                        dp[j] += dp[j - coins[i]];
                    }
                }
            }
            return dp[amount]; // 返回组合数
}
//dp[i]: 凑成目标正整数为i的排列个数为dp[i];为排列问题；物品遍历循环放在内侧，物品的可能的排序都算一种排列
int DPBasic::combinationSum4(vector<int>& nums, int target){
    vector<int> dp(target + 1, 0);
            dp[0] = 1;
            for (int i = 0; i <= target; i++) { // 遍历背包
                for (int j = 0; j < nums.size(); j++) { // 遍历物品
                    if (i - nums[j] >= 0 && dp[i] < INT_MAX - dp[i - nums[j]]) {
                        dp[i] += dp[i - nums[j]];
                    }
                }
            }
            return dp[target];
}
//求组成金额的最少硬币个数；
//dp[j] = min(dp[j - coins[i]] + 1, dp[j])
int DPBasic::coinChange(vector<int>& coins, int amount){
    vector<int> dp(amount + 1, INT_MAX);
            dp[0] = 0;
            for (int i = 0; i < coins.size(); i++) { // 遍历物品
                for (int j = coins[i]; j <= amount; j++) { // 遍历背包
                    if (dp[j - coins[i]] != INT_MAX) { // 如果dp[j - coins[i]]是初始值则跳过
                        dp[j] = min(dp[j - coins[i]] + 1, dp[j]);
                    }
                }
            }
            if (dp[amount] == INT_MAX) return -1;
            return dp[amount];
}
//279 dp[j]：和为j的完全平方数的最少数量为dp[j]
int DPBasic::numSquares(int n){
    vector<int> dp(n + 1, INT_MAX);
            dp[0] = 0;
            for (int i = 0; i <= n; i++) { // 遍历背包
                for (int j = 1; j * j <= i; j++) { // 遍历物品
                    dp[i] = min(dp[i - j * j] + 1, dp[i]);
                }
            }
            return dp[n];
}
//139 单词就是物品，字符串s就是背包，单词能否组成字符串s，就是问物品能不能把背包装满
//dp[i] : 字符串长度为i的话，dp[i]为true，表示可以拆分为一个或多个在字典中出现的单词;
//求排列数，
bool DPBasic::wordBreak(string s, vector<string>& wordDict){
    unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
            vector<bool> dp(s.size() + 1, false);
            dp[0] = true;
            for (int i = 1; i <= s.size(); i++) {   // 遍历背包
                for (int j = 0; j < i; j++) {       // 遍历物品
                    string word = s.substr(j, i - j); //substr(起始位置，截取的个数)
                    if (wordSet.find(word) != wordSet.end() && dp[j]) {
                        dp[i] = true;
                    }
                }
            }
            return dp[s.size()];
}
//卡码网56: 多重背包
int DPBasic::multiBags(int bagWeight,int n, vector<int>& nums,vector<int>& weight,vector<int>& value){
    vector<int> dp(bagWeight + 1, 0);

       for(int i = 0; i < n; i++) { // 遍历物品
           for(int j = bagWeight; j >= weight[i]; j--) { // 遍历背包容量
               // 以上为01背包，然后加一个遍历个数
               for (int k = 1; k <= nums[i] && (j - k * weight[i]) >= 0; k++) { // 遍历个数
                   dp[j] = max(dp[j], dp[j - k * weight[i]] + k * value[i]);
               }
           }
       }

       return dp[bagWeight];
}
//198 dp[i]：考虑下标i（包括i）以内的房屋，最多可以偷窃的金额为dp[i]
int DPBasic::rob(vector<int>& nums){
    if (nums.size() == 0) return 0;
            if (nums.size() == 1) return nums[0];
            vector<int> dp(nums.size());
            dp[0] = nums[0];
            dp[1] = max(nums[0], nums[1]);
            for (int i = 2; i < nums.size(); i++) {
                dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
            }
            return dp[nums.size() - 1];
}
//213 环形房屋：分为是否包括首、末元素的数组，三种情况（不包括首末元素的数组）
// 198的逻辑
int robRange(vector<int>& nums, int start, int end) {
        if (end == start) return nums[start];
        vector<int> dp(nums.size());
        dp[start] = nums[start];
        dp[start + 1] = max(nums[start], nums[start + 1]);
        for (int i = start + 2; i <= end; i++) {
            dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
        }
        return dp[end];
    }
int DPBasic::rob213(vector<int>& nums){
    if (nums.size() == 0) return 0;
    if (nums.size() == 1) return nums[0];
    int result1 = robRange(nums, 0, static_cast<int>(nums.size())  - 2); // 情况二:包含首元素的情况
    int result2 = robRange(nums, 1, static_cast<int>(nums.size()) - 1); // 情况三：包含末元素的情况
    return max(result1, result2);
}
//337 二叉树的情况
//树形dp的入门题目，因为是在树上进行状态转移
//dp数组（dp table）以及下标的含义：下标为0记录不偷该节点所得到的的最大金钱，下标为1记录偷该节点所得到的的最大金钱
int DPBasic::rob337(TreeNode* root){
    vector<int> result = robTree(root);
    return max(result[0], result[1]);
}

// 长度为2的数组，0：不偷，1：偷
vector<int> DPBasic::robTree(TreeNode* cur) {
        if (cur == NULL) return vector<int>{0, 0};
        vector<int> left = robTree(cur->left);
        vector<int> right = robTree(cur->right);
        // 偷cur，那么就不能偷左右节点。
        int val1 = cur->val + left[0] + right[0];
        // 不偷cur，那么可以偷也可以不偷左右节点，则取较大的情况
        int val2 = max(left[0], left[1]) + max(right[0], right[1]);
        return {val2, val1};
}
//121：单次买卖
//dp[i][0] 表示第i天持有股票所得最多现金,dp[i][1] 表示第i天不持有股票所得最多现金
int DPBasic::maxProfit(vector<int>& prices) {
    int len = static_cast<int>(prices.size());
            if (len == 0) return 0;
            vector<vector<int>> dp(len, vector<int>(2));
            dp[0][0] -= prices[0];
            dp[0][1] = 0;
            for (int i = 1; i < len; i++) {
                //两种持有状态时，对应手上现金的状态
                dp[i][0] = max(dp[i - 1][0], -prices[i]);
                dp[i][1] = max(dp[i - 1][1], prices[i] + dp[i - 1][0]);
            }
            return dp[len - 1][1];
}
//因为dp[i]只是依赖于dp[i - 1]的状态，所以可以用滚动数组来简化
int DPBasic::maxProfitWithRollingArray(vector<int>& prices){
    int len = static_cast<int>(prices.size());
            vector<vector<int>> dp(2, vector<int>(2)); // 注意这里只开辟了一个2 * 2大小的二维数组
            dp[0][0] -= prices[0];
            dp[0][1] = 0;
            for (int i = 1; i < len; i++) {
                dp[i % 2][0] = max(dp[(i - 1) % 2][0], -prices[i]);
                dp[i % 2][1] = max(dp[(i - 1) % 2][1], prices[i] + dp[(i - 1) % 2][0]);
            }
            return dp[(len - 1) % 2][1];
}
//122: 可以多次买卖股票
//与121的区别：推导dp[i][0]的时候，第i天买入股票的情况。
int DPBasic::maxProfit122(vector<int>& prices){
    int len = static_cast<int>(prices.size());
            vector<vector<int>> dp(2, vector<int>(2)); // 注意这里只开辟了一个2 * 2大小的二维数组
            dp[0][0] -= prices[0];
            dp[0][1] = 0;
            for (int i = 1; i < len; i++) {
                dp[i % 2][0] = max(dp[(i - 1) % 2][0], dp[(i - 1) % 2][1] - prices[i]);//区别
                dp[i % 2][1] = max(dp[(i - 1) % 2][1], prices[i] + dp[(i - 1) % 2][0]);
            }
            return dp[(len - 1) % 2][1];
}
//123:最多2笔交易
int DPBasic::maxProfit123(vector<int>& prices){
    if (prices.size() == 0) return 0;
            vector<vector<int>> dp(prices.size(), vector<int>(5, 0));
            dp[0][1] = -prices[0];
            dp[0][3] = -prices[0];
            for (int i = 1; i < prices.size(); i++) {
                //对应5种状态
                dp[i][0] = dp[i - 1][0];
                dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
                dp[i][2] = max(dp[i - 1][2], dp[i - 1][1] + prices[i]);
                dp[i][3] = max(dp[i - 1][3], dp[i - 1][2] - prices[i]);
                dp[i][4] = max(dp[i - 1][4], dp[i - 1][3] + prices[i]);
            }
            return dp[prices.size() - 1][4];
}
int DPBasic::maxProfit123WithRollingArray(vector<int>& prices){
    if (prices.size() == 0) return 0;
            vector<int> dp(5, 0);
            dp[1] = -prices[0];
            dp[3] = -prices[0];
            for (int i = 1; i < prices.size(); i++) {
                dp[1] = max(dp[1], dp[0] - prices[i]);
                dp[2] = max(dp[2], dp[1] + prices[i]);
                dp[3] = max(dp[3], dp[2] - prices[i]);
                dp[4] = max(dp[4], dp[3] + prices[i]);
            }
            return dp[4];
}
//188: 最多k笔交易
int DPBasic::maxProfit188(int k, vector<int>& prices){
    if (prices.size() == 0) return 0;
            vector<vector<int>> dp(prices.size(), vector<int>(2 * k + 1, 0));
            for (int j = 1; j < 2 * k; j += 2) {
                dp[0][j] = -prices[0];//第0天所有买入操作后
            }
            for (int i = 1;i < prices.size(); i++) {
                for (int j = 0; j < 2 * k - 1; j += 2) {
                    dp[i][j + 1] = max(dp[i - 1][j + 1], dp[i - 1][j] - prices[i]);//所有买入
                    dp[i][j + 2] = max(dp[i - 1][j + 2], dp[i - 1][j + 1] + prices[i]);//所有卖出
                }
            }
            return dp[prices.size() - 1][2 * k];//最后一次卖出后，获得最大利润
}
//309 你可以尽可能地完成更多的交易
//区别：卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)
//4种状态：
int DPBasic::maxProfit309(vector<int>& prices){
    int n = static_cast<int>(prices.size());
            if (n == 0) return 0;
            vector<vector<int>> dp(n, vector<int>(4, 0));
            dp[0][0] -= prices[0]; // 持股票
            for (int i = 1; i < n; i++) {
                //买入股票状态：前一天持有股票状态，冷冻期或保持卖出状态
                dp[i][0] = max(dp[i - 1][0], max(dp[i - 1][3] - prices[i], dp[i - 1][1] - prices[i]));
                dp[i][1] = max(dp[i - 1][1], dp[i - 1][3]);//保持卖出股票状态：前一天是卖出状态或冷冻期
                dp[i][2] = dp[i - 1][0] + prices[i];//卖出股票状态：昨天一定持有股票
                dp[i][3] = dp[i - 1][2];//冷冻期状态
            }
            return max(dp[n - 1][3], max(dp[n - 1][1], dp[n - 1][2]));
}
//714: 含手续费
//本题和动态规划：122.买卖股票的最佳时机II (opens new window)的区别就是这里需要多一个减去手续费的操作
int DPBasic::maxProfit714(vector<int>& prices, int fee){
    int n = static_cast<int>(prices.size());
    vector<vector<int>> dp(n, vector<int>(2, 0));
    dp[0][0] -= prices[0]; // 持股票
    for (int i = 1; i < n; i++) {
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
        dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i] - fee);//卖出时收手续费
    }
    return max(dp[n - 1][0], dp[n - 1][1]);
}
//300 最长递增子序列
//子序列是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序
//dp[i]表示i之前包括i的以nums[i]结尾的最长递增子序列的长度
//如果i位置的数字大于j位置的数字：位置i的最长升序子序列等于j从0到i-1各个位置的最长升序子序列 + 1 的最大值；否则不操作
int DPBasic::lengthOfLIS(vector<int>& nums){
    if (nums.size() <= 1) return static_cast<int>(nums.size());
            vector<int> dp(nums.size(), 1);
            int result = 0;
            for (int i = 1; i < nums.size(); i++) {
                for (int j = 0; j < i; j++) {
                    if (nums[i] > nums[j]) dp[i] = max(dp[i], dp[j] + 1);
                }
                if (dp[i] > result) result = dp[i]; // 取长的子序列
            }
            return result;
}
//674 最长连续递增子序列
//如果 nums[i] > nums[i - 1]，那么以 i 为结尾的连续递增的子序列长度 一定等于 以i - 1为结尾的连续递增的子序列长度 + 1 。
int DPBasic::findLengthOfLCIS(vector<int>& nums) {
    if (nums.size() == 0) return 0;
            int result = 1;
            vector<int> dp(nums.size() ,1);
            for (int i = 1; i < nums.size(); i++) {
                if (nums[i] > nums[i - 1]) { // 连续记录
                    dp[i] = dp[i - 1] + 1;
                }
                if (dp[i] > result) result = dp[i];
            }
            return result;
}
//718 返回两个数组中公共、长度最长的子数组的长度
//dp[i][j] ：以下标i - 1为结尾的A，和以下标j - 1为结尾的B，最长重复子数组长度为dp[i][j]
//递推公式：即当A[i - 1] 和B[j - 1]相等的时候，dp[i][j] = dp[i - 1][j - 1] + 1;
int DPBasic::findLength718(vector<int>& nums1, vector<int>& nums2){
    vector<vector<int>> dp (nums1.size() + 1, vector<int>(nums2.size() + 1, 0));
            int result = 0;
            for (int i = 1; i <= nums1.size(); i++) {
                for (int j = 1; j <= nums2.size(); j++) {
                    if (nums1[i - 1] == nums2[j - 1]) {
                        dp[i][j] = dp[i - 1][j - 1] + 1;
                    }
                    if (dp[i][j] > result) result = dp[i][j];
                }
            }
            return result;
}
int DPBasic::findLength718WithRollingArray(vector<int>& A, vector<int>& B){
    vector<int> dp(vector<int>(B.size() + 1, 0));
            int result = 0;
            for (int i = 1; i <= A.size(); i++) {
                for (int j = static_cast<int>(B.size()); j > 0; j--) {//要从后向前遍历，这样避免重复覆盖
                    if (A[i - 1] == B[j - 1]) {
                        dp[j] = dp[j - 1] + 1;
                    } else dp[j] = 0; // 注意这里不相等的时候要有赋0的操作
                    if (dp[j] > result) result = dp[j];
                }
            }
            return result;
}
//1143 最长公共子序列
//子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串
//与连续序列的区别：子序列是字符串中删除某些字符而得到的字符串；连续字符串用KMP
//dp[i][j]：长度为[0, i - 1]的字符串text1与长度为[0, j - 1]的字符串text2的最长公共子序列为dp[i][j]
int DPBasic::longestCommonSubsequence(string text1, string text2){
    vector<vector<int>> dp(text1.size() + 1, vector<int>(text2.size() + 1, 0));
            for (int i = 1; i <= text1.size(); i++) {
                for (int j = 1; j <= text2.size(); j++) {
                    if (text1[i - 1] == text2[j - 1]) {
                        dp[i][j] = dp[i - 1][j - 1] + 1;
                    } else {
                        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                    }
                }
            }
            return dp[text1.size()][text2.size()];
}
//1035 绘制一些连接两个数字 A[i] 和 B[j] 的直线，只要 A[i] == B[j]，且直线不能相交！
int DPBasic::maxUncrossedLines(vector<int>& text1, vector<int>& text2){
    vector<vector<int>> dp(text1.size() + 1, vector<int>(text2.size() + 1, 0));
            for (int i = 1; i <= text1.size(); i++) {
                for (int j = 1; j <= text2.size(); j++) {
                    if (text1[i - 1] == text2[j - 1]) {
                        dp[i][j] = dp[i - 1][j - 1] + 1;
                    } else {
                        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                    }
                }
            }
            return dp[text1.size()][text2.size()];
}
//53 具有最大和的连续子数组
//dp[i]：包括下标i（以nums[i]为结尾）的最大连续子序列和为dp[i]
int DPBasic::maxSubArray(vector<int>& nums){
    if (nums.size() == 0) return 0;
            vector<int> dp(nums.size());
            dp[0] = nums[0];
            int result = dp[0];
            for (int i = 1; i < nums.size(); i++) {
                dp[i] = max(dp[i - 1] + nums[i], nums[i]); // 状态转移公式
                if (dp[i] > result) result = dp[i]; // result 保存dp[i]的最大值
            }
            return result;
}
//392 判断子序列
//字符串的一个子序列是原始字符串删除一些（也可以不删除）字符而不改变剩余字符相对位置形成的新字符串。
//dp[i][j] 表示以下标i-1为结尾的字符串s，和以下标j-1为结尾的字符串t，相同子序列的长度为dp[i][j]
//与1143的区别：此处只能删除t的元素，1143是两个字符串都可以删除元素
bool DPBasic::isSubsequence(string s, string t){
    vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1, 0));
            for (int i = 1; i <= s.size(); i++) {
                for (int j = 1; j <= t.size(); j++) {
                    if (s[i - 1] == t[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
                    else dp[i][j] = dp[i][j - 1];
                }
            }
            if (dp[s.size()][t.size()] == s.size()) return true;
            return false;
}
//115 字符串s中可能的子序列t的可能性
//dp[i][j]：以i-1为结尾的s子序列中出现以j-1为结尾的t的个数为dp[i][j]
int DPBasic::numDistinct115(string s, string t){
    vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1));
            for (int i = 0; i < s.size(); i++) dp[i][0] = 1;
            for (int j = 1; j < t.size(); j++) dp[0][j] = 0;
            for (int i = 1; i <= s.size(); i++) {
                for (int j = 1; j <= t.size(); j++) {
                    if (s[i - 1] == t[j - 1]) {
                        dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];//对应两种情况
                    } else {
                        dp[i][j] = dp[i - 1][j];//只能对应1种情况，即删除s最后一个元素i再匹配
                    }
                }
            }
            return dp[static_cast<int>(s.size())][static_cast<int>(t.size())];
}
//583 两个字符串的删除字符到相等的最小次数
//dp[i][j]：以i-1为结尾的字符串word1，和以j-1位结尾的字符串word2，想要达到相等，所需要删除元素的最少次数
int DPBasic::minDistance(string word1, string word2){
    vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1));
            for (int i = 0; i <= word1.size(); i++) dp[i][0] = i;
            for (int j = 0; j <= word2.size(); j++) dp[0][j] = j;
            for (int i = 1; i <= word1.size(); i++) {
                for (int j = 1; j <= word2.size(); j++) {
                    if (word1[i - 1] == word2[j - 1]) {
                        dp[i][j] = dp[i - 1][j - 1];
                    } else {
                        dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1);
                    }
                }
            }
            return dp[word1.size()][word2.size()];
}
//利用1143找出最长子序列，然后用2个string的总长度-最长子序列的长度*2 即可
int DPBasic::minDistance2(string word1, string word2){
    int w1 = static_cast<int>(word1.size());
    int w2 = static_cast<int>(word2.size());
    vector<vector<int>> dp(word1.size()+1, vector<int>(word2.size()+1, 0));
            for (int i=1; i<=word1.size(); i++){
                for (int j=1; j<=word2.size(); j++){
                    if (word1[i-1] == word2[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
                    else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
            return w1 + w2 - dp[w1][w2]*2;
}
//72 编辑距离： 通过插入、删除、替换一个字符使w1成为w2, 求最小编辑次数
//dp[i][j] 表示以下标i-1为结尾的字符串word1，和以下标j-1为结尾的字符串word2，最近编辑距离为dp[i][j]
int DPBasic::minDistance72(string word1, string word2){
    int w1 = static_cast<int>(word1.size());
    int w2 = static_cast<int>(word2.size());
    vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));
            for (int i = 0; i <= word1.size(); i++) dp[i][0] = i;
            for (int j = 0; j <= word2.size(); j++) dp[0][j] = j;
            for (int i = 1; i <= word1.size(); i++) {
                for (int j = 1; j <= word2.size(); j++) {
                    if (word1[i - 1] == word2[j - 1]) {
                        dp[i][j] = dp[i - 1][j - 1];
                    }
                    else {
                        dp[i][j] = min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1;//插入、删除、替换的情况
                    }
                }
            }
            return dp[w1][w2];
}
//647:计算字符串中包含回文字符串的个数
//递推：布尔类型的dp[i][j]：表示区间范围[i,j] （注意是左闭右闭）的子串是否是回文子串，如果是dp[i][j]为true，否则为false。
//核心：dp[i][j]是否是回文，依赖于dp[i+1][j-1]是否是回文；同时要判断s[i]和s[j]是否相等
//从下到上，从左到右遍历
int DPBasic::countSubstrings(string s){
    vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));
            int result = 0;
            for (int i = static_cast<int>(s.size()) - 1; i >= 0; i--) {  // 注意遍历顺序
                for (int j = i; j < s.size(); j++) {
                    if (s[i] == s[j]) {
                        if (j - i <= 1) { // 情况一 和 情况二
                            result++;
                            dp[i][j] = true;
                        } else if (dp[i + 1][j - 1]) { // 情况三
                            result++;
                            dp[i][j] = true;
                        }
                    }
                }
            }
            return result;
}
//双指针法
int DPBasic::countSubstringsWithTwoPointers(string s) {
        int result = 0;
    int length = static_cast<int>(s.size());
        for (int i = 0; i < s.size(); i++) {
            result += extend(s, i, i, length); // 以i为中心
            result += extend(s, i, i + 1, length); // 以i和i+1为中心
        }
        return result;
}
int DPBasic::extend(const string& s, int i, int j, int n) {
        int res = 0;
        while (i >= 0 && j < n && s[i] == s[j]) {
            i--;
            j++;
            res++;
        }
        return res;
}
//516最长回文子序列：子序列是不连续的
//dp[i][j]：字符串s在[i, j]范围内最长的回文子序列的长度为dp[i][j]
int DPBasic::longestPalindromeSubseq(string s){
    vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));
    int length = static_cast<int>(s.size());
            for (int i = 0; i < s.size(); i++) dp[i][i] = 1;
            for (int i = length - 1; i >= 0; i--) {
                for (int j = i + 1; j < s.size(); j++) {
                    if (s[i] == s[j]) {
                        dp[i][j] = dp[i + 1][j - 1] + 2;
                    } else {
                        dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                    }
                }
            }
            return dp[0][length - 1];
}
