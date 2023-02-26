use std::collections::BTreeSet;

use proconio::input;

fn main() {
    input! {
        n: usize,
        s: String,
    }

    let s = s.chars().collect::<Vec<char>>();

    let mut now = (0, 0);
    let mut set = BTreeSet::new();

    let mut ans = false;
    set.insert(now);
    for c in s {
        match c {
            'L' => now.0 -= 1,
            'R' => now.0 += 1,
            'U' => now.1 += 1,
            'D' => now.1 -= 1,
            _ => (),
        }

        // set に now ある？
        if set.contains(&now) {
            ans = true;
            break;
        }
        set.insert(now);
    }
    println!("{}", if ans { "Yes" } else { "No" });
}
