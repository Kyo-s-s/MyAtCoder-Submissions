
// path: utils.rs
pub const DEBUG: bool = false;
pub const GOOD_PROJECT_SIZE: f64 = 8.;
pub const GOOD_PROJECT_EFFECT: f64 = 1.3;
pub const GOOD_REGULAR_WORK_NORMAL: f64 = 1.5;
pub const GOOD_REGULAR_WORK_LOW: f64 = 1.4;

/*

pub const GOOD_PROJECT_SIZE: f64 = 8.;
pub const GOOD_PROJECT_EFFECT: f64 = 1.3;
pub const GOOD_REGULAR_WORK_NORMAL: f64 = 1.5;
pub const GOOD_REGULAR_WORK_LOW: f64 = 1.4;

500/500
total: 141001727
max: (21316061, '0045')
ave: 282003.454
min: (49, '0188')
--------------------------
K=2 ave: 12853.245901639344
K=3 ave: 51967.71900826446
K=4 ave: 237077.05970149254
K=5 ave: 824204.9674796748
--------------------------
N=2 ave: 157539.85714285713
N=3 ave: 217519.4712643678
N=4 ave: 226384.2705882353
N=5 ave: 172815.16438356164
N=6 ave: 549463.5632183908
N=7 ave: 364674.1038961039

*/

// path: card.rs

#[derive(Debug, Clone, Copy)]
pub enum Card {
    RegularWork(RegularWork),
    FullForceWork(FullForceWork),
    Cancel,
    TaskSwitch,
    IncreaseCapital,
}

impl Card {
    pub fn new(t: usize, w: usize) -> Self {
        match t {
            0 => Card::RegularWork(RegularWork::new(w)),
            1 => Card::FullForceWork(FullForceWork::new(w)),
            2 => Card::Cancel,
            3 => Card::TaskSwitch,
            4 => Card::IncreaseCapital,
            _ => unreachable!(),
        }
    }

    pub fn is_regular_work(&self) -> bool {
        match self {
            Card::RegularWork(_) => true,
            _ => false,
        }
    }

    pub fn is_full_force_work(&self) -> bool {
        match self {
            Card::FullForceWork(_) => true,
            _ => false,
        }
    }

    pub fn is_cancel(&self) -> bool {
        match self {
            Card::Cancel => true,
            _ => false,
        }
    }

    pub fn is_task_switch(&self) -> bool {
        match self {
            Card::TaskSwitch => true,
            _ => false,
        }
    }

    pub fn is_increase_capital(&self) -> bool {
        match self {
            Card::IncreaseCapital => true,
            _ => false,
        }
    }
}

pub struct CardCounter {
    k: usize,
    sum: usize,
    counter: (usize, usize, usize, usize, usize),
}

impl CardCounter {
    pub fn new(k: usize) -> Self {
        Self {
            k,
            sum: 0,
            counter: (0, 0, 0, 0, 0),
        }
    }

    pub fn add(&mut self, cards: &[Card]) {
        for &card in cards {
            self.add_single(card);
        }
    }

    fn add_single(&mut self, card: Card) {
        self.sum += 1;
        match card {
            Card::RegularWork(_) => self.counter.0 += 1,
            Card::FullForceWork(_) => self.counter.1 += 1,
            Card::Cancel => self.counter.2 += 1,
            Card::TaskSwitch => self.counter.3 += 1,
            Card::IncreaseCapital => self.counter.4 += 1,
        }
    }

    pub fn next_single_increase_capital(&self) -> f64 {
        let (r, f, c, t, i) = self.counter;
        let sum = r + f + c + t + i;
        let sum = sum as f64;
        let i = i as f64;
        i / sum
    }
}

#[derive(Debug, Clone, Copy)]
pub struct RegularWork {
    pub w: usize,
}

impl RegularWork {
    pub fn new(w: usize) -> Self {
        Self { w }
    }

    pub fn is_good(&self, cost: usize, next_turn_get_increase_capital: f64) -> bool {
        if next_turn_get_increase_capital > 0.01 {
            cost != 0 && cost as f64 * GOOD_REGULAR_WORK_LOW <= self.w as f64
        } else {
            cost != 0 && cost as f64 * GOOD_REGULAR_WORK_NORMAL <= self.w as f64
        }
    }
}

#[derive(Debug, Clone, Copy)]
pub struct FullForceWork {
    pub w: usize,
}

