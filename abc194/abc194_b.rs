#![allow(unused_imports)]
use std::cmp::*;
use std::io::Write;
fn main() {

    let n = read::<usize>();
    let mut a: Vec<i32> = Vec::new();
    let mut b: Vec<i32> = Vec::new();
    
    for _ in 0..n {
        let v = read_vec::<i32>();
        let (s, t) = (v[0], v[1]);
        a.push(s); b.push(t);
    }

    let mut ans = 10000000;

    for i in 0..n {
        for j in 0..n {
            if i == j {
                ans = ans.min(a[i] + b[j]);
            } else {
                ans = ans.min(a[i].max(b[j]));
            }
        }
    }

    println!("{}", ans);


}

fn read<T: std::str::FromStr>() -> T { 
    let mut s = String::new();
    std::io::stdin().read_line(&mut s).ok();
    s.trim().parse().ok().unwrap()
}

fn read_vec<T: std::str::FromStr>() -> Vec<T> {
    read::<String>()
        .split_whitespace()
        .map(|e| e.parse().ok().unwrap())
        .collect()
}
