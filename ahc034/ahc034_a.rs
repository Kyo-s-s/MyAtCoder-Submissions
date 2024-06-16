
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

pub const TL: f64 = 1.8;

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

// path: state.rs
pub const N: usize = 20;

#[derive(Debug, Clone, Copy, PartialEq)]
pub enum Move {
    Up,
    Down,
    Left,
    Right,
}

fn move_pos(pos: (usize, usize), m: Move) -> Option<(usize, usize)> {
    let (dx, dy) = match m {
        Move::Up => (-1, 0),
        Move::Down => (1, 0),
        Move::Left => (0, -1),
        Move::Right => (0, 1),
    };
    let nx = pos.0 as i32 + dx;
    let ny = pos.1 as i32 + dy;
    if nx < 0 || ny < 0 || nx >= N as i32 || ny >= N as i32 {
        None
    } else {
        Some((nx as usize, ny as usize))
    }
}

#[derive(Debug, Clone, Copy, PartialEq)]
pub enum Operation {
    Move(Move),
    Carry(i32),
}

#[derive(Clone)]
pub struct State {
    pub grid: [[i32; N]; N],
    pub pos: (usize, usize),
    pub d: i32,
    pub answer: Vec<Operation>,
    pub cost: i32,
    pub base: i32, // 毎回コピーするconstなやつ 最悪
}

impl State {
    pub fn new_input() -> State {
        proconio::input! {
            _: usize,
            grid_vec: [[i32; N]; N]
        }
        let grid = {
            let mut grid = [[0; N]; N];
            for (i, row) in grid_vec.iter().enumerate() {
                for (j, &cell) in row.iter().enumerate() {
                    grid[i][j] = cell;
                }
            }
            grid
        };
        let base = grid
            .map(|row| row.map(|x| x.abs()).iter().sum::<i32>())
            .iter()
            .sum::<i32>();

        State {
            grid,
            pos: (0, 0),
            d: 0,
            answer: vec![],
            cost: 0,
            base,
        }
    }

    pub fn go_pos(&mut self, pos: (usize, usize)) {
        let mut dx = self.pos.0 as i32 - pos.0 as i32;
        let mut dy = self.pos.1 as i32 - pos.1 as i32;
        while dx != 0 || dy != 0 {
            match dx {
                0 => {}
                _ if dx > 0 => {
                    self.add_op(Operation::Move(Move::Up));
                    dx -= 1;
                }
                _ => {
                    self.add_op(Operation::Move(Move::Down));
                    dx += 1;
                }
            }
            match dy {
                0 => {}
                _ if dy > 0 => {
                    self.add_op(Operation::Move(Move::Left));
                    dy -= 1;
                }
                _ => {
                    self.add_op(Operation::Move(Move::Right));
                    dy += 1;
                }
            }
        }
    }

    pub fn carry(&mut self, c: i32) {
        self.add_op(Operation::Carry(c));
    }

    pub fn can_move(&self, m: Move) -> bool {
        move_pos(self.pos, m).is_some()
    }

    // move ができなかったとき壊れる
    fn add_op(&mut self, op: Operation) {
        match op {
            Operation::Move(m) => {
                let pos = move_pos(self.pos, m).unwrap();
                self.cost += self.d + 100;
                self.pos = pos;
                self.answer.push(op);

                match self.grid[pos.0][pos.1] {
                    x if x > 0 => self.carry(x),
                    // x if x < 0 => {
                    //     let carry = x.abs().min(self.d);
                    //     if carry != 0 {
                    //         self.carry(-carry);
                    //     }
                    // }
                    _ => {}
                }
            }
            Operation::Carry(c) => {
                self.d += c;
                self.grid[self.pos.0][self.pos.1] -= c;
                self.cost += c.abs();
                self.answer.push(op);
            }
        }
    }

    pub fn now_score(&self) -> i64 {
        let diff = {
            let mut diff: i64 = 0;
            for row in &self.grid {
                for &cell in row {
                    if cell > 0 {
                        diff += 100_i64 * cell as i64 + 10000_i64;
                    }
                }
            }
            diff
        };
        1000000000_i64 * self.base as i64 / (self.cost as i64 + diff)
    }

