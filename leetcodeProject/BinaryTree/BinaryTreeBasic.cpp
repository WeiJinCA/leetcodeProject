//
//  BinaryTreeBasic.cpp
//  leetcodeProject
//
//  Created by WeiJin on 2024-11-07.
//

#include "BinaryTreeBasic.hpp"
#include <vector>
#include <stack>
#include <queue>

using namespace std;

//前、中、后序递归遍历
void BinaryTreeBasic::preTraversalHelper(TreeNode* cur, vector<int>& vec){
    if(cur == NULL) return ;
    vec.push_back(cur->val);//中
    preTraversalHelper(cur->left,vec);//左
    preTraversalHelper(cur->right,vec);//右
}
void BinaryTreeBasic::midTraversalHelper(TreeNode* cur, vector<int>& vec){
    if(cur == NULL) return ;
    
    midTraversalHelper(cur->left,vec);//左
    vec.push_back(cur->val);//中
    midTraversalHelper(cur->right,vec);//右
}
void BinaryTreeBasic::postTraversalHelper(TreeNode* cur, vector<int>& vec){
    if(cur == NULL) return ;
    
    postTraversalHelper(cur->left,vec);//左
    postTraversalHelper(cur->right,vec);//右
    vec.push_back(cur->val);//中
}
//前序遍历，可调用其他遍历方法的辅助函数
vector<int> BinaryTreeBasic::preorderTraversal(TreeNode* root){
    vector<int> result;
    preTraversalHelper(root,result);
    return result;
}

//前序遍历：迭代法
vector<int> BinaryTreeBasic::preorderTraversalByIteration(TreeNode* root){
    stack<TreeNode*> st;
    vector<int> result;
    if(root == NULL) return result;
    st.push(root);
    while (!st.empty()) {
        TreeNode* node = st.top();//中
        st.pop();
        result.push_back(node->val);
        if(node->right) st.push(node->right);//右（空节点不入栈）
        if(node->left) st.push(node->left);//左 （空节点不入栈）
    }
    return result;
}
//中序遍历 迭代法
vector<int> BinaryTreeBasic::inorderTraversal(TreeNode* root){
    vector<int> result;
    stack<TreeNode*> st;
    TreeNode* cur = root;
    while (cur != NULL || !st.empty()) {
        if (cur != NULL) {// 指针来访问节点，访问到最底层
            //向下向左到底，存数据入栈
            st.push(cur);// 将访问的节点放进栈
            cur = cur->left;//左
        }else{
            //从最底层往上，往右出栈，将数据存入result中
            cur = st.top();// 从栈里弹出的数据，就是要处理的数据（放进result数组里的数据）
            st.pop();
            result.push_back(cur->val);//中
            cur = cur->right;//右
        }
    }
    return result;
}
//后序遍历：左右中
//思路： 先序遍历：中左右，调整其代码到：中右左；反转result数组至：左右中（后序遍历）
vector<int> BinaryTreeBasic::postorderTraversal(TreeNode* root){
    stack<TreeNode*> st;
    vector<int> result;
    if(root == NULL) return result;
    st.push(root);
    while (!st.empty()) {
        TreeNode* node = st.top();//中
        st.pop();
        result.push_back(node->val);
        if(node->left) st.push(node->left);//左 （空节点不入栈）
        if(node->right) st.push(node->right);//右（空节点不入栈）
    }
    reverse(result.begin(),result.end());//将调整后的结果反转
    return result;
}
//统一迭代法：解决访问节点和处理节点不同步的问题
//中序遍历举例：
//解决办法： 将访问的节点放入栈中，把要处理的节点也放入栈中但是要做标记（标记法：要处理的节点放入栈之后，紧接着放入一个空指针作为标记）
vector<int> BinaryTreeBasic::inorderTraversalUnified(TreeNode* root){
    vector<int> result;
    stack<TreeNode*> st;
    if (root != NULL) st.push(root);
    while (!st.empty()) {
        
        TreeNode* node = st.top();
        if (node != NULL) {
            st.pop();// 将该节点弹出，避免重复操作，下面再将右中左节点添加到栈中
            if(node->right) st.push(node->right);//右（空节点不入栈）
            
            st.push(node);// 添加中节点
            st.push(NULL); // 中节点访问过，但是还没有处理，加入空节点做为标记！！
            
            if(node->left) st.push(node->left);//左 （空节点不入栈）
        }else{// 只有遇到空节点的时候，才将下一个节点放进结果集；出栈顺序相反，所以是下一个，即中节点
            st.pop();// 将空节点弹出
            node = st.top();// 重新取出栈中元素
            st.pop();
            result.push_back(node->val);// 加入到结果集
        }
    }
    
    return result;
}

