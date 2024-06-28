#include <iostream>
using namespace std;

typedef struct TreeNode *Tree;
struct TreeNode
{
    int data;
    Tree left;
    Tree right;
    int flag; // 记录结点是否在序列中出现过
};

// 插入结点
Tree InsertTree(int val, Tree BST)
{
    if (!BST)
    {
        BST = new TreeNode;
        BST->data = val;
        BST->left = BST->right = NULL;
        BST->flag = 0;
    }
    else
    {
        if (val < BST->data)
            BST->left = InsertTree(val, BST->left);
        else
            BST->right = InsertTree(val, BST->right);
    }
    return BST;
}

// 利用插入创建树
Tree BuildTree(int n)
{
    Tree BST = NULL;
    int val;
    for (int i = 0; i < n; i++)
    {
        cin >> val;
        BST = InsertTree(val, BST);
    }
    return BST;
}

// 前序遍历，用于将flag置零
void ResetTree(Tree BST)
{
    if (!BST)
        return;
    BST->flag = 0;
    ResetTree(BST->left);
    ResetTree(BST->right);
}

bool CheckSeq(int val, Tree BST)
{
    if (val == BST->data)
    {
        BST->flag = 1;
        return true;
    }
    else if (BST->flag == 0)
        return false;
    else
    {
        if (val < BST->data)
            return CheckSeq(val, BST->left);
        else
            return CheckSeq(val, BST->right);
    }
}

// 检验序列是否合理
bool Judge(Tree BST, int n)
{
    bool flag = true;
    int val;
    for (int i = 0; i < n; i++)
    {
        cin >> val;
        if (flag && !CheckSeq(val, BST))
            flag = false;
    }
    if (flag)
        return true;
    else
        return false;
}

// 释放树的内存空间
void DeleteTree(Tree BST)
{
    if (BST->left)
        DeleteTree(BST->left);
    if (BST->right)
        DeleteTree(BST->right);
    delete BST;
}

int main()
{
    int n, l;
    cin >> n;
    while (n) // 当n非零时循环
    {
        cin >> l;
        Tree BST = BuildTree(n);
        for (int i = 0; i < l; i++)
        {
            ResetTree(BST);    // 将所有结点的flag置零
            if (Judge(BST, n)) // 判断序列是否合理
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
        }
        DeleteTree(BST);
        cin >> n;
    }
    return 0;
}