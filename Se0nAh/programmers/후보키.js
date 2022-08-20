
function getCombinations (arr, selectNumber) {
    const results = [];
    if (selectNumber === 1) return arr.map((el) => [el])
    
    arr.forEach((fixed, index, origin) => {
        const rest = origin.slice(index + 1)
        const combi = getCombinations(rest, selectNumber - 1)
        const attached = combi.map((el) => [fixed, ...el])
        results.push(...attached)
    })
    return results
}

function makeKey (combi, arr) {
    let key = ""
    for(const index of combi) {
        key += arr[index]
    }
    return key
}

function checkMinimality(keyCombi, candidateKeyList) {
    for (const cKey of candidateKeyList) {
        if (new Set(keyCombi.concat(cKey)).size === keyCombi.length) {
            return false
        }
    }
    return true
}

function solution(relation) {
    const columnCount = relation[0].length
    const columnList = Array(columnCount).fill(0).map((el, index)=> {return index})
    const combi = {}
    const candidateKeyList = []
    for (let i = 1; i <= columnCount; i++) {
        combi[i] = getCombinations(columnList, i)
        for (const c of combi[i]) {
            if (!checkMinimality(c, candidateKeyList)) continue
            const checkSet = []
            relation.map((r)=>checkSet.push(makeKey(c, r)))
            if(new Set(checkSet).size === relation.length) {
                candidateKeyList.push(c)
            }
        }
    }
    
    var answer = candidateKeyList.length;
    return answer;
}