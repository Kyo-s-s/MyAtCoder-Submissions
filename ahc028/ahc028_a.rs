
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

pub const TL: f64 = 1.95;

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

    pub fn get_2d(range: std::ops::Range<usize>) -> (usize, usize) {
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
use std::process::exit;


pub const N: usize = 15;
pub const M: usize = 200;

pub struct IO {
    pub si: usize,
    pub sj: usize,
    a: [[char; N]; N],
    pub key: Vec<Vec<(usize, usize)>>, // key[c]: cth character's positions
    pub t: [[usize; 5]; M],
}

impl IO {
    pub fn new() -> Self {
        proconio::input! {
            _: usize,
            _: usize,
            si: usize,
            sj: usize,
            a: [String; N],
            t: [String; M],
        }

        let a = {
            let mut res = [[0 as char; N]; N];
            for i in 0..N {
                for j in 0..N {
                    res[i][j] = a[i].chars().nth(j).unwrap();
                }
            }
            res
        };
        let key = {
            let mut res = vec![vec![]; 26];
            for i in 0..N {
                for j in 0..N {
                    let c = a[i][j] as usize - 'A' as usize;
                    res[c].push((i, j));
                }
            }
            res
        };
        let t = {
            let mut res = [[0; 5]; M];
            for i in 0..M {
                for j in 0..5 {
                    let c = t[i].chars().nth(j).unwrap();
                    res[i][j] = c as usize - 'A' as usize;
                }
            }
            res
        };
        Self { si, sj, a, key, t }
    }

    pub fn submit(state: &State) {
        for &(i, j) in &state.push {
            println!("{} {}", i, j);
        }
        exit(0);
    }
}

// path: state.rs
pub struct State {
    now: (usize, usize),
    pub push: Vec<(usize, usize)>,
    score: i64,
}

impl State {
    pub fn new(io: &IO) -> Self {
        Self {
            now: (io.si, io.sj),
            push: vec![],
            score: 0,
        }
    }

    pub fn add(&mut self, i: usize, j: usize) {
        let d = (i as i64 - self.now.0 as i64).abs() + (j as i64 - self.now.1 as i64).abs() + 1;
        self.push.push((i, j));
        self.score += d;
    }

    pub fn score(&self) -> i64 {
        return 1001.max(10000 - self.score);
    }
}

use std::collections::{BTreeMap, HashMap, VecDeque};

struct Solver {
    timer: Timer,
    io: IO,
    dob: [[usize; M]; M],
}

impl Solver {
    fn new(timer: Timer, io: IO) -> Solver {
        let dob = {
            let mut res = [[usize::MAX; M]; M];
            for i in 0..M {
                for j in 0..M {
                    if i == j {
                        continue;
                    }
                    res[i][j] = 0;
                    for k in (1..=4).rev() {
                        if (0..k).all(|l| io.t[i][5 - k + l] == io.t[j][l]) {
                            res[i][j] = k;
                            break;
                        }
                    }
                }
            }
            res
        };

        Solver { timer, io, dob }
    }

    fn make_s(&self) -> Vec<usize> {
        let mut ts = (0..M).map(|i| VecDeque::from(vec![i])).collect::<Vec<_>>();
        let mut used = vec![false; M];

        while used.iter().filter(|&&b| !b).count() > 1 {
            let mut ma = (0, 0, 0); // (dub[i][j], i, j)
            for i in 0..M {
                for j in 0..M {
                    if (i == j) | used[i] | used[j] {
                        continue;
                    }
                    let il = *ts[i].back().unwrap();
                    let jf = *ts[j].front().unwrap();

                    // 確率でやってるので毎回やるひつようがある
                    if (1 <= self.dob[il][jf] && self.dob[il][jf] == ma.0)
                        || (ma.0 < self.dob[il][jf])
                    {
                        if ma.0 == 0 || Random::get_f() < (0.05 + 0.1 * self.dob[il][jf] as f64) {
                            ma = (self.dob[il][jf], i, j);
                        }
                    }
                }
            }
            if ma.0 == 0 {
                // これ以上得なmergeができない
                let mut ids = (0..M).filter(|&i| !used[i]).collect::<Vec<_>>();
                Random::shuffle(&mut ids);
                let le = ids[0];
                for &id in &ids {
                    if le == id {
                        continue;
                    }
                    used[id] = true;
                    while let Some(x) = ts[id].pop_front() {
                        ts[le].push_back(x);
                    }
                }
                break;
            }
            let (i, j) = (ma.1, ma.2);
            if ts[i].len() < ts[j].len() {
                used[i] = true;
                while let Some(x) = ts[i].pop_back() {
                    ts[j].push_front(x);
                }
            } else {
                used[j] = true;
                while let Some(x) = ts[j].pop_front() {
                    ts[i].push_back(x);
                }
            }
        }

        let ids = {
            let k = used.iter().position(|&b| !b).unwrap();
            let mut res = vec![];
            while let Some(x) = ts[k].pop_front() {
                res.push(x);
            }
            res
        };

        let mut res = vec![];
        let mut pre = usize::MAX;
        for &id in &ids {
            let st = if pre != usize::MAX {
                self.dob[pre][id]
            } else {
                0
            };
            (st..5).for_each(|i| res.push(self.io.t[id][i]));
            pre = id;
        }

        res
    }

    fn calc_s(&self, s: &Vec<usize>) -> State {
        let id = |i: usize, j: usize| i * N + j;
        let di = |v: usize| (v / N, v % N);
        let cost = |(i, j): (usize, usize), (k, l): (usize, usize)| {
            (i as i64 - k as i64).abs() + (j as i64 - l as i64).abs() + 1
        };

        let mut dp = vec![];
        // dp.push(HashMap::new());
        dp.push(BTreeMap::new());
        dp[0].insert(id(self.io.si, self.io.sj), 0);
        for &c in s {
            // let mut nxt = HashMap::new();
            let mut nxt = BTreeMap::new();
            for &pre in dp.last().unwrap().keys() {
                let (pi, pj) = di(pre);
                for &(ni, nj) in &self.io.key[c] {
                    let co = cost((pi, pj), (ni, nj));
                    if let Some(&mi) = nxt.get(&id(ni, nj)) {
                        if mi > dp.last().unwrap()[&pre] + co {
                            nxt.insert(id(ni, nj), dp.last().unwrap()[&pre] + co);
                        }
                    } else {
                        nxt.insert(id(ni, nj), dp.last().unwrap()[&pre] + co);
                    }
                }
            }
            dp.push(nxt);
        }

        // 復元
        let mut ans = vec![];
        // let mut pos: Option<((usize, usize), i64)> = None;
        let mut pos = ((0, 0), i64::MAX);
        for map in dp.iter().rev() {
            // if let Some((poso, cos)) = pos {
            if pos.1 != i64::MAX {
                let (poso, cos) = pos;
                for (&k, &v) in map.iter() {
                    // di(k) -> pos へのコスト + v が cos と一致するのを探す
                    if cost(di(k), poso) + v == cos {
                        ans.push(di(k));
                        // pos = Some((di(k), v));
                        pos = (di(k), v);
                        break;
                    }
                }
            } else {
                // map の中で一番valueが小さいkey
                let mut mi: Option<((usize, usize), i64)> = None;
                for (&k, &v) in map.iter() {
                    if let Some((_, mv)) = mi {
                        if mv > v {
                            mi = Some((di(k), v));
                        }
                    } else {
                        mi = Some((di(k), v));
                    }
                }
                ans.push(mi.unwrap().0);
                // pos = Some(mi.unwrap());
                pos = mi.unwrap();
            }
        }

        let mut state = State::new(&self.io);
        ans.iter().rev().for_each(|&(i, j)| state.add(i, j));
        state
    }

    fn solve(&mut self) {
        // make_s: 訪れる**アルファベット** の順番
        // calc_s: sを元に最適っぽくDP

        let state = {
            // make_s でのmergeをランダムに変わるようにする TLいっぱい回す
            let mut state: Option<State> = None;
            while self.timer.get_time() < TL {
                let s = self.make_s();
                let ans = self.calc_s(&s);
                if let Some(s) = &state {
                    if s.score() < ans.score() {
                        state = Some(ans);
                    }
                } else {
                    state = Some(ans);
                }
            }
            state.unwrap()
        };

        IO::submit(&state);
    }
}

fn main() {
    let timer = Timer::new();
    let io = IO::new();
    let mut solver = Solver::new(timer, io);
    solver.solve();
}