//统一迭代法：解决访问节点和处理节点不同步的问题
//前序遍历： 只需改变中序遍历统一法中的两行代码
vector<int> BinaryTreeBasic::preorderTraversalUnified(TreeNode* root){
    vector<int> result;
    stack<TreeNode*> st;
    if (root != NULL) st.push(root);
    while (!st.empty()) {
        
        TreeNode* node = st.top();
        if (node != NULL) {
            st.pop();// 将该节点弹出，避免重复操作，下面再将右中左节点添加到栈中
            if(node->right) st.push(node->right);//右（空节点不入栈）
            if(node->left) st.push(node->left);//左 （空节点不入栈）
            
            st.push(node);// 添加中节点
            st.push(NULL); // 中节点访问过，但是还没有处理，加入空节点做为标记！！
            
        }else{// 只有遇到空节点的时候，才将下一个节点放进结果集；出栈顺序相反，所以是下一个，即中节点
            st.pop();// 将空节点弹出
            node = st.top();// 重新取出栈中元素
            st.pop();
            result.push_back(node->val);// 加入到结果集
        }
    }
    
    return result;
}
//589 N叉树前序遍历
vector<int> BinaryTreeBasic::preorderForN(Node* root){
    vector<int> result;
    stack<Node*> st;
    if (root != NULL) st.push(root);
    while (!st.empty()) {
        
        Node* node = st.top();
        if (node != NULL) {
            st.pop();// 将该节点弹出，避免重复操作，下面再将右中左节点添加到栈中
            for(int i = static_cast<int>(node->children.size())-1; i >=0; i-- )
                if(node->children[i]) st.push(node->children[i]);//字节点从右往前入栈
            
            st.push(node);// 添加中节点
            st.push(NULL); // 中节点访问过，但是还没有处理，加入空节点做为标记！！
            
        }else{// 只有遇到空节点的时候，才将下一个节点放进结果集；出栈顺序相反，所以是下一个，即中节点
            st.pop();// 将空节点弹出
            node = st.top();// 重新取出栈中元素
            st.pop();
            result.push_back(node->val);// 加入到结果集
        }
    }
    
    return result;
}
//统一迭代法：解决访问节点和处理节点不同步的问题
//后序遍历：只需改变中序遍历统一法中的两行代码
vector<int> BinaryTreeBasic::postorderTraversalUnified(TreeNode* root){
    vector<int> result;
    stack<TreeNode*> st;
    if (root != NULL) st.push(root);
    while (!st.empty()) {
        
        TreeNode* node = st.top();
        if (node != NULL) {
            st.pop();// 将该节点弹出，避免重复操作，下面再将右中左节点添加到栈中
            
            st.push(node);// 添加中节点
            st.push(NULL); // 中节点访问过，但是还没有处理，加入空节点做为标记！！
            
            if(node->right) st.push(node->right);//右（空节点不入栈）
            if(node->left) st.push(node->left);//左 （空节点不入栈）
        }else{// 只有遇到空节点的时候，才将下一个节点放进结果集；出栈顺序相反，所以是下一个，即中节点
            st.pop();// 将空节点弹出
            node = st.top();// 重新取出栈中元素
            st.pop();
            result.push_back(node->val);// 加入到结果集
        }
    }
    
    return result;
}
//590 N叉树的后序遍历，统一写法
vector<int> BinaryTreeBasic::postorderForN(Node* root){
    vector<int> result;
    stack<Node*> st;
    if (root != NULL) st.push(root);
    while (!st.empty()) {
        
        Node* node = st.top();
        if (node != NULL) {
            st.pop();// 将该节点弹出，避免重复操作，下面再将右中左节点添加到栈中
            
            st.push(node);// 添加中节点
            st.push(NULL); // 中节点访问过，但是还没有处理，加入空节点做为标记！！
            
            for(int i = static_cast<int>(node->children.size())-1; i >=0; i-- )
                if(node->children[i]) st.push(node->children[i]);//字节点从右往前入栈
        }else{// 只有遇到空节点的时候，才将下一个节点放进结果集；出栈顺序相反，所以是下一个，即中节点
            st.pop();// 将空节点弹出
            node = st.top();// 重新取出栈中元素
            st.pop();
            result.push_back(node->val);// 加入到结果集
        }
    }
    
    return result;
}
//层序遍历 leetcode 102
//借用一个辅助数据结构:队列来实现，队列先进先出，符合一层一层遍历的逻辑，而用栈先进后出适合模拟深度优先遍历也就是递归的逻辑
//先进先出
vector<vector<int>> BinaryTreeBasic::levelOrder(TreeNode* root){
    queue<TreeNode*> que;
    if (root != NULL) que.push(root);
    vector<vector<int>> result;
    while (!que.empty()) {
        int size = static_cast<int>(que.size());
        vector<int> vec;
        // 这里一定要使用固定大小size，不要使用que.size()，因为que.size是不断变化的
        for (int i = 0; i < size; i++) {
            TreeNode* node = que.front();
            que.pop();
            vec.push_back(node->val);
            
            //把下一层的push到队列，即在右支节点的后面
            if(node->left) que.push(node->left);//左
            if(node->right) que.push(node->right);
        }
        result.push_back(vec);
    }
    return result;
}
//递归法
void BinaryTreeBasic::levelOrderRecurHelper(TreeNode* cur, vector<vector<int>>& result, int depth){
    if (cur == nullptr) return;
    if (result.size() == depth) result.push_back(vector<int>());//如果到下一层了，要添加新数组
    result[depth].push_back(cur->val);//访问新一层的数组元素
    levelOrderRecurHelper(cur->left,result,depth+1);
    levelOrderRecurHelper(cur->right,result,depth+1);
}
//102
vector<vector<int>> BinaryTreeBasic::levelOrderRecur(TreeNode* root){
    vector<vector<int>> result;
    int depth = 0;
    levelOrderRecurHelper(root,result,depth);
    return result;
}
//107 从叶子结点从左到右遍历，依层往上
vector<vector<int>> BinaryTreeBasic::levelOrderBottom(TreeNode* root){
    queue<TreeNode*> que;
    if (root != NULL) que.push(root);
    vector<vector<int>> result;
    while (!que.empty()) {
        int size = static_cast<int>(que.size());
        vector<int> vec;
        // 这里一定要使用固定大小size，不要使用que.size()，因为que.size是不断变化的
        for (int i = 0; i < size; i++) {
            TreeNode* node = que.front();
            que.pop();
            vec.push_back(node->val);
            
            //把下一层的push到队列，即在右支节点的后面
            if(node->left) que.push(node->left);//左
            if(node->right) que.push(node->right);
        }
        result.push_back(vec);
    }
    reverse(result.begin(),result.end());//反转下数组
    return result;
}
//199: 层序遍历的时候，判断是否遍历到单层的最后面的元素，如果是，就放进result数组中，随后返回result就可以了。
vector<int> BinaryTreeBasic::rightSideView(TreeNode* root){
    queue<TreeNode*> que;
    if (root != NULL) que.push(root);
    vector<int> result;
    while (!que.empty()) {
        int size = static_cast<int>(que.size());
        // 这里一定要使用固定大小size，不要使用que.size()，因为que.size是不断变化的
        for (int i = 0; i < size; i++) {
            TreeNode* node = que.front();
            que.pop();
            if(i == size - 1) result.push_back(node->val);//将每层最后元素放入结果集
            
            //把下一层的push到队列，即在右支节点的后面
            if(node->left) que.push(node->left);//左
            if(node->right) que.push(node->right);
        }
    }
    
    return result;
}
//637层平均值 ： 每层求和再平均
vector<double> BinaryTreeBasic::averageOfLevels(TreeNode* root){
    queue<TreeNode*> que;
    if (root != NULL) que.push(root);
    vector<double> result;
    while (!que.empty()) {
        int size = static_cast<int>(que.size());
        double sum = 0;
        // 这里一定要使用固定大小size，不要使用que.size()，因为que.size是不断变化的
        for (int i = 0; i < size; i++) {
            TreeNode* node = que.front();
            que.pop();
            sum += node->val;
            
            //把下一层的push到队列，即在右支节点的后面
            if(node->left) que.push(node->left);//左
            if(node->right) que.push(node->right);
        }
        result.push_back(sum/size);
    }
    
    return result;
}
//429:N叉树的层序遍历
//区别：一个节点有多个孩子
vector<vector<int>> BinaryTreeBasic::levelOrderForN(Node* root){
    queue<Node*> que;
    if (root != NULL) que.push(root);
    vector<vector<int>> result;
    while (!que.empty()) {
        int size = static_cast<int>(que.size());
        vector<int> vec;
        for (int i = 0; i < size; i++) {
            Node* node = que.front();
            que.pop();
            vec.push_back(node->val);
            for (int i = 0; i < node->children.size(); i++) { // 将节点孩子加入队列
                if (node->children[i]) que.push(node->children[i]);
            }
        }
        result.push_back(vec);
    }
    return result;
}
//515:取每层的最大值返回
vector<int> BinaryTreeBasic::largestValues(TreeNode* root){
    queue<TreeNode*> que;
    if (root != NULL) que.push(root);
    vector<int> result;
    while (!que.empty()) {
        int size = static_cast<int>(que.size());
        int max = INT_MIN;
        // 这里一定要使用固定大小size，不要使用que.size()，因为que.size是不断变化的
        for (int i = 0; i < size; i++) {
            TreeNode* node = que.front();
            que.pop();
            max = node->val > max ? node->val : max;
            
            //把下一层的push到队列，即在右支节点的后面
            if(node->left) que.push(node->left);//左
            if(node->right) que.push(node->right);
        }
        result.push_back(max);
    }
    
    return result;
}
//116 对完整二叉树：填充每个节点的下一个右侧节点指针, 其初始为NULL
//适用于117
BinaryTreeBasic::Node1* BinaryTreeBasic::connect(BinaryTreeBasic::Node1* root){
    queue<Node1*> que;
    if (root != NULL) que.push(root);
    
    while (!que.empty()) {
        int size = static_cast<int>(que.size());
        Node1* nodePre = nullptr;
        Node1* node;
        for (int i = 0; i < size; i++) {
            if (i == 0) {
                nodePre = que.front();//取出一层的头节点
                que.pop();
                node = nodePre;
            }else{
                node = que.front();
                que.pop();
                nodePre->next = node;// 本层前一个节点next指向本节点
                nodePre = nodePre->next;
            }
            if (node->left) que.push(node->left);
            if (node->right) que.push(node->right);
        }
        nodePre->next = NULL;// 本层最后一个节点指向NULL
    }
    return root;
}
//104:求最大深度
//二叉树的深度为根节点到最远叶子节点的最长路径上的节点数；叶子节点是指没有子节点的节点
int BinaryTreeBasic::maxDepth104(TreeNode* root){
    if (root == NULL) return 0;
    int depth = 0;
    queue<TreeNode*> que;
    que.push(root);
    while(!que.empty()) {
        int size = static_cast<int>(que.size());
        depth++; // 记录深度
        for (int i = 0; i < size; i++) {
            TreeNode* node = que.front();
            que.pop();
            if (node->left) que.push(node->left);
            if (node->right) que.push(node->right);
        }
    }
    return depth;
}
//111:最小深度: 当左右孩子都为空的时候，说明是最低点的一层了，退出
int BinaryTreeBasic::minDepth(TreeNode* root){
    if (root == NULL) return 0;
    int depth = 0;
    queue<TreeNode*> que;
    que.push(root);
    while(!que.empty()) {
        int size = static_cast<int>(que.size());
        depth++; // 记录深度
        for (int i = 0; i < size; i++) {
            TreeNode* node = que.front();
            que.pop();
            if (node->left) que.push(node->left);
            if (node->right) que.push(node->right);
            //判断左右节点为空，说明已经到底
            if(!node->left && !node->right){// 当左右孩子都为空的时候，说明是最低点的一层了，退出
                return depth;
            }
        }
    }
    return depth;
}
//226 翻转二叉树：交换节点的左右分支
//递归法：前序遍历
BinaryTreeBasic::TreeNode* BinaryTreeBasic::invertTree(TreeNode* root){
    if (root == NULL) return root;
    swap(root->left,root->right);//中
    invertTree(root->left);//左
    invertTree(root->right);//右
    return root;
}
//226 迭代法：深度优先遍历
BinaryTreeBasic::TreeNode* BinaryTreeBasic::invertTreeByIteration(TreeNode* root){
    if (root == NULL) return root;
    stack<TreeNode*> st;
    st.push(root);
    while(!st.empty()){
        TreeNode* node = st.top();
        st.pop();
        swap(node->left, node->right);
        if (node->left) st.push(node->left);
        if (node->right) st.push(node->right);
    }
    return root;
}
//迭代法：统一写法
BinaryTreeBasic::TreeNode* BinaryTreeBasic::invertTreeByIterationUnified(TreeNode* root){
    
    stack<TreeNode*> st;
    if (root != NULL) st.push(root);
    
    while(!st.empty()){
        TreeNode* node = st.top();
        st.pop();
        if (node != NULL) {
            if (node->right) st.push(node->right);
            if (node->left) st.push(node->left);
            st.push(node);
            st.push(NULL);
        }else{
            st.pop();
            node = st.top();
            st.pop();
            swap(node->left,node->right);//节点逻辑处理
        }
    }
    return root;
}
BinaryTreeBasic::TreeNode* BinaryTreeBasic::invertTreeByLevel(TreeNode* root){
    queue<TreeNode*> que;
    if (root != NULL) que.push(root);
    
    while (!que.empty()) {
        int size = static_cast<int>(que.size());
        for (int i = 0; i < size; i++) {
            TreeNode* node = que.front();
            que.pop();
            swap(node->left,node->right);//节点翻转
            if (node->left) que.push(node->left);
            if (node->right) que.push(node->right);
        }
    }
    return root;
}
bool BinaryTreeBasic::compareHelper(TreeNode* left,TreeNode* right){
    //首先排除空节点的情况
    if (left == NULL && right != NULL) return false;
    else if (left != NULL && right == NULL) return false;
    else if (left == NULL && right == NULL) return true;
    else if (left->val != right->val) return false;//上面排除了空节点后，再排除数值不等的情况
    //简写
    //else return compareHelper(left->left,right->right) && compareHelper(left->right,right->left);
    
    //下面就只考虑数值相等的情况
    //此时才做递归
    bool outside = compareHelper(left->left,right->right);//外侧元素对比
    bool inside = compareHelper(left->right,right->left);//内侧元素对比
    bool isSame = outside && inside;
    return isSame;
}
bool BinaryTreeBasic::isSymmetric(TreeNode* root){
    if (root == NULL) return true;
    return compareHelper(root->left,root->right);
}
//判断对称：用队列和栈都可以；本质是成对的取出来比较
bool BinaryTreeBasic::isSymmetricByIteration(TreeNode* root){
    if(root == NULL) return true;
    queue<TreeNode*> que;
    que.push(root->left);
    que.push(root->right);
    
    while(!que.empty()){
        TreeNode* leftNode = que.front();que.pop();
        TreeNode* rightNode = que.front();que.pop();
        if(!leftNode && !rightNode) continue; // 都为空的情况，为真
        
        if (!leftNode || !rightNode || (leftNode->val != rightNode->val)) return false;//不对称的情况
        
        que.push(leftNode->left);//加入外侧节点
        que.push(rightNode->right);
        que.push(leftNode->right);//加入内侧节点
        que.push(rightNode->left);
    }
    return true;
}
//100 判断两个树是否相等
bool BinaryTreeBasic::isSameTree(TreeNode* p, TreeNode* q){
            if(p==NULL && q == NULL) return true;
            else if(!p || !q || (p->val != q->val)) return false;

            queue<TreeNode*> que;
            que.push(p);
            que.push(q);
            while(!que.empty()){
                TreeNode* pNode = que.front();que.pop();
                TreeNode* qNode = que.front();que.pop();

                if(!pNode && !qNode) continue;
                if(!pNode || !qNode || (pNode->val != qNode->val)) return false;

                que.push(pNode->left);
                que.push(qNode->left);
                que.push(pNode->right);
                que.push(qNode->right);
            }
            return true;
}
bool BinaryTreeBasic::isSameTreeByRecursion(TreeNode* p, TreeNode* q){
    if (p == NULL && q == NULL) {
        return true;
    }
    if (p == NULL || q == NULL) {
        return false;
    }
    if (p->val == q ->val) {
        return isSameTreeByRecursion(p->left,q->left) && isSameTreeByRecursion(p->right,q->right);
    }else return false;
}
//572 判断是否是树的子树
bool BinaryTreeBasic::isSubtree(TreeNode* root, TreeNode* subRoot){
    if (root == NULL) {
        return false;
    }
    
    if (isSameTreeByRecursion(root,subRoot)) {
        return true;
    }else{
        return isSubtree(root->left,subRoot) || isSubtree(root->right, subRoot);
    }
}

