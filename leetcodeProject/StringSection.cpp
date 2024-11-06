//
//  StringSection.cpp
//  leetcodeProject
//
//  Created by WeiJin on 2024-11-05.
//

#include "StringSection.hpp"
#include <iostream>
#include <string>
using namespace std;

//双指针法
void StringSection::reverseString(vector<char>& s){
    for (int i=0,j= static_cast<int>(s.size())-1; i < s.size()/2; i++,j--) {
        swap(s[i], s[j]);
//        int tmp = s[i];
//        s[i] = s[j];
//        s[j] = tmp;
    }
}
//反转2k个字符中的前k个
//解法：循环时 i += 2k
string StringSection::reverseStr(string s, int k){
    for (int i = 0; i < s.size(); i += (2 * k)) {
        if(i + k <= s.size()){
            reverse(s.begin()+i, s.begin()+i+k);
        }else{
            reverse(s.begin()+i,s.end());
        }
    }
    return s;
}

string StringSection::replaceNumToNumber(string s){
    if (s.size() == 0) return s;
    
    int sOldIndex = static_cast<int>(s.size()) - 1;
    int count = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            count++;
        }
    }
    //扩充字符串s的大小： 将每个数字替换成number之后的大小
    s.resize(s.size() + count*5);//数字本身已经占一个字符
    int sNewIndex = static_cast<int>(s.size()) - 1;
    while (sOldIndex >= 0) {
        if (s[sOldIndex] >= '0' && s[sOldIndex] <= '9') {
            s[sNewIndex--] = 'r';
            s[sNewIndex--] = 'e';
            s[sNewIndex--] = 'b';
            s[sNewIndex--] = 'm';
            s[sNewIndex--] = 'u';
            s[sNewIndex--] = 'n';
        }else{
            s[sNewIndex--] = s[sOldIndex];
        }
        sOldIndex--;
    }
    return s;
}
void StringSection::reverseHelper(string& s, int start,int end){
    for (int i=start,j=end; i < j; j--) {
        swap(s[i],s[j]);
    }
}
//需要注意的思路
void StringSection::removeExtraSpaces(string& s){//去除所有空格并在相邻单词之间添加空格, 快慢指针。
    int slow = 0;
    for (int i = 0; i < s.size(); ++i) {
        //开始有空时，直接跳过
        if (s[i] != ' ') {//遇到非空格就处理，即删除所有空格。
            if (slow != 0) s[slow++] = ' ';//***手动控制空格，给单词之间添加空格。slow != 0说明不是第一个单词，需要在单词前添加空格。
            //while循环一次，即处理一个单词
            while (i < s.size() && s[i] != ' ') {//补上该单词，遇到空格说明单词结束。
                s[slow++] = s[i++];
            }
        }
    }
    s.resize(slow);//slow的大小即为去除多余空格后的大小。
}
//解题步骤：1.移除多余的空格 2.将整个字符串反转 3.将每个单词反转
string StringSection::reverseWords(string s){
    removeExtraSpaces(s);//1.移除多余的空格
    reverseHelper(s, 0, static_cast<int>(s.size())-1);//2.将整个字符串反转
    int start = 0;//removeExtraSpaces后保证第一个单词的开始下标一定是0
    for (int i=0; i <= s.size(); ++i) {
        if (i == s.size() || s[i] == ' ') {//到达空格或者串尾，说明一个单词结束,进行翻转
            reverseHelper(s,start,i - 1);//翻转，注意是左闭右闭 []的翻转
            start = i + 1;//更新下一个单词的开始下标start
        }
    }
    return s;
}
//右旋字符串：将字符串截为2段，将这2段反转，2段字符串内部顺序不变
//解法：1. 将字符串倒序 2.分段字符串中再反转
string StringSection::reverseWordsbySection(string s,int k){
    int len = static_cast<int>(s.size());
    
    reverse(s.begin(),s.end());//整体反转
    reverse(s.begin(),s.begin() + k);//先反转前一段
    reverse(s.begin() + k, s.end());//再反转后一段
    
    return s;
}
//KMP算法
//给定一个 haystack 字符串和一个 needle 字符串，在 haystack 字符串中找出 needle 字符串出现的第一个位置 (从0开始)。如果不存在，则返回  -1
//解法：KMP算法：当出现字符串不匹配时，可以知道一部分之前已经匹配的文本内容，可以利用这些信息避免从头再去做匹配了
//前缀表：1.作用：用于回退的，记录了模式串和主文本串不匹配时，模式串应该回退到哪里开始重新匹配
//2. 定义：记录下标i之前(包括i)的字符串中，有多大长度的相同前缀后缀；
//前缀表要求的就是相同前后缀的长度
//****理解： 当匹配失败时，因为找到了最长的相等的前后缀，所以会退的位置是从相同的前缀的下一个位置开始匹配，因为此时前缀和后缀相同（对齐）。
//最长公共前后缀：
//前缀：指不包含最后一个字符的所有以第一个字符开头的连续子串
//后缀：指不包含第一个字符的所有以最后一个字符结尾的连续子串

