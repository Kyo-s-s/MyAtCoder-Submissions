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

    pub fn force_next(&self, current: &State, next: &State) -> bool {
        let current_score = current.score;
        let next_score = next.score;
        let temp = START_TEMP + (END_TEMP - START_TEMP) * self.get_time() / TL;
        let probability = ((current_score - next_score) / temp).exp();
        probability > Random::get_f()
    }
}

pub const TL: f64 = 1.97;

const START_TEMP: f64 = 10.0;
const END_TEMP: f64 = 0.1;
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

    pub fn _shuffle<T>(items: &mut [T]) {
        items.shuffle(&mut rand::thread_rng());
    }
}

#[derive(Debug, Clone, Copy, PartialEq)]
pub enum Direction {
    U = 0,
    R = 1,
    D = 2,
    L = 3,
}

const DIRECTIONS: [Direction; 4] = [Direction::U, Direction::R, Direction::D, Direction::L];
const DIRECTION_CHARS: [char; 4] = ['U', 'R', 'D', 'L'];
const DIRECTION_OFFSETS: [(i32, i32); 4] = [(-1, 0), (0, 1), (1, 0), (0, -1)];
const DIRECTIONS_ALL: [[Direction; 4]; 24] = [
    [Direction::U, Direction::R, Direction::D, Direction::L],
    [Direction::U, Direction::R, Direction::L, Direction::D],
    [Direction::U, Direction::D, Direction::R, Direction::L],
    [Direction::U, Direction::D, Direction::L, Direction::R],
    [Direction::U, Direction::L, Direction::R, Direction::D],
    [Direction::U, Direction::L, Direction::D, Direction::R],
    [Direction::R, Direction::U, Direction::D, Direction::L],
    [Direction::R, Direction::U, Direction::L, Direction::D],
    [Direction::R, Direction::D, Direction::U, Direction::L],
    [Direction::R, Direction::D, Direction::L, Direction::U],
    [Direction::R, Direction::L, Direction::U, Direction::D],
    [Direction::R, Direction::L, Direction::D, Direction::U],
    [Direction::D, Direction::U, Direction::R, Direction::L],
    [Direction::D, Direction::U, Direction::L, Direction::R],
    [Direction::D, Direction::R, Direction::U, Direction::L],
    [Direction::D, Direction::R, Direction::L, Direction::U],
    [Direction::D, Direction::L, Direction::U, Direction::R],
    [Direction::D, Direction::L, Direction::R, Direction::U],
    [Direction::L, Direction::U, Direction::R, Direction::D],
    [Direction::L, Direction::U, Direction::D, Direction::R],
    [Direction::L, Direction::R, Direction::U, Direction::D],
    [Direction::L, Direction::R, Direction::D, Direction::U],
    [Direction::L, Direction::D, Direction::U, Direction::R],
    [Direction::L, Direction::D, Direction::R, Direction::U],
];

impl Direction {
    pub fn opposite(&self) -> Self {
        match self {
            Self::U => Self::D,
            Self::R => Self::L,
            Self::D => Self::U,
            Self::L => Self::R,
        }
    }

    pub fn to_offset(&self) -> (i32, i32) {
        DIRECTION_OFFSETS[*self as usize]
    }

    pub fn to_char(&self) -> char {
        DIRECTION_CHARS[*self as usize]
    }

    pub fn all() -> [Direction; 4] {
        DIRECTIONS
    }

    pub fn random() -> [Direction; 4] {
        DIRECTIONS_ALL[Random::get(0..24)]
    }
}

#[derive(Debug, Clone)]
pub struct Route {
    pub t: usize,
    pub start: (usize, usize),
    pub nt: usize,
    pub goal: (usize, usize),
}

impl Route {
    fn new(t: usize, start: (usize, usize)) -> Self {
        Self {
            t,
            start,
            nt: t,
            goal: start,
        }
    }

    fn add(&mut self, io: &IO, d: Direction) {
        if let Some(nxt) = io.next_pos(self.goal, d) {
            self.goal = nxt;
            self.nt += 1;
        } else {
            unreachable!("Route::add");
        }
    }
}

#[derive(Debug, Clone)]
pub struct State {
    pub d: Vec<Direction>,
    // map[i][j] は空ではないことが保証される
    pub map: Vec<Vec<Vec<usize>>>,
    pub low_routes: Vec<Route>,
    pub score_map: Vec<Vec<usize>>,
    pub score: f64,
}

#[derive(Debug)]
pub enum Error {
    TooLong,
    CannotMove,
    NotGoal,
    NotVisited,
}

