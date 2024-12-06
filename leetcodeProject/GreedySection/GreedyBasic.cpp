//
//  GreedyBasic.cpp
//  leetcodeProject
//
//  Created by WeiJin on 2024-11-18.
//

#include "GreedyBasic.hpp"
#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <list>
using namespace std;

//455 尽可能满足更多孩子的胃口，
//局部最优就是大饼干喂给胃口大的，充分利用饼干尺寸喂饱一个，全局最优就是喂饱尽可能多的小孩。
//TC:O(nlogn);SC:1
int GreedyBasic::findContentChildren(vector<int>& g, vector<int>& s){
    sort(g.begin(),g.end());
    sort(s.begin(),s.end());
    int index = static_cast<int>(s.size()) - 1;//饼干数组的下标
    int result = 0;
    for(int i = static_cast<int>(g.size()) - 1; i >= 0 ; i--){//遍历胃口
        if(index >= 0 && s[index] >= g[i]){//遍历饼干
            result++;
            index--;
        }
    }
    return result;
}
//376 统计摆动序列的波动 prediff（nums[i] - nums[i-1]） 和 curdiff（nums[i+1] - nums[i]），如果prediff < 0 && curdiff > 0 或者 prediff > 0 && curdiff < 0 此时就有波动就需要统计。
// 要考虑三种情况
// 动态规划算法后面再看
int GreedyBasic::wiggleMaxLength(vector<int>& nums){
    if (nums.size() <= 1) return static_cast<int>(nums.size());
            int curDiff = 0; // 当前一对差值
            int preDiff = 0; // 前一对差值
            int result = 1;  // 记录峰值个数，序列默认序列最右边有一个峰值
            for (int i = 0; i < nums.size() - 1; i++) {
                curDiff = nums[i + 1] - nums[i];
                // 出现峰值
                if ((preDiff <= 0 && curDiff > 0) || (preDiff >= 0 && curDiff < 0)) {
                    result++;
                    preDiff = curDiff; // 注意这里，只在摆动变化的时候更新prediff
                }
            }
            return result;
}
//53
//局部最优：当前“连续和”为负数的时候立刻放弃，从下一个元素重新计算“连续和”，因为负数加上下一个元素 “连续和”只会越来越小。
//全局最优：选取最大“连续和”
int GreedyBasic::maxSubArray(vector<int>& nums){
    int result = INT32_MIN;
    int count = 0;
    for(int i = 0; i < nums.size();i++){
        count += nums[i];
        if(count > result){// 取区间累计的最大值（相当于不断确定最大子序终止位置）
            result = count;
        }
        if(count <= 0) count = 0;// 相当于重置最大子序起始位置，因为遇到负数一定是拉低总和
    }
    return result;
}
//122 买股票最佳时机：数组中是制定股票第i天的价格，可以多次买卖，但是买之前必须全部卖出（不能同时多笔交易）；想获得利润至少要两天为一个交易单元
//局部最优：收集每天的正利润，全局最优：求得最大利润。
//把整体利润拆为每天的利润，然后统计每天正利润的和
int GreedyBasic::maxProfit(vector<int>& prices){
    int result = 0;
            for (int i = 1; i < prices.size(); i++) {
                result += max(prices[i] - prices[i - 1], 0);
            }
            return result;
}
//55 跳跃： 思路：跳跃覆盖范围究竟可不可以覆盖到终点
//贪心算法局部最优解：每次取最大跳跃步数（取最大覆盖范围），整体最优解：最后得到整体最大覆盖范围，看是否能到终点。
bool GreedyBasic::canJump(vector<int>& nums){
    int cover = 0;
    if(nums.size() == 1) return true;//一个元素时，能达到
    for(int i = 0; i <= cover;i++){//cover不断更新，当i超过cover就不行了
        cover = max(i + nums[i],cover);
        if(cover >= nums.size() - 1) return true;// 说明可以覆盖到终点了
    }
    return false;
}
//45 最少的次数跳到终点
//要统计两个覆盖范围，当前这一步的最大覆盖和下一步最大覆盖；如果移动下标达到了当前这一步的最大覆盖最远距离了，还没有到终点的话，那么就必须再走一步来增加覆盖范围，直到覆盖范围覆盖了终点。
int GreedyBasic::jump(vector<int>& nums){
    int curDistance = 0;    // 当前覆盖的最远距离下标
            int ans = 0;            // 记录走的最大步数
            int nextDistance = 0;   // 下一步覆盖的最远距离下标
            for (int i = 0; i < nums.size() - 1; i++) { // 注意这里是小于nums.size() - 1，这是关键所在
                nextDistance = max(nums[i] + i, nextDistance); // 更新下一步覆盖的最远距离下标
                if (i == curDistance) {                 // 遇到当前覆盖的最远距离下标（题目假设总是可以到达数组的最后一个位置，如果不等，说明不用ans++,肯定可以到；注意是到倒数第二个位置）
                    curDistance = nextDistance;         // 更新当前覆盖的最远距离下标
                    ans++;
                }
            }
            return ans;
}
//1005 反转元素符号K次，返回数组最大和
//贪心的思路，局部最优：让绝对值大的负数变为正数（绝对值小的正数转为负数），当前数值达到最大，整体最优：整个数组和达到最大。
//第一步：将数组按照绝对值大小从大到小排序，注意要按照绝对值的大小；第二步：从前向后遍历，遇到负数将其变为正数，同时K--；第三步：如果K还大于0，那么反复转变数值最小的元素，将K用完；第四步：求和
//TC:nlogn
int GreedyBasic::largestSumAfterKNegations(vector<int>& nums, int k){
    sort(nums.begin(), nums.end(), [](int a, int b) {
        return std::abs(a) > std::abs(b);
    });       // 第一步
            for (int i = 0; i < nums.size(); i++) { // 第二步
                if (nums[i] < 0 && k > 0) {
                    nums[i] *= -1;
                    k--;
                }
            }
            if (k % 2 == 1) nums[nums.size() - 1] *= -1; // 第三步
            int result = 0;
            for (int a : nums) result += a;        // 第四步
            return result;
}
//134 局部最优：当前累加rest[i]的和curSum一旦小于0，起始位置至少要是i+1，因为从i之前开始一定不行。全局最优：找到可以跑一圈的起始位置;类似于53题
int GreedyBasic::canCompleteCircuit(vector<int>& gas, vector<int>& cost){
    int curSum = 0;
    int totalSum = 0;
    int start = 0;
    for(int i = 0; i < gas.size();i++){
        curSum += gas[i] - cost[i];
        totalSum += gas[i] - cost[i];
        if(curSum < 0){// 当前累加rest[i]和 curSum一旦小于0: 说明选择0，i之间的任何一个起点，此处都会断油；所以要i+1
            start = i + 1;// 起始位置更新为i+1
            curSum = 0; // curSum从0开始
        }
    }
    if(totalSum < 0) return -1;// 说明怎么走都不可能跑一圈了
    return start;
}
//135 解法：采用两次贪心算法，先从左到右遍历，确保右侧孩子拿的比左侧孩子多；然后从右往左遍历，确保左侧孩子评分高的拿的更多；
//1. 局部最优：只要右边评分比左边大，右边的孩子就多一个糖果，全局最优：相邻的孩子中，评分高的右孩子获得比左边孩子更多的糖果
//2. 一次是从右到左遍历，只比较左边孩子评分比右边大的情况
int GreedyBasic::candy(vector<int>& ratings){
    vector<int> candyVec(ratings.size(), 1);
            // 从前向后
            for (int i = 1; i < ratings.size(); i++) {
                if (ratings[i] > ratings[i - 1]) candyVec[i] = candyVec[i - 1] + 1;
            }
            // 从后向前
    for (int i = static_cast<int>(ratings.size())  - 2; i >= 0; i--) {
                if (ratings[i] > ratings[i + 1] ) {
                    candyVec[i] = max(candyVec[i], candyVec[i + 1] + 1);
                }
            }
            // 统计结果
            int result = 0;
            for (int i = 0; i < candyVec.size(); i++) result += candyVec[i];
            return result;
}
//860 林檬水找零
bool GreedyBasic::lemonadeChange(vector<int>& bills){
    int five = 0, ten = 0, twenty = 0;
    for(int bill : bills){
        //情况1
        if(bill == 5) five++;
        if(bill == 10){
            if(five <= 0) return false;
            ten++;
            five--;
        }
        if(bill == 20){
            if(five > 0 && ten >0){
                five--;
                ten--;
                twenty++;
            }else if(five > 3){
                five -= 3;
                twenty++;
            }else return false;
        }
    }
    return true;
}
//406 解法：按照身高排序之后，优先按身高高的people的k来插入，后序插入节点也不会影响前面已经插入的节点，最终按照k的规则完成了队列
//局部最优：优先按身高高的people的k来插入。插入操作过后的people满足队列属性
//全局最优：最后都做完插入操作，整个队列满足题目队列属性
// 此处使用list效率更高；vector底层使用普通数组，扩容和拷贝数据效率低
vector<vector<int>> GreedyBasic::reconstructQueue(vector<vector<int>>& people){
    sort (people.begin(), people.end(), cmpHelper);
            list<vector<int>> que; // list底层是链表实现，插入效率比vector高的多
            for (int i = 0; i < people.size(); i++) {
                int position = people[i][1]; // 插入到下标为position的位置
                std::list<vector<int>>::iterator it = que.begin();//注意此处的迭代器写法
                while (position--) { // 寻找在插入位置
                    it++;
                }
                que.insert(it, people[i]);
            }
            return vector<vector<int>>(que.begin(), que.end());
}
//406
bool GreedyBasic::cmpHelper(const vector<int>& a, const vector<int>& b){
    // 身高从大到小排（身高相同k小的站前面）
    if(a[0] == b[0]) return a[1] < b[1];
    return a[0] > b[0];
}
//452
//局部最优：当气球出现重叠，一起射，所用弓箭最少。全局最优：把所有气球射爆所用弓箭最少。
//为了让气球尽可能的重叠，需要对数组进行排序。
//时间复杂度：O(nlog n)，因为有一个快排
int GreedyBasic::findMinArrowShots(vector<vector<int>>& points){
    if(points.size() == 0) return 0;
    sort(points.begin(),points.end(),[](const vector<int>& a, const vector<int>& b){return a[0] < b[0];});
    
    int result = 1;//至少一支箭
    for(int i = 0;i< points.size();i++){
        if(points[i][0] > points[i-1][1]){// 气球i和气球i-1不挨着，注意这里不是>=; =表示可以一起射
            result++;//需要一支箭
        }else{
            points[i][1] = min(points[i-1][1],points[i][1]);//更新重叠气球最小右边界
        }
    }
    return result;
}
//452 解法：先按区间右侧排序，然后比较最小右侧边界是否与后序左侧边界重叠；重叠说明区间重叠，不重叠说明区间是间隔的
int GreedyBasic::eraseOverlapIntervals(vector<vector<int>>& intervals){
    if(intervals.size() == 0) return 0;
    sort(intervals.begin(),intervals.end(),[](const vector<int>& a, const vector<int>& b) {return a[1] < b[1];});
    
    int count = 1;//记录非交叉区间的个数
    int end = intervals[0][1];//记录区间分割点
    for(int i = 0;i < intervals.size();i++){
        if(end <= intervals[i][0]){//区间分割点与有序区间左侧边界比较，如果小于，则说明区间是不交叉的；此时要更新新的区间分割点，且区间数+1
            end = intervals[i][1];
            count++;
        }
    }
    return static_cast<int>(intervals.size()) - count;//差是需要删除的区间数量
}
//763 题目要求同一字母最多出现在一个片段中
//1.统计每一个字符最后出现的位置;2.从头遍历字符，并更新字符的最远出现下标，如果找到字符最远出现位置下标和当前下标相等了，则找到了分割点
//解法2: 也可以按不交叉区间来做，稍微麻烦
vector<int> GreedyBasic::partitionLabels(string s){
    int hash[27] = {0};//i为字符，hash[i]为字符出现的最后位置
    for(int i = 0; i < s.size();i++){
        hash[s[i] - 'a'] = i;
    }
    
    vector<int> result;
    int left = 0;
    int right = 0;
    for(int i = 0; i < s.size();i++){
        right = max(right,hash[s[i] - 'a']);// 找到字符出现的最远边界
        if(i == right){
            result.push_back(right - left + 1);
            left = i + 1;
        }
    }
    return result;
}
//56 合并区间
//时间复杂度: O(nlogn)；空间复杂度: O(logn)，排序需要的空间开销
vector<vector<int>> GreedyBasic::merge56(vector<vector<int>>& intervals){
    vector<vector<int>> result;
    if(intervals.size() == 0) return  result;//区间为空即返回
    sort(intervals.begin(),intervals.end(),[](const vector<int>& a, const vector<int>& b){return a[0] < b[0];});//按左边界排序
    
    // 第一个区间就可以放进结果集里，后面如果重叠，在result上直接合并
            result.push_back(intervals[0]);

            for (int i = 1; i < intervals.size(); i++) {
                if (result.back()[1] >= intervals[i][0]) { // 发现重叠区间
                    // 合并区间，只更新右边界就好，因为result.back()的左边界一定是最小值，因为我们按照左边界排序的
                    result.back()[1] = max(result.back()[1], intervals[i][1]);
                } else {
                    result.push_back(intervals[i]); // 区间不重叠
                }
            }
            return result;
}
//738 小于等于N的整数，其各位上的数字单调递增，可以相等
int GreedyBasic::monotoneIncreasingDigits(int n){
    string strNum = to_string(n);
    // flag用来标记赋值9从哪里开始
    // 设置为这个默认值，为了防止第二个for循环在flag没有被赋值的情况下执行
    int flag = static_cast<int>(strNum.size()) ;
    for(int i = static_cast<int>(strNum.size()) - 1; i > 0; i--){
        if(strNum[i-1] > strNum[i]){
            flag = i;
            strNum[i-1]--;
        }
    }
    for(int i = flag;i < strNum.size();i++){
        strNum[i] = '9';
    }
    return stoi(strNum);
}
//968 节点上的每个摄影头都可以监视其父对象、自身及其直接子对象。计算监控树的所有节点所需的最小摄像头数量。
//贪心：局部最优：让叶子节点的父节点安摄像头，所用摄像头最少，整体最优：全部摄像头数量所用最少！
//三种状态：节点无覆盖、有摄像头、有覆盖；分别用0，1，2表示
//核心：隔两层节点放一个摄像头；所以空节点为有覆盖状态 '2'；只要有一个孩子没有覆盖，父节点就应该放摄像头
int GreedyBasic::minCameraCover(TreeNode* root){
    result = 0;
    //情况4
    if(traversalHelper(root) == 0){// root 无覆盖
        result++;
    }
    return result;
}

int GreedyBasic::traversalHelper(TreeNode* cur){
    if(cur == NULL) return 2;// 空节点，该节点有覆盖
    int left = traversalHelper(cur->left);//左
    int right = traversalHelper(cur->right);//右
    // 情况1
    // 左右节点都有覆盖;因为要隔两层放摄像头，所以此处为无覆盖
    if(left == 2 && right == 2) return 0;
    else if(left == 0 || right ==0){
        result++;
        return 1;// 情况2：左右节点至少有一个无覆盖的情况，要放摄像头
    }else return 2;//情况3：左右节点至少有一个有摄像头，父节点是覆盖状态
}