impl FullForceWork {
    pub fn new(w: usize) -> Self {
        Self { w }
    }
}

// path: project.rs

#[derive(Debug, Clone, Copy)]
pub struct Project {
    pub h: usize,
    pub v: usize,
}

impl Project {
    pub fn new(h: usize, v: usize) -> Self {
        Self { h, v }
    }

    pub fn efficiency(&self) -> f64 {
        self.v as f64 / self.h as f64
    }

    pub fn is_good(&self, level: usize) -> bool {
        let good_size = (2. as f64).powf(GOOD_PROJECT_SIZE) as usize * (1 << level);
        self.efficiency() >= GOOD_PROJECT_EFFECT && self.h <= good_size
    }
}

// path: io.rs

use proconio::{input, source::line::LineSource};
use std::io::BufRead;

pub const T: usize = 1000;

fn clamp<T: PartialOrd>(base: T, min: T, max: T) -> T {
    if base < min {
        min
    } else if base > max {
        max
    } else {
        base
    }
}

fn single_buy_increase_capital(money: usize, l: usize) -> f64 {
    let min = (200 * (1 << l)) as f64;
    let max = (1000 * (1 << l)) as f64;
    let res = (money as f64 - min) / (max - min);
    clamp(res, 0.0, 1.0)
}

pub struct IO<R: BufRead> {
    source: LineSource<R>,
    n: usize,
    pub m: usize,
    k: usize,
    hands: Vec<Card>,
    projects: Vec<Project>,
    money: usize,
    selectable_cards: Vec<(Card, usize)>, // card, cost
    used_card_index: usize,
    counter: CardCounter,
    pub level: usize,
}

impl<R: BufRead> IO<R> {
    pub fn new(mut source: LineSource<R>) -> Self {
        input! {
            from &mut source,
            n: usize,
            m: usize,
            k: usize,
            _: usize, // t
            hands: [(usize, usize); n],
            projects: [(usize, usize); m],
        }

        let hands = hands
            .iter()
            .map(|&(t, w)| Card::new(t, w))
            .collect::<Vec<_>>();

        let projects = projects
            .iter()
            .map(|&(h, v)| Project::new(h, v))
            .collect::<Vec<_>>();

        let mut counter = CardCounter::new(k);
        counter.add(&hands);

        Self {
            source,
            n,
            m,
            k,
            hands,
            projects,
            money: 0,
            selectable_cards: vec![],
            used_card_index: 0,
            counter,
            level: 0,
        }
    }

    pub fn base(&self) -> usize {
        1 << self.level
    }

    pub fn get_hands(&self) -> Vec<(usize, Card)> {
        self.hands
            .iter()
            .enumerate()
            .filter(|(_, &c)| !(c.is_increase_capital() && self.level >= 20))
            .map(|(i, &c)| (i, c))
            .collect::<Vec<_>>()
    }

    pub fn get_projects(&self) -> Vec<(usize, Project)> {
        self.projects
            .iter()
            .enumerate()
            .map(|(i, &p)| (i, p))
            .collect::<Vec<_>>()
    }

    pub fn get_selectable_cards(&self) -> Vec<(usize, (Card, usize))> {
        self.selectable_cards
            .iter()
            .enumerate()
            .filter(|(_, &(_, cost))| cost <= self.money)
            .map(|(i, &(c, _))| (i, (c, self.selectable_cards[i].1)))
            .collect::<Vec<_>>()
    }

    // when hands[hands_index] is FullForceWork, TaskSwitch or IncreaseCapital,
    // hands_index must be 0.
    pub fn apply(&mut self, hand_index: usize, project_index: usize) {
        if self.hands[hand_index].is_increase_capital() {
            self.level += 1;
        }
        self.used_card_index = hand_index;
        println!("{} {}", hand_index, project_index);
        input! {
            from &mut self.source,
            projects: [(usize, usize); self.m],
            money: usize,
            new_cards: [(usize, usize, usize); self.k],
        }

        self.projects = projects
            .iter()
            .map(|&(h, v)| Project::new(h, v))
            .collect::<Vec<_>>();

        self.money = money;

        self.selectable_cards = new_cards
            .iter()
            .map(|&(t, w, p)| (Card::new(t, w), p))
            .collect::<Vec<_>>();

        self.counter.add(
            &self
                .selectable_cards
                .iter()
                .map(|&(c, _)| c)
                .collect::<Vec<_>>(),
        );
    }

