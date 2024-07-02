#include <iostream>
#include <cmath>
using namespace std;

#define MaxVertexNum 100
int n;
double jumpD;
int x[MaxVertexNum], y[MaxVertexNum]; // 保存坐标
bool visited[MaxVertexNum];

void initialization()
{
    cin >> n >> jumpD;
    for (int i = 0; i < n; i++)
    {
        cin >> x[i] >> y[i];
        visited[i] = false;
    }
}

// 能否从岛上跳到结点v
bool firstJump(int v)
{
    double distance = sqrt(pow(x[v], 2) + pow(y[v], 2));
    double firstD = jumpD + 7.5;
    return distance <= firstD;
}

bool jump(int v, int w)
{
    double distance = sqrt(pow(x[v] - x[w], 2) + pow(y[v] - y[w], 2));
    return distance <= jumpD;
}

bool isSafe(int v)
{
    double distance = min(50 - abs(x[v]), 50 - abs(y[v]));
    return distance <= jumpD;
}

int DFS(int v)
{
    int answer = 0;
    visited[v] = true;
    if (isSafe(v))
        answer = 1;
    else
    {
        for (int w = 0; w < n; w++)
            if (jump(v, w) && !visited[w])
            {
                answer = DFS(w);
                if (answer)
                    break;
            }
    }
    return answer;
}

void save007()
{
    int answer = 0;
    for (int v = 0; v < n; v++)
    {
        if (firstJump(v) && !visited[v])
        {
            answer = DFS(v);
            if (answer)
                break;
        }
    }
    if (answer)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
}

int main()
{
    initialization();
    save007();
    return 0;
}