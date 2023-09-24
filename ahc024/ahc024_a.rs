extern crate rand;

use rand::Rng;
use std::{collections::BTreeSet, io::Write, time::SystemTime};

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

const N: usize = 50;
const NN: usize = N + 2;
const M: usize = 100;
const DXY: [(isize, isize); 4] = [(-1, 0), (1, 0), (0, -1), (0, 1)];
fn add((x, y): (usize, usize), d: usize) -> Option<(usize, usize)> {
    let (dx, dy) = DXY[d];
    let (nx, ny) = (x as isize + dx, y as isize + dy);
    if 0 <= nx && nx < NN as isize && 0 <= ny && ny < NN as isize {
        Some((nx as usize, ny as usize))
    } else {
        None
    }
}

fn get_neighbors(
    map: &[[usize; NN]; NN],
    i: usize,
    j: usize,
    visited: &mut [[bool; NN]; NN],
) -> BTreeSet<usize> {
    visited[i][j] = true;
    let mut res = BTreeSet::new();
    let mut deque = std::collections::VecDeque::new();
    deque.push_back((i, j));
    while let Some((i, j)) = deque.pop_front() {
        for d in 0..4 {
            if let Some((ni, nj)) = add((i, j), d) {
                if map[i][j] == map[ni][nj] && !visited[ni][nj] {
                    deque.push_back((ni, nj));
                    visited[ni][nj] = true;
                }
                if map[i][j] != map[ni][nj] {
                    res.insert(map[ni][nj]);
                }
            }
        }
    }
    res
}

// 不正ならNone
fn generate_graph(map: &[[usize; NN]; NN]) -> Option<Vec<BTreeSet<usize>>> {
    let mut graph = vec![BTreeSet::new(); M + 1];
    let mut visited = [[false; NN]; NN];
    let mut checked = [false; M + 1];
    for i in 0..(NN - 1) {
        for j in 0..(NN - 1) {
            if visited[i][j] {
                continue;
            }
            if checked[map[i][j]] {
                return None;
            }
            checked[map[i][j]] = true;
            graph[map[i][j]] = get_neighbors(map, i, j, &mut visited);
        }
    }
    Some(graph)
}

struct IO {
    c: [[usize; NN]; NN],
    graph: Vec<BTreeSet<usize>>,
}

impl IO {
    fn new() -> IO {
        proconio::input! {
            _: usize,
            _: usize,
            ic: [[usize; N]; N],
        }
        let mut c = [[0; NN]; NN];
        for i in 0..N {
            for j in 0..N {
                c[i + 1][j + 1] = ic[i][j];
            }
        }
        let graph = generate_graph(&c).unwrap();
        IO { c, graph }
    }
}

#[derive(Clone)]
struct State {
    map: [[usize; NN]; NN],
    corner: usize,
}

impl State {
    fn new(map: &[[usize; NN]; NN]) -> State {
        let mut res = State {
            map: map.clone(),
            corner: 0,
        };
        let couner = res.count_corner();
        res.corner = couner;
        res
    }

    fn final_score(&self, io: &IO) -> usize {
        // TODO: refactor
        let graph = generate_graph(&self.map);
        if graph.is_none() {
            return 0;
        }
        let graph = graph.unwrap();
        if graph == io.graph {
            (1..=N)
                .map(|i| (1..=N).filter(|&j| self.map[i][j] == 0).count())
                .sum::<usize>()
                + 1
        } else {
            0
        }
    }

    fn count_corner(&self) -> usize {
        let mut count = 0;
        for i in 1..=N {
            for j in 1..=N {
                count += self.count_corner_cell(i, j);
            }
        }
        count
    }

    fn count_corner_cell(&self, i: usize, j: usize) -> usize {
        let mut count = 0;
        if self.map[i][j] == 0 {
            return 0;
        }
        let neighbor = (0..4)
            .map(|d| add((i, j), d))
            .filter(|&pos| pos.is_some())
            .map(|pos| pos.unwrap())
            .map(|(ni, nj)| self.map[i][j] != self.map[ni][nj])
            .collect::<Vec<_>>();
        if neighbor.len() != 4 {
            return 0;
        }
        for k in 0..4 {
            if neighbor[k] && neighbor[(k + 1) % 4] {
                count += 1;
            }
        }
        count
    }

    fn change_color_f(&mut self, i: usize, j: usize, c: usize) {
        let pos = {
            let mut pos = (0..4)
                .map(|d| add((i, j), d))
                .filter(|&pos| pos.is_some())
                .map(|pos| pos.unwrap())
                .collect::<Vec<_>>();
            pos.push((i, j));
            pos
        };
        let pre = pos
            .iter()
            .map(|&(i, j)| self.count_corner_cell(i, j))
            .sum::<usize>();
        self.map[i][j] = c;
        let nxt = pos
            .iter()
            .map(|&(i, j)| self.count_corner_cell(i, j))
            .sum::<usize>();
        self.corner += nxt - pre;
    }

