// 기둥이나 보가 설치됐는지를 저장해서 풀려고 했는데 둘다 설치됐을 경우를 생각 못했다. 
// 이미 시간을 어느정도 쓴 상태라 안 고치고 다른 풀이를 보려고 했는데 결국 고치긴 했다. 근데 어이없는 실수를 해서 한 시간은 더 쓴 것 같다 ^^;;
function checkRange(x, y, n) {
    if (x < 0 || x >= n || y < 0 || y >= n) return false
    else return true
}

function isPillar(x, y, frame) {
    if(!checkRange(x, y, frame.length)) return false
    return frame[x][y] % 2 === 0
}
function isPannel(x, y, frame) {
    if(!checkRange(x, y, frame.length)) return false
    return frame[x][y] > 0
}
function makeNewFrame(frame) {
    const newFrame = []
    for(let i=0; i< frame.length; i++) {
        newFrame.push([...frame[i]])
    }
    return newFrame
}

function checkPannel(x, y, frame) {
    if(!isPannel(x,y, frame)) {
        return true
    } else {
        if (isPillar(x,y-1, frame) || 
            isPillar(x+1,y-1, frame) || 
            (isPannel(x-1,y, frame) && isPannel(x+1, y, frame))) {
            return true
        } else {
            return false
        }
    }
}

function checkPillar(x, y, frame) {
    if(!isPillar(x,y, frame)) {
        return true
    } else {
        if (y === 0 || 
            isPannel(x-1,y, frame) || 
            isPannel(x,y, frame) || 
            isPillar(x,y-1, frame)
           ) 
        {
            return true
        } else {
            return false
        }
    }
}

function check(frame) {
    for(let x = 0; x < frame.length; x++){
        for(let y = 0; y < frame.length; y++){
            if(!checkPannel(x, y, frame) || !checkPillar(x, y, frame)){
                return false
            }
        }
    }
    return true
}

function solution(n, build_frame) {
    const answer = []
    let frame = []
    for (let i=0; i<n+1; i++) {
        frame.push(Array(n+1).fill(-1))
    }
    const newFrame = makeNewFrame(frame)
    for (const build of build_frame) {
        const [x, y, a, b] = build
        const newFrame = makeNewFrame(frame)
        if (b === 0) {
            if(newFrame[x][y] === 2) {
                if(a === 1) newFrame[x][y] = 0
                if(a === 0) newFrame[x][y] = 1   
            } else {
                newFrame[x][y] = -1
            }
        } else {
            if(newFrame[x][y] !== -1) {
                newFrame[x][y] = 2
            } else {
                newFrame[x][y] = a
            }
        }
        if(check(newFrame)) {
            frame = newFrame
        }
    }
    for(let x = 0; x < frame.length; x++){
        for(let y = 0; y < frame.length; y++){
            if(frame[x][y] === 0 || frame[x][y] === 1) {
                answer.push([x,y,frame[x][y]])
            } else if (frame[x][y] === 2) {
                answer.push([x,y,0])
                answer.push([x,y,1])
                
            }
        }
    }
    return answer;
}