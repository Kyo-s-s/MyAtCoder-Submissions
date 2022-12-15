use itertools::Itertools;
use proconio::input;

fn main() {
    input! {
        n: usize,
        x: usize,
        a: [usize; n],
    }

    let mut know = vec![false; n + 1];
    let mut queue = std::collections::VecDeque::new();
    queue.push_back(x);
    while queue.is_empty() == false {
        let u = queue.pop_front().unwrap();
        if know[u] == true {
            continue;
        }
        know[u] = true;
        queue.push_back(a[u - 1]);
    }

    let ans = know.iter().filter(|&&x| x).count();
    println!("{}", ans);
}
