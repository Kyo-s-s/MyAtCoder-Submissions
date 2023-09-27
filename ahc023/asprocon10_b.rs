extern crate rand;

use proconio::marker::Usize1;
use rand::Rng;
use std::{collections::VecDeque, io::Write, time::SystemTime};

const LOCAL: bool = false;
const TL: f64 = if LOCAL { 6.0 } else { 1.9 };

const H: usize = 20;
const W: usize = 20;
const T: usize = 100;

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

#[derive(Clone, Copy)]
struct Crop {
    s: usize,
    d: usize,
}

struct Query {
    k: usize,
    i: usize,
    j: usize,
    s: usize,
    d: usize,
}

impl Query {
    fn new(k: usize, i: usize, j: usize, s: usize, d: usize) -> Query {
        Query { k, i, j, s, d }
    }
}

struct IO {
    i0: usize,
    // 0: up, 1: right, 2: down, 3: left
    map: [[[bool; 4]; W]; H],
    k: usize,
    c: Vec<Crop>,
}

impl IO {
    fn new() -> IO {
        proconio::input! {
            _: usize,
            _: usize,
            _: usize,
            i0: usize,
            wall_h: [String; (H - 1) as usize],
            wall_w: [String; H],
            k: usize,
            c: [(Usize1, Usize1); k],
        }

        let mut map = [[[false; 4]; W]; H];
        let wall_h = wall_h
            .iter()
            .map(|s| s.chars().collect::<Vec<_>>())
            .collect::<Vec<_>>();
        let wall_w = wall_w
            .iter()
            .map(|s| s.chars().collect::<Vec<_>>())
            .collect::<Vec<_>>();
        for i in 0..(H - 1) {
            for j in 0..W {
                if wall_h[i][j] == '0' {
                    map[i][j][2] = true;
                    map[i + 1][j][0] = true;
                }
            }
        }
        for i in 0..H {
            for j in 0..(W - 1) {
                if wall_w[i][j] == '0' {
                    map[i][j][1] = true;
                    map[i][j + 1][3] = true;
                }
            }
        }
        IO {
            i0,
            k,
            map,
            c: c.iter().map(|&(s, d)| Crop { s, d }).collect(),
        }
    }
}

fn get_dist(d: usize) -> (i32, i32) {
    match d {
        0 => (-1, 0),
        1 => (0, 1),
        2 => (1, 0),
        3 => (0, -1),
        _ => unreachable!(),
    }
}

fn get_next_pos(i: usize, j: usize, d: usize) -> (usize, usize) {
    let (di, dj) = get_dist(d);
    ((i as i32 + di) as usize, (j as i32 + dj) as usize)
}

#[derive(Clone, Copy)]
enum Cell {
    None,
    Plant(usize),
    Grow,
    Harvest,
}

impl Cell {
    fn is_none(&self) -> bool {
        match self {
            Cell::None => true,
            _ => false,
        }
    }
    fn is_plant(&self) -> bool {
        match self {
            Cell::Plant(_) => true,
            _ => false,
        }
    }
    fn is_harvest(&self) -> bool {
        match self {
            Cell::Harvest => true,
            _ => false,
        }
    }
}

struct State {
    map: [[[Cell; W]; H]; T],
    used: Vec<bool>,
    score: usize,
    cell_score: [[usize; W]; H],
}

impl State {
    fn new(io: &IO) -> State {
        State {
            map: [[[Cell::None; W]; H]; T],
            used: vec![false; io.k],
            score: 0,
            cell_score: [[0; W]; H],
        }
    }

    fn can_go(&self, t: usize, plant: bool, i: usize, j: usize) -> bool {
        match self.map[t][i][j] {
            Cell::None => true,
            Cell::Plant(_) => plant,
            Cell::Grow => false,
            Cell::Harvest => !plant,
        }
    }

    fn can_visit_dfs(
        &self,
        res: &mut [[bool; W]; H],
        io: &IO,
        t: usize,
        plant: bool,
        i: usize,
        j: usize,
    ) {
        if res[i][j] || !self.can_go(t, plant, i, j) {
            return;
        }
        res[i][j] = true;
        for d in 0..4 {
            if io.map[i][j][d] {
                let (ni, nj) = get_next_pos(i, j, d);
                if res[ni][nj] || !self.can_go(t, plant, ni, nj) {
                    continue;
                }
                self.can_visit_dfs(res, io, t, plant, ni, nj);
            }
        }
    }

