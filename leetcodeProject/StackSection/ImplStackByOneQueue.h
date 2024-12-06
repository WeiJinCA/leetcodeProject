//
//  ImplStackByOneQueue.h
//  leetcodeProject
//
//  Created by WeiJin on 2024-11-06.
//  用一个队列模拟栈：只要将队列头部的元素（除了最后一个元素外） 重新添加到队列尾部，此时再去弹出元素就是栈的顺序了

#ifndef ImplStackByOneQueue_h
#define ImplStackByOneQueue_h

#include <stdio.h>
#include <iostream>
#include <queue>
using namespace std;


class MyStack {
public:
    queue<int> que;

    MyStack() {
        
    }
    
    void push(int x) {
        que.push(x);
    }
    
    int pop() {
        int size = que1.size();
        size--;
        while(size--){//将que1 导入que2，但要留下最后一个元素
            que.push(que.front());
            que.pop();
        }
        
        int result = que.front();// 留下的最后一个元素就是要返回的值
        que.pop();
        
        return result;
    }
    
    int top() {
        int size = que.size();
        size--;
        while (size--) {
            que.push(que.front());
            que.pop();
        }
        
        int result = que.front();
        que.push(que.front());//获取值后将最后一个元素也加入que2中，保持原本的结构不变
        que.pop();
        
        return result;
    }
    
    bool empty() {
        return que.empty();
    }
};

#endif /* ImplStackByOneQueue_h */
