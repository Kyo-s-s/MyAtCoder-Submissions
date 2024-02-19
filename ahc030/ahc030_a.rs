
// path: timer.rs
use std::time::SystemTime;

pub struct Timer {
    start: SystemTime,
}

impl Timer {
    pub fn new() -> Timer {
        Timer {
            start: SystemTime::now(),
        }
    }

    pub fn get_time(&self) -> f64 {
        let elapsed = self.start.elapsed().expect("Time elapsed failed");
        let elapsed_secs = elapsed.as_secs() as f64;
        let elapsed_micros = elapsed.subsec_micros() as f64;
        elapsed_secs + elapsed_micros / 1_000_000.0
    }
}

pub const TL: f64 = 2.8;

// path: random.rs
extern crate rand;

use rand::{seq::SliceRandom, Rng};

pub struct Random {}

impl Random {
    pub fn get_f() -> f64 {
        rand::thread_rng().gen_range(0.0..1.0)
    }

    pub fn get(range: std::ops::Range<usize>) -> usize {
        rand::thread_rng().gen_range(range)
    }

    pub fn _get_2d(range: std::ops::Range<usize>) -> (usize, usize) {
        (Self::get(range.clone()), Self::get(range))
    }

    pub fn get_item<T>(items: &[T]) -> &T {
        &items[Self::get(0..items.len())]
    }

    pub fn shuffle<T>(items: &mut [T]) {
        items.shuffle(&mut rand::thread_rng());
    }
}

// path: io.rs
use itertools::Itertools;
use proconio::{input, source::line::LineSource};
use std::{io::BufRead, process::exit};

pub struct IO<R: BufRead> {
    source: LineSource<R>,
    cost: f64,
    pub query_cnt: usize,
    excavate_history: Vec<((usize, usize), usize)>,
    submit_history: Vec<Vec<(usize, usize)>>,
}

impl<R: BufRead> IO<R> {
    pub fn new(mut source: LineSource<R>) -> Self {
        input! {
            from &mut source,
        }

        Self {
            source,
            cost: 0.0,
            query_cnt: 0,
            excavate_history: vec![],
            submit_history: vec![],
        }
    }

    pub fn init(&mut self) -> (usize, usize, f64, Vec<Vec<(usize, usize)>>) {
        input! {
            from &mut self.source,
            n: usize,
            m: usize,
            e: f64,
        }
        let oilfields = (0..m)
            .map(|_| {
                input! {
                    from &mut self.source,
                    d: usize,
                    oilfield: [(usize, usize); d],
                }
                oilfield
            })
            .collect::<Vec<_>>();
        (n, m, e, oilfields)
    }

    pub fn excavate(&mut self, (x, y): (usize, usize)) -> usize {
        if let Some(&(_, v)) = self
            .excavate_history
            .iter()
            .find(|&&((hx, hy), _)| hx == x && hy == y)
        {
            return v;
        }
        self.cost += 1.0;
        self.query_cnt += 1;
        println!("q 1 {} {}", x, y);
        input! {
            from &mut self.source,
            res: usize,
        }
        self.excavate_history.push(((x, y), res));
        res
    }

    pub fn predict(&mut self, s: &Vec<(usize, usize)>) -> f64 {
        let d = s.len();
        self.cost += 1.0 / (d as f64).sqrt();
        self.query_cnt += 1;
        let s = s.iter().map(|(x, y)| format!("{} {}", x, y)).join(" ");
        println!("q {} {}", d, s);
        input! {
            from &mut self.source,
            res: f64,
        }
        res
    }

    pub fn submit(&mut self, ans: Vec<(usize, usize)>) {
        if self.submit_history.contains(&ans) {
            return;
        }
        self.cost += 1.0;
        self.query_cnt += 1;
        self.submit_history.push(ans.clone());
        let d = ans.len();
        let ans = ans.iter().map(|(x, y)| format!("{} {}", x, y)).join(" ");
        println!("a {} {}", d, ans);
        input! {
            from &mut self.source,
            res: usize,
        }
        if res == 1 {
            println!("# submit success! cost: {}", self.cost);
            exit(0);
        }
        println!("# submit failed! {} {}", d, ans);
    }
}

