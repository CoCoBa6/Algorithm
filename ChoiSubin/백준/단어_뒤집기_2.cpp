#include <iostream>
#include <string>
#include <sstream>
#include <stack>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    string s;
    getline(cin , s);

    string tag = "";
    stack<char> str;
    for(int i = 0; i <s.length();i++)
    {
        if(s[i]=='<')
        {
            tag+= s[i];
            while(!str.empty())
            {
                cout << str.top();
                str.pop();
            }
        }
        else if(s[i] == '>')
        {
            tag += s[i];
            cout << tag;
            tag = "";
        }
        else
        {
            if(tag.empty())
            {
                if(s[i]==' ')
                {
                    while(!str.empty())
                    {
                        cout << str.top();
                        str.pop();
                    }
                    cout << ' ';
                }
                else
                {
                    str.push(s[i]);
                }
            }
            else
            {
                tag += s[i];
            }
        }
    }

    while(!str.empty())
    {
        cout << str.top();
        str.pop();
    }

    return 0;
}