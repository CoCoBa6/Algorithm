#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <string>
using namespace std;

int N,K;
vector<char> dicList;

vector<map<char,int>> makeList;

void MakeList(map<char,int> list, int count)
{
    if(list.size() == K)
    {
        makeList.push_back(list);
        return;
    }
    if(count == dicList.size())
        return;

    MakeList(list,count+1);
    list.insert({dicList[count],0});
    MakeList(list,count+1);
}

int main()
{
    cin >> N >> K;
    string tempStr;
    set<char> dicSet;
    vector<string> v;
    dicSet.insert('a');
    dicSet.insert('n');
    dicSet.insert('t');
    dicSet.insert('i');
    dicSet.insert('c');
    for(int i = 0 ; i < N ;i++)
    {
        cin >> tempStr;
        for(int i = 4;i<tempStr.size()-4;i++)
        {
            dicSet.insert(tempStr[i]);
        }
        v.push_back(tempStr);
    }

    for(auto i = dicSet.begin() ; i != dicSet.end();i++)
    {
        dicList.push_back(*i);
    }

    MakeList({},0);

    int maxResult = 0;
    int count =0;
    for(auto make = makeList.begin();make!=makeList.end();make++)
    {
        count = 0;
        for(auto str = v.begin();str!=v.end();str++)
        {
            bool strCheck = true;
            for(auto ch = (*str).begin() ; ch!= (*str).end();ch++)
            {
                if((*make).find(*ch)==(*make).end())
                {
                    strCheck = false;
                    break;
                }
            }
            if(strCheck)
                count++;
        }
        if(count>maxResult)
        {
            maxResult = count;
        }
    }
    cout << maxResult;
    return 0;
}