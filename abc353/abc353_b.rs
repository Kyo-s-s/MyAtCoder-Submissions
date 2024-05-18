fn main() {
    proconio::input! {
        n: usize,
        k: usize,
        a: [usize; n],
    }

    let mut ans = 0;
    let mut now = 0;
    for &a in a.iter() {
        if now + a > k {
            ans += 1;
            now = a;
        } else {
            now += a;
        }
    }

    if now > 0 {
        ans += 1;
    }

    println!("{}", ans);
}
