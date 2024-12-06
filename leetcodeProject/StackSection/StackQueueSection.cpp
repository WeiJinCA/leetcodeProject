//
//  StackQueueSection.cpp
//  leetcodeProject
//
//  Created by WeiJin on 2024-11-06.
//

#include "StackQueueSection.hpp"
#include <string>
#include <stack>
#include <queue>
using namespace std;

//20题：括号匹配问题
// 3种情况：1.字符串中左方向的括号多余了； 2.括号没有多余，括号的类型没有匹配上 3.字符串里右方向的括号多余了
// 对应栈的情况： 1.遍历完字符串，栈不为空， 2.栈里没有要匹配的字符 3.遍历过程中，栈已经为空，没有匹配字符了
// 全部匹配的条件： 遍历完字符串，栈为空
// 技巧：匹配左括号时，右括号先入栈；此后只需比较当前元素和栈顶是否相等即可，比左括号先入栈要简单
bool StackQueueSection::isValid(string s){
    if (s.size() % 2 != 0) {//如果字符串长度为奇数，肯定不符合要求
        return false;
    }
    
    stack<char> st;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') st.push(')');
        else if (s[i] == '{') st.push('}');
        else if (s[i] == '[') st.push(']');
        //第2和3种情况：匹配过程中，栈已经为空了，或没有要匹配的字符了
        else if (st.empty() || st.top() != s[i]) return false;
        else st.pop();//st.top() == s[i],弹出栈元素
    }
    
    return st.empty();//第一种情况：遍历完如果不为空，则说明缺少右括号
}

//删除字符串中的所有相邻重复项：用栈解决的经典题目
//将字符放入栈中，遍历后面的元素时，与栈内元素对比，如果相同就弹出；直到最后，将剩余的字符弹出后，反转即为结果
//也可用字符串直接作为栈
string StackQueueSection::removeDuplicates(string s){
    stack<char> st;
    for (char c : s) {
        if (st.empty() || c != st.top()) {
            st.push(c);
        }else{
            st.pop();//c == st.top()
        }
    }
    
    string res = "";
    while(!st.empty()){
        res += st.top();
        st.pop();
    }
    reverse(res.begin(),res.end());
    
    //第2种方法：用字符串直接作为栈
//    string result;
//    for(char s : S) {
//        if(result.empty() || result.back() != s) {
//            result.push_back(s);
//        }
//        else {
//            result.pop_back();
//        }
//    }
    
    return res;
}

//150.求值：逆波兰表达式：后缀表达式，运算符在后面；1.去掉括号后无歧义 2.适合用栈操作运算（遇到数字入栈，遇到运算符则取出栈顶两个数字进行计算，并将结果压入栈中）
//逆波兰表达式：用后序遍历的方式把二叉树序列化了
int StackQueueSection::evalRPN(vector<string>& tokens){
    stack<long long> st;
    for (int i = 0; i < tokens.size(); i++) {
        if(tokens[i] == "+" ||
           tokens[i] == "-" ||
           tokens[i] == "*" ||
           tokens[i] == "/"){
            long long num1 = st.top();
            st.pop();
            long long num2 = st.top();
            st.pop();
            if(tokens[i] == "+") st.push(num2 + num1);
            if(tokens[i] == "-") st.push(num2 - num1);
            if(tokens[i] == "*") st.push(num2 * num1);
            if(tokens[i] == "/") st.push(num2 / num1);
        }else{
            st.push(stoll(tokens[i]));//stoll 将字符转换为数字
        }
    }
    
    int res = int(st.top());
    st.pop();
    return res;
}
//239:滑动窗口最大值
//使用单调队列的经典题目,TC: n, SC:k
//
vector<int> StackQueueSection::maxSlidingWindow(vector<int>& nums, int k){
    MyQueueForMaxSlidingWindow que;
    vector<int> res;
    
    for (int i = 0; i < k; i++) {//先将前k个元素入队列
        que.push(nums[i]);
    }
    
    res.push_back(que.front());//获得前k个元素的最大值
    for (int i = k; i < nums.size(); i++) {
        que.pop(nums[i - k]);//移除滑动窗口前面的元素
        que.push(nums[i]);//添加滑动窗口后面的元素
        res.push_back(que.front());//记录滑动窗口的最大值
    }

    return res;
}
//347: 给定一个非空的整数数组，返回其中出现频率前 k 高的元素
//涉及3个问题： 1.要统计元素出现频率，用map；2.对频率排序，使用优先级队列；3.找出前K个高频元素
//优先级队列： 披着队列的堆；1.对外接口是从对头取元素，从队尾加元素；2.队列内元素是自动依照元素的权值排列（缺省情况下priority_queue利用max-heap（大顶堆）完成对元素的排序，这个大顶堆是以vector为表现形式的complete binary tree（完全二叉树））
//堆 是一棵完全二叉树，树中每个结点的值都不小于（或不大于）其左右孩子的值。 如果父亲结点是大于等于左右孩子就是大顶堆，小于等于左右孩子就是小顶堆。
//TC: nlogk ; SC:n
vector<int> StackQueueSection::topKFrequent(vector<int>& nums, int k){
    
    //统计元素出现的频率
    unordered_map<int, int> map;// map<nums[i],对应出现的次数>
    for (int i = 0; i < nums.size(); i++) {
        map[nums[i]]++;
    }
    
    //对频率排序,//定义一个小顶堆，大小为k
    priority_queue<pair<int,int>,vector<pair<int,int>>,mycomparison> pri_que;
    
    //用固定大小为k的小顶堆，扫面所有频率的数值
    for (unordered_map<int, int>::iterator it = map.begin(); it != map.end(); it++) {
        pri_que.push(*it);
        if (pri_que.size() > k) {// 如果堆的大小大于了k，则队列弹出，保证堆的大小一直为k
            pri_que.pop();
        }
    }
    
    //找出前K个高频元素，因为小顶堆先弹出的是最小的，所以倒序来输出到数组
    vector<int> result(k);
    for (int i = k - 1; i >= 0; i--) {
        result[i] = pri_que.top().first;
        pri_que.pop();
    }
    
    return result;
}
