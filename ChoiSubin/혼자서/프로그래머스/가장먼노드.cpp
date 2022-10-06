#include <string>
#include <vector>
#include <queue>
using namespace std;
vector<vector<int>> arr(20001);
int dist[200001];
bool visitCheck[200001];
struct NodeInfo 
{
    int nodeNum;
    int dist;
};
void bfs(int start)
{
    queue<NodeInfo> q;
    q.push({ start ,0});
    visitCheck[start] = true;
    while (!q.empty())
    {
        NodeInfo curNode = q.front();
        q.pop();

        for (int i = 0; i < arr[curNode.nodeNum].size(); i++)
        {
            int nextNum = arr[curNode.nodeNum][i];
            if (!visitCheck[nextNum])
            {
                visitCheck[nextNum] = true;
                dist[nextNum] = curNode.dist + 1;
                q.push({ nextNum ,dist[nextNum] });
            }
        }
    }
}

int solution(int n, vector<vector<int>> edge) {
    int answer = 0;
    for (int i = 0; i < edge.size(); i++)
    {
        arr[edge[i][0]].push_back(edge[i][1]);
        arr[edge[i][1]].push_back(edge[i][0]);
    }
    bfs(1);
    int count = 0;
    int max = 0;
    for (int i = 1; i <= n; i++)
    {
        if (dist[i] >= max)
        {
            if (dist[i] > max)
            {
                max = dist[i];
                count = 0;
            }
            count++;
        }
    }
    return count;
}

int main()
{
    solution(6, { {3, 6}, {4, 3}, {3, 2}, {1, 3}, {1, 2}, {2, 4}, {5, 2} });
    return 0;
}