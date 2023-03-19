use itertools::Itertools;
use proconio::input;

fn main() {
    input! {
        n: usize,
        a: [i64; n],
    }

    // let ans = a.iter().filter(|&x| x % 2 == 0).collect();
    let mut ans = vec![];
    for a in a {
        if a % 2 == 0 {
            ans.push(a);
        }
    }
    println!("{}", ans.iter().join(" "));
}
