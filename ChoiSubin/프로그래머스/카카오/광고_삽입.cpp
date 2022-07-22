#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

vector<string> split(string str, char c)
{
    stringstream ss(str);
    string temp;
    vector<string> result;
    while (getline(ss, temp, c))
    {
        result.push_back(temp);
    }
    return result;
}

int changeSec(string time)
{
    vector<string> splitStr = split(time, ':');
    return stoi(splitStr[0]) * 60 * 60 + stoi(splitStr[1]) * 60 + stoi(splitStr[2]);
}


string changeSecToStr(int time)
{
    string h = to_string(time / 3600);
    string m = to_string((time % 3600) / 60);
    string s = to_string((time % 60));
    if (h.size() < 2) h = '0' + h;
    if (m.size() < 2) m = '0' + m;
    if (s.size() < 2) s = '0' + s;
    string result = h + ":" + m + ":" + s;
    return result;
}

//O(N)으로 변경
long long checkCount[360002];
string solution(string play_time, string adv_time, vector<string> logs) {
    string answer = "00:00:00";
    //1.초단위로 변경할것
    //2.초단위로 보고있는 시청자수를 계산할것
    //3.가장 많은 시청자를 계속 기록할것
    
    //string으로 들어온것을 초단위로 바꾸어줌
    int playTime = changeSec(play_time);
    int advTime = changeSec(adv_time);
    vector<string> tempV;
    for (auto log : logs)
    {
        tempV = split(log, '-');
        int startTime = changeSec(tempV[0]); //시청시작시간
        int endTime = changeSec(tempV[1]); //시청종료시간
        checkCount[startTime + 1]++; //시청 시작시간엔 시청자수 카운트 ++
        checkCount[endTime + 1]--; //시청 종료시간엔 시청자수 카운트 --
    }

    //시청자수 누적합 계속 구해줌
    for (int i = 0; i < 2; i++)
    {
        for (int j = 1; j <= playTime; j++)
        {
            checkCount[j] = checkCount[j - 1] + checkCount[j]; //전에 카운트 된 놈이랑 내 현재 시간 더해서 나한테 누적시켜줌
        }
    }

    pair<int, long long> result = {0,0};
    for (int i = advTime; i <= playTime; i++) //광고 길이부터 총 영상 플레이 길이 까지 땡겨줌
    {
        if (result.second < checkCount[i] - checkCount[i - advTime]) // 광고가 끝나는 시간의 누적합 - 내가 광고를 보기 시작한 시간의 누적합 을 계산해서 이게 더 클때
        {
            result = { i - advTime, checkCount[i] - checkCount[i - advTime] }; // 현재 시간과 지금까지 최대 값 pair로 저장
        }
    }
    answer = changeSecToStr(result.first); //int값을 결과값에 맞게 string으로 변환
    return answer;
}

int main()
{
    solution("02:03:55", "00:14:15", { "01:20:15-01:45:14", "00:25:50-00:48:29", "00:40:31-01:00:00", "01:37:44-02:02:30", "01:30:59-01:53:29" });
    return 0;
}

//아래건 시간초과 발생 O(N^2)
//#include <string>
//#include <vector>
//#include <sstream>
//#include <algorithm>
//using namespace std;
//
//vector<string> split(string str, char c)
//{
//    stringstream ss(str);
//    string temp;
//    vector<string> result;
//    while (getline(ss, temp, c))
//    {
//        result.push_back(temp);
//    }
//    return result;
//}
//
//int changeSec(string time)
//{
//    vector<string> splitStr = split(time, ':');
//    return stoi(splitStr[0]) * 60 * 60 + stoi(splitStr[1]) * 60 + stoi(splitStr[2]);
//}
//
//bool Cmp(pair<int, int> p1, pair<int, int> p2)
//{
//    if (p1.first == p2.first)
//        return p1.second > p2.second; // 같으면 끝나는 시간 더 빠를 때 반환
//    return p1.first < p2.first; //시작시간만 비교해서 반환
//}
//
//string changeSecToStr(int time)
//{
//    string h = to_string(time / 3600);
//    string m = to_string((time % 3600) / 60);
//    string s = to_string((time % 60));
//    if (h.size() < 2) h = '0' + h;
//    if (m.size() < 2) m = '0' + m;
//    if (s.size() < 2) s = '0' + s;
//    string result = h + ":" + m + ":" + s;
//    return result;
//}
//
//string solution(string play_time, string adv_time, vector<string> logs) {
//    string answer = "00:00:00";
//    //1.초단위로 변경할것
//    //2.영상 시청 시작하는 시간 순으로 정렬할 것
//    //3.영상시간-광고진행시간 이 최대 시작 가능한 시간
//    int maxStart = changeSec(play_time) - changeSec(adv_time); //최대 시작 가능한 시간 계산
//    vector<pair<int, int>> logsV; //영상 시청 시작시간 , 영상 시청 종료 시간 pair Vector
//
//    vector<string> tempV;
//    for (auto log : logs) //사용자 영상 시청시간을 초단위로 바꾸고 숫자로 바꾸어 logsV에 넣어준다.
//    {
//        tempV = split(log, '-');
//        int startSec = changeSec(tempV[0]); //시청 시작시간 초단위 변경
//        int endSec = changeSec(tempV[1]); //시청 종료시간 초단위 변경
//        logsV.push_back({ startSec, endSec }); //logsV에 데이터 추가.
//    }
//
//    sort(logsV.begin(), logsV.end(), Cmp); //logsV 사용자 정의 함수에 따라 정렬
//
//    pair<int, int> maxTimePair = { 0,0 }; //영상 시청 시작시간 , 영상 누적 시간 비교를 위한 pair
//    int advTime = changeSec(adv_time); //광고 영상 길이
//
//    for (int i = 0; i < logsV.size(); i++)
//    {
//        if (logsV[i].first >= maxStart) break; //첫 시작으로부터 끝나는 시간이 광고 길이보다 짧으면 탈출
//
//        int advEndTime = logsV[i].first + advTime;// 광고 상영 종료시간 계산
//        int advStartTime = logsV[i].first; // 광고 상영 시작시간 넣어줌
//        int curResultTime = 0;
//
//        if (advEndTime >= logsV[i].second) //만약 시청 종료 시간이 광고 끝나는 시간보다 작거나 같으면
//            curResultTime += logsV[i].second - logsV[i].first;  //내 시청시간 넣어줌
//        else //내 시청시간이 더 길면
//            curResultTime += advEndTime - advStartTime; //광고 시간 넣어줌
//
//        for (int j = i + 1; j < logsV.size(); j++) //내 시청시각보다 뒤에 있는 애들 계산해줌
//        {
//            if (advEndTime <= logsV[j].first) break; //광고영상 종료시간보다 시청 시작 시간이 느리면 탈출
//            int tempTime = (advEndTime - logsV[j].first);
//            //if (tempTime > 0)
//            {
//                curResultTime += tempTime; //광고 종료시간 - 내 시청 시작시간 계산해서 누적해줌
//            }
//        }
//
//        if (maxTimePair.second < curResultTime) // 만약 기존 존재하던 누적시간보다 이번 누적시간이 더 크면 새로 갱신해줌
//        {
//            maxTimePair = { advStartTime , curResultTime };
//        }
//    }
//    answer = changeSecToStr(maxTimePair.first);
//    return answer;
//}
//
//int main()
//{
//    solution("02:03:55", "00:14:15", { "01:20:15-01:45:14", "00:25:50-00:48:29", "00:40:31-01:00:00", "01:37:44-02:02:30", "01:30:59-01:53:29" });
//    return 0;
//}