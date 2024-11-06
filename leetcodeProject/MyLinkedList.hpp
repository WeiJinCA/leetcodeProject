//
//  MyLinkedList.hpp
//  leetcodeProject
//
//  Created by WeiJin on 2024-10-30.
//

#ifndef MyLinkedList_hpp
#define MyLinkedList_hpp

#include <stdio.h>

class MyLinkedList {
public:
    struct LinkedNode{
        int val;
        LinkedNode* next;
        LinkedNode(int val):val(val),next(nullptr){}
    };

    MyLinkedList() ;
    
    int get(int index) ;
    void addAtHead(int val);
    void addAtTail(int val) ;
    void addAtIndex(int index, int val) ;
    void deleteAtIndex(int index) ;
    void printList();

private:
    int _size;
    LinkedNode* _dummyHead;
};

#endif /* MyLinkedList_hpp */
