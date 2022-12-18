use proconio::input;

// unionfind
struct UnionFind {
    par: Vec<usize>,
    rank: Vec<usize>,
}

impl UnionFind {
    fn new(n: usize) -> Self {
        UnionFind {
            par: (0..n).collect(),
            rank: vec![0; n],
        }
    }

    fn root(&mut self, x: usize) -> usize {
        if self.par[x] == x {
            x
        } else {
            let r = self.root(self.par[x]);
            self.par[x] = r;
            r
        }
    }

    fn unite(&mut self, x: usize, y: usize) {
        let x = self.root(x);
        let y = self.root(y);
        if x == y {
            return;
        }
        if self.rank[x] < self.rank[y] {
            self.par[x] = y;
        } else {
            self.par[y] = x;
            if self.rank[x] == self.rank[y] {
                self.rank[x] += 1;
            }
        }
    }

    fn same(&mut self, x: usize, y: usize) -> bool {
        self.root(x) == self.root(y)
    }
}

fn modpow(x: i64, n: i64, m: i64) -> i64 {
    let mut res = 1;
    let mut x = x;
    let mut n = n;
    while n > 0 {
        if n & 1 == 1 {
            res = res * x % m;
        }
        x = x * x % m;
        n >>= 1;
    }
    res
}

fn main() {
    input! {
        n: usize,
        m: usize,
        a: [i64; n],
    }

    let mut uf = UnionFind::new(n);
    let mut edges = vec![];
    for i in 0..(n - 1) {
        for j in (i + 1)..n {
            edges.push((
                i,
                j,
                (modpow(a[i], a[j], m as i64) + modpow(a[j], a[i], m as i64)) % m as i64,
            ));
        }
    }
    edges.sort_by_key(|&(_, _, c)| c);
    edges.reverse();

    let mut ans = 0;
    for (x, y, s) in edges {
        if !uf.same(x, y) {
            ans += s;
            uf.unite(x, y);
        }
    }
    println!("{}", ans);
}
