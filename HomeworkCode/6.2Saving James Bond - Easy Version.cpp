#include <iostream>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;

#define MaxVertexNum 100
int n;
double jump;
int x[MaxVertexNum + 1], y[MaxVertexNum + 1];        // 记录结点坐标
int graph[MaxVertexNum + 1][MaxVertexNum + 1] = {0}; // 图
bool visited[MaxVertexNum + 1];
int minZero = 100, minLand = 100;

// 计算结点v和w之间的距离
double distance(int v, int w)
{
    return sqrt(pow((x[v] - x[w]), 2) + pow((y[v] - y[w]), 2));
}

void initialization()
{
    cin >> n >> jump;
    for (int i = 1; i <= n; i++)
    {
        cin >> x[i] >> y[i];
        visited[i] = false;
    }
    x[0] = y[0] = 0;
    visited[0] = false;
}

void buildGraph()
{
    double d;
    for (int i = 1; i <= n; i++)
    {
        d = distance(0, i);
        if (d - 7.5 <= jump)
            graph[0][i] = graph[i][0] = 1;
    }
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
        {
            d = distance(i, j);
            if (d <= jump)
                graph[i][j] = graph[j][i] = 1;
        }
}

bool isSafe(int v)
{
    double distance = min(50 - abs(x[v]), 50 - abs(y[v]));
    return distance <= jump;
}

int DFS(int v)
{
    int answer = 0;
    visited[v] = true;
    if (isSafe(v))
        answer = 1;
    else
    {
        for (int w = 0; w <= n; w++)
            if (graph[v][w] && !visited[w])
            {
                answer = DFS(w);
                if (answer)
                    break;
            }
    }
    return answer;
}

int BFS(int v)
{
    int answer = 0;
    queue<int> que;
    visited[v] = true;
    que.push(v);
    while (!que.empty())
    {
        v = que.front();
        if (isSafe(v))
        {
            answer = 1;
            break;
        }
        que.pop();
        for (int w = 0; w <= n; w++)
            if (graph[v][w] == 1 && !visited[w])
            {
                visited[w] = true;
                que.push(w);
            }
    }
    return answer;
}

int main()
{
    initialization();
    buildGraph();
    int answer = BFS(0);
    // int answer = DFS(0);
    if (answer)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
    return 0;
}