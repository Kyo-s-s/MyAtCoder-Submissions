use proconio::input;

fn main() {
    input! {
        n: usize,
        x: [i32; n * 5],
    }
    let mut x = x;
    x.sort();

    let mut cnt = 0;
    let mut sum = 0;
    for i in n..(4 * n) {
        sum += x[i];
        // println!("{}: {}", i, x[i]);
        cnt += 1;
    }

    let ans = sum as f64 / cnt as f64;
    println!("{}", ans);
}
