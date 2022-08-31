use proconio::input;

fn main() {
    input! {
        a: i64,
    }
    println!("{}", a + a*a + a*a*a);
}
