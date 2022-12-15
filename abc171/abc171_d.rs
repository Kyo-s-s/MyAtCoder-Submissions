use proconio::input;

fn main() {
    input! {
        n: i64,
        a: [i64; n as usize],
        q: i64,
        m: [(i64, i64); q as usize],
    }

    let mut cnt = vec![0; 101010];
    let mut su = a.iter().sum::<i64>();
    for u in a {
        cnt[u as usize] += 1;
    }

    for (b, c) in m {
        su += (c - b) * cnt[b as usize];
        cnt[c as usize] += cnt[b as usize];
        cnt[b as usize] = 0;
        println!("{}", su);
    }
}
