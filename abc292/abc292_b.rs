use proconio::input;

fn main() {
    input! {
        n: usize,
        q: usize,
        que: [(usize, usize); q],
    }

    let mut cnt = vec![0; 200];

    for (c, x) in que {

        if c == 1 {
            cnt[x] += 1;
        }

        if c == 2 {
            cnt[x] += 2;
        }

        if c == 3 {
            if cnt[x] >= 2 {
                println!("Yes");
            } else {
                println!("No");
            }
        }

    }

}
