//
//  MyLinkedList.cpp
//  leetcodeProject
//
//  Created by WeiJin on 2024-10-30.
//

#include "MyLinkedList.hpp"
#include <iostream>
using namespace std;


MyLinkedList::MyLinkedList() {
        _dummyHead = new LinkedNode(0);
        _size = 0;
    }
    
    int MyLinkedList::get(int index) {
        if(index > (_size -1) || index < 0){
            return -1;
        }

        LinkedNode* cur = _dummyHead -> next;
        while(index--){
            cur = cur -> next;
        }

        return cur -> val;
    }
    
    void MyLinkedList::addAtHead(int val) {
        LinkedNode* head = new LinkedNode(val);
        head -> next = _dummyHead -> next;
        _dummyHead -> next = head;
        _size++;
    }
    
    void MyLinkedList::addAtTail(int val) {
        LinkedNode* tail = new LinkedNode(val);
        LinkedNode* cur = _dummyHead;
        while(cur -> next != nullptr){
            cur = cur -> next;
        }

        cur -> next = tail;
        _size++;
    }
    
    void MyLinkedList::addAtIndex(int index, int val) {
        if(index > _size) return;
        if(index < 0) index = 0;

        LinkedNode* newNode = new LinkedNode(val);
        LinkedNode* cur = _dummyHead;
        while(index--){
            cur = cur -> next;
        }

        newNode -> next = cur->next;
        cur -> next = newNode;
        _size++;
    }
    
    void MyLinkedList::deleteAtIndex(int index) {
        if(index < 0 || index >= _size)return;

        LinkedNode* cur = _dummyHead;

        while(index--){
            cur = cur -> next;
        }

        LinkedNode* tmp = cur -> next;
        cur -> next = cur->next->next;
        delete tmp;
        tmp = nullptr;
        _size--;

    }

void MyLinkedList::printList() {
    LinkedNode* head = _dummyHead;
    while (head != NULL) {
        std::cout << head->val << " -> ";
        head = head->next;
    }
    std::cout << "NULL" << std::endl;
}
