#include <iostream>
#include <queue>
#include <climits>
#include <stack>
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

vector<int> dfs_preorder(TreeNode* root) {
    vector<int> res;
    if (root == nullptr) return res;

    stack<TreeNode*> st;

    st.push(root);

    while (!st.empty()) {
        TreeNode* node = st.top();
        st.pop();

        res.push_back(node->val);

        if (node->right) { // direita primeiro porque se empilhar direita primeiro a esquedra SAI PRIMEIRO
            st.push(node->right);
        }
        if (node->left) {
            st.push(node->left);
        }
    }
    return res;
}

vector<int> dfs_inorder(TreeNode* root) {
    vector<int> res;
    if (root == nullptr) return res;
    stack<TreeNode*> st;
    TreeNode* atual = root;

    while (atual || !st.empty()) {

        while (atual) { // vai empilhando sempre os mais a esquerda ate achar o final 
            st.push(atual);
            atual = atual->left;
        }
        // quando acha o final ele volta e procura na direita
        atual = st.top(); // se chegou no final pega o ultimo empilhado e popa
        st.pop();

        res.push_back(atual->val); // adiciona o node popado no vetor

        atual = atual->right;

    }

    return res;
}   