    fn can_visit(&self, io: &IO, t: usize, plant: bool) -> [[bool; W]; H] {
        let mut res = [[false; W]; H];
        self.can_visit_dfs(&mut res, io, t, plant, io.i0, 0);
        res
    }

    fn add_score(&mut self, io: &IO, query: &Query) -> usize {
        let crop = &io.c[query.k];
        if query.s > crop.s || self.used[query.k] {
            return 0;
        }
        let (s, d, i, j) = (query.s, query.d, query.i, query.j);
        for t in s..=d {
            if !self.map[t][i][j].is_none() {
                return 0;
            }
        }
        {
            let can_visit = self.can_visit(io, s, true);
            if !can_visit[i][j] {
                return 0;
            }
        }
        {
            let can_visit = self.can_visit(io, d, false);
            if !can_visit[i][j] {
                return 0;
            }
        }
        self.insert_query_to_map(query);
        let ok = {
            let mut ok = true;
            for t in (s + 1)..=d {
                let can_visit = self.can_visit(io, t, true);
                for i in 0..H {
                    for j in 0..W {
                        if !can_visit[i][j] && self.map[t][i][j].is_plant() {
                            ok = false;
                            break;
                        }
                    }
                }
            }
            for t in s..d {
                let can_visit = self.can_visit(io, t, false);
                for i in 0..H {
                    for j in 0..W {
                        if !can_visit[i][j] && self.map[t][i][j].is_harvest() {
                            ok = false;
                            break;
                        }
                    }
                }
            }
            ok
        };

        self.delete_query_to_map(query);
        if ok {
            self.score + d - s + 1
        } else {
            0
        }
    }

    fn add_query(&mut self, io: &IO, query: &Query) -> usize {
        let (k, s, d) = (query.k, query.s, query.d);
        self.score += io.c[k].d - io.c[k].s + 1;
        self.cell_score[query.i][query.j] += io.c[k].d - io.c[k].s + 1;
        self.used[k] = true;
        self.insert_query_to_map(query);
        self.score
    }

    fn insert_query_to_map(&mut self, query: &Query) {
        let (s, d, i, j) = (query.s, query.d, query.i, query.j);
        self.map[s][i][j] = Cell::Plant(query.k);
        self.map[d][i][j] = Cell::Harvest;
        for t in (s + 1)..d {
            self.map[t][i][j] = Cell::Grow;
        }
    }

    fn delete_query(&mut self, io: &IO, query: &Query) -> usize {
        let (k, s, d) = (query.k, query.s, query.d);
        self.score -= io.c[k].d - io.c[k].s + 1;
        self.cell_score[query.i][query.j] -= io.c[k].d - io.c[k].s + 1;
        self.used[k] = false;
        self.delete_query_to_map(query);
        self.score
    }

    fn delete_query_to_map(&mut self, query: &Query) {
        let (s, d, i, j) = (query.s, query.d, query.i, query.j);
        for t in s..=d {
            self.map[t][i][j] = Cell::None;
        }
    }

    fn output(&self, io: &IO) {
        let stdout = std::io::stdout();
        let mut out = std::io::BufWriter::new(stdout.lock());
        let mut ans = vec![];
        for s in 0..T {
            for i in 0..H {
                for j in 0..W {
                    if let Cell::Plant(k) = self.map[s][i][j] {
                        let crop = io.c[k];
                        ans.push(Query::new(k, i, j, s, crop.d));
                    }
                }
            }
        }
        writeln!(out, "{}", ans.len()).unwrap();
        for q in ans {
            writeln!(out, "{} {} {} {}", q.k + 1, q.i, q.j, q.s + 1).unwrap();
        }
    }
}

struct Operation {
    destruction: Vec<Query>,
    addition: Vec<Query>,
}

impl Operation {
    fn new() -> Operation {
        Operation {
            destruction: vec![],
            addition: vec![],
        }
    }

    fn add_destruction(&mut self, io: &IO, query: Query, state: &mut State) -> bool {
        if !state.used[query.k] {
            false
        } else {
            state.delete_query(io, &query);
            self.destruction.push(query);
            true
        }
    }

