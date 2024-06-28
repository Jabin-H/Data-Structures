#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#define MaxSize 1000
int arr[MaxSize];
int BST[MaxSize];

void sortArray(int *arr, int start, int end)
{
    if (start >= end)
        return;
    int pivot = arr[start];
    int i = start, j = end;
    while (i < j)
    {
        while (arr[j] > pivot)
            j--;
        swap(arr[j], pivot);
        while (arr[i] < pivot)
            i++;
        swap(arr[i], pivot);
    }
    sortArray(arr, start, i - 1);
    sortArray(arr, i + 1, end);
}

// 计算n个结点的完全搜索树的左子树的结点个数
int GetLeftSize(int n)
{
    int h = log(n + 1) / log(2);    // 完全搜索树的层数
    int botNum = n - pow(2, h) + 1; // 最底层的结点个数
    int x = botNum < pow(2, h - 1) ? botNum : pow(2, h - 1);
    int leftSize = pow(2, h - 1) - 1 + x; // 左子树的结点个数
    return leftSize;
}

void FillSeq(int start, int end, int root)
{
    int n = end - start + 1;
    if (!n)
        return;
    int leftSize = GetLeftSize(n);
    BST[root] = arr[start + leftSize]; // root为根节点在层序遍历BST中的位置
    int leftRoot = 2 * root + 1;       // 左儿子结点在层序遍历BST中的位置
    int rightRoot = leftRoot + 1;
    FillSeq(start, start + leftSize - 1, leftRoot);
    FillSeq(start + leftSize + 1, end, rightRoot);
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    sortArray(arr, 0, n - 1);
    FillSeq(0, n - 1, 0);
    for (int i = 0; i < n; i++)
    {
        if (i)
            cout << " ";
        cout << BST[i];
    }
    return 0;
}