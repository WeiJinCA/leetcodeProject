//
//  main.cpp
//  leetcodeProject
//
//  Created by WeiJin on 2024-09-26.
//

#include <iostream>
#include <cstdio>
#include "ArraySection.hpp"
#include "LinkedListSection.hpp"
#include "HashSection.hpp"
#include "StringSection.hpp"
#include "StackQueueSection.hpp"
#include "BinaryTree/BinaryTreeBasic.hpp"
#include "Node.hpp"
#include "MyLinkedList.hpp"
#include "Graph/GraphBasic.hpp"

using namespace std;

void arraySectionTest(){
    ArraySection obj;
    vector<int> nums = {-1,0,3,5,9,12};
    
    int target = 9;
    int res = obj.binarySearch(nums,target);//704
    printf("binarySearch res : %d \n",res);
    
    int index = obj.searchInsert(nums,10);//35
    printf("searchInsert index : %d \n",index);
    
    vector<int> nums1 = {5,7,7,8,8,10};
    vector<int> startEndPos = obj.searchRange(nums1,8);//34
    int length = static_cast<int>(startEndPos.size()) ;//注意数组越界
    for (int i = 0; i < length; i++) {
            std::cout << startEndPos[i] << " ";
    }

    //69
    int root = obj.mySqrt(99);
    printf("\nmySqrt root : %d \n",root);
    
    //367
    int isSquare = obj.isPerfectSquare(81);
    printf("\nis Perfect Square root : %d \n",isSquare);
    
    //27
    length = obj.removeElement(nums1,8);
    for (int i = 0; i < length; i++) {
            std::cout << nums1[i] << " ";
    }
    std::cout << std::endl;
    
    //26
    vector<int> nums2 = {0,0,1,1,1,2,2,3,3,4};
    length = obj.removeDuplicates(nums2);
    printf("\nlength : %d \n",length);
    for (int i = 0; i < length; i++) {
            std::cout << nums2[i] << " ";
    }
    
    //844
    string x = "ab##",y="c#d#";
    bool flag = obj.backspaceCompare(x,y);
    printf("\nis equal? : %d \n",flag);
    
    //977
    vector<int> nums3 = {-10,1,5,8,9,30};
    vector<int> result = obj.sortedSquares(nums3);
    
    for (int i = 0; i < result.size(); i++) {
            std::cout << result[i] << " ";
    }
    std::cout << std::endl;
    
    //209
    vector<int> nums4 = {2,3,1,2,4,3};
    int minLength = obj.minSubArrayLen(7,nums4);
    std::cout << minLength << std::endl;
    
    //904
    vector<int> nums5 = {1,2,3,2,2};
    int maxNum = obj.totalFruit(nums5);
    std::cout << maxNum << std::endl;
    
    //76
    string s = "ADOBECODEBANC", t = "ABC";
    string minWindowOfSubString = obj.minWindow(s,t);
    std::cout << minWindowOfSubString << std::endl;
    
    //59
    int n = 3;
    vector<vector<int>> res1 = obj.generateMatrix(n);
    for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << res1[i][j] << " ";  // Access and print each element
            }
            std::cout << std::endl;  // Print a newline after each row
        }
    
    //54
    vector<vector<int>> matrix = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    vector<int> res54 = obj.spiralOrder(matrix);
    for (int j = 0; j < res54.size(); j++) {
        std::cout << res54[j] << " ";  // Access and print each element
    }
    std::cout << std::endl;  // Print a newline after each row
    
    //LCR 146 螺旋打印矩阵
    vector<vector<int>> matrix2 = {{1,2,3,4},{12,13,14,5},{11,16,15,6},{10,9,8,7}};
    vector<int> res542 = obj.spiralOrder(matrix2);
    for (int j = 0; j < res542.size(); j++) {
        std::cout << res542[j] << " ";  // Access and print each element
    }
    std::cout << std::endl;  // Print a newline after each row
    
    
    //
    vector<vector<int>> testVec1 = {
            {1, 2, 3},
            {2, 1, 3},
            {1, 2, 3}
        };
    int n1 = 3, m1 = 3;
    cout << "Test Case 1 Result: " << obj.minDifference(testVec1, n1, m1) << endl;
    std::cout << std::endl;
}

// Helper function to print the linked list
void printList(ListNode* head) {
    while (head != NULL) {
        std::cout << head->val << " -> ";
        head = head->next;
    }
    std::cout << "NULL" << std::endl;
}

// Helper function to create a linked list from an array of values
ListNode* createList(const std::vector<int>& values) {
    if (values.empty()) return NULL;
    
    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    
    for (size_t i = 1; i < values.size(); ++i) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    
    return head;
}

