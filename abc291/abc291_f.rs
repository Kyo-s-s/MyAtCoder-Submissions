use itertools::Itertools;
use proconio::input;
use std::cmp::{max, min};

const INF: i32 = 1_000_000_000;

fn main() {
    input! {
        n: usize,
        m: usize,
        s: [String; n],
    }

    let s = s
        .iter()
        .map(|s| s.chars().collect::<Vec<_>>())
        .collect::<Vec<_>>();

    let mut g = vec![vec![]; n];
    let mut g_inv = vec![vec![]; n];
    for i in 0..n {
        for j in 0..m {
            if s[i][j] == '1' {
                g[i].push(i + j + 1);
                g_inv[i + j + 1].push(i);
            }
        }
    }

    let mut s_to = vec![INF; n];
    let mut to_t = vec![INF; n];

    let mut q = std::collections::VecDeque::new();
    s_to[0] = 0;
    q.push_back(0);
    while let Some(v) = q.pop_front() {
        for &w in &g[v] {
            if s_to[w] == INF {
                s_to[w] = s_to[v] + 1;
                q.push_back(w);
            }
        }
    }

    let mut q = std::collections::VecDeque::new();
    to_t[n - 1] = 0;
    q.push_back(n - 1);
    while let Some(v) = q.pop_front() {
        for &w in &g_inv[v] {
            if to_t[w] == INF {
                to_t[w] = to_t[v] + 1;
                q.push_back(w);
            }
        }
    }
    let mut ans = vec![];
    for k in 1..(n - 1) {
        // k が無いとき
        // -10 くらいみればよい
        let mut mi = INF;

        let st = max(0, (k as i32 - 12)) as usize;
        for s in st..k {
            for &w in &g[s] {
                if k < w {
                    mi = min(mi, s_to[s] + to_t[w] + 1);
                    // println!("! {}, {}", s, w);
                }
            }
        }
        ans.push(mi);
    }

    ans = ans
        .iter()
        .map(|&x| if x == INF { -1 } else { x })
        .collect::<Vec<_>>();

    println!("{}", ans.iter().join(" "));
}
