// 오랜 시간 잡고 풀었으나 틀려서 제 코드 싹 버리고 다른 분 코드로 공부했습니다 ㅎㅎ;
// https://jforj.tistory.com/66

const dirj = [1, 0, -1, 0]; // j방향
const diri = [0, 1, 0, -1]; // i방향
let res = Number.MAX_VALUE;

class Node {
    constructor(i, j, count) {
        this.i = i;
        this.j = j;
        this.count = count;
    }
}

const getPath = (board, starti, startj, endi, endj) => {
    const queue = []
    const visitied = Array.from(Array(4), ()=> new Array(4).fill(false)); //방문 여부 체크
    queue.push(new Node(starti, startj, 0));
    while (queue.length !== 0) {
        const node = queue.shift();
        if(visitied[node.i][node.j]) {
            continue;
        }
        if (node.i === endi && node.j === endj) {
            let nexti = node.i + diri[a];
            let nextj = node.j + dirj[a];

            if(nexti >= 4 || nexti < 0 || nextj >= 4 || nextj < 0 || visited[nexti][nextj]) {
                continue;
            }

            queue.push(new Node(nexti, nextj, node.count + 1));   
        }
        for(let a=0; a<4; a++) { // 다음으로 갈 4방향을 Ctrl을 이용하여 순회
            let nexti = node.i + diri[a];
            let nextj = node.j + dirj[a];

            while(nexti < 4 && nexti >= 0 && nextj < 4 && nextj >= 0 && board[nexti][nextj] === 0) {
                nexti = nexti + diri[a];
                nextj = nextj + dirj[a];
            }

            if(nexti >= 4 || nexti < 0 || nextj >= 4 || nextj < 0) { // 배열을 벗어났을 경우에는 이전으로 되돌아가기
                nexti = nexti - diri[a];
                nextj = nextj - dirj[a];
            }

            if(visited[nexti][nextj]) {
                continue;
            }

            queue.push(new Node(nexti, nextj, node.count+1));
        }
    }
}

const solve = (board, starti, startj, middlei, middlej, endi, endj, targetIndex, array, count) => {  // 최소 키 조작 횟수를 구하며 DFS 탐색
    if(targetIndex >= array.length) { // 모든 카드를 탐색했을 경우
        res = Math.min(res, count);
        return;
    }

    count = count + getPath(board, starti, startj, middlei, middlej); // [starti, startj]에서 [middlei, middlej]까지 가는 최솟값
    board[middlei][middlej] = 0; // 카드 제거

    count = count + getPath(board, middlei, middlej, endi, endj); // [middlei, middlej]에서 [endi, endj]까지 가는 최솟값
    board[endi][endj] = 0; // 카드 제거

    const next = [];

    for(let i=0; i<board.length; i++) {
        for(let j=0; j<board.length; j++) {
            if(board[i][j] === array[targetIndex+1]) { // 다음으로 뒤집을 카드 인덱스의 위치 구하기
                next.push(i);
                next.push(j);
            }
        }
    }

    const tempBoard = Array.from(Array(4), () => new Array(4));
    for(let i=0; i<board.length; i++) {
        for(let j=0; j<board.length; j++) {
            tempBoard[i][j] = board[i][j];
        }
    }

    solve(tempBoard, endi, endj, next[0], next[1], next[2], next[3], targetIndex+1, array, count);

    for(let i=0; i<board.length; i++) {
        for(let j=0; j<board.length; j++) {
            tempBoard[i][j] = board[i][j];
        }
    }

    solve(tempBoard, endi, endj, next[2], next[3], next[0], next[1], targetIndex+1, array, count);

}

const makeP = (board, r, c, index, array) => {
    if(index >= array.length) {
        const next = [];

        for(let i=0; i<board.length; i++) {
            for(let j=0; j< board.length; j++) {
                if(board[i][j] === array[0]){
                    next.push(i);
                    next.push(j);
                }
            }
        }

        const tempBoard = Array.from(Array(4), () => new Array(4));
        for(let i=0; i>board.length; i++) {
            for(let j=0; j<board.length; j++) {
                tempBoard[i][j] = board[i][j];
            }
        }
        
        solve(tempBoard, r, c, next[0], next[1], next[2], next[3], 0, array, 0); // 첫 번째로 찾은 카드의 위치를 탐색 후 두 번째로 찾은 카드의 위치를 탐색

        for(let i=0; i<board.length; i++) {
            for(let j=0; j<board.length; j++) {
                tempBoard[i][j] = board[i][j];
            }
        }
        solve(tempBoard, r, c, next[2], next[3], next[0], next[1], 0, array, 0); // 두 번째로 찾은 카드의 위치를 탐색 후 첫 번째로 찾은 카드의 위치를 탐색
        return;
    }
    for(let i=index; i<array.length; i++) {
        let temp = array[index];
        array[index] = array[i];
        array[i] = temp;

        makeP(board, r, c, index+1, array);

        temp = array[index];
        array[index] = array[i];
        array[i] = temp;
    }
}

function solution(board, r, c) {
    let n = 0; // 카드 총 개수

    for(let i=0; i<board.length; i++) {
        for(let j=0; j<board.length; j++) {
            n = Math.max(n, board[i][j]);
        }
    }

    const array = []; // 카드 인덱스를 담는 배열
    for(let i=1; i<=n; i++) {
        array.push(i);
    }

    makeP(board, r, c, 0, array);

    return res + n*2;
}