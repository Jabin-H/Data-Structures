#include <iostream>
#include <algorithm>
using namespace std;

#define MaxSize 100005

int main()
{
    int Data[MaxSize];
    int Next[MaxSize];
    int List[MaxSize];

    int FirstAdd, N, K;
    cin >> FirstAdd >> N >> K;

    for (int i = 0; i < N; i++)
    {
        int tempAddress, tempData, tempNext;
        cin >> tempAddress >> tempData >> tempNext;
        Data[tempAddress] = tempData;
        Next[tempAddress] = tempNext;
    }

    int num = 0; // 统计有效节点的个数
    int tempAddress = FirstAdd;
    while (tempAddress != -1)
    {
        List[num] = tempAddress;
        num++;
        tempAddress = Next[tempAddress];
    }

    // 反转链表
    int size = num - num % K;
    for (int i = 0; i < size; i += K)
    {
        int low = i, high = i + K - 1;
        while (low < high)
        {
            swap(List[low], List[high]);
            low++, high--;
        }
    }

    // 打印结果
    for (int i = 0; i < num - 1; i++)
        printf("%05d %d %05d\n", List[i], Data[List[i]], List[i + 1]);
    printf("%05d %d -1\n", List[num - 1], Data[List[num - 1]]);

    return 0;
}