//next数组：把前缀表统一减一（右移一位，初始位置为-1）
//计算next数组：1. 初始化 2. 处理前后缀不相同的情况 3. 处理前后缀相同的情况
//next[i] 表示 i（包括i）之前最长相等的前后缀长度（其实就是j）
//定义两个指针i和j，j指向前缀末尾位置，i指向后缀末尾位置
void StringSection::getNext(int* next, const string& s){
    int j = -1;
    next[0] = j;//next数组：前缀表统一减一
    for (int i = 1; i < s.size(); i++) {// 注意i从1开始
        while(j >= 0 && s[i] != s[j+1]){// 前后缀不相同了
            j = next[j];// 向前回退；next[j]就是记录着j（包括j）之前的子串的相同前后缀的长度； s[i] 与 s[j+1] 不相同，就要找 j+1前一个元素在next数组里的值（就是next[j]）
        }
        if (s[i] == s[j+1]) {//找到相同的前后缀
            j++;
        }
        next[i] = j;//将j(前缀的长度)赋给next[i]
    }
}
//定义两个下标j 指向模式串起始位置，i指向文本串起始位置
//TC: n(文本字符串长度) + m(模式串长度)；SC:m, 只需保存字符串needle的前缀表
int StringSection::strStr(string haystack, string needle){
    
    if (static_cast<int>(needle.size()) == 0){
        return 0;
    }
    vector<int> next(needle.size());
    getNext(&next[0],needle);
    
    int j = -1;// 因为next数组里记录的起始位置为-1
    for (int i = 0; i < haystack.size(); i++) {// 注意i就从0开始
        while(j >= 0 && haystack[i] != needle[j + 1]){// 不匹配
          j = next[j];// j 寻找之前匹配的位置
        }
        
        if (haystack[i] == needle[j + 1]) {
            j++; // i的增加在for循环里
        }
        if (j == (needle.size() - 1) ) { // 文本串s里出现了模式串t
            return (i - static_cast<int>(needle.size()) + 1);
        }
    }
    
    return -1;
}
//使用库函数find，时间复杂度m+n
bool StringSection::repeatedSubstringPattern(string s){
    string t = s + s;
    t.erase(t.begin());t.erase(t.end() - 1);//掐头去尾
    if (t.find(s) != string::npos) return true;//在中间找到了s
    return false;
}
//使用KMP算法，使用结论：如果一个字符串s是由重复子串组成，那么 最长相等前后缀不包含的子串(部分)一定是字符串s的最小重复子串。
//如果len % (len - (next[len - 1] + 1)) == 0 ，则说明数组的长度正好可以被 最长相等前后缀不包含的子串的长度 整除 ，说明该字符串有重复的子字符串
bool StringSection::repeatedSubstringPatternbyKMP(string s){
    if (s.size() == 0) {
        return false;
    }
    
    int next[s.size()];
    getNext(next,s);
    int len = static_cast<int>(s.size());
    if(next[len-1] !=-1 &&  len % (len - (next[len-1]+1)) == 0){//最长相等前后缀不包含的子串存在，且能被整除
        return true;
    }
    return false;
}
