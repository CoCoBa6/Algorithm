#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <iostream>
using namespace std;
vector<string> split(string str,char Delimiter)
{
    stringstream ss(str);
    string buffer;

    vector<string> result;

    while(getline(ss,buffer,Delimiter))
    {
        result.push_back(buffer);
    }

    return result;
}
vector<string> solution(vector<string> record) {
    vector<string> answer;
    map<string,string> userInfo;

    vector<string> splitStr;
    vector<string> changeRecord;
    string tempStr = "";
    for(auto re:record)
    {
        splitStr = split(re,' ');
        tempStr = splitStr[0] + " " + splitStr[1];
        if(splitStr[0]!="Leave")
        {
            userInfo[splitStr[1]] = splitStr[2];
        }
        changeRecord.push_back(tempStr);
    }

    for(auto cr:changeRecord)
    {
        splitStr = split(cr,' ');
        tempStr = userInfo[splitStr[1]];
        if(splitStr[0] == "Enter")
        {
            tempStr +="님이 들어왔습니다.";
            answer.push_back(tempStr);
        }
        else if(splitStr[0] == "Leave")
        {
            tempStr +="님이 나갔습니다.";
            answer.push_back(tempStr);
        }
    }
    return answer;
}