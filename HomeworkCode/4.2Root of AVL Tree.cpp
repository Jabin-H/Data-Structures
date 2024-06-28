#include <iostream>
using namespace std;

typedef struct AVLNode *AVLTree;
struct AVLNode // 定义AVL树结点
{
    int data;
    AVLTree left, right;
    int height; // 以该结点为根结点的树的高度
};

int max(int a, int b)
{
    return a > b ? a : b;
}

// 计算树的高度
int getHeight(AVLTree root)
{
    if (!root)
        return 0;
    return 1 + max(getHeight(root->left), getHeight(root->right));
}

// 计算结点的平衡因子
int getBalanceFactor(AVLTree root)
{
    if (!root)
        return 0;
    return getHeight(root->left) - getHeight(root->right);
}

AVLTree singleRightRotation(AVLTree a)
{
    AVLTree b = a->left;
    a->left = b->right;
    b->right = a;
    // 更新结点a和b的高度
    a->height = max(getHeight(a->left), getHeight(a->right)) + 1;
    b->height = max(getHeight(b->left), a->height) + 1;
    return b;
}

AVLTree singleLeftRotation(AVLTree a)
{
    AVLTree b = a->right;
    a->right = b->left;
    b->left = a;
    // 更新结点高度
    a->height = max(getHeight(a->left), getHeight(a->right)) + 1;
    b->height = max(a->height, getHeight(b->right));
    return b;
}

AVLTree leftRightRotation(AVLTree a)
{
    a->left = singleLeftRotation(a->left);
    return singleRightRotation(a);
}

AVLTree rightLeftRotation(AVLTree a)
{
    a->right = singleRightRotation(a->right);
    return singleLeftRotation(a);
}

// 创建新结点
AVLTree createNode(int val)
{
    AVLTree node = new AVLNode;
    node->data = val;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

AVLTree insertNode(AVLTree root, int val)
{
    // 1. 在叶节点上插入新值
    if (!root)
        return createNode(val);
    if (val < root->data)
        root->left = insertNode(root->left, val);
    else if (val > root->data)
        root->right = insertNode(root->right, val);
    else
        return root;

    // 2. 更新树的高度
    root->height = getHeight(root);

    // 3. 计算平衡因子，检验需要调整
    int bf = getBalanceFactor(root);

    if (bf > 1 && val < root->left->data) // LL型不平衡
        return singleRightRotation(root);
    if (bf < -1 && val > root->right->data) // RR型不平衡
        return singleLeftRotation(root);
    if (bf > 1 && val > root->left->data) // LR型不平衡
        return leftRightRotation(root);
    if (bf < -1 && val < root->right->data) // RL型不平衡
        return rightLeftRotation(root);

    return root;
}

int main()
{
    int n, val;
    AVLTree root = NULL;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> val;
        root = insertNode(root, val);
    }
    cout << root->data << endl;
    return 0;
}