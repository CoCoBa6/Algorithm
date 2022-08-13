// 잘 모르겠어서 일단 아래 풀이 보고 공부했습니다 ,,
// https://velog.io/@longroadhome/%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%A8%B8%EC%8A%A4-LV.3-%EC%99%B8%EB%B2%BD%EC%A0%90%EA%B2%80-JS

function solution (n, weak, dist) {
    const len = weak.length
    const linearWeak = new Array(len*2 - 1).fill(0)

    for(let i = 0; i < len*2-1; i++) {
        linearWeak[i] = i < len ? weak[i] : weak[i-len] + n
    }
    dist.sort((a, b) => b - a)

    for(let i = 1; i <= dist.length; i++) {
        const permutation = getPermutation(dist, i)

        for(const p of permutaion) {
            for(let j = 0; j< len; j++) {
                let line = linearWeak.slice(j, len+j)
                for(const p of permu) {
                    const coverage = line[0] + p;
                    line = line.filter(e => e > coverage)
                    if(!line.length) return i;
                }
            }
        }
    }

    return -1;
}

const getPermutation = (arr, n) => {
    if(n === 1) return arr.map(el => [el])
    const result = []

    arr.forEach((fixed, idx, origin) => {
        const rest = [...origin.slice(0, idx), ...origin.slice(idx+1)]
        const perms = getPermutation(rest, n-1)
        const attached = perms.map(p => [fixed, ...p])
        result.push(...attached)
    })
    return result
}