int BinaryTreeBasic::maxDepth1(TreeNode* root){
    //精简代码，不用getdepth
//    if (root == NULL) return 0;
//    return 1 + max(maxDepth1(root->left),maxDepth1(root->right));
    return getdepth(root);
}
//使用前序求的就是深度，使用后序求的是高度
int BinaryTreeBasic::getdepth(TreeNode* node){
    if (node == NULL) return 0;
    int leftDepth = getdepth(node->left);
    int rightDepth = getdepth(node->right);
    int depth = 1+ max(leftDepth,rightDepth);
    return depth;
}
//使用前序遍历
int BinaryTreeBasic::maxDepthByPre(TreeNode* root){
    result = 0;
    if(root == 0)return result;
    getdepthByPre(root,1);
    return result;
}
void BinaryTreeBasic::getdepthByPre(TreeNode* node,int depth){
    result = depth > result ? depth : result;//中
    if(node->left == NULL && node->right == NULL) return ;
    if(node->left){
        getdepthByPre(node->left,depth+1);//左
    }
    if(node->right){
        getdepthByPre(node->right,depth+1);//右
    }
    return;
}
//509 n叉树的最大深度
int BinaryTreeBasic::maxDepthForN(Node* root){
    if(root == 0) return 0;
    int depth = 0;
    for (int i = 0; i < root->children.size(); i++) {
        depth = max(depth,maxDepthForN(root->children[i]));
    }
    return depth+1;
}
//111: 注意：最小深度是从根节点到最近叶子节点的最短路径上的节点数量。注意是叶子节点：左右孩子都为空的节点才是叶子节点
// 当根节点只是没有左节点时，最小深度不是1；因为只有左右孩子都为空的节点才是叶子节点；
int BinaryTreeBasic::minDepthByRecur(TreeNode* root){
    if (root == NULL) return 0;
            if (root->left == NULL && root->right != NULL) {
                return 1 + minDepthByRecur(root->right);
            }
            if (root->left != NULL && root->right == NULL) {
                return 1 + minDepthByRecur(root->left);
            }
            return 1 + min(minDepthByRecur(root->left), minDepthByRecur(root->right));
}
//222
// 求节点个数；递归遍历使用后序遍历
//int getNodesNum(TreeNode* cur) {
//        if (cur == NULL) return 0;
//        int leftNum = getNodesNum(cur->left);      // 左
//        int rightNum = getNodesNum(cur->right);    // 右
//        int treeNum = leftNum + rightNum + 1;      // 中
//        return treeNum;
//}
//精简代码
int BinaryTreeBasic::countNodes(TreeNode* root){
    if(root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);//后序遍历，左右中
}
//层序遍历
//int countNodes(TreeNode* root) {
//        queue<TreeNode*> que;
//        if (root != NULL) que.push(root);
//        int result = 0;
//        while (!que.empty()) {
//            int size = que.size();
//            for (int i = 0; i < size; i++) {
//                TreeNode* node = que.front();
//                que.pop();
//                result++;   // 记录节点数量
//                if (node->left) que.push(node->left);
//                if (node->right) que.push(node->right);
//            }
//        }
//        return result;
//    }
// 222
// 完全二叉树只有两种情况，情况一：就是满二叉树，情况二：最后一层叶子节点没有满
// 完全二叉树: 除了最底层节点可能没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。若最底层为第 h 层，则该层包含 1~ 2^(h-1)  个节点
// 在完全二叉树中，如果递归向左遍历的深度等于递归向右遍历的深度，那说明就是满二叉树
int BinaryTreeBasic::countNodesByCompleteBinaryTree(TreeNode* root){
    if(root == nullptr) return 0;
    TreeNode* left = root->left;
    TreeNode* right = root->right;
    int leftDepth = 0, rightDepth = 0;// 这里初始为0是有目的的，为了下面求指数方便
    while (left) {  // 求左子树深度
        left = left->left;
        leftDepth++;
    }
    while (right) { // 求右子树深度
        right = right->right;
        rightDepth++;
    }
    if (leftDepth == rightDepth) {
        return (2 << leftDepth) - 1; // 注意(2<<1) 相当于2^2，所以leftDepth初始为0
    }
    return countNodes(root->left) + countNodes(root->right) + 1;
}
//110 平衡二叉树
// 二叉树节点的深度：指从根节点到该节点的最长简单路径边的条数；根节点深度可以是1或0，leetcode上是 1
// 二叉树节点的高度：指从该节点到叶子节点的最长简单路径边的条数
// 求深度适合用前序遍历，而求高度适合用后序遍历。
// 高度平衡二叉树定义为：一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过1
int BinaryTreeBasic::getHeightHelper(TreeNode* node){
    if(node == NULL) return 0;
    
    int leftHeight = getHeightHelper(node->left);
    if(leftHeight == -1) return -1;
    int rightHeight = getHeightHelper(node->right);
    if(rightHeight == -1) return -1;
    return abs(leftHeight - rightHeight) > 1 ? -1 : 1 + max(leftHeight, rightHeight);
}
bool BinaryTreeBasic::isBalanced(TreeNode* root){
    return getHeightHelper(root) == -1 ? false : true;
}
//257 给定一个二叉树，返回所有从根节点到叶子节点的路径。
// 涉及回溯，要把路经记录下来，需要回溯来回退一个路径再进入另一个路径
//在叶子结点时，即处理记录路径的工作
void BinaryTreeBasic::traversal(TreeNode* cur, string path, vector<string>& result){//此处path是复制赋值，递归结束后起到回溯效果
    path += to_string(cur->val);//中
    if(cur->left == NULL && cur->right == NULL){
        result.push_back(path);//到叶子节点了，将路径保存到结果集中
        return;
    }
    if(cur->left) traversal(cur->left,path + "->", result);//左
    if(cur->right) traversal(cur->right,path + "->", result);//右
}
vector<string> BinaryTreeBasic::binaryTreePaths(TreeNode* root){
    vector<string> result;
    string path;
    if(root == NULL) return result;
    traversal(root,path,result);
    return result;
}
//404 计算给定二叉树的所有左叶子之和
//左叶子节点：当左侧叶子节点的左右子树都为空时。 右侧叶子结点不算
int BinaryTreeBasic::sumOfLeftLeaves(TreeNode* root){
    if(root == NULL) return 0;
    if(root->left == NULL && root->right == NULL) return 0;
    
    int leftValue = sumOfLeftLeaves(root->left);//左
    if(root->left && !root->left->left && !root->left->right) {// 左子树就是一个左叶子的情况
        leftValue = root->left->val;
    }
    int rightValue = sumOfLeftLeaves(root->right);//右
    int sum = leftValue + rightValue;//中
    return sum;
}

