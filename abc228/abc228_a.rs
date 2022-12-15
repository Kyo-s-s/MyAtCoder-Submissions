use itertools::Itertools;
use proconio::input;

fn main() {
    input! {
        s: i32,
        t: i32,
        x: i32,
    }

    let mut sw = false;
    let mut ans = false;
    for now in 0..=100 {
        let n = now % 24;
        if n == s {
            sw = true;
        }
        if n == t {
            sw = false;
        }
        if n == x && sw {
            ans = true;
        }
    }

    println!("{}", if ans { "Yes" } else { "No" });

}
