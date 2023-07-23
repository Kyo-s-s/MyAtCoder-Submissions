let map: number[][];
let visited: number[][];

let stack: [number, number][] = [[1, 1]];

function dfs(h: number, w: number) {
    if(visited[h][w] === 2) return;
    visited[h][w] = 2;
  	const dhw = [[1, 0], [0, 1], [-1, 0], [0, -1]];
  
  	for (const [dh, dw] of dhw) {
    	let nh = h, nw = w;
      	while(map[nh][nw] !== 1) {
        	visited[nh][nw] = Math.max(visited[nh][nw], 1);
         	nh += dh;
         	nw += dw;
        }
      	stack.push([nh - dh, nw - dw]);
      	// dfs(nh - dh, nw - dw);
    }
  
}

function main(lines: string[]) {
    const [N, M] = lines[0].split(" ").map(Number); 
    // N高さ M幅
    map = lines.slice(1, N + 1).map(line => line.split("").map(c => (c === "#")? 1 : 0));
    //1 が壁 0が通路
    visited = Array(N).fill(0).map(() => Array(M).fill(0));

  	while (stack.length > 0) {
    	const [h, w] = stack.pop();
      	dfs(h, w);
    }
  
  
    // 0到達不可能 1到達可能 2分岐点    
    // let now = [1, 1];
    // 深さ優先探索
    // dfs(now[0], now[1]);
    console.log(visited.flat().filter(v => v > 0).length);
}



function readFromStdin(): Promise<string[]> {
    return new Promise(resolve => {
        let data: string = "";
        process.stdin.resume();
        process.stdin.setEncoding("utf8");

        process.stdin.on("data", d => {
            data += d;
        });
        process.stdin.on("end", () => {
            resolve(data.split("\n"));
        });
    })
}

readFromStdin().then(main)