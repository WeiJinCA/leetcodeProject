//
//  BinaryTreeBasic.hpp
//  leetcodeProject
//
//  Created by WeiJin on 2024-11-07.
//

#ifndef BinaryTreeBasic_hpp
#define BinaryTreeBasic_hpp

#include <stdio.h>
#include <vector>
#include <unordered_map>

using namespace std;
// 二叉树理论
// 种类：满二叉树和完全二叉树
// 满二叉树： 如果一棵二叉树只有度为0的结点和度为2的结点，并且度为0的结点在同一层上，则这棵二叉树为满二叉树。 度指子节点的个数，
// 完全二叉树：在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。若最底层为第 h 层（h从1开始），则该层包含 1~ 2^(h-1) 个节点。
// 平衡二叉树：左右子树的高度绝对值差不超过1
// 二叉搜索树： 有序树； 若它的左子树不空，则左子树上所有结点的值均小于它的根结点的值；若它的右子树不空，则右子树上所有结点的值均大于它的根结点的值；它的左、右子树也分别为二叉排序树
// 堆：完全二叉树和排序的组合（保证父子节点的顺序关系，父节点大于子节点）；注意区分搜索树（父节点大于左孩子，小于右孩子）；所以堆不是平衡二叉搜索树
// 平衡二叉搜索树： AVL（Adelson-Velsky and Landis）；它是一棵空树或它的左右两个子树的高度差的绝对值不超过1，并且左右两个子树都是一棵平衡二叉树。
// C++中map、set、multimap，multiset的底层实现都是平衡二叉搜索树，所以map、set的增删操作时间时间复杂度是logn，注意我这里没有说unordered_map、unordered_set，unordered_map、unordered_set底层实现是哈希表。

// 存储方式： 链式存储 / 数组存储（父节点下标为i，字节点下标为2i+1,2i+2）
// 遍历方式：1.深度优先遍历（前、中、后序遍历）：先往深走，遇到叶子节点再往回走。（递归法，迭代法），借助栈实现
// 2.广度优先遍历（层次遍历）：一层一层的去遍历。用队列实现

// 二叉树深度 ： 从根节点到该节点的最长简单路径边的条数或者节点数（取决于深度从0开始还是从1开始）
// 二叉树高度 ： 从该节点到叶子节点的最长简单路径边的条数或者节点数（取决于高度从0开始还是从1开始）
// 根节点的高度就是二叉树的最大深度
// 递归写法：1.确定递归函数的参数和返回值 2.确定终止条件 3. 确定单层递归的逻辑

class BinaryTreeBasic {

public:
    int maxDepth = INT_MIN;
    int result;
    int maxCount = 0;//501 统计最大频率
    int count = 0;//501 统计频率
    
    //for 113
    vector<vector<int>> res;
    vector<int> path;
    vector<int> vec;//98
    
    
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
    //for 429
    class Node {
    public:
        int val;
        vector<Node*> children;

        Node() {}

        Node(int _val) {
            val = _val;
        }

        Node(int _val, vector<Node*> _children) {
            val = _val;
            children = _children;
        }
    };
    //for 116
    struct Node1 {
      int val;
        Node1 *left;
        Node1 *right;
        Node1 *next;
    };
    
    TreeNode* pre = NULL; //98 用来记录前一个节点
    
    //递归法
    void preTraversalHelper(TreeNode* cur, vector<int>& vec);//144
    void midTraversalHelper(TreeNode* cur, vector<int>& vec);//94
    void postTraversalHelper(TreeNode* cur, vector<int>& vec);//145
    vector<int> preorderTraversal(TreeNode* root);//前序遍历
    
    //迭代法
    vector<int> preorderTraversalByIteration(TreeNode* root);//前序遍历 迭代法
    vector<int> inorderTraversal(TreeNode* root);////中序遍历 迭代法
    vector<int> postorderTraversal(TreeNode* root);//后序遍历：左右中
    //统一迭代法
    vector<int> inorderTraversalUnified(TreeNode* root);//统一迭代法：中序遍历
    vector<int> preorderTraversalUnified(TreeNode* root);
    vector<int> postorderTraversalUnified(TreeNode* root);
    
    //前序遍历 + 后序遍历 for N叉树：589 590
    vector<int> preorderForN(Node* root);//589
    vector<int> postorderForN(Node* root);//590
    
    //层序遍历 102
    vector<vector<int>> levelOrder(TreeNode* root);
    void levelOrderRecurHelper(TreeNode* cur, vector<vector<int>>& result, int depth);//递归法辅助函数
    vector<vector<int>> levelOrderRecur(TreeNode* root);//递归法
    vector<vector<int>> levelOrderBottom(TreeNode* root);//107
    vector<int> rightSideView(TreeNode* root);//19
    vector<double> averageOfLevels(TreeNode* root);//637
    vector<vector<int>> levelOrderForN(Node* root);//429 //N叉树
    vector<int> largestValues(TreeNode* root);//515
    Node1* connect(Node1* root);//116 / 117//填充每个节点的下一个右侧节点指针
    int maxDepth104(TreeNode* root);//104
    int minDepth(TreeNode* root);//111
    
    //翻转二叉树 226
    TreeNode* invertTree(TreeNode* root);//递归法
    TreeNode* invertTreeByIteration(TreeNode* root);//迭代法
    TreeNode* invertTreeByIterationUnified(TreeNode* root);//迭代法统一写法
    TreeNode* invertTreeByLevel(TreeNode* root);//层序遍历翻转
    