    pub fn output(&self) {
        for op in &self.answer {
            match op {
                Operation::Move(Move::Up) => println!("U"),
                Operation::Move(Move::Down) => println!("D"),
                Operation::Move(Move::Left) => println!("L"),
                Operation::Move(Move::Right) => println!("R"),
                Operation::Carry(c) => {
                    if c > &0 {
                        println!("+{}", c);
                    } else {
                        println!("{}", c);
                    }
                }
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test() {
        let grid = [[0; N]; N];
        let mut state = State {
            grid,
            pos: (0, 0),
            d: 0,
            answer: vec![],
            cost: 0,
            base: 0,
        };

        state.go_pos((1, 2));
        assert_eq!(state.pos, (1, 2));
        assert_eq!(
            state.answer,
            vec![
                Operation::Move(Move::Down),
                Operation::Move(Move::Right),
                Operation::Move(Move::Right)
            ]
        );

        state.carry(3);
        assert_eq!(state.d, 3);
        assert_eq!(state.grid[1][2], -3);

        state.go_pos((2, 3));
        state.carry(-2);
        assert_eq!(state.d, 1);
        assert_eq!(state.grid[2][3], 2);
    }
}

struct Solver {
    initial_state: State,
    timer: Timer,
}

impl Solver {
    fn new() -> Solver {
        let timer = Timer::new();
        let initial_state = State::new_input();
        Solver {
            initial_state,
            timer,
        }
    }

    fn solve(&mut self) -> State {
        let mut state = self.initial_state.clone();

        let divs = {
            let mut div = vec![];
            let k = 1; // 20 の約数
            let dxy = (0..k)
                .map(|i| {
                    if i % 2 == 0 {
                        (0..k).map(|j| (i, j)).collect::<Vec<_>>()
                    } else {
                        (0..k).rev().map(|j| (i, j)).collect::<Vec<_>>()
                    }
                })
                .collect::<Vec<_>>()
                .concat();
            for i in (0..N).step_by(k) {
                for j in (0..N).step_by(k) {
                    div.push(
                        dxy.iter()
                            .map(|&(di, dj)| (i + di, j + dj))
                            .collect::<Vec<_>>(),
                    );
                }
            }
            div
        };

        loop {
            let dist = |(i, j): (usize, usize)| {
                (i as i32 - state.pos.0 as i32).abs() + (j as i32 - state.pos.1 as i32).abs()
            };
            // 各 div で、今の now_d との和が 0 を超える一番近いものを探す
            let best_div_id = {
                let mut best_div_id: Option<usize> = None;
                let mut best_div_sum = 0;
                for (i, div) in divs.iter().enumerate() {
                    if div.iter().all(|&pos| state.grid[pos.0][pos.1] == 0) {
                        continue;
                    }
                    let sum = div.iter().map(|&pos| state.grid[pos.0][pos.1]).sum::<i32>();
                    if sum + state.d >= 0 {
                        if let Some(best_id) = best_div_id {
                            let k = -5;
                            let now_dist = dist(div[0]) + if sum < 0 { k } else { 0 };
                            let best_dist =
                                dist(divs[best_id][0]) + if best_div_sum < 0 { k } else { 0 };
                            if now_dist < best_dist {
                                best_div_id = Some(i);
                                best_div_sum = sum;
                            }
                        } else {
                            best_div_id = Some(i);
                            best_div_sum = sum;
                        }
                    }
                }
                best_div_id
            };
            if best_div_id.is_none() {
                break;
            }
            let best_div = divs[best_div_id.unwrap()].clone();
            for &pos in best_div.iter() {
                match state.grid[pos.0][pos.1] {
                    x if x > 0 => {
                        state.go_pos(pos);
                        state.carry(x);
                    }
                    x if x < 0 => {
                        state.go_pos(pos);
                        let carry = x.abs().min(state.d);
                        if carry != 0 {
                            state.carry(-carry);
                        }
                    }
                    _ => {}
                }
            }
            for &pos in best_div.iter() {
                if state.grid[pos.0][pos.1] < 0 && state.d >= state.grid[pos.0][pos.1].abs() {
                    state.go_pos(pos);
                    state.carry(state.grid[pos.0][pos.1]);
                }
            }
        }

        state
    }
}

// AHC って、めんどくさいんだな...
fn main() {
    let timer = Timer::new();
    let mut solver = Solver::new();
    let answer_state = solver.solve();
    answer_state.output();
    eprintln!("time: {:.3}", timer.get_time());
}
