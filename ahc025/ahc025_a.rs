extern crate rand;

use rand::Rng;

use std::collections::VecDeque;
use std::io::BufRead;
use std::{cmp::Ordering, io::BufReader, time::SystemTime};

use proconio::source::line::LineSource;

struct Timer {
    start: SystemTime,
}

impl Timer {
    fn new() -> Timer {
        Timer {
            start: SystemTime::now(),
        }
    }

    fn get_time(&self) -> f64 {
        let elapsed = self.start.elapsed().expect("Time elapsed failed");
        let elapsed_secs = elapsed.as_secs() as f64;
        let elapsed_micros = elapsed.subsec_micros() as f64;
        elapsed_secs + elapsed_micros / 1_000_000.0
    }
}

fn convert_vec_to_string<T: ToString>(v: &Vec<T>) -> String {
    v.iter()
        .map(|x| x.to_string())
        .collect::<Vec<_>>()
        .join(" ")
}

struct IO {
    n: usize,
    d: usize,
    q: usize,
    q_cnt: usize,
}

impl IO {
    fn new<R: BufRead>(source: &mut LineSource<R>) -> IO {
        proconio::input! {
            from source,
            n: usize,
            d: usize,
            q: usize,
        }

        IO { n, d, q, q_cnt: 0 }
    }

    fn query<R: BufRead>(
        &mut self,
        source: &mut LineSource<R>,
        lhs: &Vec<usize>,
        rhs: &Vec<usize>,
    ) -> Option<Ordering> {
        if self.q_cnt >= self.q {
            return None;
        }
        Some(match (lhs.len(), rhs.len()) {
            (0, 0) => Ordering::Equal,
            (0, _) => Ordering::Less,
            (_, 0) => Ordering::Greater,
            _ => {
                let len = format!("{} {}", lhs.len(), rhs.len());
                let lhs = convert_vec_to_string(lhs);
                let rhs = convert_vec_to_string(rhs);
                self.q_cnt += 1;
                println!("{} {} {}", len, lhs, rhs);
                proconio::input! {
                    from source,
                    ans: char,
                }
                match ans {
                    '<' => Ordering::Less,
                    '>' => Ordering::Greater,
                    '=' => Ordering::Equal,
                    _ => panic!("invalid answer"),
                }
            }
        })
    }

    fn output(&mut self, ans: &State) {
        println!("#c {}", convert_vec_to_string(&ans.d));
    }

    fn submit<R: BufRead>(&mut self, source: &mut LineSource<R>, ans: &State) {
        while self.q > self.q_cnt {
            self.query(source, &vec![0], &vec![1]);
        }
        println!("{}", convert_vec_to_string(&ans.d));
    }
}

struct State {
    estimate_weight: Vec<usize>,
    d: Vec<usize>,
    t: Vec<usize>,
}

// 一点変更より、複数個所変更したほうがよいかも
struct Apply {
    i: usize,
    before: usize,
    after: usize,
}

impl State {
    fn new(io: &IO, estimate_weight: &Vec<usize>) -> State {
        let d = (0..io.n).map(|i| i % io.d).collect::<Vec<_>>();
        let t = {
            let mut t = vec![0; io.d];
            for i in 0..io.n {
                t[d[i]] += estimate_weight[i];
            }
            t
        };
        State {
            estimate_weight: estimate_weight.clone(),
            d,
            t,
        }
    }

    fn score(&self) -> usize {
        let t_ave = self.t.iter().sum::<usize>() / self.t.len();
        let v = {
            let mut v = 0.;
            for &t in &self.t {
                v += (t as f64 - t_ave as f64).powi(2);
            }
            v / self.t.len() as f64
        };
        1 + (100. * v.sqrt()) as usize
    }

    fn update_estimate_weight(&mut self, estimate_weight: &Vec<usize>) {
        self.estimate_weight = estimate_weight.clone();
        self.t = vec![0; self.t.len()];
        for i in 0..self.d.len() {
            self.t[self.d[i]] += self.estimate_weight[i];
        }
    }

    fn generate_diff(&self, io: &IO) -> Apply {
        let i = rand::thread_rng().gen_range(0..io.n);
        let before = self.d[i];
        let after = rand::thread_rng().gen_range(0..io.d);
        Apply { i, before, after }
    }

    fn apply(&mut self, apply: &Apply) {
        self.d[apply.i] = apply.after;
        self.t[apply.before] -= self.estimate_weight[apply.i];
        self.t[apply.after] += self.estimate_weight[apply.i];
    }

    fn revert(&mut self, apply: &Apply) {
        self.d[apply.i] = apply.before;
        self.t[apply.before] += self.estimate_weight[apply.i];
        self.t[apply.after] -= self.estimate_weight[apply.i];
    }
}

struct Solver {
    io: IO,
}

impl Solver {
    fn new(io: IO) -> Solver {
        Solver { io }
    }

