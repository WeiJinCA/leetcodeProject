//
//  LinkedListSection.hpp
//  leetcodeProject
//
//  Created by WeiJin on 2024-10-30.
//

#ifndef LinkedListSection_hpp
#define LinkedListSection_hpp


#include <stdio.h>
#include "Node.hpp"
//using namespace std;

class LinkedListSection {
private:

public:
    //移除链表元素
    ListNode* removeElements(ListNode* head, int val);
    ListNode* removeElementsWithDummyHead(ListNode* head, int val);
    
    //翻转链表
    ListNode* reverseList(ListNode* head);
    ListNode* reverse(ListNode* pre,ListNode* cur);
    ListNode* reverseListByRecursion(ListNode* head);
    //两两交换
    ListNode* swapPairs(ListNode* head);
    
    //删除链表的倒数第N个节点
    ListNode* removeNthFromEnd(ListNode* head, int n);
    
    //求相交链表的交点节点
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB);
    
    //环链表
    //141探测环形链表 ， 代码在142种，快慢指针法
    ListNode *detectCycle(ListNode *head);//142
    
    //回文链表
    bool isPalindrome234(ListNode* head);
    ListNode* reverseList234(ListNode* head);
    
    //143
    void reorderListWithDeque(ListNode* head);
    void reorderList143_3(ListNode* head);
    ListNode* reverseListHelper143(ListNode* head);
    
    
};
#endif /* LinkedListSection_hpp */
