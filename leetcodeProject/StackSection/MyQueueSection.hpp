//
//  MyQueueSection.hpp
//  leetcode 232: 用栈实现队列
//
//  Created by WeiJin on 2024-11-06.
//

#ifndef MyQueueSection_hpp
#define MyQueueSection_hpp

#include <stdio.h>
#include <iostream>
#include <stack>
using namespace std;

//必须使用2个栈，一个进栈，一个出栈
//1. push数据时，只需将数据放入输入栈就好
//2. pop数据时，输出栈如果为空，就把进栈数据全部导入进来（注意是全部导入），再从出栈弹出数据，如果输出栈不为空，则直接从出栈弹出数据就可以了。
// 判断队列为空：如果进栈和出栈都为空的话，说明模拟的队列为空
class MyQueue {
public:
    stack<int> stIn;
    stack<int> stOut;
    MyQueue() {
        
    }
    
    void push(int x) {
        stIn.push(x);
    }
    
    int pop() {
        if (stOut.empty()) {
            while(!stIn.empty()){
                stOut.push(stIn.top());
                stIn.pop();
            }
        }
        int result = stOut.top();
        stOut.pop();
        return result;
    }
    //Just get the front element
    int peek() {
        int res = this->pop();//直接调用写好的pop函数
        stOut.push(res);//pop弹出了元素，再添加回去
        return res;
    }
    
    bool empty() {
        return stIn.empty() && stOut.empty();
    }
};

#endif /* MyQueueSection_hpp */
