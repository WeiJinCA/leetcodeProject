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
#include <unordered_map>

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
//205 两个字符串的字符是否以相同的映射关系一一对应
//使用两个map 保存 s[i] 到 t[j] 和 t[j] 到 s[i] 的映射关系，如果发现对应不上，立刻返回 false
bool HashSection::isIsomorphic(string s, string t){
    unordered_map<char, char> map1;
    unordered_map<char, char> map2;
    
    for(int i = 0, j =0; i < s.size();i++,j++){
        if(map1.find(s[i]) == map1.end()){
            map1[s[i]] = t[j];
        }
        
        if(map2.find(t[j]) == map2.end()){
            map2[t[j]] = s[i];
        }
        
        if(map1[s[i]] != t[j] || map2[t[j]] != s[i])return false;
    }
    return true;
}
//1002 找出字符串数组中每个字符串都共用的字符，返回数组
//思路：统计出搜索字符串里26个字符的出现的频率，然后取每个字符频率最小值，最后转成输出格式就可以了。
vector<string> HashSection::commonChars(vector<string>& words){
    vector<string> result;
    if(words.size() == 0) return result;
    int hash[26] = {0};// 用来统计所有字符串里字符出现的最小频率
    for(int i = 0; i < words[0].size();i++){
        hash[words[0][i] - 'a']++;
    }
    
    int hashOtherStr[26] = {0}; // 统计除第一个字符串外字符的出现频率
            for (int i = 1; i < words.size(); i++) {
                memset(hashOtherStr, 0, 26 * sizeof(int));
                for (int j = 0; j < words[i].size(); j++) {
                    hashOtherStr[words[i][j] - 'a']++;
                }
                // 更新hash，保证hash里统计26个字符在所有字符串里出现的最小次数
                for (int k = 0; k < 26; k++) {
                    hash[k] = min(hash[k], hashOtherStr[k]);
                }
            }
            // 将hash统计的字符次数，转成输出形式
            for (int i = 0; i < 26; i++) {
                while (hash[i] != 0) { // 注意这里是while，多个重复的字符
                    string s(1, i + 'a'); // char -> string
                    result.push_back(s);
                    hash[i]--;
                }
            }

            return result;
}
//925 长按键入
//时间复杂度：O(n) 空间复杂度：O(1)
bool HashSection::isLongPressedName(string name, string typed){
    int i = 0, j= 0;
    while(i < name.size() && j < typed.size()){
        if(name[i] == typed[j]){
            i++;j++;
        }else{//不相同
            if(j == 0) return false;//如果第一位都不同，直接返回false
            //跨越重复项
            while(j < typed.size() && typed[j] == typed[j - 1]) j++;
            if(name[i] == typed[j]){
                i++;j++;
            }
            else return false;
        }
    }
    if(i < name.size()) return false;
    
    //如果typed没匹配完
    while(j < typed.size()){
        if(typed[j] == typed[j - 1]) j++;
        else return false;
    }
    return true;
}
