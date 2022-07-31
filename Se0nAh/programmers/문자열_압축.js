// 1시간?92점??ㅋㅋㅋㅋ 2번 20번 틀림
// + 반복되는 문자가 10개 포함된 테스트케이스를 확인하고 고침
// 반복되는 문자개수가 10의 자리수가 넘어갈 수 있었단건 알고 있었으나 count를 0으로 시작해서 틀림... 1로 시작했어야했다
function solution(s) {
    // 단위별 압축 길이를 담는 result 배열
    let result = [s.length];
    
    //단위를 1씩 늘리며 확인
    for (let i = 1; i <= s.length ; i++) {
        // 반복되는 문자개수를 기록하기 위한 count 변수
        let count = 1
        let currentStr = s.slice(0, i)
        let next = i
        result[i] = 0
        // 단위 길이만큼의 다음 문자열이 있을 때까지 반복
        while (next + i <= s.length) {
            const nextStr = s.slice(next, next + i)
            //현재 선택된 문자열이 다음 문자열과 같으면 count를 늘리고 다음 문자열 탐색
            if (currentStr === nextStr){
                count += 1 
                next = next + i
            } else {
            // 현재 선택된 문자열이 다음 문자열과 다르면 현재 단위의 길이만큼 더해줌
            // 기존에 반복되는 문자열을 세고 있었다면 반복 개수도 압축 문자열에 포함시켜야하므로 count의 길이를 또 더해줌
                result[i] += i
                if (count > 1) {
                    console.log(count)
                    result[i] += count.toString().length
                }
                count = 1
                currentStr = nextStr
                next = next + i
            }
        }
        // 세고 있던 반복 개수 더해주고 남은 문자열 길이 더해줌
        if (count > 1) {
            console.log(count)
            result[i] += count.toString().length
        }
        result[i] += i
        if (next < s.length) {
            result[i] += (s.length -next)
        }
    }
    return Math.min(...result);
}