    fn add_addition(&mut self, io: &IO, state: &mut State, query: Query) -> bool {
        if state.add_score(io, &query) == 0 {
            false
        } else {
            state.add_query(io, &query);
            self.addition.push(query);
            true
        }
    }

    fn generate(&mut self, io: &IO, state: &mut State, start_crops: &Vec<Vec<usize>>) {
        let (i, j) = loop {
            let i = rand::thread_rng().gen_range(0..H);
            let j = rand::thread_rng().gen_range(0..W);
            if state.cell_score[i][j] <= 50 && io.map[i][j].iter().all(|&b| b) {
                break (i, j);
            }
        };
        // let i = rand::thread_rng().gen_range(0..H);
        // let j = rand::thread_rng().gen_range(0..W);
        // 破壊する期間
        let r = rand::thread_rng().gen_range(1..=5);
        // 破壊する開始時刻
        let start = rand::thread_rng().gen_range(0..(T - r));
        // 破壊する個数
        // let c = rand::thread_rng().gen_range(1..=3);
        let c = rand::thread_rng().gen_range(1..=10);
        let lim = 7;
        self.generate_pos(io, state, start_crops, i, j, start, r, c, lim);
    }

    fn generate_pos(
        &mut self,
        io: &IO,
        state: &mut State,
        start_crops: &Vec<Vec<usize>>,
        i: usize,
        j: usize,
        start: usize,
        r: usize,
        c: usize,
        lim: usize,
    ) {
        let destroy_pos = {
            let mut destroy_pos = vec![];
            let deque = &mut VecDeque::new();
            deque.push_back((i, j));
            destroy_pos.push((i, j));
            while let Some((i, j)) = deque.pop_front() {
                if destroy_pos.len() >= c {
                    break;
                }
                for d in 0..4 {
                    if io.map[i][j][d] {
                        let (ni, nj) = get_next_pos(i, j, d);
                        if destroy_pos.iter().any(|&(i, j)| i == ni && j == nj) {
                            continue;
                        }
                        destroy_pos.push((ni, nj));
                        deque.push_back((ni, nj));
                    }
                }
            }
            destroy_pos
        };
        for &(i, j) in &destroy_pos {
            self.destruction(io, state, i, j, start, start + r - 1);
        }
        for &(i, j) in &destroy_pos {
            self.addition(io, state, i, j, start, start + r - 1, start_crops, lim);
        }
    }

    fn addition(
        &mut self,
        io: &IO,
        state: &mut State,
        i: usize,
        j: usize,
        start: usize,
        end: usize,
        start_crops: &Vec<Vec<usize>>,
        lim: usize,
    ) {
        let mut start = {
            let mut s = start;
            while s > 0 && state.map[s][i][j].is_none() {
                s -= 1;
            }
            s
        };
        let end = {
            let mut e = end;
            while e < T && state.map[e][i][j].is_none() {
                e += 1;
            }
            e
        };
        while start + 5 <= end {
            if let Some(d) = self.addition_cell(io, state, i, j, start, end, start_crops, lim) {
                start = d;
            } else {
                start += 5;
            }
        }
    }

    // state.map[start][i][j] == Cell::None であるとする、そこに植える
    fn addition_cell(
        &mut self,
        io: &IO,
        state: &mut State,
        i: usize,
        j: usize,
        start: usize,
        end: usize,
        start_crops: &Vec<Vec<usize>>,
        lim: usize,
    ) -> Option<usize> {
        let crops = {
            let mut crops = vec![];
            let mut s = start;
            while s < T && crops.len() < 10 {
                for &k in &start_crops[s] {
                    let crop = &io.c[k];
                    if crop.d < end && !state.used[k] && crop.d - crop.s + 1 <= lim {
                        let mut add = 0;
                        for d in 0..4 {
                            if io.map[i][j][d] {
                                let (ni, nj) = get_next_pos(i, j, d);
                                if state.map[s][ni][nj].is_plant()
                                    || state.map[s][ni][nj].is_harvest()
                                {
                                    add += 100;
                                }
                            }
                        }
                        crops.push((crop, k, add));
                    }
                }
                s += 1;
            }
            crops.sort_by(|&(a, _, aa), &(b, _, bb)| {
                let a = a.d - a.s + 1 + aa;
                let b = b.d - b.s + 1 + bb;
                a.cmp(&b)
            });
            crops
        };
        if crops.is_empty() {
            return None;
        }
        // let k = rand::thread_rng().gen_range(0..crops.len().min(10));
        let k = rand::thread_rng().gen_range(0..crops.len());
        let (crop, k, _) = crops[k];
        let query = Query::new(k, i, j, crop.s, crop.d);
        if self.add_addition(io, state, query) {
            return Some(crop.d + 1);
        }
        None
    }

