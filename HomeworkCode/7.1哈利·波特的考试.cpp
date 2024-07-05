#include <iostream>
using namespace std;

#define MaxVertexNum 100
#define INF 10000
int graph[MaxVertexNum][MaxVertexNum];
bool collected[MaxVertexNum];
int n, m;

void buildGraph()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = INF;
        }
    }

    int v, w, weight;
    for (int i = 0; i < m; i++)
    {
        cin >> v >> w >> weight;
        graph[v - 1][w - 1] = graph[w - 1][v - 1] = weight;
    }
}

void floyd()
{
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (graph[i][j] > graph[i][k] + graph[k][j])
                    graph[i][j] = graph[i][k] + graph[k][j];
}

void chooseAnimal()
{
    floyd();
    int index = -1, minMaxLength = INF;
    for (int i = 0; i < n; i++)
    {
        int maxLength = 0;
        for (int j = 0; j < n; j++) // 找每行的最大值
            if (maxLength < graph[i][j])
                maxLength = graph[i][j];

        if (maxLength == INF) // 返回INF，表示图不连通
        {
            cout << 0 << endl;
            return;
        }
        if (minMaxLength > maxLength) // 找最大值的最小值
        {
            minMaxLength = maxLength;
            index = i + 1;
        }
    }
    cout << index << " " << minMaxLength << endl;
}

int main()
{
    buildGraph();
    chooseAnimal();
    return 0;
}