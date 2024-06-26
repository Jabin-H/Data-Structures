#include <iostream>
using namespace std;
#define MaxSize 10
#define Null -1

// 静态链表存储二叉树
struct TreeNode
{
    char data;
    int left;
    int right;
} T1[MaxSize], T2[MaxSize];

// 创建树，返回根节点
int BuildTree(struct TreeNode T[])
{
    int n, root = 0;
    char left, right;

    cin >> n;
    if (!n)
        return Null;
    for (int i = 0; i < n; i++)
    {
        cin >> T[i].data >> left >> right;

        if (left != '-')
        {
            T[i].left = left - '0';
            root -= T[i].left;
        }
        else
            T[i].left = Null;

        if (right != '-')
        {
            T[i].right = right - '0';
            root -= T[i].right;
        }
        else
            T[i].right = Null;

        root += i;
    }

    return root;
}

// 判断同构
int Isomorphic(int root1, int root2)
{
    if (root1 == Null && root2 == Null) // 两者都为空
        return 1;
    if ((root1 == Null && root2 != Null) || (root1 != Null && root2 == Null)) // 一个为空，另一个不空
        return 0;
    if (T1[root1].data != T2[root2].data) // 树根值不同
        return 0;
    // 判断左右子树
    // if 左子树均不为空且值相等
    if ((T1[root1].left != Null && T2[root2].left != Null) && (T1[T1[root1].left].data == T2[T2[root2].left].data))
        return Isomorphic(T1[root1].left, T2[root2].left) && Isomorphic(T1[root1].right, T2[root2].right);
    else
        return Isomorphic(T1[root1].right, T2[root2].left) && Isomorphic(T1[root1].left, T2[root2].right);
}

int main()
{
    int root1, root2; // 树的根节点
    root1 = BuildTree(T1);
    root2 = BuildTree(T2);

    if (Isomorphic(root1, root2))
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    return 0;
}