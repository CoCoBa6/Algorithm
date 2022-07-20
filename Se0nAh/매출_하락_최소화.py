# 풀이 출처 https://www.youtube.com/watch?v=FX9n1PFv2K4&ab_channel=BaaarkingDog
# tree dp 
# 고민만 두 시간하고 결국 못 푼... dp일 거같긴 했는데... 다시 풀자 ㅋㅋ;
answer = 0
# 각 직원(팀장) 밑에 있는 팀원
adj = [[] for i in range(300005)]
INF = 0x7fffffff7fffffff
# d[i][0] : i번 노드가 루트인 서브트리에서 조건을 만족했을 때 매출합의 최소, i번은 워크숍에 참석
# d[i][1] : i번 노드가 루트인 서브트리에서 조건을 만족했을 때 매출합의 최소, i번은 워크숍에 불참
d = [[0]*2 for i in range(300005)]
# 직원 당 매출액
s = []

def dfs(cur):
    # leaf node에 있는 직원일 때 d[i][0] = s[i], d[i][1] = 0
    if not adj[cur]:
        d[cur][0], d[cur][1] = s[cur], 0
        return None
    mingap = INF
    d[cur][0] = s[cur]
    for x in adj[cur]:
        dfs(x)
        d[cur][0] += min(d[x])
        mingap = min(mingap, d[x][0] - d[x][1])
    
    # d[i][1] 은 팀원 중 누군가 워크숍에 참석해야함. 참석했을 때 손해가 작은 사람이 참석
    # d[i][1] = max(0, min(d[c0][0]-d[c0][1], d[c1][0]-d[c1][1], ..)) + d[i][0] - s[k]
    if mingap < 0: mingap = 0
    d[cur][1] = d[cur][0] + mingap - s[cur]

def solution(sales, links):
    global s
    s = [0] + sales
    for x in links:
        adj(x[0]).append(x[1])
    dfs(1)
    return min(d[1])
    
           
    
    return answer