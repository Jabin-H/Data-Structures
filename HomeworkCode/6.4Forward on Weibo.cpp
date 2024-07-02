#include <iostream>
#include <queue>
using namespace std;

#define MaxUserNum 1000
int n, l;
int graph[MaxUserNum][MaxUserNum] = {0};
bool visited[MaxUserNum];
int m[MaxUserNum]; // 记录每个用户的关注数

// 建立有向图,边<v,w>表示用户w关注了用户v
void buildGraph()
{
    cin >> n >> l;
    int user;
    for (int i = 0; i < n; i++)
    {
        cin >> m[i];
        for (int j = 0; j < m[i]; j++)
        {
            cin >> user;
            graph[user - 1][i] = 1;
        }
    }
}

void initVisited()
{
    for (int i = 0; i < n; i++)
        visited[i] = false;
}

int BFS(int v)
{
    initVisited();
    queue<int> que;
    int cnt = 0, level = 0, last = v, tail;
    visited[v] = true;
    que.push(v);
    while (!que.empty())
    {
        v = que.front();
        que.pop();
        for (int w = 0; w < n; w++)
            if (graph[v][w] && !visited[w])
            {
                visited[w] = true;
                que.push(w);
                cnt++;
                tail = w;
            }
        if (v == last)
        {
            last = tail;
            level++;
        }
        if (level == l)
            break;
    }
    return cnt;
}

void foward()
{
    int num, userId;
    cin >> num;
    for (int i = 0; i < num; i++)
    {
        cin >> userId;
        cout << BFS(userId - 1) << endl;
    }
}

int main()
{
    buildGraph();
    foward();
    return 0;
}