fn main() {
    proconio::input! {
        n: usize,
    }

    let mut ans = 0;
    for _ in 0..n {
        ans *= 10;
        ans += n;
    }

    println!("{}", ans);
}
