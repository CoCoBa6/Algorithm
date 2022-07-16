#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <iostream>
using namespace std;

map<int, int> salesMap;
vector<int> v[300001];
bool visited[300001];
int dp[300001][2];
void dfs(int n)
{
    visited[n] = true;
    if (v[n].empty())
    {
        dp[n][0] = 0;
        dp[n][1] = salesMap[n];
    }
    else
    {
        for (int i = 0; i < v[n].size(); i++)
        {
            if (!visited[v[n][i]])
            {
                dfs(v[n][i]);
            }
        }
    }
    cout << dp[n][0] << endl;
    cout << dp[n][1] << endl;
}

int dfs2(int n, bool isParticipate)
{
    visited[n] = true;
    if (v[n].empty())
    {
        if (isParticipate)
            dp[n][1] = salesMap[n];
        else
            dp[n][0] = 0;
        return dp[n][isParticipate];
    }
    else
    {
        if (isParticipate)
        {
            int minNum = -1;
            if (v[n].size() == 0)
            {
                minNum = salesMap[n];
            }
            for (int i = 0; i < v[n].size(); i++)
            {
                for (int isJoin = 0; isJoin < 2; isJoin++)
                {
                    if (dp[v[n][i]][isJoin] == NULL)
                        dp[v[n][i]][isJoin] = dfs2(v[n][i], isJoin);
                    if (minNum == -1 || minNum > salesMap[n] + dp[v[n][i]][isJoin])
                    {
                        minNum = salesMap[n] + dp[v[n][i]][isJoin];
                    }
                }
            }
            return minNum;
        }
        else
        {
            int minNum = -1;
            if (v[n].size() == 0)
            {
                minNum = 0;
            }
            for (int i = 0; i < v[n].size(); i++)
            {
                if (dp[v[n][i]][1] == 0)
                    dp[v[n][i]][1] = dfs2(v[n][i], 1);
                if (minNum == -1 || minNum > salesMap[n] + dp[v[n][i]][1])
                {
                    minNum = salesMap[n] + dp[v[n][i]][1];
                }
            }
            return minNum;
        }
        return 0;
    }
}

int solution(vector<int> sales, vector<vector<int>> links) {

    int answer = 0;
    memset(visited, false, sizeof(visited));
    for (int i = 0; i < sales.size(); i++)
    {
        salesMap[i + 1] = sales[i];
    }

    for (auto link : links)
    {
        v[link[0]].push_back(link[1]);
    }
    cout << dfs2(1,true);
    cout << dfs2(1, false);
    return answer;
}

int main()
{
    solution({ 5, 6, 5, 3, 4 }, { {2, 3}, {1, 4}, {2, 5}, {1, 2} });
    cout << 1 << endl;
    return 0;
}