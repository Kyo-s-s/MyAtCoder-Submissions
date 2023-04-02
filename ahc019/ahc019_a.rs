use itertools::Itertools;

struct Solver {
    d: usize,
    f: Vec<Vec<Vec<bool>>>,
    r: Vec<Vec<Vec<bool>>>,
}

impl Solver {
    fn new() -> Self {
        proconio::input! {
            d: usize,
            f1: [String; d],
            r1: [String; d],
            f2: [String; d],
            r2: [String; d],
        }
        Self {
            d,
            f: vec![
                f1.iter()
                    .map(|s| s.chars().map(|c| c == '1').collect())
                    .collect(),
                f2.iter()
                    .map(|s| s.chars().map(|c| c == '1').collect())
                    .collect(),
            ],
            r: vec![
                r1.iter()
                    .map(|s| s.chars().map(|c| c == '1').collect())
                    .collect(),
                r2.iter()
                    .map(|s| s.chars().map(|c| c == '1').collect())
                    .collect(),
            ],
        }
    }

    fn solve(&self) {
        let mut b = vec![
            vec![0; self.d * self.d * self.d],
            vec![0; self.d * self.d * self.d],
        ];
        let mut n = 0;
        let mut cf = vec![vec![vec![false; self.d]; self.d]; 2];
        let mut cr = vec![vec![vec![false; self.d]; self.d]; 2];

        let ch = |x: usize, y: usize, z: usize| x * self.d * self.d + y * self.d + z;

        for i in 0..2 {
            let mut cn = 0;
            for x in 0..self.d {
                for y in 0..self.d {
                    for z in 0..self.d {
                        if self.f[i][z][x] && self.r[i][z][y] && !(cf[i][z][x] && cr[i][z][y]) {
                            cn += 1;
                            cf[i][z][x] = true;
                            cr[i][z][y] = true;
                            b[i][ch(x, y, z)] = cn;
                        }
                    }
                }
            }
            n = std::cmp::max(n, cn);
        }
        println!("{}", n);
        println!("{}", b[0].iter().join(" "));
        println!("{}", b[1].iter().join(" "));
    }
}

fn main() {
    let solver = Solver::new();
    solver.solve();
}
