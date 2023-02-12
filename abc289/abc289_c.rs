use proconio::input;

fn main() {
    input! {
        n: usize,
        m: usize,
    }
    let mut v = vec![vec![false; n]; m];
    for i in 0..m {
        input! {
            k: usize,
            a: [usize; k],
        }
        for j in a {
            v[i][j - 1] = true;
        }
    }

    let mut ans = 0;
    for msk in 0..(1 << m) {
        let mut c = vec![false; n];
        for i in 0..m {
            if (msk >> i) & 1 == 1 {
                for j in 0..n {
                    c[j] |= v[i][j];
                }
            }
        }
        if c.iter().all(|&x| x) {
            ans += 1;
        }
    }
    println!("{}", ans);

}
