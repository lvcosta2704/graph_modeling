#include <iostream>
#include <queue>
#include <climits>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) {
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

    return root;
}

vector<int> dfs_postorder(TreeNode* root, vector<int>& arr) {
    if (!root) return arr;
    dfs_postorder(root->left, arr);
    dfs_postorder(root->right, arr);
    arr.push_back(root->val);

    return arr;
}

vector<int> dfs_preorder(TreeNode* root, vector<int>& arr) {
    if (!root) return arr;
	arr.push_back(root->val);
    dfs_preorder(root->left, arr);
    dfs_preorder(root->right, arr);

    return arr;
}

vector<int> dfs_inorder(TreeNode* root, vector<int>& arr) {
	if (!root) return arr;
	dfs_inorder(root->left, arr);
	arr.push_back(root->val);
	dfs_inorder(root->right, arr);

	return arr;
}

bool valid(TreeNode* root, long min, long max) {
	if (root == nullptr) return true;
	if (root->val <= min || root->val >= max ) return false;

	return valid(root->left, min, root->val) &&
	valid(root->right, root->val, max);
}	
int main () {
    TreeNode* root;
    root = buildTree();
	long min = INT_MIN;
	long max = INT_MAX;
    
}
