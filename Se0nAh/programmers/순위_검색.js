function solution(info, query) {
    var answer = [];
    
    const infoKey = ["lan", "job", "career", "food", "score"]
    
    const p = []
    sortedInfo = info.map(i => i.split(' ')).sort((a, b) => a[4]*1 - b[4]*1)
    // query.forEach(q => {
        // splittedQ = q.split(' ')
        // scoreCutline = splittedQ[7]
        // let start = 0 
        // let end = info.length
        // let m = end / 2 
        // while (true) {
        //     if (start < 0 || end > info.length)
        //     if(splittedQ[m] < scoreCutline) {
        //         start = m
        //         m = (end - start) / 2
        //     } else if(splittedQ[m] === scoreCutline) {
        //         m
        //     } else {
        //         end = m
        //         m = (end - start) / 2
        //     }
        // }
    // })
    return answer;
}