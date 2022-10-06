
#include <iostream>
#include <queue>
using namespace std;
struct Shark {
    int move = 0;
    pair<int, int> pos;
};
int arr[21][21];
int sharkSize = 2;
int eatCount = 0;
int dx[4] = { 0,-1,0,1 };
int dy[4] = { -1,0,1,0 };
int N;
bool visitArr[21][21];
void ResetVisit()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            visitArr[i][j] = false;
        }
    }
}

bool checkRange(pair<int, int> pos)
{
    return pos.first >= 0 && pos.second >= 0 && pos.first < N&& pos.second < N;
}

int GetRange(pair<int, int> startPos, pair<int, int> goalPos)
{
    return abs(startPos.first - goalPos.first) + abs(startPos.second - goalPos.second);
}

Shark bfs(pair<int, int> startPos)
{
    queue<Shark> q;
    Shark result = { 0,{-1,-1}};
    ResetVisit();
    q.push({ 0,startPos });
    visitArr[startPos.second][startPos.first] = true;
    while (!q.empty())
    {
        Shark curInfo = q.front();
        q.pop();
        if (arr[curInfo.pos.second][curInfo.pos.first] < sharkSize && arr[curInfo.pos.second][curInfo.pos.first] != 0)
        {
            if (result.move == 0 || result.move >= curInfo.move)
            {
                if (result.move > curInfo.move || result.move == 0)
                {
                    result = curInfo;
                }
                else
                {
                    if (result.pos.second == curInfo.pos.second && result.pos.first > curInfo.pos.first)
                    {
                        result = curInfo;
                    }
                    else if (result.pos.second > curInfo.pos.second)
                    {
                        result = curInfo;
                    }
                }
            }
        }
        else
        {
            for (int i = 0; i < 4; i++)
            {
                pair<int, int> tempPos = { curInfo.pos.first + dx[i],curInfo.pos.second + dy[i] };
                if (checkRange(tempPos) && !visitArr[tempPos.second][tempPos.first] && arr[tempPos.second][tempPos.first]<=sharkSize)
                {
                    q.push({ curInfo.move+1,tempPos });
                    visitArr[tempPos.second][tempPos.first] = true;
                }
            }
        }

    }

    return result;
}

int main()
{
    cin >> N;
    pair<int, int> startPos;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> arr[i][j];
            if (arr[i][j] == 9)
            {
                startPos = { j,i };
                arr[i][j] = 0;
            }
        }
    }

    Shark findResult;
    int countSec = 0;
    while (1)
    {
        findResult = bfs(startPos);
        if (findResult.pos == make_pair(-1,-1))
            break;

        if (sharkSize == (++eatCount))
        {
            sharkSize++;
            eatCount = 0;
        }
        countSec += findResult.move;
        startPos = findResult.pos;
        arr[startPos.second][startPos.first] = 0;
        ResetVisit();
    }
    cout << countSec;
    return 0;
}
