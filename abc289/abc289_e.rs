use std::collections::VecDeque;

use proconio::{input, marker::Usize1};

fn solve() {
    input! {
        n: usize,
        m: usize,
        c: [i32; n],
    }
    let mut graph = vec![vec![]; n];
    for _ in 0..m {
        input! {
            u: Usize1, v: Usize1,
        }
        graph[u].push(v);
        graph[v].push(u);
    }

    let inf = 1_000_000_000;
    let mut dp = vec![vec![inf; n]; n];
    dp[0][n - 1] = 0;
    let mut deque = VecDeque::new();
    deque.push_back((0, n - 1));

    while let Some((a, b)) = deque.pop_front() {
        for &na in &graph[a] {
            for &nb in &graph[b] {
                if c[na] == c[nb] {
                    continue;
                }
                if dp[na][nb] == inf {
                    dp[na][nb] = dp[a][b] + 1;
                    deque.push_back((na, nb));
                }
            }
        }
    }

    println!(
        "{}",
        if dp[n - 1][0] == inf {
            -1
        } else {
            dp[n - 1][0]
        }
    );
}

fn main() {
    input! {
        t: usize,
    }
    for _ in 0..t {
        solve();
    }
}
