#include <string>
#include <vector>
#include <map>
#include <queue>
#include <cstring>
#include <memory>
#include <set>

#include <iostream>


using namespace std;
//[ [1,0,0,3],
//  [2,0,0,0],
//  [0,0,0,2],
//  [3,0,1,0]]
// r = 세로행
// c = 가로행

struct Pos
{
    int r;
    int c;
};

int Distance(Pos a, Pos b)
{
    return abs(a.r-b.r) + abs(a.c-b.c);
}

bool isClear(vector<vector<int>> board) //  보드가 클리어 상태인지 확인하는 함수
{
    for(auto r : board)
    {
        for(auto c : r)
        {
            if(c != 0)
                return false;
        }
    }
    return true;
}

bool isCheck(Pos p)
{
    return p.c>=0 && p.c<4&&p.r>=0&&p.r<4;
}

Pos CtrlUp(Pos p, vector<vector<int>> board)
{
    for(int i = p.r-1 ; i >= 0 ;i--)
    {
        if(board[i][p.c] != 0 || i == 0)
            return {i,p.c};
    }
}
Pos CtrlDown(Pos p, vector<vector<int>> board)
{
    for(int i = p.r+1 ; i < 4;i++)
    {
        if(board[i][p.c] != 0 || i == 3)
            return {i,p.c};
    }
}
Pos CtrlLeft(Pos p, vector<vector<int>> board)
{
    for(int i = p.c-1 ; i >= 0 ;i--)
    {
        if(board[p.r][i] != 0 || i == 0)
            return{p.r,i};
    }
}
Pos CtrlRight(Pos p, vector<vector<int>> board)
{
    for(int i = p.c+1 ; i < 4 ; i++)
    {
        if(board[p.r][i] != 0 || i == 3)
            return {p.r,i};
    }
}

set<int> cardSet; //어떤 카드 존재하는지 알아보기위한 set
vector<int> cardList;// 카드 찾는 순서 조합 계산하기 위한 cardSet 벡터 변환용
vector<vector<int>> findList; // 카드 찾는 순서 조합 리스트


void MakeFindList(vector<int> list,set<int> cur,int count) //조합 생성
{
    if(list.size() == cardList.size())
    {
        findList.push_back(list);
        return;
    }
    
    for(auto card : cardList)
    {
        if(cur.find(card) == cur.end())
        {
            list.push_back(card);
            cur.insert(card);
            MakeFindList(list,cur,count + 1);
            list.pop_back();
            cur.erase(card);
        }
    }
}

int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
int Solved(Pos start, vector<int> visitList,vector<vector<int>> board)
{
    queue<pair<Pos,int>> q;
    q.push({start, 0});
    int findIndex = 0;
    int count = 0;
    while(!q.empty())
    {
        pair<Pos,int> cur = q.front();
        q.pop();
        Pos curPos = cur.first;
        if(visitList[findIndex] == board[curPos.r][curPos.c]) //엔터 입력
        {
            cur.second++;
            board[curPos.r][curPos.c] = 0;
            count++;
            if(count == 2)
            {
                findIndex++;
                count = 0;
            }

            if(isClear(board))
                return cur.second;
        }

        Pos goal = {-1,-1};
        for(int y = 0 ; y< board.size();y++)
        {
            for(int x = 0 ; x< board[y].size();x++)
            {
                if(board[y][x] == visitList[findIndex])
                {
                    if(goal.r == -1)
                        goal = {y,x};
                    else if(Distance(curPos,goal) > Distance(curPos,{y,x}))
                        goal = {y,x};
                }
            }
        }
        int minDistance = -1;
        Pos minPos;
        Pos tempPos;
        //방향키 움직임
        for(int i = 0 ; i < 4 ; i++)
        {
            tempPos = curPos;
            tempPos.r += dy[i];
            tempPos.c += dx[i];
            if(isCheck(tempPos))
            {
                if((Distance(tempPos,goal) < minDistance) || (minDistance==-1))
                {
                    minPos = tempPos;
                    minDistance = Distance(tempPos,goal);
                }
            }
        }
        
        tempPos = CtrlUp(curPos,board);
        if(Distance(tempPos,goal) < minDistance || minDistance==-1)
        {
            minPos = tempPos;
            minDistance = Distance(tempPos,goal);
        }

        tempPos = CtrlDown(curPos,board);
        if(Distance(tempPos,goal) < minDistance || minDistance==-1)
        {
            minPos = tempPos;
            minDistance = Distance(tempPos,goal);
        }

        tempPos = CtrlLeft(curPos,board);
        if(Distance(tempPos,goal) < minDistance || minDistance==-1)
        {
            minPos = tempPos;
            minDistance = Distance(tempPos,goal);
        }

        tempPos = CtrlRight(curPos,board);
        if(Distance(tempPos,goal) < minDistance || minDistance==-1)
        {
            minPos = tempPos;
            minDistance = Distance(tempPos,goal);
        }
        q.push({minPos,cur.second+1});
    }
}

int solution(vector<vector<int>> board, int r, int c) {
    cardSet.clear();
    for(auto r : board)
    {
        for(auto c : r)
        {
            if(c != 0)
                cardSet.emplace(c);
        }
    }
    cardList.clear();
    for(auto card : cardSet)
    {
        cardList.push_back(card);
    }
    MakeFindList({},{},0);
    int minNum = 987654321;
    for(auto f : findList)
    {
        for(auto l : f)
        {
            cout <<l<<' ';
        }
        cout <<endl;
        int num = Solved(Pos{r,c},f,board);
        if(minNum > num)
        {
            minNum = num;
        }
    }

    return minNum;
}

int main()
{
    cout << solution({{1, 0, 0, 3}, {2, 0, 0, 0}, {0, 0, 0, 2}, {3, 0, 1, 0}},1,0);
    return 0;
}