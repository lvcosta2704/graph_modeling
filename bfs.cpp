#include <iostream>
#include <queue>
#include <climits>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) { // constructor
        val = x;
        left = nullptr;
        right = nullptr;
    }
};

TreeNode* buildTree() {
    TreeNode* root = new TreeNode(8);

    root->left = new TreeNode(3);
    root->right = new TreeNode(10);

    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(6);

    root->left->right->left = new TreeNode(4);
    root->left->right->right = new TreeNode(7);

    root->right->right = new TreeNode(14);
    root->right->right->left = new TreeNode(13);

    root->right->right->right = new TreeNode(20);

    return root;
}
vector<int> bfs(TreeNode* root) {
        vector<int> res;
        if (root == nullptr) return res;

        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            
            res.push_back(node->val);

            if(node->left) {
                q.push(node->left);
            }
            
            if(node->right) {
                q.push(node->right);
            }
            
            
        } 
        return res;
}
int main () {
    TreeNode* root;
    root = buildTree();
    vector<int> arr;
    arr = bfs(root);

    for (int i : arr) {
        cout << i << " ";
    }


}
