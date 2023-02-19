use proconio::input;

fn main() {
    input! {
        n: usize,
        m: usize,
        a: [i32; n],
        b: [i32; m],
    }

    let mut ans = 0;

    for i in b {
        let i = (i - 1) as usize;
        ans += a[i];
    }

    println!("{}", ans);
}
