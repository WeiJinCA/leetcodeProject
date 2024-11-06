//
//  ArraySection.cpp
//  leetcodeProject
//
//  Created by WeiJin on 2024-10-16.
//
#include <iostream>
#include <cmath>
#include "ArraySection.hpp"
using namespace std;

//采用左闭右闭区间
int ArraySection::binarySearch(vector<int>& nums, int target) {
        int left = 0;
        int right = static_cast<int>(nums.size()) ;//强制转换为int

        while(left < right){
            int middle = left + (right -left )/2;

            if(nums[middle] > target){
                right = middle ;
            }else if(nums[middle] < target){
                left = middle +1;
            }else return middle;
        }

        return -1;
}

//35
int ArraySection::searchInsert(vector<int>& nums, int target){
    int left = 0;
    int right = static_cast<int>(nums.size()) ;//强制转换为int

    while(left < right){
        int middle = left + (right -left )/2;

        if(nums[middle] > target){
            right = middle ;
        }else if(nums[middle] < target){
            left = middle +1;
        }else return middle;
    }

    return left;
}

//34
int ArraySection::BinarySearchHelper(vector<int>& nums, int target,int side){
    int left = 0;
    int right = static_cast<int>(nums.size()) ;//强制转换为int
    int idx = -1;

    while(left < right){
        int middle = left + (right -left )/2;

        if(nums[middle] > target){
            right = middle ;
        }else if(nums[middle] < target){
            left = middle +1;
        }else {
            idx = middle;
            if(side == 1){
                right = middle -1;
            }else if (side == 0){
                left = middle +1;
            }
        };
    }

    return idx;
    }

vector<int> ArraySection::searchRange(vector<int>& nums, int target){
    int left = BinarySearchHelper(nums,target, 1);
    int right = BinarySearchHelper(nums,target, 0);
    return {left, right};
}

//69
int ArraySection::mySqrt(int x){
    // For special cases when x is 0 or 1, return x.
            if (x == 0 || x == 1)
                return x;

            // Initialize the search range for the square root.
            int start = 1;
            int end = x;
            int mid = -1;

            // Perform binary search to find the square root of x.
            while (start <= end) {
                // Calculate the middle point using "start + (end - start) / 2" to avoid integer overflow.
                mid = start + (end - start) / 2;

                // If the square of the middle value is greater than x, move the "end" to the left (mid - 1).
                if ((long) mid * mid > (long) x)
                    end = mid - 1;
                else if (mid * mid == x)
                    // If the square of the middle value is equal to x, we found the square root.
                    return mid;
                else
                    // If the square of the middle value is less than x, move the "start" to the right (mid + 1).
                    start = mid + 1;
            }

            // The loop ends when "start" becomes greater than "end", and "end" is the integer value of the square root.
            // However, since we might have been using integer division in the calculations,
            // we round down the value of "end" to the nearest integer to get the correct square root.
            return round(end);
}

//367
bool ArraySection::isPerfectSquare(int num) {
    int start=1; int end= num;
    int mid= start+(end-start)/2;
    while(start<=end){ //high-low>=0
        //cout<<mid<<endl;
        if(num%mid==0 && mid==num/mid)return true;
        if (mid > num/mid){  //9 1 9 5 25>num
            end=mid-1;
        }
        else start= mid+1;
            mid= start+(end-start)/2;
    }
        return false;
}

//27
int ArraySection::removeElement(vector<int>& nums, int val){
    int slowIndex = 0;
    for(int fastIndex = 0;fastIndex < nums.size();fastIndex++){
        if(val != nums[fastIndex]){
            nums[slowIndex++] = nums[fastIndex];
        }
    }
    
    return slowIndex;
}

int ArraySection::removeDuplicates(vector<int>& nums){
    int j = 1;//slow pointer
    for(int i=1;i< nums.size();i++){
        if(nums[i] != nums[i-1]){
            nums[j] = nums[i];
            j++;
        }
    }

    return j;
}

//把非零值前移
void ArraySection::moveZeroes(vector<int>& nums){
    int j = 0;
    for(int i = 0; i < nums.size();i++){
        if(nums[i] != 0){
            int temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
            j++;
        }
    }
}

bool ArraySection::backspaceCompare(string s, string t){
    string x="",y="";
    for(int i=0;i<s.size();i++){
        if(s[i]=='#' && x.size() == 0) continue;
        else if(s[i]=='#') x.pop_back();
        else x +=s[i];
    }
    
    for(int i=0;i<t.size();i++){
        if(t[i]=='#' && y.size() == 0) continue;
        else if(t[i]=='#') y.pop_back();
        else y +=t[i];
    }
    
    if(x == y) return true;
    else return false;
}

vector<int> ArraySection::sortedSquares(vector<int>& A){
    int len = static_cast<int>(A.size());
    int k = len -1;
    vector<int> result(len,0);
    for(int i=0,j= len - 1;i <=j;){// 注意这里要i <= j，因为最后要处理两个元素
        if(A[i] * A[i] < A[j] * A[j]){
            result[k--] =A[j] * A[j];
            j--;
        }else{
            result[k--] =A[i] * A[i];
            i++;
        }
    }
    
    return result;
}

