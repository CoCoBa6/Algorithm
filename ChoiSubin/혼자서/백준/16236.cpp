
#include <iostream>
#include <queue>
using namespace std;
int arr[21][21];
int sharkSize = 2;
int dx[4] = {0,-1,0,1};
int dy[4] = {-1,0,1,0};
int N;
bool visitArr[21][21];
void ResetVisit()
{
    for(int i = 0 ; i < N ; i++)
    {
        for(int j = 0 ; j < N ; j++)
        {
            visitArr[i][j] = false;
        }  
    }
}

bool checkRange(pair<int,int> pos)
{
    return pos.first>=0 && pos.second>=0 && pos.first<N&&pos.second<N;
}

int GetRange(pair<int,int> startPos,pair<int,int> goalPos)
{
    return abs(startPos.first-goalPos.first) +  abs(startPos.second-goalPos.second);
}

int bfs(pair<int,int> startPos)
{
    queue<pair<int,int>> q;
    pair<int,int> result = {-1,-1};
    int minResult = -1;
    ResetVisit();
    q.push(startPos);
    visitArr[startPos.second][startPos.first] = true;
    while(!q.empty())
    {
        pair<int,int> curPos = q.front();
        q.pop();
        if(arr[curPos.second][curPos.first]<=sharkSize &&arr[curPos.second][curPos.first]!=0)
        {
            int range = GetRange(startPos,curPos);
            if(minResult==-1 || minResult >= range)
            {
                if(minResult>range || minResult == -1)
                {
                    result = curPos;
                }
                else
                {
                    if(result.second == curPos.second)
                    {
                        if(result.first>curPos.first)
                        {
                            result = curPos;     
                        }
                    }
                    else if(result.second > curPos.second)
                    {
                        result = curPos;
                    }
                }
            }
        }
        else
        {
            for(int i = 0 ; i < 4;i++)
            {
                pair<int,int> tempPos = {curPos.first+dx[i],curPos.second+dy[i]};
                if(checkRange(tempPos) && !visitArr[tempPos.second][tempPos.first])
                {
                    q.push(tempPos);
                    visitArr[tempPos.second][tempPos.first] = true;
                }
            }
        }

    }
    
    cout << result.first << "," <<result.second<<endl;
    return 0;
}

int main()
{
    cin >> N;
    pair<int,int> startPos;
    for(int i = 0 ; i < N ; i++)
    {
        for(int j = 0 ; j < N ; j++)
        {
            cin >> arr[i][j];
            if(arr[i][j] == 9)
            {
                startPos = {j,i};
            }
        }  
    }
    bfs(startPos);
    
    return 0;
}
