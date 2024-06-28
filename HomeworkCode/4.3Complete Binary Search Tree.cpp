#include <iostream>
#include <algorithm>
using namespace std;

#define MaxSize 1005
int CBT[MaxSize], arr[MaxSize];
int n, k = 0;

// 二叉搜索树的中序遍历即为所有结点值按从小到大排列
void InOrder(int root)
{
    if (root > n)
        return;
    InOrder(root * 2); // 左子树
    CBT[root] = arr[k++];
    InOrder(root * 2 + 1); // 右子树
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    sort(arr, arr + n); // 排序后的arr为树的中序遍历
    InOrder(1);
    for (int i = 1; i <= n; i++)
    {
        if (i - 1)
            cout << " ";
        cout << CBT[i];
    }
    return 0;
}