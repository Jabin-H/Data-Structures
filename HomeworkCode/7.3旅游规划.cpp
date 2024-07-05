#include <iostream>
using namespace std;

#define MaxVertexNum 500
#define INF 10000
int n, m, source, destination;
int graph[MaxVertexNum][MaxVertexNum];
int costs[MaxVertexNum][MaxVertexNum];
int dist[MaxVertexNum];
int path[MaxVertexNum];
int minCost[MaxVertexNum];
bool collected[MaxVertexNum];

void buildGraph()
{
    cin >> n >> m >> source >> destination;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    int s, d, len, cost;
    for (int i = 0; i < m; i++)
    {
        cin >> s >> d >> len >> cost;
        graph[s][d] = graph[d][s] = len;
        costs[s][d] = costs[d][s] = cost;
    }
}

void init(int source)
{
    for (int i = 0; i < n; i++)
    {
        dist[i] = INF;
        path[i] = -1;
        minCost[i] = INF;
    }
    dist[source] = 0;
    minCost[source] = 0;
}

int findMin()
{
    int v = -1, minD = INF;
    for (int i = 0; i < n; i++)
        if (!collected[i] && dist[i] < minD)
        {
            v = i;
            minD = dist[i];
        }
    return v;
}

void dijkstra(int s)
{
    init(s);
    while (true)
    {
        int v = findMin();
        if (v == -1)
            break;
        collected[v] = true;
        for (int w = 0; w < n; w++)
            if (graph[v][w] && !collected[w])
            {
                if ((dist[v] + graph[v][w] < dist[w]) || (dist[v] + graph[v][w] == dist[w] && minCost[w] > minCost[v] + costs[v][w]))
                {
                    dist[w] = dist[v] + graph[v][w];
                    path[w] = v;
                    minCost[w] = minCost[v] + costs[v][w];
                }
            }
    }
}

void calCost(int s, int d)
{
    dijkstra(s);
    cout << dist[d] << " " << minCost[d];
}

int main()
{
    buildGraph();
    calCost(source, destination);
    return 0;
}