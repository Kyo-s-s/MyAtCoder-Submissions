fn main() {
    proconio::input! {
        n: usize,
        h: [usize; n],
    }

    let mut ans = -1;
    for i in 0..n {
        if i > 0 && h[i] > h[0] {
            ans = i as i32 + 1;
            break;
        }
    }

    println!("{}", ans);
}
