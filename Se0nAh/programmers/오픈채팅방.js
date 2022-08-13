function solution(record) {
    var answer = [];
    const userData = {}
    for (const r of record) {
        const [state, id, name] = r.split(' ')
        if (state === "Enter") {
            userData[id] = name
        } else if (state === "Change") {
            userData[id] = name  
        }
    }
    for (const r of record) {
        const [state, id, name] = r.split(' ')
        if (state === "Enter") {
            answer.push(`${userData[id]}님이 들어왔습니다.`)
        }else if (state === "Leave") {
            answer.push(`${userData[id]}님이 나갔습니다.`)
        }
    }
    
    return answer;
}