    fn destruction(
        &mut self,
        io: &IO,
        state: &mut State,
        i: usize,
        j: usize,
        start: usize,
        end: usize,
    ) {
        // let start = if !state.map[start][i][j].is_none() {
        //     let mut s = start;
        //     while s > 0 && !state.map[start][i][j].is_none() {
        //         s -= 1;
        //     }
        //     s
        // } else {
        //     start
        // };
        for t in start..=end {
            self.destruction_cell(io, state, i, j, t);
        }
    }

    // state.map[t][i][j] == Cell::Plant(k) であるとき、それを破壊しdestroyedに追加する
    fn destruction_cell(&mut self, io: &IO, state: &mut State, i: usize, j: usize, t: usize) {
        if let Cell::Plant(k) = state.map[t][i][j] {
            let crop = &io.c[k];
            let query = Query::new(k, i, j, crop.s, crop.d);
            self.add_destruction(io, query, state);
        }
    }

    fn undo(&self, io: &IO, state: &mut State) {
        for query in &self.addition {
            assert!(state.used[query.k]);
            state.delete_query(io, query);
        }
        for query in &self.destruction {
            assert!(!state.used[query.k]);
            state.add_query(io, query);
        }
    }
}

struct Solver {
    io: IO,
    rng: rand::rngs::ThreadRng,
}

impl Solver {
    fn new(io: IO) -> Solver {
        Solver {
            io,
            rng: rand::thread_rng(),
        }
    }

    fn state_add_query(&mut self, state: &mut State, query: &Query) -> bool {
        let score = state.add_score(&self.io, &query);
        if score == 0 {
            false
        } else {
            state.add_query(&self.io, &query);
            true
        }
    }

