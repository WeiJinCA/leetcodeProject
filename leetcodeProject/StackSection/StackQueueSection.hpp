//
//  栈：
//  栈是以底层容器完成其所有的工作，对外提供统一的接口，底层容器是可插拔的（也就是说我们可以控制使用哪种容器来实现栈的功能）;可以是vector，deque，list，主要是数组和链表的底层实现
// 所以STL栈和队列 不被归类为 容器，而是container adapter（ 容器适配器）。
// 对于SGI STL,默认是以deque为缺省情况下栈的底层结构；deque是一个双向队列，只要封住一段，只开通另一端就可以实现栈的逻辑
// SGI STL中 队列底层实现缺省情况下一样使用deque实现的

#ifndef StackQueueSection_hpp
#define StackQueueSection_hpp

#include <stdio.h>
#include <string>
#include <deque>
using namespace std;


class StackQueueSection {
private:
    //239: MaxSlidingWindow：返回滑动窗口中的最大值
    //每次窗口移动的时候，调用que.pop(滑动窗口中移除元素的数值)，que.push(滑动窗口添加元素的数值)，然后que.front()就返回我们要的最大值。
    //单调队列：队列元素单调递增或递减
    class MyQueueForMaxSlidingWindow {
    public:
        deque<int> que;// 使用deque来实现单调队列
        // pop规则：如果窗口移动时左侧需要弹出的值 < 队列出口元素的数值(最大值)，不做操作，因为push时已经丢弃
        //         如果窗口移动时左侧需要弹出的值 = 队列出口元素的数值(最大值) 如果相等则弹出，去掉了窗口中的最大值
        // 同时pop之前，判断队列当前是否为空。
        void pop(int value) {
            if (!que.empty() && value == que.front()) {
                que.pop_front();
            }
        }
        // push规则1:如果push的数值（窗口移动的下一位：新值）大于队列入口元素的数值，那么就将队列后端的数值弹出，直到push的数值小于等于队列入口元素的数值为止。保持队列出口位置的元素始终最大，
        // push规则2:如果push的数值小于等于入口处的值，则直接加进去
        // 这样就保持了队列里的数值是单调从大到小的了。
        void push(int value) {
            while (!que.empty() && value > que.back()) {
                que.pop_back();
            }
            que.push_back(value);
        }
        
        // 查询当前队列里的最大值 直接返回队列前端也就是front就可以了。
        int front() {
            return que.front();
        }
    };
    
    //347 小顶堆
    class mycomparison{
        public:
        bool operator()(const pair<int,int>& lhs,const pair<int,int>& rhs){
            return lhs.second > rhs.second;
        }
    };
public:
    bool isValid(string s);//20 括号匹配：用栈解决的经典问题
    string removeDuplicates(string s);//1047
    int evalRPN(vector<string>& tokens);//150
    vector<int> maxSlidingWindow(vector<int>& nums, int k);
    vector<int> topKFrequent(vector<int>& nums, int k);
};

#endif /* StackQueueSection_hpp */
