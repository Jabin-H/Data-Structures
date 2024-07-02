#include <iostream>
#include <queue>
using namespace std;

#define MaxVertexNum 10
int G[MaxVertexNum][MaxVertexNum] = {0};
bool visited[MaxVertexNum];
int n, e; // 结点数，边数

void initVisited()
{
    for (int i = 0; i < n; i++)
        visited[i] = false;
}

// 建图
void buildGraph()
{
    cin >> n >> e;
    int v, w;
    for (int i = 0; i < e; i++)
    {
        cin >> v >> w;
        G[v][w] = G[w][v] = 1;
    }
}

void DFS(int v)
{
    cout << v << " ";
    visited[v] = true;
    for (int w = 0; w < n; w++)
        if (G[v][w] == 1 && !visited[w])
            DFS(w);
}

void BFS(int v)
{
    queue<int> que;
    visited[v] = true;
    que.push(v);
    while (!que.empty())
    {
        v = que.front();
        que.pop();
        cout << v << " ";
        for (int w = 0; w < n; w++)
            if (G[v][w] == 1 && !visited[w])
            {
                visited[w] = true;
                que.push(w);
            }
    }
}

void listComponents(void (*searchFunc)(int))
{
    for (int v = 0; v < n; v++)
        if (!visited[v])
        {
            cout << "{ ";
            searchFunc(v);
            cout << "}" << endl;
        }
}

int main()
{
    buildGraph();
    initVisited();
    listComponents(DFS);
    initVisited();
    listComponents(BFS);
    return 0;
}