// path: solver.rs

enum Query {
    Excavate((usize, usize)),
    Predict(Vec<(usize, usize)>),
}

pub struct Solver<R: BufRead> {
    timer: Timer,
    n: usize,
    m: usize,
    e: f64,
    oilfields: Vec<Vec<(usize, usize)>>,
    io: IO<R>,
    probability: Probability,
}

impl<R: BufRead> Solver<R> {
    pub fn new(
        timer: Timer,
        io: IO<R>,
        n: usize,
        m: usize,
        e: f64,
        oilfields: Vec<Vec<(usize, usize)>>,
    ) -> Self {
        Self {
            timer,
            n,
            m,
            e,
            oilfields: oilfields.clone(),
            io,
            probability: Probability::new(n, m, e, oilfields),
        }
    }

    fn excavate(&mut self, (x, y): (usize, usize)) -> usize {
        let v = self.io.excavate((x, y));
        self.probability.update_excavate((x, y), v);
        v
    }

    fn predict(&mut self, set: &Vec<(usize, usize)>) -> f64 {
        let v = self.io.predict(set);
        self.probability.update_predict(set, v);
        v
    }

    fn submit(&mut self, ans: Vec<(usize, usize)>) {
        self.io.submit(ans);
    }

    fn next_query(&self, is_excavated: &[Vec<bool>]) -> Query {
        let p = self.probability.expected_value();
        // 期待値 0.25 < p < 0.75 のセルから、 0.5に一番近い掘っていないものを選ぶ
        if let Some(pair) = self.next_excavate_good_pos(is_excavated, &p) {
            return Query::Excavate(pair);
        }

        // Predict
        if let Some(set) = self.next_predict(is_excavated, &p) {
            return Query::Predict(set);
        }

        // 上ですり抜けてるケースを補間
        // if let Some(pair) = self.next_excavate_good_pos(is_excavated, &p) {
        //     return Query::Excavate(pair);
        // }

        // まだ掘っていないセルからランダムに選ぶ
        Query::Excavate(self.next_random_pos(is_excavated, &p))
    }

    fn next_excavate_good_pos(
        &self,
        is_excavated: &[Vec<bool>],
        p: &[Vec<f64>],
    ) -> Option<(usize, usize)> {
        if let Some((_, (x, y))) = (0..self.n)
            .flat_map(|i| (0..self.n).map(move |j| (i, j)))
            .map(|(x, y)| (p[x][y], (x, y)))
            .filter(|&(_, (x, y))| !is_excavated[x][y])
            // これなに？謎
            // ここの制約を厳しくして、Predictへ誘導？
            // .filter(|&(p, _)| 0.02 < p && p < 1.) // こっちのほうがスコアは良い(それはそう、出ちゃうとRandomなので)
            // .filter(|&(p, _)| 0.05 < p && p < 1.) // こっちのほうがスコアは良い(それはそう、出ちゃうとRandomなので)
            .filter(|&(p, _)| 0.1 < p && p < 1.) // こっちのほうがスコアは良い(それはそう、出ちゃうとRandomなので)
            .min_by(|a, b| {
                let f = |x: f64| (x - 0.6).abs();
                let a = f(a.0);
                let b = f(b.0);
                a.partial_cmp(&b).unwrap()
            })
        {
            Some((x, y))
        } else {
            None
        }
    }

