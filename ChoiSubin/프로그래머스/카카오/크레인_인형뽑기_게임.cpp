#include <string>
#include <vector>
#include <stack>
using namespace std;

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    stack<int> stackPipe;
    for (int i = 0; i < moves.size(); i++)
    {
        for (int y = 0; y < board.size(); y++)
        {
            if (board[y][moves[i]-1] != 0)
            {
                if (stackPipe.empty())
                {
                    stackPipe.push(board[y][moves[i]-1]);
                }
                else
                {
                    if (stackPipe.top() == board[y][moves[i]-1])
                    {
                        answer += 2;
                        stackPipe.pop();
                    }
                    else
                    {
                        stackPipe.push(board[y][moves[i] - 1]);
                    }
                }
                board[y][moves[i] - 1] = 0;
                break;
            }
        }
    }
    return answer;
}
