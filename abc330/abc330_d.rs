fn main() {
    proconio::input! {
        n: usize,
        s: [String; n],
    }
    let s = s
        .iter()
        .map(|x| x.chars().collect::<Vec<_>>())
        .collect::<Vec<_>>();

    let (row, col) = {
        let mut row = vec![0 as i64; n];
        let mut col = vec![0 as i64; n];
        for i in 0..n {
            for j in 0..n {
                if s[i][j] == 'o' {
                    row[i] += 1;
                    col[j] += 1;
                }
            }
        }
        (row, col)
    };

    let mut ans = 0;
    for i in 0..n {
        for j in 0..n {
            if s[i][j] == 'o' {
                ans += (row[i] - 1) * (col[j] - 1);
            }
        }
    }
    println!("{}", ans);
}
