#include <string>
#include <vector>
using namespace std;

int M=0,N=0;
int lockEmpty = 0;
vector<vector<int>> resizeV;

int isCheck(vector<vector<int>> key,int nx, int ny)
{
    int tempX=0;
    int tempY = 0;
    int result = 0;

    for(int i = nx;i<nx+M;i++,tempX++)
    {
        for(int j = ny;j<ny+M;j++,tempY++)
        {
            if(resizeV[i][j] == 1 && key[tempX][tempY] == 1) // 만약 비어있지 않은 부분을 key가 채우면
                return -1;
            else if(resizeV[i][j] == 0  && key[tempX][tempY]==0)//비어있는데 그 부분을 key가 채우지 못한다면
                return -1;
            else if(resizeV[i][j] == 0 && key[tempX][tempY]==1)
                result++;
        }
        tempY = 0;
    }
    return result;
}

bool Solved(vector<vector<int>> key, vector<vector<int>> lock)
{
    M = key.size(); // key배열의 최대 사이즈
    N = lock.size(); //자물쇠 최대 사이즈
    
    //자물쇠에 열쇠를 이리저리 가져다 대야함
    //넉넉한 사이즈를 구해야함 
    //자물쇠 최대 사이즈 + (키 최대사이즈 - 1)*2 만큼 필요
    int resize = N + (M-1)*2;
    resizeV.resize(resize, vector<int>(resize,-1)); 
    //열쇠를 연결하기위해 일반 비어있는 공간은 -1, 열쇠를 넣어야하는 공간은 0으로 지정

    //자물쇠를 resize한 공간으로 옮김
    int curX = 0;
    int curY = 0;
    for(int i = M-1 ; i < resize - (M-1); i++,curX++)
    {
        for(int j = M-1 ; j<resize - (M-1); j++,curY++)
        {
            resizeV[i][j] = lock[curX][curY];
            if(resizeV[i][j] == 0)
                lockEmpty++;
        }
        curY = 0;
    }

    for(int i = 0 ; i < 4 ; i++) //90도씩 3번 회전
    {
        for(int x = 0 ; x< M+N-1; x++)
        {
            for(int y = 0 ; y<M+N-1;y++)
            {
                if(isCheck(key,x,y) == lockEmpty) //비어있는 모든 부분을 매꾸었다면
                    return true;
            }
        }

        //키를 회전 시켜주어야함
        vector<vector<int>> tempV = key;
        for(int x = 0 ; x< M; x++)
        {
            for(int y = 0 ; y<M;y++)
            {
                tempV[x][y] = key[M-1-y][x];
            }
        }
        key = tempV;
    }
    return false;
}
bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    return Solved(key,lock);
}