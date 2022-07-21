#include <string>
#include <vector>
#include <cstring>
#define INF 987654321
using namespace std;
int arr[201][201];
int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
                arr[i][j] = 0;
            else
                arr[i][j] = INF;
        }
    }

    for (auto f : fares)
    {
        arr[f[0]][f[1]] = f[2];
        arr[f[1]][f[0]] = f[2];
    }

    //플로이드 와샬로 모든 정점에서 부터 최단거리 계산
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i != j && i != k && k != j && arr[i][k]!=INF && arr[k][j]!=INF)
                {
                    if (arr[i][k] + arr[k][j] < arr[i][j])
                    {
                        arr[i][j] = arr[i][k] + arr[k][j];
                        arr[j][i] = arr[i][j];
                    }
                }
            }
        }
    }

    answer = arr[s][a] + arr[s][b]; //둘이 따로 탔을때 드는 비용
    for (int i = 1; i <= n; i++) //모든 정점 돌면서 둘이 합승했을때 최솟값 있으면 answer에 넣어주기
    {
        if (arr[s][i] != INF && arr[i][a] != INF && arr[i][b] != INF) //i정점을 들렸을때 도착할 수 있으면
        {
            answer = (answer > arr[s][i] + arr[i][a] + arr[i][b]) ? arr[s][i] + arr[i][a] + arr[i][b] : answer;
            //만약 중간에 i정점을 들려서 도착하는 비용이 더 싸면 그 비용을 대입해주고 아니면 그냥 원래 값 넣어주기
        }
    }
    return answer;
}

int main()
{
    solution(6, 4, 5, 6, {{2, 6, 6}, {6, 3, 7}, {4, 6, 7}, {6, 5, 11}, {2, 5, 12}, {5, 3, 20}, {2, 4, 8}, {4, 3, 9}} );
    return 0;
}