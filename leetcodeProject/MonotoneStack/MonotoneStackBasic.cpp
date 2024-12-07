//
//  MonotoneStackBasic.cpp
//  leetcodeProject
//
//  Created by WeiJin on 2024-12-07.
//  

#include "MonotoneStackBasic.hpp"
#include <stack>
//739
// Result数组：记录栈顶元素右面比他大的元素的下标的距离
vector<int> MonotoneStackBasic::dailyTemperatures(vector<int>& temperatures){
    //递增栈
    stack<int> st;
    vector<int>result(temperatures.size(),0);
    st.push(0);
    for (int i = 1; i < temperatures.size(); i++) {
        //当元素小于等于栈顶元素时，入栈，此时栈里递增；if判断可以精简删除，逻辑相同
        if(temperatures[i] < temperatures[st.top()]){// 情况1
            st.push(i);
        }else if(temperatures[i] == temperatures[st.top()]){// 情况2
            st.push(i);
        }else{
            while(!st.empty() && temperatures[i] > temperatures[st.top()]){// 情况3
                result[st.top()] = i - st.top();
                st.pop();
            }
            st.push(i);
        }
        
    }
    return result;
}
//496
vector<int> MonotoneStackBasic::nextGreaterElement(vector<int>& nums1, vector<int>& nums2){
    stack<int> st;
            vector<int> result(nums1.size(), -1);
            if (nums1.size() == 0) return result;

            unordered_map<int, int> umap; // key:下标元素，value：下标
            for (int i = 0; i < nums1.size(); i++) {
                umap[nums1[i]] = i;
            }
            st.push(0);
            for (int i = 1; i < nums2.size(); i++) {
                //if判断可以精简删除，逻辑相同
                if (nums2[i] < nums2[st.top()]) {           // 情况一
                    st.push(i);
                } else if (nums2[i] == nums2[st.top()]) {   // 情况二
                    st.push(i);
                } else {                                    // 情况三
                    while (!st.empty() && nums2[i] > nums2[st.top()]) {
                        if (umap.count(nums2[st.top()]) > 0) { // 看map里是否存在这个元素
                            int index = umap[nums2[st.top()]]; // 根据map找到nums2[st.top()] 在 nums1中的下标
                            result[index] = nums2[i];
                        }
                        st.pop();
                    }
                    st.push(i);
                }
            }
            return result;
}
//503 循环数组：最后一个元素的下一个元素是数组的第一个元素
//相当于数组遍历了两遍，result记录不受影响
vector<int> MonotoneStackBasic::nextGreaterElements(vector<int>& nums){
    vector<int> result(nums.size(), -1);
            if (nums.size() == 0) return result;
            stack<int> st;
            st.push(0);
    
            for (int i = 1; i < nums.size() * 2; i++) {
                // 模拟遍历两边nums，注意一下都是用i % nums.size()来操作 //if判断可以精简删除，逻辑相同
                if (nums[i % nums.size()] < nums[st.top()]) st.push(i % nums.size());
                else if (nums[i % nums.size()] == nums[st.top()]) st.push(i % nums.size());
                else {
                    while (!st.empty() && nums[i % nums.size()] > nums[st.top()]) {
                        result[st.top()] = nums[i % nums.size()];
                        st.pop();
                    }
                    st.push(i % nums.size());
                }
            }
            return result;
}
//42接雨水的问题
//按列计算，每一列雨水的高度，取决于，该列 左侧最高的柱子和右侧最高的柱子中最矮的那个柱子的高度。
int MonotoneStackBasic::trap(vector<int>& height){
    int sum = 0;
    for (int i = 0; i < height.size(); i++) {
        // 第一个柱子和最后一个柱子不接雨水
        if (i == 0 || i == height.size() - 1) continue;
        
        int rHeight = height[i]; // 记录右边柱子的最高高度
        int lHeight = height[i]; // 记录左边柱子的最高高度
        for (int r = i + 1; r < height.size(); r++) {
                        if (height[r] > rHeight) rHeight = height[r];
                    }
                    for (int l = i - 1; l >= 0; l--) {
                        if (height[l] > lHeight) lHeight = height[l];
                    }
                    int h = min(lHeight, rHeight) - height[i];//计算雨水值
                    if (h > 0) sum += h;
    }
    return sum;
}
//优化上面的算法，将左侧和右侧最大高度存入数组，避免重复计算
int MonotoneStackBasic::trap1(vector<int>& height) {
        if (height.size() <= 2) return 0;
        vector<int> maxLeft(height.size(), 0);
        vector<int> maxRight(height.size(), 0);
        int size = static_cast<int>(maxRight.size());

        // 记录每个柱子左边柱子最大高度
        maxLeft[0] = height[0];
        for (int i = 1; i < size; i++) {
            maxLeft[i] = max(height[i], maxLeft[i - 1]);
        }
        // 记录每个柱子右边柱子最大高度
        maxRight[size - 1] = height[size - 1];
        for (int i = size - 2; i >= 0; i--) {
            maxRight[i] = max(height[i], maxRight[i + 1]);
        }
        // 求和
        int sum = 0;
        for (int i = 0; i < size; i++) {
            int count = min(maxLeft[i], maxRight[i]) - height[i];
            if (count > 0) sum += count;
        }
        return sum;
    }
//单调栈解法
//因为一旦发现添加的柱子高度大于栈头元素了，此时就出现凹槽了，栈头元素就是凹槽底部的柱子，栈头第二个元素就是凹槽左边的柱子，而添加的元素就是凹槽右边的柱子
int MonotoneStackBasic::trap2(vector<int>& height) {
    if (height.size() <= 2) return 0; // 可以不加
            stack<int> st; // 存着下标，计算的时候用下标对应的柱子高度
            st.push(0);
            int sum = 0;
    
    for (int i = 1; i < height.size(); i++) {
        //if可以省略，此处为了易读性
        if(height[i] < height[st.top()]){//case 1: 维持栈内从小到大
            st.push(i);
        }else if(height[i] == height[st.top()]){//case 2: 相同元素，用右边的高度来计算面积
            st.pop();
            st.push(i);
        }else{
            while (!st.empty() && height[i] > height[st.top()]) {
                int mid = st.top();
                st.pop();
                if(!st.empty()){
                    int h = min(height[st.top()],height[i])-height[mid];
                    int w = i - st.top() - 1;//减1， 只求中间宽度
                    sum += h*w;
                }
            }
            st.push(i);
        }
    }
    return  sum;
}
//84
//栈顶和栈顶的下一个元素以及要入栈的三个元素组成了我们要求最大面积的高度和宽度
int MonotoneStackBasic::largestRectangleArea(vector<int>& heights){
    int result = 0;
            stack<int> st;
            heights.insert(heights.begin(), 0); // 数组头部加入元素0
            heights.push_back(0); // 数组尾部加入元素0
            st.push(0);

            // 第一个元素已经入栈，从下标1开始
            for (int i = 1; i < heights.size(); i++) {
                if (heights[i] > heights[st.top()]) { // 情况一
                    st.push(i);
                } else if (heights[i] == heights[st.top()]) { // 情况二
                    st.pop(); // 这个可以加，可以不加，效果一样，思路不同
                    st.push(i);
                } else { // 情况三
                    while (!st.empty() && heights[i] < heights[st.top()]) { // 注意是while
                        int mid = st.top();
                        st.pop();
                        if (!st.empty()) {
                            int left = st.top();
                            int right = i;
                            int w = right - left - 1;
                            int h = heights[mid];
                            result = max(result, w * h);
                        }
                    }
                    st.push(i);
                }
            }
            return result;
}
