use std::f64::MAX;

use itertools::Itertools;
use proconio::input;

fn main() {
    input! {
        q: usize,
        queries: [(usize, i64); q],
    }

    let mut set = std::collections::BTreeSet::new();
    (0..(1 << 20)).for_each(|i| {
        set.insert(i);
    });
    set.insert(MAX as i64);

    let mut a = vec![-1 as i64; 1 << 20];

    for (t, xi) in queries {
        let x = xi % (1 << 20) as i64;
        if t == 1 {
            let nxv = {
                let u = set.range(x..).next().unwrap();
                if u == &(MAX as i64) {
                    set.range(0..).next().unwrap()
                } else {
                    u
                }
                .clone()
            };
            set.remove(&nxv);
            a[nxv as usize] = xi;
            // println!("dev: {} {}", nxv, xi);
        } else {
            println!("{}", a[x as usize]);
        }
    }
}
