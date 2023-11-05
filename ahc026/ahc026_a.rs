use std::{
    cmp::{Ordering, Reverse},
    collections::BinaryHeap,
    time::SystemTime,
};

const N: usize = 200;
const M: usize = 10;
const mv: usize = 10000;

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

struct IO {
    b: [[usize; N / M]; M],
}

impl IO {
    fn new() -> IO {
        proconio::input! {
            _: usize,
            _: usize,
            gb: [[usize; N / M]; M],
        }
        let b = {
            let mut b: [[usize; N / M]; M] = [[0; N / M]; M];
            for i in 0..M {
                for j in 0..N / M {
                    b[i][j] = gb[i][j];
                }
            }
            b
        };
        IO { b }
    }
}

#[derive(Clone, Eq, PartialEq)]
struct State {
    next: usize,
    vi: Vec<(usize, usize)>,
    b: Vec<Vec<usize>>,
    score: usize,
}

impl State {
    fn new(io: &IO) -> State {
        let mut b = vec![vec![0; N / M]; M];
        for i in 0..M {
            for j in 0..N / M {
                b[i][j] = io.b[i][j];
            }
        }
        State {
            next: 0,
            vi: vec![],
            b,
            score: 0,
        }
    }

    fn pickup(&self, v: usize) -> State {
        let mut b = self.b.clone();
        (0..M).for_each(|i| {
            if b[i].last() == Some(&v) {
                b[i].pop();
            }
        });
        // TODO: できないときのpanic
        let mut vi = self.vi.clone();
        vi.push((v, mv));
        State {
            next: self.next + 1,
            vi,
            b,
            score: self.score,
        }
    }

    fn mv(&self, v: usize, i: usize, v_i: usize) -> State {
        let vi = {
            let mut vi = self.vi.clone();
            vi.push((v, i));
            vi
        };
        let mut b = self.b.clone();
        let mut we = vec![];
        loop {
            let bk = b[v_i].pop().unwrap();
            we.push(bk);
            if bk == v {
                break;
            }
        }
        let score = self.score + we.len() + 1;
        while let Some(bk) = we.pop() {
            b[i].push(bk);
        }
        State {
            next: self.next,
            vi,
            b,
            score,
        }
    }

    fn output(&self) {
        for &(v, i) in self.vi.iter() {
            println!("{} {}", v, if i == mv { 0 } else { i + 1 });
        }
        std::process::exit(0);
    }
}

impl Ord for State {
    fn cmp(&self, other: &State) -> Ordering {
        self.score.cmp(&other.score)
    }
}

impl PartialOrd for State {
    fn partial_cmp(&self, other: &State) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

struct Solver {
    io: IO,
}

impl Solver {
    fn new(io: IO) -> Solver {
        Solver { io }
    }

    fn solve(&self, _: Timer) {
        let mut queue = BinaryHeap::new();
        queue.push(Reverse(State::new(&self.io)));
        let weight = 400;
        for item in 1..=N {
            let mut next_queue = BinaryHeap::new();
            for _ in 0..weight {
                if let Some(Reverse(now)) = queue.pop() {
                    let pickup_item = {
                        let mut res = None;
                        for i in 0..M {
                            if now.b[i].len() == 0 {
                                continue;
                            }
                            for j in 0..now.b[i].len() - 1 {
                                if now.b[i][j] == item {
                                    res = Some((i, now.b[i][j + 1]));
                                    break;
                                }
                            }
                        }
                        res
                    };

                    if let Some((i, v)) = pickup_item {
                        // v を i 以外にやる
                        for u in 0..M {
                            if u == i {
                                continue;
                            }
                            let next = now.mv(v, u, i).pickup(item);
                            next_queue.push(Reverse(next));
                        }
                    } else {
                        let next = now.pickup(item);
                        // for i in 0..M {
                        //     // b[i]を出力
                        //     let line = next.b[i]
                        //         .iter()
                        //         .map(|&v| v.to_string())
                        //         .collect::<Vec<_>>()
                        //         .join(" ");
                        //     println!("> {}", line);
                        // }
                        next_queue.push(Reverse(next));
                    }
                }
            }
            queue = next_queue;
        }

        let ans = queue.pop().unwrap().0;
        ans.output();
    }
}

fn main() {
    let timer = Timer::new();
    let io = IO::new();
    let solver = Solver::new(io);
    solver.solve(timer);
}