int BinaryTreeBasic::sumOfLeftLeavesByIter(TreeNode* root){
    stack<TreeNode*> st;
    if(root == NULL) return 0;
    st.push(root);
    int result = 0;
    while(!st.empty()){
        TreeNode* node = st.top();
        st.pop();
        
        if(node->left != NULL && node->left->left == NULL && node->left->right==NULL){
            result += node->left->val;
        }
        if(node->right) st.push(node->right);
        if(node->left) st.push(node->left);
    }
    return result;
}
//513 找到最后一行左边的节点的值（最深左节点）
void BinaryTreeBasic::traversalHelper513(TreeNode* root, int depth){
    if(root->left == NULL && root->right == NULL){
        if(depth > maxDepth){
            maxDepth = depth;
            result = root->val;
        }
        return;
    }
    if(root->left){
        traversalHelper513(root->left, depth + 1);//隐藏着回溯
    }
    if(root->right){
        traversalHelper513(root->right, depth + 1);//隐藏着回溯
    }
    return;
}
int BinaryTreeBasic::findBottomLeftValue(TreeNode* root){
    traversalHelper513(root,0);
    return result;
}
//513
int BinaryTreeBasic::findBottomLeftValueByLevelIter(TreeNode* root){
    queue<TreeNode*> que;
    if(root != NULL)que.push(root);
    int result = 0;
    while(!que.empty()){
        int size = static_cast<int>(que.size());
        for(int i=0;i<size;i++){
            TreeNode* node = que.front();
            que.pop();
            
            if(i == 0)result = node->val;// 记录最后一行第一个元素
            if(node->left) que.push(node->left);
            if(node->right) que.push(node->right);
        }
    }
    return result;
}
//112 路径上所有节点和为目标值
bool BinaryTreeBasic::hasPathSum(TreeNode* root, int targetSum){
    if(!root) return false;
    if(!root->left && !root->right && targetSum == root->val){
        return true;
    }
    return hasPathSum(root->left, targetSum - root->val) || hasPathSum(root->right, targetSum - root->val);//隐藏回溯，因为传递的是值
}
//迭代法
bool BinaryTreeBasic::hasPathSumByIter(TreeNode* root, int sum){
    if(root == NULL) return false;
    stack<pair<TreeNode*,int>>st;
    st.push(pair<TreeNode*,int>(root,root->val));
    while(!st.empty()){
        pair<TreeNode*,int> node = st.top();
        st.pop();
        // 如果该节点是叶子节点了，同时该节点的路径数值等于sum，那么就返回true
        if(!node.first->left && !node.first->right && sum == node.second)return true;
        
        //右节点，压进去一个节点的时候，将该节点的路径数值也记录下来
        if (node.first->right) {
            st.push(pair<TreeNode*, int>(node.first->right, node.second + node.first->right->val));
        }
        // 左节点，压进去一个节点的时候，将该节点的路径数值也记录下来
        if (node.first->left) {
            st.push(pair<TreeNode*, int>(node.first->left, node.second + node.first->left->val));
        }
    }
    return false;
}
//113 返回总和等于目标和的路径
vector<vector<int>> BinaryTreeBasic::pathSum(TreeNode* root, int targetSum){
    res.clear();
    path.clear();
    if(root == NULL) return res;
    path.push_back(root->val);
    traversalHelper113(root,targetSum - root->val);
    return res;
}
// 递归函数不需要返回值，因为我们要遍历整个树
void BinaryTreeBasic::traversalHelper113(TreeNode* cur, int count) {
    if(!cur->left && !cur->right && count == 0){// 遇到了叶子节点且找到了和为sum的路径
        res.push_back(path);
        return;
    }
    
    if(!cur->left && !cur->right)return;
    
    if(cur->left){//左
        path.push_back(cur->left->val);
        traversalHelper113(cur->left, count - cur->left->val);
        path.pop_back();
    }
    if(cur->right){//右
        path.push_back(cur->right->val);
        traversalHelper113(cur->right, count - cur->right->val);
        path.pop_back();
    }
    return;
}

