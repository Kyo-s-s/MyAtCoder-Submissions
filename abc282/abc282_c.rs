use proconio::input;

fn main() {
    input! {
        n: usize,
        s: String,
    }

    let mut s = s.chars().collect::<Vec<char>>();
    let mut flag = true;
    let ans = s
        .iter()
        .map(|&c| {
            if c == '"' {
                flag = !flag;
            }
            if c == ',' && flag {
                '.'
            } else {
                c
            }
        })
        .collect::<String>();
    println!("{}", ans);
}
