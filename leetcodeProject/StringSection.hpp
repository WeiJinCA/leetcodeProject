//
//  StringSection.hpp
//  leetcodeProject
//
//  Created by WeiJin on 2024-11-05.
//

#ifndef StringSection_hpp
#define StringSection_hpp

#include <stdio.h>
#include <string>
using namespace std;

//在C语言中，把一个字符串存入一个数组时，也把结束符 '\0'存入数组，并以此作为该字符串是否结束的标志。
//在C++中，提供一个string类，string类会提供 size接口，可以用来判断string类字符串是否结束，就不用'\0'来判断是否结束
//vector< char > 和 string : 在基本操作上没有区别，但是 string提供更多的字符串处理的相关接口，例如string 重载了+，而vector却没有
//一般处理字符串使用string

class StringSection {
public:
    void reverseString(vector<char>& s);//344 反转字符串
    string reverseStr(string s, int k);//541 反转字符串2
    string replaceNumToNumber(string s);//将字符串中的数字替换为'number'
    void reverseHelper(string& s, int start,int end);//辅助函数1
    void removeExtraSpaces(string& s);//辅助函数2
    string reverseWords(string s);//151 反转字符串中的单词
    string reverseWordsbySection(string s,int k);//右旋字符串
    void getNext(int* next, const string& s);//辅助函数：构建next数组
    int strStr(string haystack, string needle);//***28 实现strStr():KMP算法
    bool repeatedSubstringPattern(string s);//459 重复的子字符串
    bool repeatedSubstringPatternbyKMP(string s);//459 重复的子字符串,使用KMP解法
    
    
    
    
    
};
#endif /* StringSection_hpp */