BinaryTreeBasic::TreeNode* BinaryTreeBasic::traversalBuildTreeHelper (
                 vector<int>& inorder,int inorderBegin, int inorderEnd,
                 vector<int>& postorder, int postorderBegin, int postorderEnd){
    //1. 如果数组大小为零的话，说明是空节点
    if(postorderBegin == postorderEnd) return NULL;
    
    //2.如果不为空，那么取后序数组最后一个元素作为节点元素
    int rootValue = postorder[postorderEnd - 1];//取后序数组中最后一个元素作为中间节点
    TreeNode* root = new TreeNode(rootValue);
    
    if(postorderEnd - postorderBegin == 1) return root;
    
    //3.找到后序数组最后一个元素在中序数组的位置，作为切割点
    int delimiterIndex;
    for(delimiterIndex = inorderBegin; delimiterIndex < inorderEnd; delimiterIndex++){
        if(inorder[delimiterIndex] == rootValue) break;
    }
    
    //4.切割中序数组
    //左中序区间，左闭右开[leftInorderBegin, leftInorderEnd)
    int leftInorderBegin = inorderBegin;
    int leftInorderEnd = inorderEnd;
    //右中序区间，左闭右开[rightInorderBegin, rightInorderEnd)
    int rightInorderBegin = delimiterIndex + 1;
    int rightInorderEnd = inorderEnd;
    
    //5.切割后序数组
    //左后序区间，左闭右开[leftPostorderBegin, leftPostorderEnd)
    int leftPostorderBegin = postorderBegin;
    int leftPostorderEnd = postorderBegin + delimiterIndex - inorderBegin;// 终止位置是 需要加上 中序区间的大小size
    // 右后序区间，左闭右开[rightPostorderBegin, rightPostorderEnd)
    int rightPostorderBegin = postorderBegin + (delimiterIndex - inorderBegin);
    int rightPostorderEnd = postorderEnd - 1;// 排除最后一个元素，已经作为节点了
    
    root->left = traversalBuildTreeHelper(inorder,leftInorderBegin,leftInorderEnd,postorder,leftPostorderBegin,leftPostorderEnd);
    root->right = traversalBuildTreeHelper(inorder,rightInorderBegin,rightInorderEnd,postorder,rightPostorderBegin,rightPostorderEnd);
    
    return root;
}
//106.从中序与后序遍历序列构造二叉树
BinaryTreeBasic::TreeNode* BinaryTreeBasic::buildTree(vector<int>& inorder, vector<int>& postorder){
    if(inorder.size() == 0 || postorder.size() == 0) return NULL;
    //左闭右开原则
    return traversalBuildTreeHelper(inorder,0,static_cast<int>(inorder.size()),postorder,0,static_cast<int>(postorder.size()));
}

