#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
bool isCheck(char c)
{
    return (c>='A'&&c<='Z'|| c>='a'&&c<='z');
}
char changeAtoa(char ch)
{
    if(ch>='a'&&ch<='z')
        return ch - ('a'-'A');
    else
        return ch;
}

vector<string> changeVecSet(string str)
{
    vector<string> result;
    for(int i = 1; i < str.length();i++)
    {
        char temp1,temp2;
        temp1 = str[i-1];
        temp2 = str[i];
        if(isCheck(temp1)&&isCheck(temp2))
        {
            string tempStr = "";
            tempStr+=changeAtoa(temp1);
            tempStr+=changeAtoa(temp2);
            result.push_back(tempStr);
        }
    }
    return result;
}

int solution(string str1, string str2) {
    int answer = 0;
    map<string,int> mapStr1;
    vector<string> vStr1 = changeVecSet(str1);
    vector<string> vStr2 = changeVecSet(str2);
    int overlapNum = 0;
    for(auto str: vStr1)
    {
        mapStr1[str]++;
    }

    for(auto str: vStr2)
    {
        if(find(vStr1.begin(),vStr1.end(),str)!=vStr1.end())
        {
            if(mapStr1[str]>0)
            {
                overlapNum++;
                mapStr1[str]--;
            }
        }
    }

    float fanswer = (float)(vStr1.size()+vStr2.size()-overlapNum);
    
    if(vStr2.empty()&&vStr1.empty())
    {
        return 65536;
    }
    
    fanswer = overlapNum / fanswer;
    

    answer = (int)(fanswer*65536.0);
    return answer;
}