    fn next_predict(
        &self,
        is_excavated: &[Vec<bool>],
        p: &[Vec<f64>],
    ) -> Option<Vec<(usize, usize)>> {
        if self.io.query_cnt > self.n * self.n * 2 / 3 {
            return None;
        }
        // このままだとTLまでずっとこれをやってしまう
        if Random::get_f() < 0.5 {
            return None;
        }
        let less = (0..self.n)
            .flat_map(|i| (0..self.n).map(move |j| (i, j)))
            .filter(|&(x, y)| !is_excavated[x][y] && 0. < p[x][y] && p[x][y] < 0.2)
            .collect::<Vec<_>>();

        if less.is_empty() {
            return None;
        }

        let center = *Random::get_item(&less);
        let mut less = less
            .into_iter()
            .map(|(x, y)| {
                (
                    (x as i64 - center.0 as i64).abs() + (y as i64 - center.1 as i64).abs(),
                    (x, y),
                )
            })
            .collect::<Vec<_>>();

        less.sort_by(|a, b| a.0.cmp(&b.0));

        // Random::shuffle(&mut less);
        // なんか近くのをいい感じに選ぶとよさげ
        let k = Random::get(11..21);
        if less.len() < k {
            None
        } else {
            Some(less.into_iter().map(|(_, (x, y))| (x, y)).take(k).collect())
        }
    }

    fn next_random_pos(&self, is_excavated: &[Vec<bool>], p: &[Vec<f64>]) -> (usize, usize) {
        let points = (0..self.n)
            .flat_map(|i| (0..self.n).map(move |j| (i, j)))
            .filter(|&(x, y)| !is_excavated[x][y])
            .filter(|&(x, y)| 0. < p[x][y] && p[x][y] < 10000.0)
            .map(|(x, y)| (p[x][y], (x, y)))
            .collect::<Vec<_>>();

        if points.is_empty() {
            (0, 0)
        } else {
            // *Random::get_item(&points)
            points
                .iter()
                .max_by(|a, b| a.0.partial_cmp(&b.0).unwrap())
                .unwrap()
                .1
        }
    }

    // TODO: self.e によってもかえる
    fn divide(&self) -> Vec<usize> {
        let oilfield_size_ave = self
            .oilfields
            .iter()
            .map(|oilfield| oilfield.len())
            .sum::<usize>() as f64
            / self.m as f64;

        if oilfield_size_ave < 6.0 {
            match self.n {
                10 => vec![2, 3, 2, 3],
                11 => vec![3, 3, 3, 2],
                12 => vec![3, 3, 3, 3],
                13 => vec![3, 3, 4, 3],
                14 => vec![3, 4, 4, 3],
                15 => vec![3, 3, 3, 3, 3],
                16 => vec![3, 3, 3, 4, 3],
                17 => vec![3, 4, 3, 4, 3],
                18 => vec![3, 3, 3, 3, 3, 3],
                19 => vec![3, 3, 3, 3, 4, 3],
                20 => vec![3, 4, 3, 3, 4, 3],
                _ => unimplemented!("n = {}", self.n),
            }
        } else if oilfield_size_ave < 30.0 {
            match self.n {
                10 => vec![3, 3, 4],
                11 => vec![3, 4, 4],
                12 => vec![4, 4, 4],
                13 => vec![4, 4, 5],
                14 => vec![4, 5, 5],
                15 => vec![5, 5, 5],
                16 => vec![4, 4, 4, 4],
                17 => vec![4, 4, 4, 5],
                18 => vec![4, 4, 5, 5],
                19 => vec![4, 5, 5, 5],
                20 => vec![5, 5, 5, 5],
                _ => unimplemented!("n = {}", self.n),
            }
        } else {
            match self.n {
                10 => vec![5, 5],
                11 => vec![5, 6],
                12 => vec![6, 6],
                13 => vec![6, 7],
                14 => vec![7, 7],
                15 => vec![5, 5, 5],
                16 => vec![5, 6, 5],
                17 => vec![6, 5, 6],
                18 => vec![6, 6, 6],
                19 => vec![6, 7, 6],
                20 => vec![7, 6, 7],
                _ => unimplemented!("n = {}", self.n),
            }
        }
    }

    fn preprocess_predict(&self) -> Vec<Vec<(usize, usize)>> {
        let div = self.divide();
        let mut ret = vec![];
        let mut x = 0;
        for &dx in &div {
            let mut y = 0;
            for &dy in &div {
                let mut set = vec![];
                for i in x..x + dx {
                    for j in y..y + dy {
                        set.push((i, j));
                    }
                }
                ret.push(set);
                y += dy;
            }
            x += dx;
        }
        ret
    }