//105 从前序与中序遍历序列构造二叉树
BinaryTreeBasic::TreeNode* BinaryTreeBasic::buildTreeFromPreAndInorder(vector<int>& preorder, vector<int>& inorder){
    if(inorder.size() == 0 || preorder.size() == 0) return NULL;
    //左闭右开原则
    return traversalBuildTreeHelperFromPreAndInorder(inorder,0,static_cast<int>(inorder.size()),preorder,0,static_cast<int>(preorder.size()));
}

BinaryTreeBasic::TreeNode* BinaryTreeBasic::traversalBuildTreeHelperFromPreAndInorder (
                 vector<int>& inorder,int inorderBegin, int inorderEnd,
                 vector<int>& preorder, int preorderBegin, int preorderEnd){
    //1. 如果数组大小为零的话，说明是空节点
    if(preorderBegin == preorderEnd) return NULL;
    
    //2.如果不为空，那么取后序数组最后一个元素作为节点元素
    int rootValue = preorder[preorderBegin];//取前序数组中最前面的一个元素作为中间节点
    TreeNode* root = new TreeNode(rootValue);
    
    if(preorderEnd - preorderBegin == 1) return root;
    
    //3.找到后序数组最后一个元素在中序数组的位置，作为切割点
    int delimiterIndex;
    for(delimiterIndex = inorderBegin; delimiterIndex < inorderEnd; delimiterIndex++){
        if(inorder[delimiterIndex] == rootValue) break;
    }
    
    //4.切割中序数组
    //中序左区间，左闭右开[leftInorderBegin, leftInorderEnd)
    int leftInorderBegin = inorderBegin;
    int leftInorderEnd = delimiterIndex;
    //右中序区间，左闭右开[rightInorderBegin, rightInorderEnd)
    int rightInorderBegin = delimiterIndex + 1;
    int rightInorderEnd = inorderEnd;
    
    //5.切割前序数组
    //左后序区间，左闭右开[leftPostorderBegin, leftPostorderEnd)
    int leftPreorderBegin = preorderBegin + 1;
    int leftPreorderEnd = preorderBegin + delimiterIndex - inorderBegin;// 终止位置是 需要加上 中序区间的大小size
    // 右后序区间，左闭右开[rightPostorderBegin, rightPostorderEnd)
    int rightPreorderBegin = preorderBegin + 1 + (delimiterIndex - inorderBegin);
    int rightPreorderEnd = preorderEnd;// 排除最后一个元素，已经作为节点了
    
    root->left = traversalBuildTreeHelperFromPreAndInorder(inorder,leftInorderBegin,leftInorderEnd,preorder,leftPreorderBegin,leftPreorderEnd);
    root->right = traversalBuildTreeHelperFromPreAndInorder(inorder,rightInorderBegin,rightInorderEnd,preorder,rightPreorderBegin,rightPreorderEnd);
    
    return root;
}
//654 给定一个不含重复元素的整数数组。一个以此数组构建的最大二叉树定义如下：

