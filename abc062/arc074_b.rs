use proconio::input;

fn main() {
    input! {
        n: usize,
        a: [i64; 3 * n],
    }

    // iより前/後 で考えて、舐めてく 逆にしてmax/ min をよしなに

    let mut prev_max = vec![];
    // [0, i) としたときの上位 n 個の和の総和
    // 最小取得priority_queue
    let mut pq = std::collections::BinaryHeap::new();
    // 最初のn個入れる
    let mut sum = 0;
    for i in 0..n {
        sum += a[i];
        pq.push(std::cmp::Reverse(a[i]));
    }
    prev_max.push(sum);
    for i in n..(2 * n) {
        // 追加
        sum += a[i];
        pq.push(std::cmp::Reverse(a[i]));

        // 一番小さいのを引く
        if let Some(std::cmp::Reverse(x)) = pq.pop() {
            sum -= x;
        }
        prev_max.push(sum);
    }

    let mut rev_a = a.clone();
    rev_a.reverse();
    let mut pq = std::collections::BinaryHeap::new();
    let mut sum = 0;
    for i in 0..n {
        sum += rev_a[i];
        pq.push(rev_a[i]);
    }
    let mut next_min = vec![sum];
    for i in n..(2 * n) {
        // 追加
        sum += rev_a[i];
        pq.push(rev_a[i]);

        // 一番大きい
        if let Some(x) = pq.pop() {
            sum -= x;
        }
        next_min.push(sum);
    }

    next_min.reverse();
    let mut ans = std::i64::MIN;
    for i in 0..next_min.len() {
        ans = std::cmp::max(ans, prev_max[i] - next_min[i]);
    }

    // println!("{}", prev_max.iter().join(" "));
    // next_min.reverse();
    // println!("{}", next_min.iter().join(" "));
    println!("{}", ans);
}
