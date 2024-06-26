#include <iostream>
#include <string>
#include <stack>
#define MaxSize 30
using namespace std;

int N;                 // 节点个数
int PreOrder[MaxSize]; // 前序遍历序列
int PreNum = 0;
int InOrder[MaxSize]; // 中序遍历序列
int InNum = 0;
// int PostOrder[MaxSize]; // 后续遍历序列
stack<int> PostStack;

// 记录前序遍历序列和中序遍历序列
void ReadData()
{
    cin >> N;

    string opt;
    int data;
    stack<int> st;
    for (int i = 0; i < N * 2; i++)
    {
        cin >> opt;
        if (opt == "Push")
        {
            cin >> data;
            PreOrder[PreNum++] = data;
            st.push(data);
        }
        else
        {
            InOrder[InNum++] = st.top();
            st.pop();
        }
    }
}

void getPostOrder(int startPre, int endPre, int startIn, int endIN)
{
    if (startPre > endPre || startIn > endIN)
        return;

    PostStack.push(PreOrder[startPre]);
    if (startPre == endPre)
        return;

    int root = PreOrder[startPre];
    int i = 0; // 左子树节点个数
    while (InOrder[startIn + i] != root)
        i++;

    // 右子树入栈
    getPostOrder(startPre + i + 1, endPre, startIn + i + 1, endIN);
    // 左子树入栈
    getPostOrder(startPre + 1, startPre + i, startIn, startIn + i - 1);
}

int main()
{
    ReadData();
    getPostOrder(0, N - 1, 0, N - 1);

    // 输出结果
    cout << PostStack.top();
    PostStack.pop();
    while (!PostStack.empty())
    {
        cout << " " << PostStack.top();
        PostStack.pop();
    }

    return 0;
}