//双指针：结束位置j遍历数组, 如果sum >= target, 右移起始位置缩小窗口
int ArraySection::minSubArrayLen(int target, vector<int>& nums){
    
    int result = INT32_MAX;
    int sum = 0;//滑动窗口数值之和
    int i = 0;//窗口滑动的起始位置
    int subLength = 0;//窗口滑动的长度

    for(int j = 0;j < nums.size();j++){
        sum += nums[j];
        while(sum >= target){
            subLength = j - i + 1;
            result = result < subLength ? result : subLength;
            sum -= nums[i++];//缩小窗口，并减去起始位置的值
        }
    }
    
    return result == INT32_MAX ? 0 : result;
}

//返回树最多的字数组长度，即最长的窗口
int ArraySection::totalFruit(vector<int>& fruits){
    
    unordered_map<int, int> baskets;
    int left = 0;
    int ans = 0;
    
    for(int right = 0; right < fruits.size();right++){
        baskets[fruits[right]]++;
        
        if(baskets.size() > 2){
            baskets[fruits[left]]--;
            if(baskets[fruits[left]] == 0){
                baskets.erase(fruits[left]);
            }
            left++;
        }
        
        ans = max(ans,right - left + 1);
    }
    
    return ans;
}

string ArraySection::minWindow(string s, string t){
    
    unordered_map<char, int> m;
    //保持短字符串t的特征
    for (int i=0; i < t.size(); i++) {
        m[t[i]]++;
    }
    
    int left = 0;
    int right = 0;
    
    // # of chars in t that must be in s
    int counter = static_cast<int>(t. size());
    
    int minStart = 0;
    int minLength = INT_MAX;
    
    while(right < s.size()){
        // if char in s exists in t, decrease
        if(m[s[right]] > 0){
            counter--;
        }
        // if char doesn't exist in t, will be -'ve
        m[s[right]]--;
        // move right to find valid window
        right++;
        
        // counter == 0:字符完全匹配；when window found, move left to find smaller
        while(counter == 0){
            if(right - left < minLength){
                minStart = left;
                minLength = right - left;
            }
            
            m[s[left]]++;
            // when char exists in t, increase
            if(m[s[left]] > 0){
                counter++;
            }
            left++;
        }

    }
    
    if(minLength != INT_MAX){
        //For debug, print unordered_map
//        for (const auto& pair : m) {
//                std::cout << pair.first << " => " << pair.second << std::endl;
//            }
//        std::cout << std::endl;
        return s.substr(minStart,minLength);
    }
    return "";
}

//左闭右开
vector<vector<int>> ArraySection::generateMatrix(int n){
    vector<vector<int>> res(n,vector<int>(n,0));
    
    int startx = 0, starty=0;
    int loop = n/2;
    int mid = n/2;
    int count = 1;
    int offset = 1;
    int i,j;
    
    while(loop--){
        i = startx;
        j = starty;
        
        for (; j < n - offset; j++) {
            res[i][j] = count++;
        }
        
        for (; i < n - offset; i++) {
            res[i][j] = count++;
        }
        
        for (; j > starty; j--) {
            res[i][j] = count++;
        }
        
        for (; i > startx; i--) {
            res[i][j] = count++;
        }
        
        startx++;//每个循环向内收缩
        starty++;
        offset++;//每个循环向内偏置+1
    }
    
    if(n % 2 == 1){
        res[mid][mid] = count;// 单独处理最中间的数字
    }
    
    return res;
}

//按螺旋顺序打印按行排列数字的erweijuzhen
vector<int> ArraySection::spiralOrder(vector<vector<int>>& matrix){
    
    int m = static_cast<int>(matrix.size());//行
    int n = static_cast<int>(matrix[0].size());//列
    int left=0,right=n-1;
    int top=0,bottom = m-1;
    
    vector<int> ans;
    
    while(top <= bottom && left <= right){
        
        for(int i=left; i <= right;i++){
            ans.push_back(matrix[top][i]);
        }
        top++;
        
        for(int i=top;i<= bottom;i++){
            ans.push_back(matrix[i][right]);
        }
        right--;
        
        if(top <= bottom){
            for (int i=right; i >= left; i--) {
                ans.push_back(matrix[bottom][i]);
            }
            bottom--;
        }
        
        if(left <= right){
            for(int i = bottom; i >= top;i--){
                ans.push_back(matrix[i][left]);
            }
            left++;
        }
    }
    
    return ans;
}

//在一个城市区域内，被划分成了n * m个连续的区块，每个区块都拥有不同的权值，代表着其土地价值。目前，有两家开发公司，A 公司和 B 公司，希望购买这个城市区域的土地。
//现在，需要将这个城市区域的所有区块分配给 A 公司和 B 公司。然而，由于城市规划的限制，只允许将区域按横向或纵向划分成两个子区域，而且每个子区域都必须包含一个或多个区块。
//为了确保公平竞争，你需要找到一种分配方式，使得 A 公司和 B 公司各自的子区域内的土地总价值之差最小。注意：区块不可再分。
int ArraySection::minDifference(const vector<vector<int>>& vec, int n, int m){
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            sum += vec[i][j];
        }
    }
    
    int result = INT_MAX;
    int count = 0; // Count for rows
    
    // Check by splitting along rows
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            count += vec[i][j];
            if (j == m - 1) result = min(result, abs(sum - 2 * count));//abs(sum - 2 * count) 是两半的差值
        }
    }
    
    count = 0; // Reset count for columns
    
    // Check by splitting along columns
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            count += vec[i][j];
            if (i == n - 1) result = min(result, abs(sum - 2 * count));
        }
    }
    
    return result;
}
