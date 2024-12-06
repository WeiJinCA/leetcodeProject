//
//  ImplStackByQueue.h
//  leetcodeProject
//
//  Created by WeiJin on 2024-11-06.
// 用队列模拟栈
// 用两个队列que1和que2实现队列的功能，que2其实完全就是一个备份的作用，把que1最后面的元素以外的元素都备份到que2，然后弹出最后面的元素，再把其他元素从que2导回que1。

#ifndef ImplStackByQueue_h
#define ImplStackByQueue_h

#include <stdio.h>
#include <iostream>
#include <queue>
using namespace std;


class MyStack {
public:
    queue<int> que1;
    queue<int> que2;//辅助队列，用来备份
    MyStack() {
        
    }
    
    void push(int x) {
        que1.push(x);
    }
    
    int pop() {
        int size = que1.size();
        size--;
        while(size--){//将que1 导入que2，但要留下最后一个元素
            que2.push(que1.front());
            que1.pop();
        }
        
        int result = que1.front();// 留下的最后一个元素就是要返回的值
        que1.pop();
        que1 = que2; // 再将que2赋值给que1
        while (!que2.empty()) {// 清空que2
            que2.pop();
        }
        return result;
    }
    
    int top() {
        int size = que1.size();
        size--;
        while (size--) {
            que2.push(que1.front());
            que1.pop();
        }
        
        int result = que1.front();
        que2.push(que1.front());//获取值后将最后一个元素也加入que2中，保持原本的结构不变
        que1.pop();
        
        que1 = que2;//将que2中的值恢复到que1
        while (!que2.empty()) {
            que2.pop();
        }
        return result;
    }
    
    bool empty() {
        return que1.empty();
    }
};

#endif /* ImplStackByQueue_h */
