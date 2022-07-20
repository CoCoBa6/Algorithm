#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> solution(string msg) {
    vector<int> answer;
    map<string, int> dicMap;
    for (char i = 'A'; i <= 'Z'; i++)
    {
        string str = "";
        dicMap.insert({ str + i, i - 64});
    }

    int curCount = 27;
    string curStr = "";
    curStr += msg[0];

    for (int i = 0; i < msg.length();)
    {
        curStr = "";
        curStr += msg[i];
        int j;
        for (j = i+1; j < msg.length(); j++)
        {
            if (dicMap.find(curStr + msg[j])==dicMap.end())
            {
                break;
            }
            else
            {
                curStr += msg[j];
            }
        }
        answer.push_back(dicMap[curStr]);
        dicMap.insert({ curStr + msg[j],curCount++ });
        i = j;
    }

    return answer;
}