use itertools::Itertools;
use proconio::input;
fn main() {
    input! {
        h: usize,
        w: usize,
        s: [String; h],
    }

    let ans = s
        .iter()
        .map(|s| s.chars().filter(|&c| c == '#').count())
        .sum::<usize>();
    println!("{}", ans);
}
