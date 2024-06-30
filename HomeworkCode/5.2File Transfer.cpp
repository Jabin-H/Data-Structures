#include <iostream>
using namespace std;

int find(int s[], int val)
{
    // int i = val - 1;
    //  while (s[i] >= 0)
    //      i = s[i];
    if (s[val] < 0)
        return val;
    else
        return s[val] = find(s, s[val]); // 路径压缩
}

void unionSet(int s[], int val1, int val2)
{
    int root1 = find(s, val1);
    int root2 = find(s, val2);
    if (root1 != root2) // 当两个元素不属于同一集合时，按规模合并集合
    {
        if (s[root1] <= s[root2])
        {
            s[root1] += s[root2];
            s[root2] = root1;
        }
        else
        {
            s[root2] += s[root1];
            s[root1] = root2;
        }
    }
}

void checkNetwork(int s[], int n)
{
    int cnt = 0;
    for (int i = 0; i < n; i++)
        if (s[i] < 0)
            cnt++;
    if (cnt == 1)
        cout << "The network is connected." << endl;
    else
        cout << "There are " << cnt << " components." << endl;
}

int main()
{
    int n, val1, val2, cnt = 0;
    cin >> n;
    // 初始化集合
    int *s = new int[n];
    for (int i = 0; i < n; i++)
        s[i] = -1;
    char opt;
    cin >> opt;
    while (opt != 'S')
    {
        cin >> val1 >> val2;
        if (opt == 'I')
        {
            unionSet(s, val1 - 1, val2 - 1);
        }
        else if (opt == 'C')
        {
            if (find(s, val1 - 1) != find(s, val2 - 1))
                cout << "no" << endl;
            else
                cout << "yes" << endl;
        }
        cin >> opt;
    }
    checkNetwork(s, n);
    return 0;
}