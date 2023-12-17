use proconio::marker::Usize1;

fn main() {
    proconio::input! {
        n: usize,
        edges: [(Usize1, Usize1); n - 1],
    }

    let graph = {
        let mut graph = vec![vec![]; n];
        for (u, v) in edges {
            graph[u].push(v);
            graph[v].push(u);
        }
        graph
    };

    let mut dp = vec![usize::MAX; n];

    dfs(&graph, 0, usize::MAX, &mut dp);
    let mut sum = 0;
    let mut max = 0;
    for &i in &graph[0] {
        sum += dp[i];
        max = max.max(dp[i]);
    }
    let ans = sum - max + 1;
    println!("{}", ans);
}

fn dfs(graph: &Vec<Vec<usize>>, now: usize, prev: usize, dp: &mut Vec<usize>) -> usize {
    if dp[now] != usize::MAX {
        return dp[now];
    }
    let mut res = 0;
    for &next in &graph[now] {
        if next == prev {
            continue;
        }
        res += dfs(graph, next, now, dp);
    }
    dp[now] = res + 1;
    dp[now]
}