    //101 对称二叉树
    bool compareHelper(TreeNode* left,TreeNode* right);
    bool isSymmetric(TreeNode* root);
    bool isSymmetricByIteration(TreeNode* root);
    bool isSameTree(TreeNode* p, TreeNode* q);//100 判断两个树是否相等
    bool isSameTreeByRecursion(TreeNode* p, TreeNode* q);//100 判断两个树是否相等
    bool isSubtree(TreeNode* root, TreeNode* subRoot);//572 判断是否是树的子树
    //最大深度 类似104
    int maxDepth1(TreeNode* root);//
    int getdepth(TreeNode* node);//使用后序遍历获取高度
    int maxDepthByPre(TreeNode* root);//
    void getdepthByPre(TreeNode* node,int depth);//使用后序遍历获取高度
    //使用迭代法求深度见104
    //509 n叉树的最大深度;迭代法参考429代码改动
    int maxDepthForN(Node* root);
    
    //最小深度 111
    int minDepthByRecur(TreeNode* root);//递归
    
    //完全二叉树的节点个数
    int countNodes(TreeNode* root);//使用普通二叉树来做
    int countNodesByCompleteBinaryTree(TreeNode* root);//使用完全二叉树的特性做
    
    // 返回以该节点为根节点的二叉树的高度，如果不是平衡二叉树了则返回-1
    int getHeightHelper(TreeNode* node);
    bool isBalanced(TreeNode* root);//110平衡二叉树
    
    void traversal(TreeNode* cur, string path, vector<string>& result);
    vector<string> binaryTreePaths(TreeNode* root);//257 二叉树的所有路经
    
    //代码随想录二叉树 15左叶子之和
    int sumOfLeftLeaves(TreeNode* root);//404
    int sumOfLeftLeavesByIter(TreeNode* root);
    
    //16
    void traversalHelper513(TreeNode* root, int depth);
    int findBottomLeftValue(TreeNode* root);//513
    int findBottomLeftValueByLevelIter(TreeNode* root);//513
    
    //17 路径总和
    bool hasPathSum(TreeNode* root, int targetSum);//112 递归法
    bool hasPathSumByIter(TreeNode* root, int sum);//迭代法
    vector<vector<int>> pathSum(TreeNode* root, int targetSum);//113
    void traversalHelper113(TreeNode* cur, int count) ;
    
    //18 从中序与后序遍历序列构造二叉树
    TreeNode* traversalBuildTreeHelper (vector<int>& inorder, int inorderBegin, int inorderEnd, vector<int>& postorder, int postorderBegin, int postorderEnd);
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder);//106 从中序与后序遍历序列构造二叉树
    TreeNode* buildTreeFromPreAndInorder(vector<int>& preorder, vector<int>& inorder);//105 从前序与中序遍历序列构造二叉树
    TreeNode* traversalBuildTreeHelperFromPreAndInorder (
                     vector<int>& inorder,int inorderBegin, int inorderEnd,
                                                         vector<int>& preorder, int preorderBegin, int preorderEnd);
    
    //19最大二叉树
    TreeNode* constructMaximumBinaryTree(vector<int>& nums);//654
    TreeNode* traversalConstructMaximumBinaryTreeHelper(vector<int>& nums, int left, int right);
    
    //21 合并二叉树
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2);
    TreeNode* mergeTreesByIter(TreeNode* t1, TreeNode* t2);
    
    //22 二叉搜索树中的搜索
    TreeNode* searchBST(TreeNode* root, int val);
    TreeNode* searchBSTByIter(TreeNode* root, int val);
    
    //23 验证二叉搜索树
    void traversal98ByRecurHelper(TreeNode* root);
    bool isValidBST(TreeNode* root);//98 先递归转换为数组，再判断数组是否有序
    bool isValidBSTByRecur98(TreeNode* root);//98 递归过程中直接判断是否有序
    bool isValidBSTByIter98(TreeNode* root);//98 迭代法直接判断是否有序
    
    //24 二叉搜索树最小绝对差
    int getMinimumDifference(TreeNode* root);
    
    //25 二叉搜索树的众数；
    void searchBST501(TreeNode* cur, unordered_map<int, int>& map);
    static bool  cmp501 (const pair<int, int>& a, const pair<int, int>& b) ;
    vector<int> findModeForNormalTree(TreeNode* root);//对于普通二叉树
    //for 二叉搜索树
    vector<int> findModeForBST501(TreeNode* root);
    void searchBST501_2(TreeNode* cur);
    //迭代法
    vector<int> findModeByIter501(TreeNode* root);
    
    //26 找最近公共祖先
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q);//236
    //28
    TreeNode* lowestCommonAncestorForBST(TreeNode* root, TreeNode* p, TreeNode* q);//235
    TreeNode* lowestCommonAncestorForBSTByIter235(TreeNode* root, TreeNode* p, TreeNode* q);
    //29
    TreeNode* insertIntoBSTByRecur701(TreeNode* root, int val);//701
    TreeNode* insertIntoBSTByIter701(TreeNode* root, int val);//迭代法
    //30 缺失：删除二叉搜索树中的节点
    //450
    
    //31 修剪二叉搜索树
    TreeNode* trimBST(TreeNode* root, int low, int high);//669
    TreeNode* trimBSTByIter(TreeNode* root, int low, int high);
    
    //32 将有序数组转换为二叉搜索树
    TreeNode* traversalHelper108(vector<int>& nums, int left, int right);
    TreeNode* sortedArrayToBST(vector<int>& nums);//108
    TreeNode* sortedArrayToBSTByIter(vector<int>& nums);//108
    
    //32 将二叉搜索树转换为累加树 缺失
    
    
};
#endif /* BinaryTreeBasic_hpp */
