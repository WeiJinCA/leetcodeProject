//
//  MonotoneStackBasic.hpp
//  leetcodeProject
//
//  Created by WeiJin on 2024-12-07.
//  单调栈：存放的是元素的下标； 元素为递增或递减的； 用于记录之前遍历过的元素，和当前遍历的元素对比
//  
//  一维数组，要寻找任一个元素的右边或者左边第一个比自己大或者小的元素的位置;
//  单调栈的本质是空间换时间，因为在遍历的过程中需要用一个栈来记录右边第一个比当前元素高的元素，优点是整个数组只需要遍历一次

#ifndef MonotoneStackBasic_hpp
#define MonotoneStackBasic_hpp

#include <stdio.h>
#include <vector>
#include <unordered_map>

using namespace std;
class MonotoneStackBasic {
    
public:
    vector<int> dailyTemperatures(vector<int>& temperatures);//739
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2);//496
    vector<int> nextGreaterElements(vector<int>& nums);//503
    int trap(vector<int>& height);//42
    int trap1(vector<int>& height);
    int trap2(vector<int>& height) ;
    int largestRectangleArea(vector<int>& heights);//84
};

#endif /* MonotoneStackBasic_hpp */
