#include <vector>
#include <queue>
using namespace std;
bool visitCheck[101][101] = { false };
int N, M;
int maxArea = 0;
bool isCheck(pair<int, int> pos)
{
    return pos.first >= 0 && pos.first < N&& pos.second >= 0 && pos.second < M;
}

void bfs(pair<int, int> start, vector<vector<int>> picture)
{
    int dx[4] = { 1,0,-1,0 };
    int dy[4] = { 0,1,0,-1 };
    queue<pair<int, int>> q;
    q.push(start);
    visitCheck[start.second][start.first] = true;
    int areaNum = 1;
    while (!q.empty())
    {
        pair<int, int> curPos = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            pair<int, int> next = { curPos.first + dx[i], curPos.second + dy[i] };
            if (!visitCheck[next.second][next.first])
            {
                if (isCheck(next)
                    && picture[start.second][start.first] == picture[next.second][next.first])
                {
                    areaNum++;
                    q.push(next);
                    visitCheck[next.second][next.first] = true;
                }
            }
        }
    }

    if (maxArea < areaNum) maxArea = areaNum;
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
    int number_of_area = 0;
    int max_size_of_one_area = 0;
    for (int y = 0; y < m; y++)
    {
        for (int x = 0; x < n; x++)
        {
            visitCheck[y][x] = false;
        }
    }
    maxArea = 0;
    N = n;
    M = m;

    for (int y = 0; y < m; y++)
    {
        for (int x = 0; x < n; x++)
        {
            if (!visitCheck[y][x] && picture[y][x] > 0)
            {
                bfs({ x,y }, picture);
                number_of_area++;
            }
        }
    }

    vector<int> answer(2);
    answer[0] = number_of_area;
    answer[1] = maxArea;
    return answer;
}