    pub fn solve(&mut self) {
        let mut is_excavated = vec![vec![false; self.n]; self.n];

        for set in self.preprocess_predict() {
            self.predict(&set);
        }

        while self.timer.get_time() < TL {
            let query = self.next_query(&is_excavated);
            match query {
                Query::Excavate((x, y)) => {
                    self.excavate((x, y));
                    if !is_excavated[x][y] {
                        is_excavated[x][y] = true;
                    }
                }
                Query::Predict(set) => {
                    self.predict(&set);
                }
            }
            if let Some(ans) = self.probability.solved_check(&self.io) {
                self.submit(ans);
            }
            if is_excavated.iter().flatten().all(|&b| b) {
                break;
            }
        }

        self.honesty();
    }

    fn honesty(&mut self) {
        let p = self.probability.expected_value();
        let mut pos = (0..self.n)
            .flat_map(|i| (0..self.n).map(move |j| (i, j)))
            .map(|(x, y)| {
                (
                    if p[x][y].is_infinite() || p[x][y].is_nan() {
                        1.
                    } else {
                        p[x][y]
                    },
                    (x, y),
                )
            })
            .collect::<Vec<_>>();

        pos.sort_by(|a, b| b.0.partial_cmp(&a.0).unwrap());

        for (_, (x, y)) in pos.iter() {
            self.excavate((*x, *y));
            if let Some(ans) = self.probability.all_excavate(&self.io) {
                self.io.submit(ans);
            }
        }

        // let mut island = vec![vec![false; self.n]; self.n];
        // for (x, island) in island.iter_mut().enumerate() {
        //     for (y, island) in island.iter_mut().enumerate() {
        //         *island = self.excavate((x, y)) > 0;
        //         self.io.debug(DEBUG, "honesty");

        //         if let Some(ans) = self.probability.all_excavate(&self.io) {
        //             self.io.submit(ans);
        //         }
        //     }
        // }

        // let ans = (0..self.n)
        //     .flat_map(|i| (0..self.n).map(move |j| (i, j)))
        //     .filter(|&(i, j)| island[i][j])
        //     .collect::<Vec<_>>();

        // self.io.submit(ans);
    }
}

// path: probability.rs

pub struct Probability {
    n: usize,
    m: usize,
    e: f64,
    oilfields: Vec<Vec<(usize, usize)>>,
    oilfields_count: Vec<(usize, usize)>, // idx, sum
    pub p: Vec<Vec<Vec<f64>>>,
    excavate_history: Vec<((usize, usize), usize)>,
    predict_history: Vec<(Vec<(usize, usize)>, f64)>,
}

impl Probability {
    pub fn new(n: usize, m: usize, e: f64, oilfields: Vec<Vec<(usize, usize)>>) -> Self {
        let p = (0..m)
            .map(|i| {
                let (mx, my) = oilfields[i]
                    .iter()
                    .fold((0, 0), |(mx, my), &(x, y)| (mx.max(x), my.max(y)));
                vec![vec![1.0 / ((n - mx) as f64 * (n - my) as f64); n - my]; n - mx]
            })
            .collect::<Vec<_>>();

        let oilfields_count = (0..m)
            .map(|i| {
                let mut idx = 1;
                let mut cnt = 1;
                for j in 0..m {
                    if oilfields[i] == oilfields[j] {
                        if j < i {
                            idx += 1;
                        }
                        cnt += 1;
                    }
                }
                (idx, cnt)
            })
            .collect::<Vec<_>>();

        Self {
            n,
            m,
            e,
            oilfields: oilfields.clone(),
            oilfields_count,
            p,
            excavate_history: vec![],
            predict_history: vec![],
        }
    }

