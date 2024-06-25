#include <iostream>
#include <stack>
using namespace std;

#define MaxSize 1000

int main()
{
    int M, N, K;
    cin >> M >> N >> K;

    int arr[MaxSize];
    for (int i = 0; i < K; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> arr[j];
        }

        int num = 1, j = 0;
        stack<int> st;
        //输出的序列是从栈pop出来的，因此只看栈顶元素
        while (num <= N)
        {
            st.push(num);
            num++;
            //判断栈溢出
            if (st.size() > M)
                break;
            while (!st.empty() && st.top() == arr[j])
            {
                st.pop();
                j++;
            }
        }

        if (j == N)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }

    return 0;
}