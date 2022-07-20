#include <string>
#include <vector>
#include <stack>
using namespace std;
bool isClear(string str)
{
    string answer = "";
    stack<char> stackTemp;
    for (char c : str)
    {
        if (stackTemp.size() > 0 && stackTemp.top() == '(' && c == ')')
        {
            stackTemp.pop();
        }
        else
        {
            stackTemp.push(c);
        }
    }

    return stackTemp.empty();
}
string Solved(string p)
{
    if (p.empty()) return "";
    string u, v;

    int openNum = 0;
    int closeNum = 0;

    //문자열 w를 두 "균형잡힌 괄호 문자열" u,v로 분리
    for (int i = 0; i < p.length(); i++)
    {
        if (p[i] == '(') openNum++;
        else closeNum++;
        u += p[i];
        if (openNum == closeNum)
        {
            v = p.substr(i+1);
            break;
        }
    }

    //문자열 u가 "올바른 문자열" 이라면 문자열 v에 대해 1단계부터 수행
    if (isClear(u))
    {
        return u+Solved(v);
    }
    else //문자열 u가 "올바른 괄호 문자열"이 아니라면 아래 과정을 수행
    {
        string tempStr = "(" + Solved(v)+ ")";
        for (int i = 0; i < u.length(); i++)
        {
            if (i != 0 && i != u.length() - 1)
            {
                if (u[i] == ')')
                    tempStr += '(';
                else
                    tempStr += ')';
            }
        }

        return tempStr;
    }
}

string solution(string p) {
    string answer = "";
    if (isClear(p))
    {
        answer = p;
    }
    else
    {
        answer = Solved(p);
    }
    return answer;
}