    pub fn reset(&mut self) {
        self.p = (0..self.m)
            .map(|i| {
                let (mx, my) = self.oilfields[i]
                    .iter()
                    .fold((0, 0), |(mx, my), &(x, y)| (mx.max(x), my.max(y)));
                vec![
                    vec![1.0 / ((self.n - mx) as f64 * (self.n - my) as f64); self.n - my];
                    self.n - mx
                ]
            })
            .collect::<Vec<_>>();
        let mut excavate_history = self.excavate_history.clone();
        excavate_history.sort_by(|a, b| b.1.cmp(&a.1));
        for ((x, y), v) in excavate_history {
            self.update_excavate((x, y), v);
        }
        let mut predict_history = self.predict_history.clone();
        predict_history.sort_by(|a, b| a.1.partial_cmp(&b.1).unwrap());
        for (s, v) in predict_history {
            self.update_predict(&s, v);
        }
    }

    fn invalid(&self) -> bool {
        self.p.iter().any(|p| {
            p.iter()
                .any(|p| p.iter().any(|&p| !(0.0..=1.0).contains(&p)))
        })
    }

    pub fn all_excavate<R: std::io::BufRead>(&mut self, io: &IO<R>) -> Option<Vec<(usize, usize)>> {
        let a = self.excavate_history.iter().map(|(_, v)| v).sum::<usize>();
        let b = self.oilfields.iter().map(|v| v.len()).sum::<usize>();

        if a == b {
            Some(
                self.excavate_history
                    .iter()
                    .filter(|(_, v)| *v > 0)
                    .map(|((x, y), _)| (*x, *y))
                    .collect(),
            )
        } else {
            None
        }
    }

    pub fn solved_check<R: std::io::BufRead>(&mut self, io: &IO<R>) -> Option<Vec<(usize, usize)>> {
        if let Some(set) = self.all_excavate(io) {
            return Some(set);
        }

        if self.invalid() {
            self.reset();
        }

        // reset 後がもうinvalidなケースがあるらしい
        if self.invalid() {
            return None;
        }

        // max_by 使うんじゃなく、ピース i の位置 (dx, dy) を前処理で求めるべき
        // 同じピース同士はdx, dy の**filter**ではずせばよろしい
        // よしなに個数を掛ければよい？
        let positions = self
            .p
            .iter()
            .enumerate()
            .map(|(i, p)| {
                if self.oilfields_count[i].1 == 1 {
                    let mut ma = (f64::MIN, (0, 0));
                    for (dx, p) in p.iter().enumerate() {
                        for (dy, p) in p.iter().enumerate() {
                            if ma.0 < *p {
                                ma = (*p, (dx, dy));
                            }
                        }
                    }
                    ma
                } else {
                    let mut s = vec![];
                    for (dx, p) in p.iter().enumerate() {
                        for (dy, p) in p.iter().enumerate() {
                            let per = (p * self.oilfields_count[i].1 as f64).min(1.);
                            s.push((per, (dx, dy)));
                        }
                    }
                    s.sort_by(|a, b| b.0.partial_cmp(&a.0).unwrap());
                    s[self.oilfields_count[i].0 - 1]
                }
            })
            .collect::<Vec<_>>();

        let ac_per = positions
            .iter()
            .map(|(per, _)| *per)
            .fold(1.0, |acc, x| acc * x);

        if ac_per > (0.7_f64).powf(self.m as f64) {
            let mut r = vec![vec![0; self.n]; self.n];
            for (i, (_, (dx, dy))) in positions.iter().enumerate() {
                for (x, y) in &self.oilfields[i] {
                    r[x + dx][y + dy] += 1;
                }
            }
            // excavate_history check
            let invalid_pos = self
                .excavate_history
                .iter()
                .filter(|((x, y), v)| r[*x][*y] != *v)
                .map(|((x, y), v)| ((*x, *y), *v))
                .collect::<Vec<_>>();

            // こういうことをするとダブりで困りそうではある
            if !invalid_pos.is_empty() {
                for &((x, y), v) in &invalid_pos {
                    self.update_excavate((x, y), v)
                }
                return self.submit_expected(io);
            }
            Some(
                (0..self.n)
                    .flat_map(|i| (0..self.n).map(move |j| (i, j)))
                    .filter(|&(i, j)| r[i][j] > 0)
                    .collect::<Vec<_>>(),
            )
        } else {
            self.submit_expected(io)
        }
    }

