#include <iostream>
#include <queue>
#include <iomanip>
using namespace std;

#define MaxVertexNum 1000
int graph[MaxVertexNum][MaxVertexNum] = {0};
bool visited[MaxVertexNum];
int n, m;

void buildGraph()
{
    int v, w;
    for (int i = 0; i < m; i++)
    {
        cin >> v >> w;
        graph[v - 1][w - 1] = graph[w - 1][v - 1] = 1;
    }
}

void initVisited()
{
    for (int i = 0; i < n; i++)
        visited[i] = false;
}

int BFS(int v)
{
    queue<int> que;
    visited[v] = true;
    que.push(v);
    int cnt = 1, level = 0, last = v, tail;
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
            level++;
            last = tail;
        }
        if (level == 6)
            break;
    }
    return cnt;
}

int main()
{
    cin >> n >> m;
    buildGraph();
    for (int i = 0; i < n; i++)
    {
        initVisited();
        int cnt = BFS(i);
        double percent = (double)cnt / (double)n * 100;
        cout << fixed << setprecision(2) << i + 1 << ": " << percent << "%" << endl;
        // printf("%d: %.2f%\n", i + 1, percent);
    }
    return 0;
}