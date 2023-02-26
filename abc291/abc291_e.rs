use itertools::Itertools;
use proconio::{input, marker::Usize1};

fn main() {
    input! {
        n: usize,
        m: usize,
        xy: [(Usize1, Usize1); m],
    }

    let mut g = vec![vec![]; n];
    let mut in_deg = vec![0; n];

    for &(x, y) in &xy {
        g[x].push(y);
        in_deg[y] += 1;
    }

    let mut q = std::collections::VecDeque::new();
    for i in 0..n {
        if in_deg[i] == 0 {
            q.push_back(i);
        }
    }
    let mut ans = true;

    let mut ans_vec = vec![-1; n];
    let mut add = 1;
    while let Some(v) = q.pop_front() {
        if q.len() != 0 {
            ans = false;
        }
        // println!("len(): {}", q.len());
        ans_vec[v] = add;
        add += 1;
        for &w in &g[v] {
            in_deg[w] -= 1;
            if in_deg[w] == 0 {
                q.push_back(w);
            }
        }
    }

    // ans に-1が存在？

    if ans_vec.iter().any(|&x| x == -1) {
        ans = false;
    }

    if !ans {
        println!("No");
    } else {
        println!("Yes");
        // check
        for &(x, y) in &xy {
            if ans_vec[x] > ans_vec[y] {
                panic!("{} {}", x, y);
            }
        }
        println!("{}", ans_vec.iter().join(" "));
    }
}