    fn generate_init(
        &mut self,
        timer: &Timer,
        start_crops: &Vec<Vec<usize>>,
        end_crops: &Vec<Vec<usize>>,
    ) -> State {
        let mut state = State::new(&self.io);
        let map_dist = {
            let mut map = [[usize::MAX; W]; H];
            let mut deque = VecDeque::new();
            deque.push_back((self.io.i0, 0));
            map[self.io.i0][0] = 0;
            while let Some((i, j)) = deque.pop_front() {
                for d in 0..4 {
                    if self.io.map[i][j][d] {
                        let (ni, nj) = get_next_pos(i, j, d);
                        if map[ni][nj] > map[i][j] + 1 {
                            map[ni][nj] = map[i][j] + 1;
                            deque.push_back((ni, nj));
                        }
                    }
                }
            }
            map
        };
        let dist_pos = {
            let map_dist = {
                let mut map = map_dist.clone();
                for i in 0..H {
                    for j in 0..W {
                        for d in 0..4 {
                            if !self.io.map[i][j][d] {
                                map[i][j] += 5;
                            }
                        }
                    }
                }
                map
            };
            let mut dist = vec![];
            let mut used = [[false; W]; H];
            while dist.len() < H * W {
                // usedがfalseで、map_distが最大のものを探す
                let mut pos: Option<(usize, usize)> = None;
                for i in 0..H {
                    for j in 0..W {
                        if used[i][j] {
                            continue;
                        }
                        if let Some((ni, nj)) = pos {
                            if map_dist[i][j] > map_dist[ni][nj] {
                                pos = Some((i, j));
                            }
                        } else {
                            pos = Some((i, j));
                        }
                    }
                }
                // そこから近くc個、未使用のを取る
                let mut c = 3;
                let (i, j) = pos.unwrap();
                let mut deque = VecDeque::new();
                deque.push_back((i, j));
                while let Some((i, j)) = deque.pop_front() {
                    if used[i][j] {
                        continue;
                    }
                    dist.push((map_dist[i][j], i, j));
                    used[i][j] = true;
                    c -= 1;
                    if c == 0 {
                        break;
                    }
                    for d in 0..4 {
                        if self.io.map[i][j][d] {
                            let (ni, nj) = get_next_pos(i, j, d);
                            if !used[ni][nj] {
                                deque.push_back((ni, nj));
                            }
                        }
                    }
                }
            }
            dist
        };

        let crops = {
            let mut crops = vec![];
            for k in 0..self.io.k {
                let crop = self.io.c[k];
                crops.push((crop, k));
            }
            crops.sort_by(|(a, _), (b, _)| {
                if a.s == b.s {
                    (b.d - b.s).cmp(&(a.d - a.s))
                } else {
                    a.s.cmp(&b.s)
                }
            });
            crops
        };

        for (_, i, j) in dist_pos {
            if timer.get_time() > TL {
                break;
            }

            // 近傍クエリを見る
            let mut start = 0;
            for _ in 0..33 {
                let crops = {
                    let mut crops = vec![];
                    let mut idx = start;
                    while crops.len() < 100 {
                        for &k in &start_crops[idx] {
                            let crop = &self.io.c[k];
                            if !state.used[k] {
                                if crop.d - crop.s + 1 < 7 {
                                    continue;
                                }
                                let mut add = 0;
                                // 近傍にs, d のクエリがあったら加点
                                for d in 0..4 {
                                    if self.io.map[i][j][d] {
                                        let (ni, nj) = get_next_pos(i, j, d);
                                        if state.map[idx][ni][nj].is_plant()
                                            || state.map[idx][ni][nj].is_harvest()
                                        {
                                            add += 100;
                                        }
                                    }
                                }
                                crops.push((crop, k, add));
                            }
                        }
                        idx += 1;
                        if idx >= T {
                            break;
                        }
                    }
                    crops.sort_by(|&(a, _, aa), &(b, _, bb)| {
                        let a = a.d - a.s + 1 + aa;
                        let b = b.d - b.s + 1 + bb;
                        b.cmp(&a)
                    });
                    crops
                };
                if crops.is_empty() {
                    break;
                }
                // let k = self.rng.gen_range(0..(crops.len().min(3)));
                let k = 0;
                let (crop, k, _) = crops[k];
                let query = Query::new(k, i, j, crop.s, crop.d);
                let score = state.add_score(&self.io, &query);
                if score > state.score {
                    state.add_query(&self.io, &query);
                    start = crop.d + 1;
                } else {
                    start += 3;
                }
                if start >= T {
                    break;
                }
            }
        }
        state
    }

    fn solve(&mut self, timer: Timer) {
        let start_crops = {
            let mut start_crops = vec![vec![]; T];
            for k in 0..self.io.k {
                let crop = &self.io.c[k];
                start_crops[crop.s].push(k);
            }
            start_crops
        };
        let end_crops = {
            let mut end_crops = vec![vec![]; T];
            for k in 0..self.io.k {
                let crop = &self.io.c[k];
                end_crops[crop.d].push(k);
            }
            end_crops
        };

        let mut state = self.generate_init(&timer, &start_crops, &end_crops);
        let mut cnt = 0;
        let mut acc = 0;

        // while timer.get_time() < 0. {
        while timer.get_time() < TL {
            cnt += 1;
            let i = self.rng.gen_range(0..H);
            let j = self.rng.gen_range(0..W);
            let k = self.rng.gen_range(0..self.io.k);
            let crop = &self.io.c[k];
            let query = Query::new(k, i, j, crop.s, crop.d);
            let score = state.add_score(&self.io, &query);
            if score > state.score {
                acc += 1;
                state.add_query(&self.io, &query);
            }

            // cnt += 1;
            // let prev_score = state.score;
            // let mut op = Operation::new();
            // op.generate(&self.io, &mut state, &start_crops);
            // let score = state.score;
            // if score <= prev_score || score == 0 {
            //     op.undo(&self.io, &mut state);
            // } else {
            //     acc += 1;
            // }
        }
        state.output(&self.io);
        eprint!("cnt: {}, acc: {}, time: {}\n", cnt, acc, timer.get_time());
    }
}

fn main() {
    let timer = Timer::new();
    let io = IO::new();
    let mut solver = Solver::new(io);
    solver.solve(timer);
}