impl State {
    pub fn new(io: &IO, data: &Data, d: Vec<Direction>) -> Result<Self, Error> {
        let l = d.len();

        if l > 100000 {
            return Err(Error::TooLong);
        }

        let (low_routes, map) = {
            let mut low_routes: Vec<Route> = vec![];
            let mut map = vec![vec![vec![]; io.n]; io.n];
            let mut now = (0, 0);
            for (t, &d) in d.iter().enumerate() {
                if let Some(nxt) = io.next_pos(now, d) {
                    map[nxt.0][nxt.1].push(t);
                    if io.d[nxt.0][nxt.1] < Random::get(0..500) {
                        if low_routes.is_empty() || low_routes.last().unwrap().nt != t - 1 {
                            low_routes.push(Route::new(t, nxt));
                        } else if low_routes.last().unwrap().nt == t - 1 {
                            low_routes.last_mut().unwrap().add(io, d);
                        }
                    }
                    now = nxt;
                } else {
                    return Err(Error::CannotMove);
                }
            }
            if now != (0, 0) {
                return Err(Error::NotGoal);
            }
            let low_routes = low_routes
                .iter()
                .filter(|&r| {
                    if r.t == r.nt {
                        return false;
                    }
                    let d = r.nt - r.t;
                    // TODO: 切り分け
                    data.dist(r.start, r.goal) <= SHORT_ROUTE || data.dist(r.start, r.goal) + 3 < d
                })
                .cloned()
                .collect::<Vec<_>>();
            (low_routes, map)
        };

        let score_map = {
            let mut score_map = vec![vec![0; io.n]; io.n];
            for i in 0..io.n {
                for j in 0..io.n {
                    if map[i][j].is_empty() {
                        return Err(Error::NotVisited);
                    }
                    for (k, &t) in map[i][j].iter().enumerate() {
                        let diff = if k == map[i][j].len() - 1 {
                            map[i][j][0] + l - t
                        } else {
                            map[i][j][k + 1] - t
                        };
                        score_map[i][j] += (diff - 1) * diff / 2 * io.d[i][j];
                    }
                }
            }
            score_map
        };

        let score = score_map
            .iter()
            .map(|row| row.iter().sum::<usize>())
            .sum::<usize>() as f64
            / l as f64;

        Ok(Self {
            d,
            map,
            low_routes,
            score_map,
            score,
        })
    }

    pub fn convert_to_string(&self) -> String {
        self.d.iter().map(|&d| d.to_char()).collect()
    }

    pub fn apply(&self, io: &IO, data: &Data, operation: &Operation) -> Result<State, Error> {
        match operation {
            Operation::Del(op) => self.apply_del(io, data, op),
            Operation::DelAdd(op) => self.apply_del_add(io, data, op),
            Operation::Tie(op) => self.apply_tie(io, data, op),
        }
    }

    fn apply_del(&self, io: &IO, data: &Data, operation: &DelOperation) -> Result<State, Error> {
        let (l, r, d) = (operation.l, operation.r, operation.d);
        let mut new_d = vec![];
        for i in 0..self.d.len() {
            if !(l + 1 <= i && i <= r) {
                new_d.push(self.d[i]);
            }
            if i == l + 1 {
                new_d.push(d);
            }
        }
        State::new(io, data, new_d)
    }

    fn apply_del_add(
        &self,
        io: &IO,
        data: &Data,
        operation: &DelAddOperation,
    ) -> Result<State, Error> {
        let (l, r, d) = (operation.l, operation.r, &operation.d);
        let mut new_d = vec![];
        for i in 0..self.d.len() {
            if !(l + 1 <= i && i <= r) {
                new_d.push(self.d[i]);
            }
            if i == l + 1 {
                new_d.extend_from_slice(d);
            }
        }
        State::new(io, data, new_d)
    }

    pub fn apply_tie(
        &self,
        io: &IO,
        data: &Data,
        operation: &TieOperation,
    ) -> Result<State, Error> {
        if operation.count == 1 {
            return Ok(self.clone());
        }
        let mut new_d = vec![];
        for _ in 0..operation.count {
            new_d.extend_from_slice(&self.d);
        }
        State::new(io, data, new_d)
    }
}

use std::process::exit;

pub struct IO {
    pub n: usize,
    map: Vec<Vec<u8>>,
    pub d: Vec<Vec<usize>>,
}