    fn submit_expected<R: std::io::BufRead>(&mut self, io: &IO<R>) -> Option<Vec<(usize, usize)>> {
        if io.query_cnt > self.n * self.n && Random::get_f() < 0.2 {
            let p = self.expected_value();
            let set = (0..self.n)
                .flat_map(|i| (0..self.n).map(move |j| (i, j)))
                .filter(|&(i, j)| p[i][j] > 0.1)
                .collect::<Vec<_>>();

            if self.excavate_history.iter().all(|((x, y), v)| {
                if *v > 0 {
                    set.contains(&(*x, *y))
                } else {
                    !set.contains(&(*x, *y))
                }
            }) {
                return Some(set);
            }
        }
        None
    }

    pub fn update_excavate(&mut self, (x, y): (usize, usize), v: usize) {
        if !self.excavate_history.contains(&((x, y), v)) {
            self.excavate_history.push(((x, y), v));
        }
        // 各ピースについて、 (x, y) が 1 になる確率を求めておく
        let pick_p = (0..self.m)
            .map(|i| {
                let mut res = 0.0;
                for dx in 0..(self.p[i].len()) {
                    for dy in 0..(self.p[i][dx].len()) {
                        // if self.oilfields[i].contains(&(x - dx, y - dy)) {
                        if self.oilfields[i]
                            .iter()
                            .any(|&(ox, oy)| x == ox + dx && y == oy + dy)
                        {
                            res += self.p[i][dx][dy];
                        }
                    }
                }
                res
            })
            .collect::<Vec<_>>();

        for i in 0..self.m {
            // dp[k] := ピース i 以外のピースを使って、合計 k になる確率
            let dp = {
                let mut dp = vec![0.0; v + 2];
                dp[0] = 1.0;
                for (j, &p) in pick_p.iter().enumerate() {
                    if i == j {
                        continue;
                    }
                    let mut pd = vec![0.0; v + 2];
                    for k in 0..(v + 1) {
                        pd[k + 1] += dp[k] * p;
                        pd[k] += dp[k] * (1.0 - p);
                    }
                    std::mem::swap(&mut dp, &mut pd);
                }
                dp
            };
            let (a, b) = {
                let a = if v == 0 { 0.0 } else { dp[v - 1] };
                let b = dp[v];
                let su = a + b;
                (a / su, b / su)
            };
            for dx in 0..(self.p[i].len()) {
                for dy in 0..(self.p[i][dx].len()) {
                    if self.oilfields[i]
                        .iter()
                        .any(|&(ox, oy)| x == ox + dx && y == oy + dy)
                    {
                        self.p[i][dx][dy] *= a;
                    } else {
                        self.p[i][dx][dy] *= b;
                    }
                }
            }
        }
        self.normalize();
    }

    fn normal_distribution(mu: f64, sig2: f64) -> impl Fn(f64) -> f64 {
        move |x: f64| {
            let a = 1. / (2. * std::f64::consts::PI * sig2).sqrt();
            let b = (x - mu).powi(2) / (2. * sig2);
            a * (-b).exp()
        }
    }

    fn integrate(f: impl Fn(f64) -> f64, a: f64, b: f64) -> f64 {
        let n = 10;
        let h = (b - a) / n as f64;
        let s = (0..n)
            .map(|i| {
                let x = a + h * i as f64;
                f(x) + 4. * f(x + h / 2.) + f(x + h)
            })
            .sum::<f64>();
        (h / 6.) * s
    }