    pub fn select_card(&mut self, card_index: usize) {
        println!("{}", card_index);
        self.hands[self.used_card_index] = self.selectable_cards[card_index].0;
    }

    pub fn debug(&self, debug: String) {
        if DEBUG {
            println!("# {}", debug);
        }
    }

    pub fn next_turn_get_increase_capital(&self) -> f64 {
        let app = self.counter.next_single_increase_capital();
        let buy = single_buy_increase_capital(self.money, self.level);
        let next_single = app * buy;
        let mut res = 1.;
        (0..self.k).for_each(|_| res *= 1. - next_single);
        1. - res
    }

    pub fn next_turn10_get_increase_capital(&self) -> f64 {
        let app = self.counter.next_single_increase_capital();
        let buy = single_buy_increase_capital(self.money, self.level);
        let next_single = app * buy;
        let mut res = 1.;
        (0..self.k * 10).for_each(|_| res *= 1. - next_single);
        1. - res
    }

    pub fn next_turn20_get_increase_capital(&self) -> f64 {
        let app = self.counter.next_single_increase_capital();
        let buy = single_buy_increase_capital(self.money, self.level);
        let next_single = app * buy;
        let mut res = 1.;
        (0..self.k * 20).for_each(|_| res *= 1. - next_single);
        1. - res
    }
}

// path: solver.rs

pub struct Solver<R: BufRead> {
    io: IO<R>,
}

impl<R: BufRead> Solver<R> {
    pub fn new(io: IO<R>) -> Self {
        Self { io }
    }

    pub fn solve(&mut self) {
        for t in 0..T {
            // use card
            let (hand_index, project_index) = self.generate_apply();
            self.io.apply(hand_index, project_index);

            // choice get card
            let card_index = self.generate_select_card(t);
            self.io.select_card(card_index);

            // debug
            self.io.debug(format!(
                "next_turn_increase_capital: {}",
                self.io.next_turn_get_increase_capital(),
            ));

            self.io.debug(format!(
                "next_turn10_increase_capital: {}",
                self.io.next_turn10_get_increase_capital(),
            ));

            self.io.debug(format!(
                "next_turn20_increase_capital: {}",
                self.io.next_turn20_get_increase_capital(),
            ));
        }
    }
}

impl<R: BufRead> Solver<R> {
    fn choice_increase_capital(&self, hands: &Vec<(usize, Card)>) -> Option<(usize, usize)> {
        if let Some(&(idx, _)) = hands.iter().find(|&&(_, card)| card.is_increase_capital()) {
            Some((idx, 0))
        } else {
            None
        }
    }

    fn choice_cancel_bad_project(
        &self,
        hands: &Vec<(usize, Card)>,
        projects: &Vec<(usize, Project)>,
    ) -> Option<(usize, usize)> {
        if let Some(&(card_idx, _)) = hands.iter().find(|&&(_, card)| card.is_cancel()) {
            if let Some(&(project_idx, _)) = projects
                .iter()
                .find(|&&(_, project)| !project.is_good(self.io.level))
            {
                return Some((card_idx, project_idx));
            }
        }
        None
    }

    fn choice_task_switch(
        &self,
        hands: &Vec<(usize, Card)>,
        projects: &Vec<(usize, Project)>,
    ) -> Option<(usize, usize)> {
        if let Some(&(card_idx, _)) = hands.iter().find(|&&(_, card)| card.is_task_switch()) {
            if projects
                .iter()
                .all(|&(_, project)| !project.is_good(self.io.level))
            {
                return Some((card_idx, 0));
            }
        }
        None
    }

    fn chioce_full_force_work(&self, hands: &Vec<(usize, Card)>) -> Option<(usize, usize)> {
        if let Some(&(idx, _)) = hands.iter().find(|&&(_, card)| card.is_full_force_work()) {
            Some((idx, 0))
        } else {
            None
        }
    }

