//
//  LinkedListSection.cpp
//  leetcodeProject
//
//  Created by WeiJin on 2024-10-30.
//

#include "LinkedListSection.hpp"
#include <iostream>
#include <cmath>
#include "Node.hpp"

using namespace std;

//无虚拟头节点，头节点操作要单独处理
ListNode* LinkedListSection::removeElements(ListNode* head, int val){
    // 删除头结点
            while (head != NULL && head->val == val) { // 注意这里不是if
                ListNode* tmp = head;
                head = head->next;
                delete tmp;
            }

            // 删除非头结点
            ListNode* cur = head;
            while (cur != NULL && cur->next!= NULL) {
                if (cur->next->val == val) {
                    ListNode* tmp = cur->next;
                    cur->next = cur->next->next;
                    delete tmp;
                } else {
                    cur = cur->next;
                }
            }
            return head;
}

//设置虚拟头节点，处理节点时可以同样对待
ListNode* LinkedListSection::removeElementsWithDummyHead(ListNode* head, int val) {
        ListNode* dummyHead = new ListNode(0); // 设置一个虚拟头结点
        dummyHead->next = head; // 将虚拟头结点指向head，这样方便后面做删除操作
        ListNode* cur = dummyHead;
        while (cur->next != NULL) {
            if(cur->next->val == val) {
                ListNode* tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            } else {
                cur = cur->next;
            }
        }
        head = dummyHead->next;
        delete dummyHead;
        return head;
}

//双指针法
ListNode* LinkedListSection::reverseList(ListNode* head){
    
    ListNode* temp;
    ListNode* cur = head;
    ListNode* pre = NULL;
    
    while(cur){
        temp = cur->next;
        cur->next = pre;//翻转操作
        //更新pre和cur
        pre = cur;
        cur = temp;
        
    }
    
    return pre;
}

//递归法
ListNode* LinkedListSection::reverse(ListNode* pre,ListNode* cur){
    if(cur == NULL) return pre;
    ListNode* temp = cur->next;
    cur->next = pre;
    // 可以和双指针法的代码进行对比，如下递归的写法，其实就是做了这两步
    // pre = cur;
    // cur = temp;
    return reverse(cur,temp);
}
ListNode* LinkedListSection::reverseListByRecursion(ListNode* head) {
    // 和双指针法初始化是一样的逻辑
    // ListNode* cur = head;
    // ListNode* pre = NULL;
    return reverse(NULL, head);
}

ListNode* LinkedListSection::swapPairs(ListNode* head){
    ListNode* dummyHead  = new ListNode(0);
    dummyHead->next = head;
    ListNode* cur = dummyHead;
    while(cur->next != nullptr && cur->next->next != nullptr){
        ListNode* tmp = cur->next;
        ListNode* tmp1 = cur->next->next->next;
        
        cur->next = cur->next->next;//将第2个和第4个交换
        cur->next->next = tmp;
        cur->next->next->next = tmp1;
        
        cur = cur->next->next;
    }
    
    ListNode* result = dummyHead->next;
    delete dummyHead;
    return result;
}

//删除链表的倒数第N个节点: 双指针法，让fast先走n步，然后和slow一起走，直到fast到达末尾
ListNode* LinkedListSection::removeNthFromEnd(ListNode* head, int n){
    ListNode* dummyHead = new ListNode(0);
    dummyHead->next = head;
    ListNode* fast = dummyHead;
    ListNode* slow = dummyHead;
    
    while(n-- && fast != NULL){
        fast = fast->next;
    }
    
    fast = fast->next;//fast提前再走一步，因为需要让slow节点指向删除节点的上一个节点
    while (fast != NULL){
        fast = fast->next;
        slow = slow->next;
    }
    slow->next = slow->next->next;
    
    return dummyHead->next;
}
//求两个链表交点的节点指针
ListNode* LinkedListSection::getIntersectionNode(ListNode *headA, ListNode *headB){
    ListNode* curA = headA;
    ListNode* curB = headB;
    int lenA = 0,lenB = 0;
    
    while(curA != NULL){//求链表A的长度
        lenA++;
        curA = curA->next;
    }
    
    while(curB != NULL){//求链表B的长度
        lenA++;
        curB = curB->next;
    }
    curA = headA;
    curB = headB;
    //用长度长的循环
    if(lenB > lenA){
        swap(lenA,lenB);
        swap(curA,curB);
    }
    
    int gap = lenA-lenB;
    while(gap--){
        curA = curA->next;//两个链表共用末尾一段
    }
    while(curA != NULL){
        if(curA == curB){
            return curA;
        }
        curA = curA->next;
        curB = curB->next;
    }
    return NULL;
}

