use proconio::input;

fn main() {
    input! {
        n: usize,
        query: [(usize, usize); n],
    }

    let query = query.iter().zip(0..).collect::<Vec<_>>();

    let mut need = [0; 202020];
    let mut pickup = vec![false; n];

    for (&(t, x), i) in query.iter().rev() {
        let i = *i as usize;
        match t {
            1 => {
                if need[x] > 0 {
                    need[x] -= 1;
                    pickup[i] = true;
                }
            }
            2 => {
                need[x] += 1;
            }
            _ => unreachable!(),
        }
    }

    if need.iter().any(|&x| x > 0) {
        println!("-1");
        return;
    }

    let mut hav = 0;
    let mut ans = 0;
    let mut v = vec![];
    for (&(t, _), i) in &query {
        let i = *i as usize;
        if pickup[i] {
            hav += 1;
        }
        if t == 2 {
            hav -= 1;
        }
        if t == 1 {
            v.push(if pickup[i] { 1 } else { 0 })
        }
        ans = ans.max(hav);
    }

    println!("{}", ans);
    println!(
        "{}",
        v.iter()
            .map(|&x| x.to_string())
            .collect::<Vec<_>>()
            .join(" ")
    );
}