    fn choice_regular_work(
        &self,
        hands: &Vec<(usize, Card)>,
        projects: &Vec<(usize, Project)>,
    ) -> Option<(usize, usize)> {
        let card_idx = {
            let mut hands = hands
                .iter()
                .flat_map(|&(idx, card)| match card {
                    Card::RegularWork(card) => Some((idx, card)),
                    _ => None,
                })
                .collect::<Vec<_>>();
            if hands.is_empty() {
                return None;
            }
            hands.sort_by_key(|&(_, card)| -1 * card.w as isize);
            hands[0].0
        };

        let projects_idx = {
            let mut good_projects = projects
                .iter()
                .filter(|&(_, project)| project.is_good(self.io.level))
                .collect::<Vec<_>>();
            good_projects.sort_by(|&(_, a), &(_, b)| {
                let (a, b) = (a.efficiency(), b.efficiency());
                b.partial_cmp(&a).unwrap()
            });
            if let Some(&&(idx, _)) = good_projects.first() {
                idx
            } else {
                let mut projects = projects.clone();
                projects.sort_by(|&(_, a), &(_, b)| {
                    let (a, b) = (a.efficiency(), b.efficiency());
                    b.partial_cmp(&a).unwrap()
                });
                projects[0].0
            }
        };
        return Some((card_idx, projects_idx));
    }

    fn generate_apply(&mut self) -> (usize, usize) {
        let hands = self.io.get_hands();
        let projects = self.io.get_projects();

        None.or(self.choice_increase_capital(&hands))
            .or(self.choice_cancel_bad_project(&hands, &projects))
            .or(self.choice_task_switch(&hands, &projects))
            .or(self.chioce_full_force_work(&hands))
            .or(self.choice_regular_work(&hands, &projects))
            .unwrap_or((0, 0))
    }
}

impl<R: BufRead> Solver<R> {
    fn select_increase_capital(
        &self,
        turn: usize,
        selectable: &Vec<(usize, (Card, usize))>,
    ) -> Option<usize> {
        let mut increase_capital = selectable
            .iter()
            .filter(|&&(_, (card, _))| card.is_increase_capital())
            .collect::<Vec<_>>();
        if increase_capital.is_empty() || turn >= T - 100 {
            return None;
        } else {
            increase_capital.sort_by_key(|&(_, (_, cost))| cost);
            return Some(increase_capital[0].0);
        }
    }

    fn select_good_regular_work(&self, selectable: &Vec<(usize, (Card, usize))>) -> Option<usize> {
        let mut good_regular_work = selectable
            .iter()
            .flat_map(|&(idx, (card, cost))| match card {
                Card::RegularWork(card) => {
                    if card.is_good(cost, self.io.next_turn_get_increase_capital()) {
                        Some((idx, card, cost))
                    } else {
                        None
                    }
                }
                _ => None,
            })
            .collect::<Vec<_>>();
        if good_regular_work.is_empty() {
            None
        } else {
            good_regular_work.sort_by(|&(_, a, ca), &(_, b, cb)| {
                let (a, b) = (a.w as f64 / ca as f64, b.w as f64 / cb as f64);
                b.partial_cmp(&a).unwrap()
            });
            Some(good_regular_work[0].0)
        }
    }

    fn hand_full_cancel_and_task_switch(&self, hands: &Vec<(usize, Card)>) -> bool {
        hands
            .iter()
            .filter(|&&(_, card)| !(card.is_cancel() || card.is_task_switch()))
            .collect::<Vec<_>>()
            .len()
            < 2
    }

    fn select_task_switch(
        &self,
        hands: &Vec<(usize, Card)>,
        selectable: &Vec<(usize, (Card, usize))>,
    ) -> Option<usize> {
        if self.hand_full_cancel_and_task_switch(hands) {
            return None;
        }
        selectable
            .iter()
            .find(|&&(_, (card, cost))| card.is_task_switch() && cost == 0)
            .map(|&(idx, _)| idx)
    }

    fn select_cancel(
        &self,
        hands: &Vec<(usize, Card)>,
        selectable: &Vec<(usize, (Card, usize))>,
    ) -> Option<usize> {
        if self.hand_full_cancel_and_task_switch(hands) {
            return None;
        }
        selectable
            .iter()
            .find(|&&(_, (card, cost))| card.is_cancel() && cost == 0)
            .map(|&(idx, _)| idx)
    }

    fn generate_select_card(&mut self, turn: usize) -> usize {
        let hands = self.io.get_hands();
        let selectable = self.io.get_selectable_cards();

        None.or(self.select_increase_capital(turn, &selectable))
            .or(self.select_good_regular_work(&selectable))
            .or(self.select_task_switch(&hands, &selectable))
            .or(self.select_cancel(&hands, &selectable))
            .unwrap_or(0)
    }
}
fn main() {
    let source = proconio::source::line::LineSource::new(std::io::stdin().lock());
    let io = IO::new(source);
    let mut solver = Solver::new(io);
    solver.solve();
}
