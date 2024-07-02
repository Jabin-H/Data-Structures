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
    int cnt = 0;
    queue<int> que1, que2;
    visited[v] = true;
    que1.push(v);
    for (int i = 0; i < 6; i++)
    {
        if (!que1.empty())
        {
            while (!que1.empty())
            {
                v = que1.front();
                que1.pop();
                for (int w = 0; w < n; w++)
                    if (graph[v][w] && !visited[w])
                    {
                        visited[w] = true;
                        que2.push(w);
                        cnt++;
                    }
            }
        }
        else if (!que2.empty())
        {
            while (!que2.empty())
            {
                v = que2.front();
                que2.pop();
                for (int w = 0; w < n; w++)
                    if (graph[v][w] && !visited[w])
                    {
                        visited[w] = true;
                        que1.push(w);
                        cnt++;
                    }
            }
        }
    }
    return cnt;
}

// void BFS(int v)
// {
//     queue<int> que;
//     visited[v] = true;
//     que.push(v);
//     while (!que.empty())
//     {
//         v = que.front();
//         que.pop();
//         for (int w = 0; w < n; w++)
//             if (graph[v][w] && !visited[w])
//             {
//                 visited[w] = true;
//                 que.push(w);
//             }
//     }
// }

void DFS(int v)
{
    visited[v] = true;
    for (int w = 0; w < n; w++)
        if (graph[v][w] && !visited[w])
        {
            visited[w] = true;
            DFS(w);
        }
}

int main()
{
    cin >> n >> m;
    buildGraph();
    for (int i = 0; i < n; i++)
    {
        initVisited();
        int cnt = BFS(i) + 1;
        double percent = (double)cnt / (double)n * 100;
        cout << fixed << setprecision(2) << i + 1 << ": " << percent << "%" << endl;
        // printf("%d: %.2f%\n", i + 1, percent);
    }
    return 0;
}