impl IO {
    pub fn new() -> Self {
        proconio::input! {
            n: usize,
            h: [String; n - 1],
            v: [String; n],
            d: [[usize; n]; n],
        }

        let h = h
            .iter()
            .map(|s| {
                s.chars()
                    .map(|c| c.to_digit(10).unwrap() as u8)
                    .collect::<Vec<_>>()
            })
            .collect::<Vec<_>>();

        let v = v
            .iter()
            .map(|s| {
                s.chars()
                    .map(|c| c.to_digit(10).unwrap() as u8)
                    .collect::<Vec<_>>()
            })
            .collect::<Vec<_>>();

        let map = {
            let mut map = vec![vec![(1 << 4) - 1; n]; n];
            for i in 0..n - 1 {
                for j in 0..n {
                    if h[i][j] == 1 {
                        map[i][j] &= !(1 << Direction::D as u8);
                        map[i + 1][j] &= !(1 << Direction::U as u8);
                    }
                }
            }
            for i in 0..n {
                for j in 0..n - 1 {
                    if v[i][j] == 1 {
                        map[i][j] &= !(1 << Direction::R as u8);
                        map[i][j + 1] &= !(1 << Direction::L as u8);
                    }
                }
            }

            for j in 0..n {
                map[0][j] &= !(1 << Direction::U as u8);
                map[n - 1][j] &= !(1 << Direction::D as u8);
            }

            for i in 0..n {
                map[i][0] &= !(1 << Direction::L as u8);
                map[i][n - 1] &= !(1 << Direction::R as u8);
            }
            map
        };

        Self { n, map, d }
    }

    // 枠外に出る場合もここで判定
    fn check(&self, pos: (usize, usize), d: Direction) -> bool {
        self.map[pos.0][pos.1] & (1 << d as u8) != 0
    }

    pub fn next_pos(&self, pos: (usize, usize), d: Direction) -> Option<(usize, usize)> {
        if !self.check(pos, d) {
            return None;
        }
        let d = d.to_offset();
        Some(((pos.0 as i32 + d.0) as usize, (pos.1 as i32 + d.1) as usize))
    }

    pub fn output(&self, res: &State) {
        let ans = res.convert_to_string();
        println!("{}", ans);
        exit(0);
    }
}

pub struct Walk {
    pub d: Vec<Direction>,
    start: (usize, usize),
    pos: (usize, usize),
}

impl Walk {
    fn new(pos: (usize, usize)) -> Self {
        Self {
            d: vec![],
            start: pos,
            pos,
        }
    }

    fn add(&mut self, io: &IO, d: Direction) {
        self.d.push(d);
        if let Some(npos) = io.next_pos(self.pos, d) {
            self.pos = npos;
        } else {
            unreachable!("Walk::add");
        }
    }

    pub fn connect(&mut self, other: Self) {
        if self.pos != other.start {
            unreachable!("Walk::connect");
        }
        self.d.extend(other.d);
        self.pos = other.pos;
    }
}

pub struct Data<'a> {
    io: &'a IO,
    dist: Vec<Vec<Vec<Vec<usize>>>>,
    pub neighborhood: Vec<Vec<Vec<(usize, usize)>>>,
}

impl<'a> Data<'a> {
    pub fn new(io: &'a IO) -> Self {
        // dist の計算に N = 40 のときで 50ms くらい 前処理なので許容範囲？
        let (dist, neighborhood) = {
            let mut dist = vec![vec![vec![vec![usize::MAX; io.n]; io.n]; io.n]; io.n];
            let mut neighborhood = vec![vec![vec![]; io.n]; io.n];
            for si in 0..io.n {
                for sj in 0..io.n {
                    let mut q = std::collections::VecDeque::new();
                    q.push_back((si, sj));
                    dist[si][sj][si][sj] = 0;
                    while let Some((i, j)) = q.pop_front() {
                        for d in Direction::all() {
                            if let Some((ni, nj)) = io.next_pos((i, j), d) {
                                if dist[si][sj][ni][nj] == usize::MAX {
                                    dist[si][sj][ni][nj] = dist[si][sj][i][j] + 1;
                                    if dist[si][sj][ni][nj] <= NEIGHBORHOOD_DIST {
                                        neighborhood[si][sj].push((ni, nj));
                                    }
                                    q.push_back((ni, nj));
                                }
                            }
                        }
                    }
                }
            }
            (dist, neighborhood)
        };

        Self {
            io,
            dist,
            neighborhood,
        }
    }

    pub fn dist(&self, start: (usize, usize), goal: (usize, usize)) -> usize {
        self.dist[start.0][start.1][goal.0][goal.1]
    }