    pub fn update_predict(&mut self, set: &Vec<(usize, usize)>, v: f64) {
        let k = set.len() as f64;
        let per = (0..(3 * set.len()))
            .map(|vs| {
                let mu = (k - vs as f64) * self.e + vs as f64 * (1. - self.e);
                let sig2 = k * self.e * (1. - self.e);
                // Probability::normal_distribution(mu, sig2)(v)
                Probability::integrate(
                    Probability::normal_distribution(mu, sig2),
                    if v != 0. { v } else { -10.0 },
                    v + 1.,
                )
            })
            .collect::<Vec<_>>();

        let s = per.iter().sum::<f64>();

        for (i, p) in self.p.iter_mut().enumerate() {
            for (dx, p) in p.iter_mut().enumerate() {
                for (dy, p) in p.iter_mut().enumerate() {
                    // P(i, dx, dy) が正当である確率 -> (i, dx, dy) でset上に置かれる個数以上になる確率
                    let dub = set
                        .iter()
                        .filter(|&&(x, y)| {
                            self.oilfields[i]
                                .iter()
                                .any(|&(ox, oy)| x == ox + dx && y == oy + dy)
                        })
                        .count();
                    // 全部 s で割ってるので、やらないで後で正規化パートに任せる
                    let u = s - (0..dub).map(|dub| per[dub]).sum::<f64>();
                    *p *= u;
                }
            }
        }
        self.normalize();
    }

    // 正規化 各ピース i について、p[i] の合計が 1 になるようにする
    fn normalize(&mut self) {
        for i in 0..self.m {
            let sum = self.p[i].iter().map(|v| v.iter().sum::<f64>()).sum::<f64>();
            for p in self.p[i].iter_mut().flatten() {
                *p /= sum;
            }
        }
    }

    // セル (i, j) の油田量の期待値
    pub fn expected_value(&self) -> Vec<Vec<f64>> {
        let mut ev = vec![vec![0.0; self.n]; self.n];
        for (i, oilfield) in self.oilfields.iter().enumerate() {
            for dx in 0..(self.p[i].len()) {
                for dy in 0..(self.p[i][dx].len()) {
                    let p = self.p[i][dx][dy];
                    for &(x, y) in oilfield {
                        ev[x + dx][y + dy] += p;
                    }
                }
            }
        }
        ev
    }
}

fn relative_eq_eps(a: f64, b: f64, epsilon: f64) -> bool {
    // 0.0の場合は特別扱いする
    if a == 0.0 || b == 0.0 {
        return (a - b).abs() < epsilon;
    }

    // 相対誤差を計算
    let relative_difference = (a - b).abs() / a.abs().max(b.abs());

    // 相対誤差がepsilon以下ならtrueを返す
    relative_difference < epsilon
}

fn relative_eq(a: f64, b: f64) -> bool {
    relative_eq_eps(a, b, 1.0e-6)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_probability() {
        let n = 4;
        let m = 2;
        let e = 0.01;

        // piece 1    piece 2
        //   .#.       ..#.
        //   ###       ####
        //   .#.

        let oilfields = vec![
            vec![(0, 1), (1, 0), (1, 1), (1, 2), (2, 1)],
            vec![(1, 0), (1, 1), (1, 2), (1, 3), (0, 2)],
        ];
        let mut probability = Probability::new(n, m, e, oilfields);
        assert_eq!(
            probability.p,
            vec![
                vec![vec![1. / 4., 1. / 4.], vec![1. / 4., 1. / 4.]],
                vec![vec![1. / 3.], vec![1. / 3.], vec![1. / 3.]]
            ]
        );

        // answer
        // 0 0 1 0
        // 0 1 2 1
        // 2 2 2 1
        // 0 0 0 0

        probability.update_excavate((1, 1), 1);

        assert!(relative_eq(probability.p[0][0][0], 2. / 7.));
        assert!(relative_eq(probability.p[0][0][1], 2. / 7.));
        assert!(relative_eq(probability.p[0][1][0], 2. / 7.));
        assert!(relative_eq(probability.p[0][1][1], 1. / 7.));
        assert!(relative_eq(probability.p[1][0][0], 1. / 7.));
        assert!(relative_eq(probability.p[1][1][0], 3. / 7.));
        assert!(relative_eq(probability.p[1][2][0], 3. / 7.));
    }
}

fn main() {
    let timer = Timer::new();
    let source = proconio::source::line::LineSource::new(std::io::stdin().lock());
    let mut io = IO::new(source);
    let (n, m, e, oilfields) = io.init();
    let mut solver = Solver::new(timer, io, n, m, e, oilfields);
    solver.solve();
}
