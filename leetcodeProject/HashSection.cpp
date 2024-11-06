//
//  HashSection.cpp
//  leetcodeProject
//
//  Created by WeiJin on 2024-11-01.
//

#include "HashSection.hpp"
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

bool HashSection::isAnagram(string s, string t){
    int record[26] = {0};
    for (int i=0; i < s.size(); i++) {
        record[s[i] - 'a']++;
    }
    
    for (int i=0; i < t.size(); i++) {
        record[t[i] - 'a']--;
    }
    
    for (int i=0; i < 26; i++) {
        if(record[i] != 0) return false;
        //if(record[i] < 0) return false; //For 383赎金信，
    }
    
    return true;
}

vector<vector<string>> HashSection::groupAnagrams(vector<string>& strs){
    unordered_map<string, vector<string>> mp;
    
    for(auto x:strs){
        string word = x;
        sort(word.begin(),word.end());
        mp[word].push_back(x);
    }
    
    vector<vector<string>> ans;
    for(auto x:mp){
        ans.push_back(x.second);
    }
    return ans;
}

vector<int> HashSection::findAnagrams(string s, string p){
    vector<int> f1(26,0),f2(26,0);
    
    int n = static_cast<int>(s.size());
    int m = static_cast<int>(p.size());
    if (m > n) {
        return {};
    }
    vector<int> ans;
    
    //考虑开始m长的字符串
    for (int i=0; i < m; i++) {
        f1[s[i]-'a']++;
        f2[p[i]-'a']++;
    }
    if (f1 == f2) {
        ans.push_back(0);
    }
    
    //考虑之后的字符串;双指针法：从第一位往后挪，如有匹配的则返回索引值
    for(int i=m,j=0;i<n;i++,j++){
        f1[s[j]-'a']--;
        f1[s[i]-'a']++;
        
        if (f1 == f2) {
            ans.push_back(i-m+1);
        }
    }
    
    return ans;
}

//TC:n+m; SC:n
vector<int> HashSection::intersection(vector<int>& nums1, vector<int>& nums2){
    unordered_set<int> res_set;
    unordered_set<int> nums_set(nums1.begin(),nums1.end());
    for (int num:nums2) {
        if(nums_set.find(num) != nums_set.end()){
            res_set.insert(num);//将共同的数保持的结果集中
        }
    }
    
    return vector<int>(res_set.begin(),res_set.end());
}

vector<int> HashSection::intersect(vector<int>& nums1, vector<int>& nums2){
    int n1 = static_cast<int>(nums1.size());
    int n2 = static_cast<int>(nums2.size());
    sort(nums1.begin(),nums1.end());
    sort(nums2.begin(),nums2.end());
    
    vector<int> output;
    int start1 = 0, start2 = 0;
    while(start1 < n1 && start2 < n2){
        if(nums1[start1]==nums2[start2]){
            output.push_back(nums1[start1]);
            start1++;
            start2++;
        }
        else if(nums1[start1] < nums2[start2]){
            start1++;
        }else start2++;
    }
    
    return output;
}

int HashSection::getSum(int n){
    int sum = 0;
    while(n){
        sum += (n % 10) * (n % 10);
        n /= 10;
    }
    return sum;
}
bool HashSection::isHappy(int n){
    unordered_set<int> set;//用set来存储可能重复出现的中间的sum
    while(1){
        int sum = getSum(n);
        if(sum == 1) return true;
        if(set.find(sum) != set.end()){
            return false;
        }else{
            set.insert(sum);//重复出现。没有得到1
        }
        
        n = sum;
    }
}
//数组中只有一组解
vector<int> HashSection::twoSum(vector<int>& nums, int target){
    unordered_map<int, int> map;
    for(int i = 0;i < nums.size();i++){
        auto iter = map.find(target - nums[i]);
        if(iter != map.end()){
            return {iter->second,i};
        }
        
        map.insert(pair<int,int>(nums[i],i));
    }
    
    return {};
}

