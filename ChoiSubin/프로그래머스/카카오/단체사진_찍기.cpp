#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cmath>
using namespace std;


// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n, vector<string> data) {
    vector<char> v = { 'A','C','F' ,'J' ,'M' ,'N' ,'R' ,'T' };
    int answer = 0;
    bool isAble;
    do
    {
        isAble = true;
        for (int i = 0; i < n; i++)
        {
            int fPos = 0 , sPos = 0;
            for (int j = 0; j < v.size(); j++)
            {
                if (v[j] == data[i][0]) fPos = j;
                else if (v[j] == data[i][2]) sPos = j;
            }

            int range = abs(fPos - sPos) - 1;
            if (data[i][3] == '=')
            {
                if (range != (data[i][4] - '0'))
                    isAble = false;
            }
            else if (data[i][3] == '<')
            {
                if (range >= (data[i][4] - '0'))
                    isAble = false;
            }
            else if (data[i][3] == '>')
            {
                if (range <= (data[i][4] - '0'))
                    isAble = false;
            }
        }
        if (isAble) answer++;
    } while (next_permutation(v.begin(), v.end()));

    return answer;
}