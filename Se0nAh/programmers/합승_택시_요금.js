// 1시간 풀고도 틀림 ㅎㅎ; 다시 수정...
// 정확성: 40.0
// 효율성: 36.7
// 합계: 76.7 / 100.0
function solution(n, s, a, b, fares) {
    const INF = 100001
    var answer = INF;
    
    var arr, i, j, initialMat, lowestCostMat = [];
    for (i = 0; i < n+1; i += 1) {
        arr = [];
        for (j = 0; j < n+1; j += 1) {
            if (i === j) arr[j] = 0
            else arr[j] = INF;
        }
        lowestCostMat[i] = arr;
    }
    
    fares.forEach(fare => {
        lowestCostMat[fare[0]][fare[1]] = fare[2]
        lowestCostMat[fare[1]][fare[0]] = fare[2]
    }) 


    function floyedWarshall (g){
        for (let t = 1; t < n+1 ; t+=1){ // 경유 노드
            for (let s = 1; s < n+1; s+=1){ // 시작 노드
                if (s === t) continue
                for (let a =1; a < n+1; a+=1) { // 도착 노드
                    if (s === a) continue
                    if (g[s][a] > g[s][t] + g[t][a]){
                        g[s][a] = g[s][t] + g[t][a]
                    }
                }
            }
        }
    }
    floyedWarshall(lowestCostMat)
    
    
    console.log(lowestCostMat)
        for (let t = 1; t < n + 1 ; t++) {            
            // 각 지점에서 a 와 b 목적지까지 가는 데 드는 최소 비용 계산
            // s에서 각지점까지 가는 데 드는 최소  비용 계산\
            // 두값을 더해 나온 값들 중 최소값??
            answer = Math.min(answer, lowestCostMat[t][a] + lowestCostMat[t][b] + lowestCostMat[s][t])
            console.log(answer)
        }
    
    return answer;
}