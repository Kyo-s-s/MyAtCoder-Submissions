use std::collections::VecDeque;

use proconio::input;

fn main() {
    input! {
        n: usize,
        m: usize,
        edges: [(usize, usize); m],
    }

    let mut g = vec![vec![]; n];
    for (a, b) in edges {
        g[a - 1].push(b - 1);
        g[b - 1].push(a - 1);
    }

    let mut visited = vec![false; n];
    let mut color = vec![false; n];

    let mut ok = true;
    let mut ans = -(m as i64);
    // let mut ans = 0 as i64;
    let mut u = n as i64;
    for i in 0..n {
        if visited[i] {
            continue;
        }
        let mut que = VecDeque::new();
        que.push_back(i);
        visited[i] = true;
        color[i] = true;
        let mut black = 1;
        let mut white = 0;
        while !que.is_empty() {
            let v = que.pop_front().unwrap();
            for &e in &g[v] {
                if visited[e] {
                    if color[e] == color[v] {
                        ok = false;
                    }
                } else {
                    visited[e] = true;
                    color[e] = !color[v];
                    if color[e] {
                        black += 1;
                    } else {
                        white += 1;
                    }
                    que.push_back(e);
                }
            }
        }
        ans += black * white;
        u -= black + white;
        ans += (black + white) * u;
    }

    println!("{}", if ok { ans } else { 0 });
}
