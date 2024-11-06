//
//  ArraySection.hpp
//  leetcodeProject
//
//  Created by WeiJin on 2024-10-16.
//

#ifndef ArraySection_hpp
#define ArraySection_hpp

using namespace std;
#include <stdio.h>


class ArraySection {
public:
    //二分查找
    int binarySearch(vector<int>& nums, int target);// 704
    int searchInsert(vector<int>& nums, int target);//35
    int BinarySearchHelper(vector<int>& nums, int target,int side);//34 helper
    vector<int> searchRange(vector<int>& nums, int target);//34
    int mySqrt(int x);//69
    bool isPerfectSquare(int num) ;//367
    
    //移除元素
    int removeElement(vector<int>& nums, int val);//27
    int removeDuplicates(vector<int>& nums);//26
    void moveZeroes(vector<int>& nums);//283
    bool backspaceCompare(string s, string t);//844 含退格字符，比较字符串
    vector<int> sortedSquares(vector<int>& A);//977 平方后有序
    
    //长度最小的子数组
    int minSubArrayLen(int target, vector<int>& nums);//209 长度最小的子数组
    int totalFruit(vector<int>& fruits);//904 水果篮子
    string minWindow(string s, string t);//*76 最小覆盖字串
    
    //螺旋矩阵
    vector<vector<int>> generateMatrix(int n);//59
    vector<int> spiralOrder(vector<vector<int>>& matrix);//54
    
    //区间和: 核心思想是先获得某数组的index对应的前n相和的新数组，然后区间和 = s[i] - sum[k]
    
    //开发商买土地
    int minDifference(const vector<vector<int>>& vec, int n, int m);
    
    
    
};

#endif /* ArraySection_hpp */
