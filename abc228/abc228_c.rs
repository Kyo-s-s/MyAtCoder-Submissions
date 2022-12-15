use itertools::Itertools;
use proconio::input;

fn main() {
    input! {
        n: usize,
        k: usize,
        p: [(i64, i64, i64); n],
    }
    let mut p = p.iter().map(|(x, y, z)| x + y + z).collect_vec();
    let mut q = p.clone();
    q.sort();
    q.reverse();

    let kscore = q[k - 1];
    for i in p {
        println!("{}", if i + 300 >= kscore { "Yes" } else { "No" });
    }
}