    fn change_color(&mut self, io: &IO, i: usize, j: usize, c: usize) -> bool {
        let prev_color = self.map[i][j];
        let prev_corner = self.corner;
        self.change_color_f(i, j, c);
        if c != 0 && prev_corner < self.corner {
            self.change_color_f(i, j, prev_color);
            return false;
        }
        let mut visited = [[false; NN]; NN];
        let pos = {
            let mut pos = (0..4)
                .map(|d| add((i, j), d))
                .filter(|&pos| pos.is_some())
                .map(|pos| pos.unwrap())
                .collect::<Vec<_>>();
            pos.push((i, j));
            pos
        };
        for &(ni, nj) in &pos {
            if visited[ni][nj] {
                continue;
            }
            let set = get_neighbors(&self.map, ni, nj, &mut visited);
            if io.graph[self.map[ni][nj]] != set {
                self.change_color_f(i, j, prev_color);
                return false;
            }
        }
        true
    }

    fn delete_line(&mut self, is_x: bool, k: usize) {
        if is_x {
            for i in 0..NN {
                for j in 0..NN {
                    self.map[i][j] = if i <= k {
                        self.map[i][j]
                    } else if i + 1 < NN {
                        self.map[i + 1][j]
                    } else {
                        0
                    };
                }
            }
        } else {
            for j in 0..NN {
                for i in 0..NN {
                    self.map[i][j] = if j <= k {
                        self.map[i][j]
                    } else if j + 1 < NN {
                        self.map[i][j + 1]
                    } else {
                        0
                    };
                }
            }
        }
    }

    fn output(&self) {
        let stdout = std::io::stdout();
        let mut out = std::io::BufWriter::new(stdout.lock());
        for i in 1..=N {
            let line = self.map[i][1..=N]
                .iter()
                .map(|x| x.to_string())
                .collect::<Vec<_>>()
                .join(" ");
            writeln!(out, "{}", line).unwrap();
        }
    }
}

struct Solver {
    io: IO,
    rng: rand::rngs::ThreadRng,
    H: usize,
    W: usize,
}

impl Solver {
    fn new(io: IO) -> Solver {
        Solver {
            io,
            rng: rand::thread_rng(),
            H: N,
            W: N,
        }
    }

    fn op_change_map(&mut self, state: &mut State) {
        let (i, j) = (
            self.rng.gen_range(1..=self.H),
            self.rng.gen_range(1..=self.W),
        );
        if state.map[i][j] == 0 {
            return;
        }
        let neighbor_color = DXY
            .iter()
            .map(|&(dx, dy)| self.io.c[(i as isize + dx) as usize][(j as isize + dy) as usize])
            // .filter(|&c| c != 0 && c != state.map[i][j])
            .filter(|&c| c != state.map[i][j])
            .collect::<Vec<_>>();
        if neighbor_color.len() >= 2 {
            let neighbor_color = neighbor_color
                .iter()
                .filter(|&&c| c != 0)
                .collect::<Vec<_>>();
            if neighbor_color.len() == 0 {
                return;
            }
            let c = *neighbor_color[self.rng.gen_range(0..neighbor_color.len())];
            if state.change_color(&self.io, i, j, c) {
                // state.output();
            }
        }
    }

    fn op_delete_line(&mut self, state: &mut State, now_score: &mut usize) {
        let is_x = self.rng.gen_range(0..=1) == 0;
        let k = self.rng.gen_range(1..=(if is_x { self.H } else { self.W }));
        let mut nxt = state.clone();
        nxt.delete_line(is_x, k);
        let nxt_score = nxt.final_score(&self.io);
        if *now_score < nxt_score {
            *now_score = nxt_score;
            *state = nxt;
            if is_x {
                self.H -= 1;
            } else {
                self.W -= 1;
            }
        }
    }

    fn erase_round(&mut self, timer: &Timer, state: &mut State) {
        let mut deque = std::collections::VecDeque::new();
        let mut visited = [[false; NN]; NN];
        deque.push_back((0, 0));
        // println!("time: {}", timer.get_time());
        while let Some((i, j)) = deque.pop_back() {
            // println!("# {}, {}, {}", i, j, timer.get_time());
            if timer.get_time() > 1.98 {
                return;
            }
            visited[i][j] = true;
            if state.map[i][j] != 0 {
                if !state.change_color(&self.io, i, j, 0) {
                    continue;
                }
            }

            for d in 0..4 {
                if let Some((ni, nj)) = add((i, j), d) {
                    if !visited[ni][nj] {
                        deque.push_back((ni, nj));
                        // visited[ni][nj] = true;
                    }
                }
            }
        }
    }

    fn solve(&mut self, timer: Timer) {
        let mut state = State::new(&self.io.c);
        let mut now_score = state.final_score(&self.io);
        while timer.get_time() < 1.92 {
            let k = self.rng.gen_range(1..=100);
            if k > 95 {
                self.op_delete_line(&mut state, &mut now_score);
            } else {
                for _ in 0..100 {
                    self.op_change_map(&mut state);
                }
            }
        }

        // for k in (0..NN).rev() {
        //     for v in 0..=1 {
        //         let is_x = v == 0;
        //         let mut nxt = state.clone();
        //         nxt.delete_line(is_x, k);
        //         let nxt_score = nxt.final_score(&self.io);
        //         if now_score < nxt_score {
        //             now_score = nxt_score;
        //             state = nxt;
        //         }
        //     }
        // }

        state.output();

        self.erase_round(&timer, &mut state);
        self.erase_round(&timer, &mut state);
        self.erase_round(&timer, &mut state);

        state.output();
        // eprintln!("count: {}", cnt);
    }
}

fn main() {
    let timer = Timer::new();
    let io = IO::new();
    let mut solver = Solver::new(io);
    solver.solve(timer);
}
