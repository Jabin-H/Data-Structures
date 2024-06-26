#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// 记录树T各节点的左右子树
void SetTree(char **T, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (T[i][1] != '-')
            T[i][1] = T[T[i][1] - '0'][0];
        if (T[i][2] != '-')
            T[i][2] = T[T[i][2] - '0'][0];

        if (T[i][1] > T[i][2])
            swap(T[i][1], T[i][2]);
    }
}

// 将树T的按第一列升序排序
void SortTree(char **T, int begin, int end)
{
    if (begin >= end)
        return;

    int i = begin, j = end, pivot = begin;
    while (i < j)
    {
        while (i < j && T[j][0] > T[pivot][0])
            j--;
        swap(T[pivot], T[j]);
        pivot = j;
        while (i < j && T[i][0] < T[pivot][0])
            i++;
        swap(T[pivot], T[i]);
        pivot = i;
    }

    SortTree(T, begin, i - 1);
    SortTree(T, i + 1, end);
}

int main()
{
    int n1;
    cin >> n1;
    char **T1 = new char *[n1]; // 树T1第一列为节点名称，第二三列为左右子树名称
    for (int i = 0; i < n1; i++)
    {
        T1[i] = new char[3];
        cin >> T1[i][0] >> T1[i][1] >> T1[i][2];
    }
    SetTree(T1, n1);
    SortTree(T1, 0, n1 - 1);

    int n2;
    cin >> n2;
    char **T2 = new char *[n2];
    for (int i = 0; i < n2; i++)
    {
        T2[i] = new char[3];
        cin >> T2[i][0] >> T2[i][1] >> T2[i][2];
    }
    SetTree(T2, n2);
    SortTree(T2, 0, n2 - 1);

    // 判断同构
    if (n1 != n2) // 节点数不相同
    {
        cout << "No" << endl;
        return 0;
    }

    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (T1[i][j] != T2[i][j])
            {
                cout << "No" << endl;
                return 0;
            }
        }
    }
    cout << "Yes" << endl;

    return 0;
}