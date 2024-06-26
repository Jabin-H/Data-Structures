#include <iostream>
#include <queue>
#define MaxSize 10
#define null -1
using namespace std;

struct TreeNode
{
    int data;
    int left;
    int right;

} T[MaxSize];

// 创建树，返回根节点
int BuildTree()
{
    int n;
    cin >> n;

    int root = 0;
    char left, right;
    for (int i = 0; i < n; i++)
    {
        T[i].data = i;
        cin >> left >> right;
        if (left == '-')
            T[i].left = -1;
        else
        {
            T[i].left = left - '0';
            root -= T[i].left;
        }
        if (right == '-')
            T[i].right = -1;
        else
        {
            T[i].right = right - '0';
            root -= T[i].right;
        }
        root += i;
    }

    return root;
}

// 层序遍历，按要求输出叶子节点
void LevelOrderTraversal(int root)
{
    queue<int> que;
    que.push(root);

    int flag = 0; // 控制空格
    while (!que.empty())
    {
        root = que.front();
        que.pop();
        if (T[root].left == -1 && T[root].right == -1)
        {
            if (!flag)
            {
                cout << T[root].data;
                flag = 1;
            }
            else
                cout << " " << T[root].data;
        }
        else
        {
            if (T[root].left != -1)
                que.push(T[root].left);
            if (T[root].right != -1)
                que.push(T[root].right);
        }
    }
}

int main()
{
    int root = BuildTree();    // 根节点
    LevelOrderTraversal(root); // 层序遍历
    return 0;
}