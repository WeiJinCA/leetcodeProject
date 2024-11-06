//
//  Node.hpp
//  leetcodeProject
//
//  Created by WeiJin on 2024-10-30.
//

#ifndef Node_hpp
#define Node_hpp

struct ListNode {
     int val;
     ListNode *next;
    ListNode() : val(0), next(nullptr) {}
   ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
#endif /* Node_hpp */
