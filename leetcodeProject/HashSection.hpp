//
//  HashSection.hpp
//  leetcodeProject
//
//  Created by WeiJin on 2024-11-01.
//

#ifndef HashSection_hpp
#define HashSection_hpp

#include <string>
using namespace std;


//哈希表：将查询值通过哈希函数映射到集合的下标，通过访问下标可以快速判断一个元素是否出现在集合里
//哈希碰撞：当不同的值映射到相同的索引时；
//解决办法：拉链法：将冲突的元素存储在链表中，索引指向链表的头节点；优点：表的大小不会太大，空间不会浪费
//线性探测法：在冲突的位置向后顺延一个位置放冲突的元素；要求表的大小足够大，以保持冲突的元素
//三种结构：数组、set、map
//set首选unordered_set(底层为哈希表):查询和增删效率最优；（后面两个底层为红黑树）有序set用set；有序且包含重复元素用multiset;
//map:key的存储方式是红黑树实现的
//哈希法：依靠键来访问值；典型应用：快速判断一个元素是否出现在集合里的情况
class HashSection {
public:
    //判断字母异位词
    bool isAnagram(string s, string t);//242, 383赎金信
    vector<vector<string>> groupAnagrams(vector<string>& strs);//49
    vector<int> findAnagrams(string s, string p);//438
    
    //两个数组的交集
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2);//349
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2);//350
    int getSum(int n);
    bool isHappy(int n);//202
    
    //两数之和
    vector<int> twoSum(vector<int>& nums, int target);//1
    //四数相加 454
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4);
    //赎金信383
    bool canConstruct(string ransomNote, string magazine);
    vector<vector<int>> threeSum(vector<int>& nums);//三数之和 15
    vector<vector<int>> threeSumByHash(vector<int>& nums);//三数之和 15 by 哈希法
    vector<vector<int>> fourSum(vector<int>& nums, int target);//18.四数之和
    
    //同构字符串
    bool isIsomorphic(string s, string t);
    //查找常用字符
    vector<string> commonChars(vector<string>& words);//1002*
    //
    bool isLongPressedName(string name, string typed);//925
    
    
};
#endif /* HashSection_hpp */