//这道题目是四个独立的数组，只要找到A[i] + B[j] + C[k] + D[l] = 0就可以，不用考虑有重复的四个元素相加等于0的情况
int HashSection::fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4){
    
    unordered_map<int,int> umap;
    for (int a : nums1) {
        for (int b:nums2) {
            umap[a + b]++;//放a+b两数之和出现的次数
        }
    }
    int count = 0;//统计a+b+c+d=0的次数
    
    for(int c:nums3){
        for(int d:nums4){
            if(umap.find(0 - (c+d)) != umap.end()) //如果找到满足条件的a+b
                count += umap[0 - (c+d)]; //所有a+b出现的次数，都加到结果中
        }
    }
    
    return count;
}
//判断是否可以用magazine中的字母来组成赎金信ransomNote,所以赎金信的字母长度要小于magazine
bool HashSection::canConstruct(string ransomNote, string magazine){
    int record[26] = {0};
    
    if (ransomNote.size() > magazine.size()) {
        return false;
    }
    
    for (int i = 0; i < magazine.length(); i++) {
        record[magazine[i] - 'a']++;//统计我们有什么
    }
    
    for (int j=0; j < ransomNote.length(); j++) {
        record[ransomNote[j]-'a']--;
        if (record[ransomNote[j]-'a']<0) {
            return false;//小于0 说明有字母magazine中没有
        }
    }
    return true;
}
//给定一个数组，找出不重复的三个数，满足a+b+c=0
//使用双指针法，比哈希法效率高一些
//注意：双指针法：要求要排序，如果要返回索引，则不能使用双指针法
vector<vector<int>> HashSection::threeSum(vector<int>& nums){
    vector<vector<int>> res;
    sort(nums.begin(),nums.end());
    
    //找出a + b +c=0; 其中 a = nums[i], b = nums[left], c = nums[right]
    for (int i=0; i < nums.size(); i++) {
        if (nums[i] > 0) {
            return res;
        }
        
        //正确的去重a的方法
        if (i > 0 && nums[i] == nums[i-1]) {//此处不能使用nums[i] == nums[i+1] 去重，会漏掉情况
            continue;
        }
        
        int left = i + 1;
        int right = static_cast<int>(nums.size()) - 1;
        while(right > left){
            if (nums[i] + nums[left] + nums[right] > 0) right--;
            else if(nums[i] + nums[left] + nums[right] < 0)left++;
            else{
                res.push_back(vector<int>{nums[i], nums[left], nums[right]});
                //去重逻辑应放到找到一个三元组后，对b,c去重
                while(right > left && nums[right] == nums[right - 1])  right--;
                while(right > left && nums[left] == nums[left - 1])  left++;
                
                //找到答案时，双指针同时收缩
                right--;
                left++;
            }
        }
    }
    return res;
}

vector<vector<int>> HashSection::threeSumByHash(vector<int>& nums){
    vector<vector<int>> res;
    sort(nums.begin(),nums.end());
    
    //找出a + b +c=0; 其中 a = nums[i], b = nums[j], c = -(a+b)
    for (int i=0; i < nums.size(); i++) {
        if (nums[i] > 0) {
            break;
        }
        
        if (i > 0 && nums[i] == nums[i - 1]) {//三元组元素a去重
            continue;
        }
        
        unordered_set<int> set;
        for (int j = i+1; j < nums.size(); j++) {
            if(j > i + 2
               && nums[j] == nums[j-1]
               && nums[j-1] == nums[j-2]){//三元组元素b去重
                continue;
            }
            int c = 0 - (nums[i] + nums[j]);
            if(set.find(c) != set.end()){
                res.push_back({nums[i],nums[j],c});
                set.erase(c);//三元组元素c去重
            }else{
                set.insert(nums[j]);
            }
        }
        
    }
    return res;
}
//四数之和的双指针解法：在三数之和的基础上加一层循环
//解法：两层for循环nums[k] + nums[i]为确定值，依然是循环内有left和right下标作为双指针，找出nums[k] + nums[i] + nums[left] + nums[right] == target的情况
vector<vector<int>> HashSection::fourSum(vector<int>& nums, int target){
    vector<vector<int>> res;
    sort(nums.begin(),nums.end());
    
    for (int k=0; k < nums.size(); k++) {
        //减枝处理：对于不满足条件的，提前结束循环
        if (nums[k] > target && nums[k] >= 0) {
            break;//统一使用后面的return返回
        }
        
        //对nums[k]去重
        if(k > 0 && nums[k] == nums[k-1]){
            continue;
        }
        for (int i = k + 1; i < nums.size(); i++) {
            //2级减枝处理
            if (nums[k] + nums[i] > target && nums[i] >= 0) {
                break;
            }
            //对nums[i]去重
            if(i > k+1 && nums[i] == nums[i-1]){
                continue;
            }
            int left = i + 1;
            int right = static_cast<int>(nums.size()) - 1;
            while (right > left) {
                // nums[k] + nums[i] + nums[left] + nums[right] > target 会溢出
                if ((long) nums[k] + nums[i] + nums[left] + nums[right] > target) {
                    right--;
                }else if((long) nums[k] + nums[i] + nums[left] + nums[right] < target){
                    left++;
                }else{
                    res.push_back(vector<int>{nums[k] , nums[i] , nums[left] , nums[right]});
                    // 对nums[left]和nums[right]去重
                    while (right > left && nums[right] == nums[right - 1]) right--;
                    while (right > left && nums[left] == nums[left + 1]) left++;
                    
                    //找到答案时，双指针同时收缩
                    right--;
                    left++;
                }
            }
            
        }
    }
    
    return res;
}