    pub fn generate_path(
        &self,
        state: &State,
        start: (usize, usize),
        goal: (usize, usize),
    ) -> Walk {
        let mut res = Walk::new(start);
        let dist = &self.dist[goal.0][goal.1];
        let mut t = 0;
        while res.pos != goal {
            // let d = Direction::all()
            //     .iter()
            //     .filter(|&&d| {
            //         if let Some((nx, ny)) = self.io.next_pos(res.pos, d) {
            //             return dist[nx][ny] < dist[res.pos.0][res.pos.1];
            //         }
            //         false
            //     })
            //     .cloned()
            //     .collect::<Vec<_>>();

            // let d = *Random::get_item(&d);
            // res.add(self.io, d);

            let d = Direction::all()
                .iter()
                .map(|&d| {
                    if let Some((nx, ny)) = self.io.next_pos(res.pos, d) {
                        if dist[nx][ny] < dist[res.pos.0][res.pos.1] {
                            // return Some((self.io.d[nx][ny], d));
                            return Some((
                                time_score(&state.map[nx][ny], t, state.d.len(), self.io.d[nx][ny]),
                                d,
                            ));
                        }
                    }
                    return None;
                })
                .filter_map(|x| x)
                .max_by_key(|&(t, _)| t);

            if let Some((_, d)) = d {
                res.add(self.io, d);
                t += 1;
            } else {
                unreachable!("generate_path");
            }
        }
        res
    }
}

pub enum Operation {
    Del(DelOperation),
    DelAdd(DelAddOperation),
    Tie(TieOperation),
}

pub fn generate_operation(timer: &Timer, state: &State, io: &IO, data: &Data) -> Operation {
    if Random::get(0..1000) < 1 {
        return Operation::Tie(generate_tie_operation(state, io));
    }
    let t = timer.get_time() / TL;
    let r = Random::get_f();
    if r < t && state.low_routes.len() > 50 {
        // 時間経過でDelAddが選ばれるように
        // 削除区間が決まっちゃって...みたいな？
        Operation::DelAdd(generate_del_add_operation(state, io, data))
    } else {
        Operation::Del(generate_del_operation(state, io))
    }
}

pub struct DelOperation {
    // [l, r] を削除、 d を入れる
    pub l: usize,
    pub r: usize,
    pub d: Direction,
}

fn generate_del_operation(state: &State, io: &IO) -> DelOperation {
    loop {
        // d が小さいのを start に選びやすくする...など
        let start = Random::get_2d(0..io.n);
        let t = *Random::get_item(&state.map[start.0][start.1]);
        for d in Direction::random() {
            if let Some(goal) = io.next_pos(start, d) {
                if state.map[goal.0][goal.1].contains(&(t + 1))
                    || state.map[goal.0][goal.1].contains(&(t - 1))
                {
                    continue;
                }
                let nt = state.map[goal.0][goal.1]
                    .iter()
                    .map(|&x| (x, (x as i32 - t as i32).abs()))
                    .min_by_key(|&(_, d)| d)
                    .unwrap()
                    .0;

                let l = t.min(nt);
                let r = t.max(nt);
                let d = if t < nt { d } else { d.opposite() };

                return DelOperation { l, r, d };
            }
        }
    }
}

pub const SHORT_ROUTE: usize = 8;
pub const NEIGHBORHOOD_DIST: usize = 5;

pub struct DelAddOperation {
    pub l: usize,
    pub r: usize,
    pub d: Vec<Direction>,
}

pub fn time_score(time: &Vec<usize>, t: usize, l: usize, d: usize) -> usize {
    let diff = if time[0] >= t {
        time.last().unwrap() + t - l
    } else {
        let (mut ok, mut ng) = (0, time.len());
        while ng - ok > 1 {
            let mid = (ok + ng) / 2;
            if time[mid] < t {
                ok = mid
            } else {
                ng = mid
            }
        }
        t - time[ok]
    };
    (diff - 1) * diff / 2 * d
}

