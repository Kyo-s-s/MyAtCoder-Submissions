use std::collections::VecDeque;

use proconio::{input, marker::Usize1};

fn main() {
    let inf = 1_000_000_000;

    input! {
        n: usize,
        m: usize,
        edges: [(Usize1, Usize1); m],
    }

    let mut graph = vec![vec![]; n];
    for &(u, v) in &edges {
        graph[u].push(v);
    }

    let mut ans = 0;

    for st in 0..n {
        let mut dist = vec![inf; n];
        dist[st] = 0;
        let mut deque = VecDeque::new();
        deque.push_back(st);

        while let Some(v) = deque.pop_front() {
            for &e in &graph[v] {
                if dist[e] > dist[v] + 1 {
                    dist[e] = dist[v] + 1;
                    deque.push_back(e);
                }
            }
        }

        for &d in &dist {
            if d != inf && d > 1 {
                ans += 1;
            }
        }
    }


    println!("{}", ans);
}