void linkedListSectionTest(){
    std::vector<int> values = {1, 2, 6, 3, 4, 5, 6};
    ListNode* head = createList(values);

    std::cout << "Original list: ";
    printList(head);

    LinkedListSection solution;
    int valToRemove = 6;

    // Remove elements with value 6
    head = solution.removeElements(head, valToRemove);

    std::cout << "List after removing " << valToRemove << ": ";
    printList(head);

    // Clean up the remaining nodes
    while (head != NULL) {
        ListNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}

void myLinkedListTest(){
    
    MyLinkedList myLinkedList;
    myLinkedList.addAtHead(1);
    myLinkedList.printList();
    myLinkedList.addAtTail(3);
    myLinkedList.printList();
    myLinkedList.addAtIndex(1, 2);    // linked list becomes 1->2->3
    myLinkedList.printList();
    myLinkedList.get(1);              // return 2
    myLinkedList.deleteAtIndex(1);    // now the linked list is 1->3
    myLinkedList.printList();
    myLinkedList.get(1);              // return 3
    
}

void HashSectionTest(){
    
    HashSection obj;
    //242
    string s = "anagram", t = "nagaram";
    string result = obj.isAnagram(s,t) ? "true" : "False";
    std::cout << "is Anagram?: " + result << endl;
    
    //49
    vector<string> strs = {"eat","tea","tan","ate","nat","bat"};
    vector<vector<string>> result1 = obj.groupAnagrams(strs);
    for(auto arr:result1){
        for(auto ele:arr){
            std::cout << ele + " ";
        }
        std::cout << ",";
    }
    std::cout << endl;
    
    //438
    string s1 = "cbaebabacd", p1 = "abc";
    vector<int> res2 = obj.findAnagrams(s1, p1);
    for(auto ele:res2){
        std::cout << ele << ", ";
    }
    
    std::cout << endl;
    
    //349
    vector<int> nums1 = {4,9,5}, nums2 = {9,4,9,8,4};
    vector<int> res3 = obj.intersection(nums1, nums2);
    for(auto ele:res3){
        std::cout << ele << ", ";
    }
    
    std::cout << endl;
    
    //350:相比349， 350会返回重复出现的相同的数
    vector<int> nums21 = {1,2,2,1}, nums22 = {2,2};
    vector<int> res4 = obj.intersect(nums21, nums22);
    for(auto ele:res4){
        std::cout << ele << ", ";
    }
    
    std::cout << endl;
    
    //202
    string res5 = obj.isHappy(19) ? "true" : "False";
    std::cout << "19 is Happy num?: " + res5 << endl;
    
    //15
    vector<int> nums15 = {-1,0,1,2,-1,-4};
    vector<vector<int>> res15 = obj.threeSum(nums15);
    for(auto arr:res15){
        for(auto ele:arr){
            std::cout << ele ;
            std::cout << ",";
        }
        std::cout << endl;
    }
    std::cout << endl;
    
    //18
    vector<int> nums18 = {1,0,-1,0,-2,2};
    int target = 0;
    vector<vector<int>> res18 = obj.fourSum(nums18,target);
    for(auto arr:res18){
        for(auto ele:arr){
            std::cout << ele ;
            std::cout << ",";
        }
        std::cout << endl;
    }
    std::cout << endl;
    
}

void StringSectionTest(){
    StringSection obj;
    string s = "abc1b2b3b4";
    string res = obj.replaceNumToNumber(s);
    std::cout << res << endl;
    
    string s1 = "abcdefg";
    string res1 = obj.reverseWordsbySection(s1, 2);
    std::cout << res1 << endl;
    
    //28
    string haystack = "hello", needle = "ll";
    int res2 = obj.strStr(haystack, needle);
    std::cout << res2 << endl;
    
    //459
    string s459 = "abcabcabcabc";
    //bool res459 = obj.repeatedSubstringPattern(s459);
    bool res459 = obj.repeatedSubstringPatternbyKMP(s459);
    string result = res459 ? "true" : "false";
    std::cout << result << endl;
    
}

void StackSectionTest(){
    StackQueueSection obj;
    string s = "()[]{}";
    string res = obj.isValid(s)? "true":"false";
    std::cout << res << endl;
    
    //239
    vector<int> a = {1,3,-1,-3,5,3,6,7};
    int k = 3;
    vector<int> result = obj.maxSlidingWindow(a, k);
    for (size_t i = 0; i < result.size(); ++i) {
            std::cout << result[i];
            if (i != result.size() - 1) { // Si ce n'est pas le dernier élément
                std::cout << ", ";
            }
        }
    std::cout << endl;
    
    //347
    vector<int> a1 = {1,1,1,2,2,3};
    int k1 = 2;
    vector<int> res347 = obj.topKFrequent(a1, k1);
    for (size_t i = 0; i < res347.size(); ++i) {
            std::cout << res347[i];
            if (i != res347.size() - 1) { // Si ce n'est pas le dernier élément
                std::cout << ", ";
            }
        }
    std::cout << endl;
    
}
void BinaryTreeSectionTest(){
    //BinaryTreeBasic obj;
    
}

void Graphtest(){
    GraphBasic obj;
    //797
    //obj.includeInput797Matrix();
    //obj.includeInput797List();
    //obj.includeInputKama99Dfs();
    //obj.includeInputKama99Bfs();
    obj.includeInputKama101Dfs();
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    //cout << "Hello, World!\n";
    
    //数组
    //arraySectionTest();
    //链表
    //linkedListSectionTest();
    //myLinkedListTest();//设计链表
    //哈希表
    //HashSectionTest();
    //字符串
    //StringSectionTest();
    
    //栈
    //StackSectionTest();
    
    //Binary Tree
    //BinaryTreeSectionTest();
    
    //Graphtest
    Graphtest();
    
    return 0;
}


