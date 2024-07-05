#include <iostream>
#include <cmath>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

#define MaxVertexNum 102
#define Infinity 105
const double diameter = 15;
int n, jumpD;
int x[MaxVertexNum], y[MaxVertexNum]; // 鳄鱼的坐标
int graph[MaxVertexNum][MaxVertexNum];
int dist[MaxVertexNum]; // 最短路径长度
int path[MaxVertexNum]; // 最短路径中的前一个结点

// 判断能否从原点跳到w
double firstJump(int v)
{
    double distance = sqrt(pow(x[v], 2) + pow(y[v], 2));
    return distance;
}

// 判断能否从v跳到w
bool canJump(int v, int w)
{
    double distance = sqrt(pow(x[v] - x[w], 2) + pow(y[v] - y[w], 2));
    return distance <= jumpD;
}

// 判断能否跳到岸上
bool isSafe(int v)
{
    double xx = 50 - abs(x[v]);
    double yy = 50 - abs(y[v]);
    double distance = xx <= yy ? xx : yy;
    return distance <= jumpD;
}

void buildGraph()
{
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            graph[i][j] = 0;

    cin >> n >> jumpD;
    for (int i = 1; i <= n; i++)
    {
        cin >> x[i] >> y[i];
        if (firstJump(i) <= jumpD + diameter / 2)
            graph[0][i] = graph[i][0] = 1;
    }
    x[0] = y[0] = 0;

    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (canJump(i, j))
                graph[i][j] = graph[j][i] = 1;
}

void initialization()
{
    for (int i = 0; i <= n; i++)
    {
        dist[i] = Infinity;
        path[i] = -1;
    }
}

bool comp(int v, int w)
{
    return firstJump(v) <= firstJump(w);
}

int unweighted(int s)
{
    initialization();
    int destination = -1;
    queue<int> que;
    dist[s] = 0;

    vector<int> vec;
    for (int v = 1; v <= n; v++)
        if (graph[0][v])
        {
            dist[v] = 1;
            path[v] = s;
            vec.push_back(v);
        }
    sort(vec.begin(), vec.end(), comp);
    for (int v = 0; v < vec.size(); v++)
        que.push(vec[v]);

    while (!que.empty())
    {
        s = que.front();
        que.pop();
        if (isSafe(s))
        {
            destination = s;
            break;
        }
        for (int v = 1; v <= n; v++)
            if (graph[s][v] && dist[v] == Infinity)
            {
                dist[v] = dist[s] + 1;
                path[v] = s;
                que.push(v);
            }
    }
    return destination;
}

void save007()
{
    if (jumpD > 50 - diameter / 2)
    {
        cout << 1 << endl;
        return;
    }

    stack<int> st;
    int v = unweighted(0);
    if (v != -1)
    {
        cout << dist[v] + 1 << endl;
        while (v)
        {
            st.push(v);
            v = path[v];
        }
        while (!st.empty())
        {
            v = st.top();
            st.pop();
            cout << x[v] << " " << y[v] << endl;
        }
    }
    else
    {
        cout << 0 << endl;
    }
}

int main()
{
    buildGraph();
    save007();
    return 0;
}