pub fn generate_del_add_operation(state: &State, io: &IO, data: &Data) -> DelAddOperation {
    let route = Random::get_item(&state.low_routes);
    if data.dist(route.start, route.goal) <= SHORT_ROUTE {
        // let (_, pos) = data.neighborhood[route.start.0][route.start.1]
        //     .iter()
        //     // score_map ではなく、そのタイミングで大きいやつを選択したい
        //     .map(|&pos| (state.score_map[pos.0][pos.1], pos))
        //     .max_by_key(|&(score, _)| score)
        //     .unwrap();

        let neighborhood = data.neighborhood[route.start.0][route.start.1]
            .iter()
            .filter(|&&pos| {
                data.dist(route.start, pos) + data.dist(pos, route.goal)
                    <= SHORT_ROUTE + 2 * NEIGHBORHOOD_DIST
            })
            .cloned()
            .collect::<Vec<_>>();

        let pos = {
            let mut scores = neighborhood
                .iter()
                // .map(|&pos| (state.score_map[pos.0][pos.1], pos))
                .map(|&pos| {
                    (
                        time_score(
                            &state.map[pos.0][pos.1],
                            route.t,
                            state.d.len(),
                            io.d[pos.0][pos.1],
                        ),
                        pos,
                    )
                })
                .collect::<Vec<_>>();
            scores.sort_by_key(|&(d, _)| usize::MAX - d);
            // let r = Random::get(0..10.min(scores.len()));
            let r = Random::get(0..5.min(scores.len()));
            scores[r].1
        };

        let walk = {
            let mut res = data.generate_path(state, route.start, pos);
            res.connect(data.generate_path(state, pos, route.goal));
            res
        };

        DelAddOperation {
            l: route.t,
            r: route.nt,
            d: walk.d,
        }
    } else {
        let path = data.generate_path(state, route.start, route.goal);
        DelAddOperation {
            l: route.t,
            r: route.nt,
            d: path.d,
        }
    }
}

pub struct TieOperation {
    pub count: usize,
}

pub fn generate_tie_operation(state: &State, io: &IO) -> TieOperation {
    let l = state.d.len();
    let lim = if io.n < 25 {
        5000
    } else if io.n < 30 {
        5000
    } else if io.n < 35 {
        10000
    } else {
        10000
    };

    if l * 2 > lim {
        return TieOperation { count: 1 };
    }
    TieOperation { count: 2 }
}

struct Solver<'a> {
    timer: Timer,
    io: &'a IO,
    data: Data<'a>,
    visited: Vec<Vec<bool>>,
}

impl<'a> Solver<'a> {
    fn new(timer: Timer, io: &'a IO, data: Data<'a>) -> Self {
        let visited = vec![vec![false; io.n]; io.n];
        Self {
            timer,
            io,
            data,
            visited,
        }
    }

    fn dfs(&mut self, i: usize, j: usize, res: &mut Vec<Direction>) {
        self.visited[i][j] = true;
        for d in Direction::all() {
            if let Some((ni, nj)) = self.io.next_pos((i, j), d) {
                if self.visited[ni][nj] {
                    continue;
                }
                res.push(d);
                self.dfs(ni, nj, res);
                res.push(d.opposite());
            } else {
                continue;
            }
        }
    }

    fn solve(&mut self) {
        let mut res = vec![];
        self.dfs(0, 0, &mut res);
        // eprintln!("{}", res.judge(&self.io).unwrap());
        let state = State::new(self.io, &self.data, res).unwrap();
        let tie_op = generate_tie_operation(&state, &self.io);
        let mut state = state.apply_tie(self.io, &self.data, &tie_op).unwrap();
        // .apply_tie(self.io, &self.data, &tie_op)
        // .unwrap();

        let mut gen = (0, 0, 0);
        let mut app = (0, 0, 0);
        let mut acc = (0, 0, 0);

        let count = |op: &Operation, cnt: (usize, usize, usize)| match op {
            Operation::Del(_) => (cnt.0 + 1, cnt.1, cnt.2),
            Operation::DelAdd(_) => (cnt.0, cnt.1 + 1, cnt.2),
            Operation::Tie(_) => (cnt.0, cnt.1, cnt.2 + 1),
        };

        // let mut err_cnt = [0; 4];

        while self.timer.get_time() < TL {
            let op = generate_operation(&self.timer, &state, &self.io, &self.data);
            gen = count(&op, gen);
            match state.apply(self.io, &self.data, &op) {
                Ok(new_state) => {
                    app = count(&op, app);
                    if self.timer.force_next(&state, &new_state) {
                        acc = count(&op, acc);
                        state = new_state;
                    }
                }
                _ => {}
                // Err(error) => match op {
                //     Operation::DelAdd(_) => {
                //         err_cnt[error as usize] += 1;
                //     }
                //     _ => {}
                // },
            }
        }

        eprintln!(
            "del: {} / {} / {}, delAdd: {} / {} / {}, tie: {} / {} / {}",
            gen.0, app.0, acc.0, gen.1, app.1, acc.1, gen.2, app.2, acc.2
        );
        eprintln!("score: {}", state.score);
        // eprintln!("err: {:?}", err_cnt);

        self.io.output(&state);
    }
}

fn main() {
    let timer = Timer::new();
    let io = IO::new();
    let data = Data::new(&io);
    let mut solver = Solver::new(timer, &io, data);
    solver.solve()
}
