use proconio::input;

fn main() {
    input! {
        n: usize,
        m: usize,
        s: [String; n],
    }

    let mut ans = 0;
    for i in 0..(n - 1) {
        for j in (i + 1)..n {
            let si = s[i].chars().collect::<Vec<char>>();
            let sj = s[j].chars().collect::<Vec<char>>();
            let mut add = 1;
            for k in 0..m {
                if si[k] == 'x' && sj[k] == 'x' {
                    add = 0;
                    break;
                }
            }
            ans += add;
        }
    }
    println!("{}", ans);
}