//二叉树的根是数组中的最大元素。
//左子树是通过数组中最大值左边部分构造出的最大二叉树。
//右子树是通过数组中最大值右边部分构造出的最大二叉树。
BinaryTreeBasic::TreeNode* BinaryTreeBasic::constructMaximumBinaryTree(vector<int>& nums){
    return traversalConstructMaximumBinaryTreeHelper(nums,0,static_cast<int>(nums.size()));
}
//在左闭右开区间[left, right)，构造二叉树
BinaryTreeBasic::TreeNode* BinaryTreeBasic::traversalConstructMaximumBinaryTreeHelper(vector<int>& nums, int left, int right){
    if(left >= right) return nullptr;
    
    //分割点下表：maxValueIndex
    int maxValueIndex = left;
    for(int i = left+1;i<right;i++){
        if(nums[i] > nums[maxValueIndex]) maxValueIndex = i;
    }
    
    TreeNode* root = new TreeNode(nums[maxValueIndex]);
    // 左闭右开：[left, maxValueIndex)
    root->left = traversalConstructMaximumBinaryTreeHelper(nums,left,maxValueIndex);
    root->right = traversalConstructMaximumBinaryTreeHelper(nums,maxValueIndex + 1, right);
    return root;
}
//617 合并二叉树，如有重叠，则将节点值相加作为新节点值
BinaryTreeBasic::TreeNode* BinaryTreeBasic::mergeTrees(TreeNode* root1, TreeNode* root2){
    if(root1 == NULL) return root2;// 如果t1为空，合并之后就应该是t2
    if (root2 == NULL) return root1; // 如果t2为空，合并之后就应该是t1
    //修改了t1的数值和结构
    root1->val += root2->val;//中
    root1->left = mergeTrees(root1->left, root2->left);//左
    root1->right = mergeTrees(root1->right, root2->right);//左
    return root1;
}
//迭代法：同时处理两个树
BinaryTreeBasic::TreeNode* BinaryTreeBasic::mergeTreesByIter(TreeNode* t1, TreeNode* t2){
    if (t1 == NULL) return t2;
            if (t2 == NULL) return t1;
            queue<TreeNode*> que;
            que.push(t1);
            que.push(t2);
            while(!que.empty()) {
                TreeNode* node1 = que.front(); que.pop();
                TreeNode* node2 = que.front(); que.pop();
                // 此时两个节点一定不为空，val相加
                node1->val += node2->val;

                // 如果两棵树左节点都不为空，加入队列
                if (node1->left != NULL && node2->left != NULL) {
                    que.push(node1->left);
                    que.push(node2->left);
                }
                // 如果两棵树右节点都不为空，加入队列
                if (node1->right != NULL && node2->right != NULL) {
                    que.push(node1->right);
                    que.push(node2->right);
                }

                // 当t1的左节点 为空 t2左节点不为空，就赋值过去
                if (node1->left == NULL && node2->left != NULL) {
                    node1->left = node2->left;
                }
                // 当t1的右节点 为空 t2右节点不为空，就赋值过去
                if (node1->right == NULL && node2->right != NULL) {
                    node1->right = node2->right;
                }
            }
            return t1;
}
//700 给定二叉搜索树（BST）的根节点和一个值。 你需要在BST中找到节点值等于给定值的节点。 返回以该节点为根的子树。 如果节点不存在，则返回 NULL。
BinaryTreeBasic::TreeNode* BinaryTreeBasic::searchBST(TreeNode* root, int val){
    if (root == NULL || root->val == val) return root;
            TreeNode* result = NULL;
            if (root->val > val) result = searchBST(root->left, val);
            if (root->val < val) result = searchBST(root->right, val);
            return result;
}
//迭代法：因为是有序树，所以搜索路径是一定的。所以不需要栈或队列来辅助搜索
BinaryTreeBasic::TreeNode* BinaryTreeBasic::searchBSTByIter(TreeNode* root, int val){
    while(root != NULL){
        if(root->val > val) root = root->left;
        else if(root->val < val) root = root->right;
        else return root;
    }
    return NULL;
}
//98 验证二叉搜索树
// 中序遍历下，输出的二叉搜索树节点的数值是有序序列; 验证二叉搜索树，就相当于变成了判断一个序列是不是递增的
//注意二叉搜索树中不能有重复元素。
void BinaryTreeBasic::traversal98ByRecurHelper(TreeNode* root){
    if(root == NULL) return;
    traversal98ByRecurHelper(root->left);
    vec.push_back(root->val);//将二叉搜索树转换为有序数组
    traversal98ByRecurHelper(root->right);
}
bool BinaryTreeBasic::isValidBST(TreeNode* root){
    vec.clear();// 不加这句在leetcode上也可以过，但最好加上
    traversal98ByRecurHelper(root);
    for(int i = 0; i < vec.size();i++){
        if(vec[i] <= vec[i - 1]) return false;//注意要小于等于，搜索树里不能有相同元素
    }
    return true;
}
//98 递归过程中直接判断是否有序
bool BinaryTreeBasic::isValidBSTByRecur98(TreeNode* root){
    if(root == NULL) return true;
    bool left = isValidBSTByRecur98(root->left);
    
    if(pre != NULL && pre->val >= root->val) return false;//前一个节点 <= 后一个节点
    pre = root;//记录前一个节点
    
    bool right = isValidBSTByRecur98(root->right);
    return left && right;
}
//迭代法
bool BinaryTreeBasic::isValidBSTByIter98(TreeNode* root){
    stack<TreeNode*> st;
    TreeNode* cur = root;
    TreeNode* pre = NULL; // 记录前一个节点
    while (cur != NULL || !st.empty()) {
                if (cur != NULL) {
                    st.push(cur);
                    cur = cur->left;                // 左
                } else {
                    cur = st.top();                 // 中
                    st.pop();
                    if (pre != NULL && cur->val <= pre->val)
                    return false;
                    pre = cur; //保存前一个访问的结点

                    cur = cur->right;               // 右
                }
            }
            return true;
}
//530 给你一棵所有节点为非负值的二叉搜索树，请你计算树中任意两节点的差的绝对值的最小值。
//解法类似于98
//递归法：可以利用中序遍历转换为有序数列，再找绝对差；也可以在递归过程中找最小绝对差，改动代码类似于迭代法
//迭代法：
int BinaryTreeBasic::getMinimumDifference(TreeNode* root){
    stack<TreeNode*> st;
    TreeNode* cur = root;
    TreeNode* pre = NULL; // 记录前一个节点
    int result = INT_MAX;
    while (cur != NULL || !st.empty()) {
                if (cur != NULL) {
                    st.push(cur);
                    cur = cur->left;                // 左
                } else {
                    cur = st.top();                 // 中
                    st.pop();
                    if (pre != NULL)
                    {
                        result = min( result, cur->val - pre->val);//取得最小绝对差
                    }
                    pre = cur; //保存前一个访问的结点

                    cur = cur->right;               // 右
                }
            }
            return true;
}
//501 找出现频率最高的
// 如果众数超过1个，不需考虑输出顺序
//1.对于普通二叉树，先利用前序遍历统计到map中，然后排序，最后取出众数集合
void BinaryTreeBasic::searchBST501(TreeNode* cur, unordered_map<int, int>& map) { // 前序遍历
    if (cur == NULL) return ;
    map[cur->val]++; // 统计元素频率
    searchBST501(cur->left, map);
    searchBST501(cur->right, map);
    return ;
}
bool BinaryTreeBasic::cmp501 (const pair<int, int>& a, const pair<int, int>& b) {
    return a.second > b.second;
}
vector<int> BinaryTreeBasic::findModeForNormalTree(TreeNode* root){
    unordered_map<int, int> map; // key:元素，value:出现频率
    vector<int> result;
    if (root == NULL) return result;
    
    searchBST501(root, map);//遍历节点，并放入map
    
    vector<pair<int, int>> vec(map.begin(), map.end());
    
    sort(vec.begin(), vec.end(), cmp501); // 给频率排个序
    
    result.push_back(vec[0].first);
    for (int i = 1; i < vec.size(); i++) {
        // 取最高的放到result数组中
        if (vec[i].second == vec[0].second) result.push_back(vec[i].first);//取前几个频率相同的众数集合
        else break;
    }
    return result;
}
//对于二叉搜索树
vector<int> BinaryTreeBasic::findModeForBST501(TreeNode* root) {
        count = 0;
        maxCount = 0;
        pre = NULL; // 记录前一个节点
        vec.clear();

        searchBST501_2(root);
        return vec;
    }
void BinaryTreeBasic::searchBST501_2(TreeNode* cur){
    if (cur == NULL) return ;

    searchBST501_2(cur->left);       // 左
                                        // 中
            if (pre == NULL) { // 第一个节点
                count = 1;
            } else if (pre->val == cur->val) { // 与前一个节点数值相同
                count++;
            } else { // 与前一个节点数值不同
                count = 1;
            }
            pre = cur; // 更新上一个节点

            if (count == maxCount) { // 如果和最大值相同，放进result中
                vec.push_back(cur->val);
            }

            if (count > maxCount) { // 如果计数大于最大值频率
                maxCount = count;   // 更新最大频率
                vec.clear();     // 很关键的一步，不要忘记清空result，之前result里的元素都失效了
                vec.push_back(cur->val);
            }

    searchBST501_2(cur->right);      // 右
            return ;
        }