//环链表：1.判断是否有环；2.如果有环，如何找到这个环的入口
//1.使用快慢指针：fast每次移动2个节点，slow每次移动1个节点，如果两个指针在途中相遇，则有环；如果有环，进入环之后，每走一步，两个指针就靠近一步，直至重合
//2.找环的入口：在头节点和环中相遇节点各放一个指针，每次都走一步，当他们相遇时则到了环的入口
ListNode *LinkedListSection::detectCycle(ListNode *head){
    ListNode* fast = head;
    ListNode* slow = head;
    while(fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
        
        //如快慢指针相遇,找环入口
        if(fast == slow){
            ListNode* index1 = fast;
            ListNode* index2 = head;
            while(index1 != index2){
                index1 = index1->next;
                index2 = index2->next;
            }
            return index2;//返回环入口
        }
    }
    return NULL;
}
//234
//思路1：将链表转换为数组，然后双指针判断数组首尾是否相同
//思路2:将链表后半部分反转，然后和前半部分比较；
//思路2步骤：用快慢指针找出中间节点；用pre记录中间节点的前一个节点用于分割；反转后半部分；比较两部分
bool LinkedListSection::isPalindrome234(ListNode* head){
    if(head == nullptr || head->next == nullptr) return true;
    ListNode* slow = head;//慢指针，找到链表中间部分，作为分割
    ListNode* fast = head;//慢指针，找到链表中间部分，作为分割
    ListNode* pre = head;//慢指针，找到链表中间部分，作为分割
    while(fast && fast->next){
        pre = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    pre->next = nullptr;//分割链表
    
    ListNode* cur1 = head;
    ListNode* cur2 = reverseList(slow);//反转后半部分
    
    //比较两个部分
    while(cur1){
        if(cur1->val != cur2->val) return false;
        cur1 = cur1->next;
        cur2 = cur2->next;
    }
    return true;
}
// 反转链表
ListNode* LinkedListSection::reverseList234(ListNode* head){
    ListNode* temp;//保存cur的下一个节点
    ListNode* cur = head;
    ListNode* pre = nullptr;
    
    while(cur){
        temp = cur->next;// 保存一下 cur的下一个节点，因为接下来要改变cur->next
        cur->next = pre;//反转操作
        pre = cur;
        cur = temp;
    }
    
    return pre;
}
//143
//方法二：使用双向队列
void LinkedListSection::reorderListWithDeque(ListNode* head){
    deque<ListNode*> que;
    ListNode* cur = head;
    if(cur == nullptr) return;
    
    while(cur->next != nullptr){
        que.push_back(cur->next);
        cur = cur->next;
    }
    
    cur = head;
    int count = 0;//偶数取后面，奇数取前面
    ListNode* node;
    while(que.size()){
        if(count %2 == 0){
            node = que.back();
            que.pop_back();
        }else{
            node = que.front();
            que.pop_back();
        }
        count++;
        cur->next = node;
        cur = cur->next;
    }
}
//143方法三：链表拼接：将链表分割成两个链表，然后把第二个链表反转，之后在通过两个链表拼接成新的链表
void LinkedListSection::reorderList143_3(ListNode* head){
    if(head == nullptr) return ;
    
    // 使用快慢指针法，将链表分成长度均等的两个链表head1和head2
    // 如果总链表长度为奇数，则head1相对head2多一个节点
    ListNode* fast = head;
    ListNode* slow = head;
    while(fast && fast->next && fast->next->next){
        fast = fast->next->next;
        slow = slow->next;
    }
    
    ListNode* head1 = head;
    ListNode* head2;
    head2 = slow->next;//后半部分的头
    slow->next = nullptr;
    
    // 对head2进行翻转
    head2 = reverseListHelper143(head2);
    
    // 将head1和head2交替生成新的链表head
    ListNode* cur1 = head1;
    ListNode* cur2 = head2;
    ListNode* cur = head;
    cur1 = cur1->next;
    int count = 0;// 偶数取head2的元素，奇数取head1的元素
    while(cur1 && cur2){
        if(count %2 == 0){
            cur->next = cur2;
            cur2 = cur2->next;
        }else{
            cur->next = cur1;
            cur1 = cur1->next;
        }
        count++;
        cur = cur->next;
    }
    if (cur2 != nullptr) { // 处理结尾
        cur->next = cur2;
            }
    if (cur1 != nullptr) {
        cur->next = cur1;
    }
}
// 反转链表
ListNode* LinkedListSection::reverseListHelper143(ListNode* head){
    ListNode* temp;
    ListNode* cur = head;
    ListNode* pre = NULL;
    while(cur){
        temp = cur->next;
        cur->next = pre;//翻转
        pre = cur;
        cur = temp;
    }
    return pre;
}
