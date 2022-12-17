use proconio::input;

fn main() {
    input! {
        k: usize,
    }
    let s = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    println!("{}", s.chars().take(k).collect::<String>());
}
