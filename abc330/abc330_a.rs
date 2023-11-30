fn main() {
    proconio::input! {
        n: usize,
        l: usize,
        a: [usize; n],
    }
    let ans = a.iter().filter(|&&x| x >= l).count();
    println!("{}", ans);
}
