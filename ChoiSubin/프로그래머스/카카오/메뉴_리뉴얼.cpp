#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;
map<string, int> infoMap;
void SubSets(string str)
{
    int len = str.length();
    string tempStr;
    for (int i = 0; i < (1 << len); i++)
    {
        tempStr = "";
        for (int j = 0; j < len; j++)
        {
            if (i & (1 << j))
            {
                tempStr += str[j];
            }
        }

        if (tempStr.length() > 0)
        {
            sort(tempStr.begin(), tempStr.end());
            infoMap[tempStr]++;
        }
    }
}

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
    infoMap.clear();
    for (auto order : orders)
    {
        SubSets(order);
    }

    for (auto num : course)
    {
        vector<string> menu;
        int count = 0;
        for (auto info : infoMap)
        {
            if (info.first.length() == num)
            {
                if (info.second > 1 && info.second >= count)
                {
                    if (info.second > count)
                    {
                        menu.clear();
                    }
                    menu.push_back(info.first);
                    count = info.second;
                }
            }
        }
        
        for (auto m : menu)
        {
            answer.push_back(m);
        }
    }

    sort(answer.begin(), answer.end());
    return answer;
}