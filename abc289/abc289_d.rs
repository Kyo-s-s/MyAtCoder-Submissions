use proconio::input;

fn main() {
    input! {
        n: usize,
        a: [i64; n],
        m: usize,
        b: [i64; m],
        x: i64,
    }

    let mut dp = vec![true; x as usize + 1];
    for b in b {
        dp[b as usize] = false;
    }

    dp[0] = true;
    for i in 1..=x {
        if !dp[i as usize] {
            continue;
        }
        dp[i as usize] = false;
        for a in &a {
            let u = i - a;
            if u >= 0 {
                dp[i as usize] |= dp[u as usize];
            }
        }
    }

    println!("{}", if dp[x as usize] { "Yes" } else { "No" });
}
