#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;

map<string, string> mCode;
void InitCode()
{
    mCode.insert({ "cpp", "1" });
    mCode.insert({ "java", "2" });
    mCode.insert({ "python", "3" });
    mCode.insert({ "backend", "1" });
    mCode.insert({ "frontend", "2" });
    mCode.insert({ "junior", "1" });
    mCode.insert({ "senior", "2" });
    mCode.insert({ "chicken", "1" });
    mCode.insert({ "pizza", "2" });
    mCode.insert({ "-", "0" });
}

vector<string> split(string str)
{
    vector<string> vStr;
    stringstream ss(str);
    string temp;

    while (getline(ss, temp, ' '))
        vStr.push_back(temp);

    return vStr;
}

vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> answer;

    vector<string> vStr;
    map<string, vector<int>> mCount;

    InitCode(); //map에 지원자 정보별 코드 추가
    for (auto _info : info) // 들어온 정보를 모두 돌아봄
    {
        vStr = split(_info);

        string tempStr = "";
        for (int i = 0; i < vStr.size() - 1; i++) //들어온 input을 숫자 코드로 변환
            tempStr += mCode[vStr[i]];
        mCount[tempStr].push_back(stoi(vStr[4])); //맵에 점수랑 추가해줌
    }

    vector<int> vResult;
    for (auto _query : query) // 들어온 쿼리문 탐색
    {
        vStr = split(_query);

        string tempStr = "";        //들어온 쿼리문도 숫자 코드로 변환시켜줌
        tempStr += mCode[vStr[0]];
        tempStr += mCode[vStr[2]];
        tempStr += mCode[vStr[4]];
        tempStr += mCode[vStr[6]];
        int goalScore = stoi(vStr[7]);
        vResult.clear();

        int countNum = 0;
        for (auto m : mCount)   //들어왔던 info를 숫자코드화 시킨 map 탐색
        {
            string keyStr = m.first;
            if (keyStr[0] != tempStr[0] && tempStr[0] != '0')
                continue;
            else if (keyStr[1] != tempStr[1] && tempStr[1] != '0')
                continue;
            else if (keyStr[2] != tempStr[2] && tempStr[2] != '0')
                continue;
            else if (keyStr[3] != tempStr[3] && tempStr[3] != '0') //만약 각자리 숫자가 0이 아니거나 탐색하는 숫자코드와 다르다면
                continue;

            for (auto result : m.second)
            {
                if (result >= goalScore) countNum++; //정해둔 목표 점수보다 점수가 높으면 카운팅 해줌
            }
        }

        answer.push_back(countNum); //카운팅 결과를 answer에 넣어준다.
    }
    return answer;
}