vector<int> BinaryTreeBasic::findModeByIter501(TreeNode* root){
    stack<TreeNode*> st;
            TreeNode* cur = root;
            TreeNode* pre = NULL;
            int maxCount = 0; // 最大频率
            int count = 0; // 统计频率
            vector<int> result;
            while (cur != NULL || !st.empty()) {
                if (cur != NULL) { // 指针来访问节点，访问到最底层
                    st.push(cur); // 将访问的节点放进栈
                    cur = cur->left;                // 左
                } else {
                    cur = st.top();
                    st.pop();                       // 中
                    if (pre == NULL) { // 第一个节点
                        count = 1;
                    } else if (pre->val == cur->val) { // 与前一个节点数值相同
                        count++;
                    } else { // 与前一个节点数值不同
                        count = 1;
                    }
                    if (count == maxCount) { // 如果和最大值相同，放进result中
                        result.push_back(cur->val);
                    }

                    if (count > maxCount) { // 如果计数大于最大值频率
                        maxCount = count;   // 更新最大频率
                        result.clear();     // 很关键的一步，不要忘记清空result，之前result里的元素都失效了
                        result.push_back(cur->val);
                    }
                    pre = cur;
                    cur = cur->right;               // 右
                }
            }
            return result;
}
//236 找最近公共祖先：节点值唯一，p,q为不同节点
//使用回溯，后序遍历：处理逻辑在处理中节点时
BinaryTreeBasic::TreeNode* BinaryTreeBasic::lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q){
    if (root == q || root == p || root == NULL) return root;//找到p或q，则返回该节点
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    if (left != NULL && right != NULL) return root; //左右子树返回都不为空，说明左右子树包含p,q;所以该节点是最近祖先
    if (left == NULL) return right;//如果左右子树有一个为空，则向上返回不为空的返回值，只有不为空的那一侧存在p或q
    return left;
}
//235 二叉搜索树： 找最近公共祖先
// 因为有序，所以如果第一次发现cur节点在区间[p,q]中，那么它就是最近祖先
BinaryTreeBasic::TreeNode* BinaryTreeBasic::lowestCommonAncestorForBST(TreeNode* root, TreeNode* p, TreeNode* q){
    if(root->val > p->val && root->val > q->val){
        return lowestCommonAncestorForBST(root->left, p, q);//如果节点值比p,q节点值都大，则在左侧继续找；找到就返回
    }else if(root->val < p->val && root->val < q->val){
        return lowestCommonAncestorForBST(root->right, p, q);
    }else
        return root;//如果第一次发现cur节点在区间[p,q]中，那么它就是最近祖先
    
}
//迭代法
BinaryTreeBasic::TreeNode* BinaryTreeBasic::lowestCommonAncestorForBSTByIter235(TreeNode* root, TreeNode* p, TreeNode* q){
    while(root){
        if(root->val > p->val && root->val > q->val){
            root = root->left;
        }else if(root->val < p->val && root->val < q->val){
            root = root->right;
        }else return root;
    }
    return NULL;
}
//701 给定二叉搜索树（BST）的根节点和要插入树中的值，将值插入二叉搜索树;返回插入后二叉搜索树的根节点。 输入数据保证，新值和原始二叉搜索树中的任意节点值都不同。
// 可能有多种插入方式：在原树上插入，也可以重新构造新的树结构
BinaryTreeBasic::TreeNode* BinaryTreeBasic::insertIntoBSTByRecur701(TreeNode* root, int val){
    if(root == NULL){
        TreeNode* node = new TreeNode(val);
        return node;
    }
    
    if(root->val > val) root->left = insertIntoBSTByRecur701(root->left, val);//添加的新节点返回给root->left/right接住，即完成添加
    if(root->val < val) root->right = insertIntoBSTByRecur701(root->right, val);
    return root;
}
//迭代法
BinaryTreeBasic::TreeNode* BinaryTreeBasic::insertIntoBSTByIter701(TreeNode* root, int val){
    if(root == NULL){
        TreeNode* node = new TreeNode(val);
        return node;
    }
    
    TreeNode* cur = root;
    TreeNode* parent = root;//需要记录父节点来插入
    while(cur != NULL){
        parent = cur;
        if(cur->val > val) cur = cur->left;
        else cur = cur->right;
    }
    //插入操作，需要用父节点
    TreeNode* node = new TreeNode(val);
    if(val < parent->val) parent->left = node;
    else parent->right = node;
    return root;
}
//669 修剪二叉搜索树，即将不符合条件的值删除
BinaryTreeBasic::TreeNode* BinaryTreeBasic::trimBST(TreeNode* root, int low, int high){
    if(root == nullptr) return nullptr;//空指针不处理
    //需要修剪时，在指向符合条件的搜索区间继续
    if(root->val < low) return trimBST(root->right,low,high);//修剪操作
    if(root->val > high) return trimBST(root->left,low,high);
    //符合条件时，继续
    root->left = trimBST(root->left,low,high);//赋值操作，接住修剪后的子树
    root->right = trimBST(root->right,low,high);
    return root;
}
//迭代法
BinaryTreeBasic::TreeNode* BinaryTreeBasic::trimBSTByIter(TreeNode* root, int low, int high){
    if(!root) return nullptr;
    
    // 处理头结点，让root移动到[L, R] 范围内，注意是左闭右闭
            while (root != nullptr && (root->val < low || root->val > high)) {
                if (root->val < low) root = root->right; // 小于L往右走
                else root = root->left; // 大于R往左走
            }
    TreeNode *cur = root;
    
    // 此时root已经在[L, R] 范围内，处理左孩子元素小于L的情况
            while (cur != nullptr) {
                while (cur->left && cur->left->val < low) {
                    cur->left = cur->left->right;
                }
                cur = cur->left;
            }
            cur = root;
    
    // 此时root已经在[L, R] 范围内，处理右孩子大于R的情况
            while (cur != nullptr) {
                while (cur->right && cur->right->val > high) {
                    cur->right = cur->right->left;
                }
                cur = cur->right;
            }
            return root;
}
//108 将一个按照升序排列的有序数组，转换为一棵高度平衡二叉搜索树
// 一个高度平衡二叉树是指一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1
// 本质就是寻找分割点，分割点作为当前节点，然后递归左区间和右区间
// 取数组中间节点为分割点，如果是偶数个数，取哪一个都行，将会构成不同的平衡二叉搜索树；答案不唯一
BinaryTreeBasic::TreeNode* BinaryTreeBasic::traversalHelper108(vector<int>& nums, int left, int right){
    if(left > right) return nullptr;
    int mid = left + ((right - left) / 2);//如果是偶数个节点，取区间中部左侧的值
    TreeNode* root = new TreeNode(nums[mid]);
    root->left = traversalHelper108(nums, left, mid-1);
    root->right = traversalHelper108(nums, mid + 1, right);
    return root;
}
BinaryTreeBasic::TreeNode* BinaryTreeBasic::sortedArrayToBST(vector<int>& nums){
    TreeNode* root = traversalHelper108(nums, 0, static_cast<int>(nums.size()-1));;//左闭右闭
    return root;
}
BinaryTreeBasic::TreeNode* BinaryTreeBasic::sortedArrayToBSTByIter(vector<int>& nums){
    if(static_cast<int>(nums.size()) == 0) return nullptr;
    
    TreeNode* root = new TreeNode(0);   // 初始根节点
            queue<TreeNode*> nodeQue;           // 放遍历的节点
            queue<int> leftQue;                 // 保存左区间下标
            queue<int> rightQue;                // 保存右区间下标
            nodeQue.push(root);                 // 根节点入队列
            leftQue.push(0);                    // 0为左区间下标初始位置
            rightQue.push(static_cast<int>(nums.size()) - 1);     // nums.size() - 1为右区间下标初始位置

            while (!nodeQue.empty()) {
                TreeNode* curNode = nodeQue.front();
                nodeQue.pop();
                int left = leftQue.front(); leftQue.pop();
                int right = rightQue.front(); rightQue.pop();
                int mid = left + ((right - left) / 2);

                curNode->val = nums[mid];       // 将mid对应的元素给中间节点

                if (left <= mid - 1) {          // 处理左区间
                    curNode->left = new TreeNode(0);
                    nodeQue.push(curNode->left);
                    leftQue.push(left);
                    rightQue.push(mid - 1);
                }

                if (right >= mid + 1) {         // 处理右区间
                    curNode->right = new TreeNode(0);
                    nodeQue.push(curNode->right);
                    leftQue.push(mid + 1);
                    rightQue.push(right);
                }
            }
            return root;
}