    fn sort<R: BufRead>(&mut self, source: &mut LineSource<R>) -> Vec<usize> {
        let mut deque = VecDeque::new();
        (0..self.io.n).for_each(|i| deque.push_back(VecDeque::from([i])));
        let random = || {
            let r = rand::thread_rng().gen_range(0..2);
            if r == 0 {
                Ordering::Less
            } else {
                Ordering::Greater
            }
        };
        loop {
            let lhs = deque.pop_front();
            let rhs = deque.pop_front();
            match (lhs, rhs) {
                (Some(mut lhs), Some(mut rhs)) => {
                    let mut add = VecDeque::new();
                    loop {
                        if lhs.len() == 0 {
                            rhs.iter().for_each(|&x| add.push_back(x));
                            break;
                        }
                        if rhs.len() == 0 {
                            lhs.iter().for_each(|&x| add.push_back(x));
                            break;
                        }
                        let l = *lhs.front().unwrap();
                        let r = *rhs.front().unwrap();
                        let ord = self
                            .io
                            .query(source, &vec![l], &vec![r])
                            .unwrap_or(random());
                        match ord {
                            Ordering::Less => {
                                add.push_back(l);
                                lhs.pop_front();
                            }
                            _ => {
                                add.push_back(r);
                                rhs.pop_front();
                            }
                        }
                    }
                    deque.push_back(add);
                }
                (Some(v), None) => {
                    return v.iter().map(|&x| x).collect::<Vec<_>>();
                }
                _ => panic!("invalid"),
            }
        }
    }

    fn solve<R: BufRead>(&mut self, source: &mut LineSource<R>, timer: Timer) {
        // // とりあえずの推定をする、ソートが足りないケースがあるのでもっと雑な推定でもよいかも
        let sorted = self.sort(source);
        let sorted_estimate_weight = {
            let mut res = (0..self.io.n)
                .map(|_| self.exponential())
                .collect::<Vec<_>>();
            res.sort();
            res
        };

        let estimate_weight = {
            let mut estimate_weight = vec![0; self.io.n];
            for i in 0..self.io.n {
                estimate_weight[sorted[i]] = sorted_estimate_weight[i];
            }
            estimate_weight
        };

        let mut state = State::new(&self.io, &estimate_weight);
        let mut now_score = state.score();
        let mut cnt = 0;
        while timer.get_time() < 1.8 {
            cnt += 1;
            if cnt % 10 == 0 && self.io.q_cnt < self.io.q {
                self.update_estimate_weight(source, &mut state);
            }
            let apply = state.generate_diff(&self.io);
            state.apply(&apply);
            let next_score = state.score();
            if next_score < now_score {
                now_score = next_score;
            } else {
                state.revert(&apply);
            }
        }
        println!("# cnt: {}", cnt);
        self.io.submit(source, &state);
    }

    fn update_estimate_weight<R: BufRead>(
        &mut self,
        source: &mut LineSource<R>,
        state: &mut State,
    ) {
        self.io.output(state);
        let (lhs, rhs, lsum, rsum) = {
            let (mut lhs, mut rhs) = (vec![], vec![]);
            let (mut lsum, mut rsum) = (0, 0);
            let r = rand::thread_rng().gen_range(3..7);
            let random = |lhs: &Vec<usize>, rhs: &Vec<usize>| loop {
                let i = rand::thread_rng().gen_range(0..self.io.n);
                if lhs.iter().filter(|&&x| x == i).count() == 0
                    && rhs.iter().filter(|&&x| x == i).count() == 0
                {
                    break i;
                }
            };
            // 同じくらいのを取らないと意味ない！
            for _ in 0..r {
                let i = random(&lhs, &rhs);
                if lsum < rsum {
                    lhs.push(i);
                    lsum += state.estimate_weight[i];
                } else {
                    rhs.push(i);
                    rsum += state.estimate_weight[i];
                }
            }
            if lsum < rsum {
                (lhs, rhs, lsum, rsum)
            } else {
                (rhs, lhs, rsum, lsum)
            }
        };
        let ord = self.io.query(source, &lhs, &rhs);
        let generate_estimate_weight = |x: f64| {
            let mut estimate_weight = state.estimate_weight.clone();
            lhs.iter().for_each(|&i| {
                estimate_weight[i] = (estimate_weight[i] as f64 * x).round() as usize
            });
            rhs.iter().for_each(|&i| {
                estimate_weight[i] = (estimate_weight[i] as f64 / x).round() as usize
            });
            estimate_weight
        };
        match ord {
            Some(Ordering::Greater) => {
                let x = (rsum as f64 / lsum as f64).sqrt() * 1.05;
                let estimate_weight = generate_estimate_weight(x);
                state.update_estimate_weight(&estimate_weight);
            }
            Some(Ordering::Equal) => {
                let x = (rsum as f64 / lsum as f64).sqrt();
                let estimate_weight = generate_estimate_weight(x);
                state.update_estimate_weight(&estimate_weight);
            }
            _ => {}
        }
    }

    fn exponential(&self) -> usize {
        loop {
            let u: f64 = rand::thread_rng().gen();
            let res = 1.max((-100000.0 * u.ln()).round() as usize);
            if res < 100000 * self.io.n / self.io.d {
                return res;
            }
        }
    }
}

fn main() {
    let timer = Timer::new();
    let stdin = std::io::stdin();
    let mut source = LineSource::new(BufReader::new(stdin.lock()));
    let io = IO::new(&mut source);
    let mut solver = Solver::new(io);
    solver.solve(&mut source, timer);
}
