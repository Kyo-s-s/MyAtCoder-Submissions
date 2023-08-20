#include<bits/stdc++.h>
using namespace std;

int L, N, S;

struct Timer {
    double start_time;
    Timer() {
        start_time = clock();
    }
    double get_time() {
        return (clock() - start_time) / CLOCKS_PER_SEC;
    }
} timer;

struct Pos {
    int y, x;
    Pos() : y(0), x(0) {}
    Pos(int y, int x) : y(y), x(x) {}
    bool operator<(const Pos& p) const {
        return y == p.y ? x < p.x : y < p.y;
    }

    int dist(const Pos& p) const {
        int dy = min(abs(y - p.y), L - abs(y - p.y));
        int dx = min(abs(x - p.x), L - abs(x - p.x));
        return dy + dx;
    }
};

struct Temperature : public vector<vector<int>> {
    const int L;
    Temperature(int L) : L(L), vector<vector<int>>(L, vector<int>(L, 0)), _score(-1) {}
    int _score;

    long long score() {
        if (_score != -1) {
            return _score;
        }
        long long res = 0;
        for (int y = 0; y < L; y++) {
            for (int x = 0; x < L; x++) {
                long long dy = abs((*this)[y][x] - (*this)[(y + 1) % L][x]);
                long long dx = abs((*this)[y][x] - (*this)[y][(x + 1) % L]);
                res += dy * dy + dx * dx;
            }
        }
        _score = res;
        return _score;
    }

    // いくつ増加するかを返す
    long long change(int y, int x, int v, bool change) {
        if (_score == -1) {
            score();
        }
        long long dec = [&](){
            long long dy1 = abs((*this)[y][x] - (*this)[(y + 1) % L][x]);
            long long dy2 = abs((*this)[y][x] - (*this)[(y - 1 + L) % L][x]);
            long long dx1 = abs((*this)[y][x] - (*this)[y][(x + 1) % L]);
            long long dx2 = abs((*this)[y][x] - (*this)[y][(x - 1 + L) % L]);
            return dy1 * dy1 + dy2 * dy2 + dx1 * dx1 + dx2 * dx2;
        }();
        long long inc = [&](){
            long long dy1 = abs(v - (*this)[(y + 1) % L][x]);
            long long dy2 = abs(v - (*this)[(y - 1 + L) % L][x]);
            long long dx1 = abs(v - (*this)[y][(x + 1) % L]);
            long long dx2 = abs(v - (*this)[y][(x - 1 + L) % L]);
            return dy1 * dy1 + dy2 * dy2 + dx1 * dx1 + dx2 * dx2;
        }();
        if (change) {
            (*this)[y][x] = v;
            _score += inc - dec;
        }
        return inc - dec;
    }

    Temperature operator=(const Temperature& temp) {
        for (int y = 0; y < L; y++) {
            for (int x = 0; x < L; x++) {
                (*this)[y][x] = temp[y][x];
            }
        }
        _score = temp._score;
        return *this;
    }

    void smooth(const vector<vector<bool>> &protect) {
        for (int u = 0; u < 10; u++) {
            Temperature temp = *this;
            for (int y = 0; y < L; y++) {
                for (int x = 0; x < L; x++) {
                    if (protect[y][x]) {
                        continue;
                    }
                    int sum = 0;
                    for (auto [dy, dx] : vector<pair<int, int>> {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}) {
                        sum += (*this)[(y + dy + L) % L][(x + dx + L) % L];
                    }
                    temp[y][x] = sum / 4;
                }
            }
            *this = temp;
        }
    }
};

struct Judge {
    void set_temperature(const Temperature &temp) {
        for (const vector<int>& row : temp) {
            for (int i = 0; i < row.size(); i++) {
                cout << row[i] << (i + 1 == row.size() ? '\n' : ' ');
            }
        }
        cout.flush();
    }

    int query(int i, int y, int x) {
        cout << i << ' ' << y << ' ' << x << endl;
        int v;
        cin >> v;
        if (v == -1) {
            cerr << "something went wrong. i=" << i << " y=" << y << " x=" << x << endl;
            exit(1);
        }
        return v;
    }

    void answer(const vector<int>& estimate) {
        cout << "-1 -1 -1" << endl;
        for (int e : estimate) {
            cout << e << endl;
        }
    }
} judge;

struct Solver {
    const vector<Pos> landing_pos;
    int allow_error;
    int query_cnt;
    vector<int> use_temp;
    vector<pair<int, int>> neighborhood;

    Solver(vector<Pos> landing_pos) : landing_pos(landing_pos) {
        int s = (int)sqrt(S);
        auto qs = [&](int n) {
            return 10000 / N / n;
        };
        auto [a, q, n] = [&]() -> tuple<int, int, int> {
            // TODO: 近傍の個数 調整
            switch (s) {
                case  1: return {10, 1, 2};
                case  2: return {10, 4, 2};
                case  3: return {20, 6, 3};
                case  4: return {20, 8, 3};
                case  5: return {50, 5, 4};
                case  6: return {50, 7, 4};
                case  7: return {75, 10, 5};
                case  8: return {100, 5, 5};
                case  9: return {100, 10, 5};
                case 10: return {150, 10, 4}; // ?
                case 11: return {150, 10, 4};
                case 12: return {200, 10, 7};
                case 13: return {250, 9, 7};
                case 14: return {250, 10, 7};
                case 15: return {250, 11, 7};
                case 16: return {250, 12, 7};
                case 17: return {500, qs(11), 11};
                case 18: return {500, qs(11), 11};
                case 19: return {500, qs(11), 11};
                case 20: return {500, qs(11), 11};
                case 21: return {500, qs(11), 11};
                case 22: return {500, qs(11), 11};
                case 23: return {500, qs(11), 11};
                case 24: return {500, qs(11), 11};
                case 25: return {500, qs(11), 11};
                case 26: return {500, qs(11), 11};
                case 27: return {500, qs(11), 11};
                case 28: return {500, qs(11), 11};
                case 29: return {500, qs(11), 11};
                case 30: return {500, qs(11), 11};
            }
            cout << "? " << s << endl;
            exit(1);
        }();
        allow_error = a;
        query_cnt = q;
        int neighbor_size = n;
        generate_neighborhood(neighbor_size);
    }

    void generate_neighborhood(int n) {
        // 隣接セルがある: 10
        // 1-隣接セルがある: 1
        int now_score = 9999999;
        while (timer.get_time() < 1.5) {
            set<pair<int, int>> pivs;
            while ((int)pivs.size() < n) {
                int y, x;
                if (L < 30) {
                    y = rand() % (L / 2 * 2 + 1) - L / 2;
                    x = rand() % (L / 2 * 2 + 1) - L / 2;
                } else {
                    y = rand() % (L / 3 * 2 + 1) - L / 3;
                    x = rand() % (L / 3 * 2 + 1) - L / 3;
                }
                pivs.insert({y, x});
            }
            vector<vector<bool>> used(L, vector<bool>(L, false));
            for (const Pos& p : landing_pos) {
                for (auto [dy, dx] : pivs) {
                    used[(p.y + dy + L) % L][(p.x + dx + L) % L] = true;
                }
            }
            int score = 0;
            for (auto [dy, dx] : pivs) {
                // score += 10 * (dy * dy + dx * dx);
                score += 100 * (10 + abs(dy) + abs(dx));
            }
            for (int y = 0; y < L; y++) {
                for (int x = 0; x < L; x++) {
                    if (!used[y][x]) continue;
                    for (auto [dy, dx] : vector<pair<int, int>> {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}) {
                        if (used[(y + dy + L) % L][(x + dx + L) % L]) {
                            score += 1000;   
                        }
                    }
                    for (auto [dy, dx] : vector<pair<int, int>> {{2, 0}, {0, 2}, {-2, 0}, {0, -2}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}}) {
                        if (used[(y + dy + L) % L][(x + dx + L) % L]) {
                            score += 100;   
                        }
                    }
                    for (auto [dy, dx] : vector<pair<int, int>> {{3, 0}, {0, 3}, {-3, 0}, {0, -3}, {2, 1}, {-2, 1}, {2, -1}, {-2, -1}, {1, 2}, {-1, 2}, {1, -2}, {-1, -2}}) {
                        if (used[(y + dy + L) % L][(x + dx + L) % L]) {
                            score += 10;   
                        }
                    }
                    for (auto [dy, dx] : vector<pair<int, int>> {{4, 0}, {0, 4}, {-4, 0}, {0, -4}, {3, 1}, {-3, 1}, {3, -1}, {-3, -1}, {1, 3}, {-1, 3}, {1, -3}, {-1, -3}, {2, 2}, {-2, 2}, {2, -2}, {-2, -2}}) {
                        if (used[(y + dy + L) % L][(x + dx + L) % L]) {
                            score += 1;   
                        }
                    }
                }
            }
            if (score < now_score) {
                now_score = score;
                neighborhood.clear();
                for (auto [dy, dx] : pivs) {
                    neighborhood.push_back({dy, dx});
                }
            }
        }
    }


    Temperature create_temperature() {
        auto is_unique = [&](const Temperature& temp) -> bool {
            set<vector<int>> s;
            for (const Pos& p : landing_pos) {
                vector<int> v;
                for (auto [dy, dx] : neighborhood) {
                    v.push_back(temp[(p.y + dy + L) % L][(p.x + dx + L) % L]);
                }
                if (s.count(v)) {
                    return false;
                }
                s.insert(v);
            }
            return true;
        };

        Temperature temp(L);
        vector<int> use_temp;
        for (int v = 0; v <= 1000; v += 2 * allow_error) {
            use_temp.push_back(v);
        }
        vector<vector<bool>> protect(L, vector<bool>(L, false));
        for (const Pos& p : landing_pos) {
            for (auto [dy, dx] : neighborhood) {
                protect[(p.y + dy + L) % L][(p.x + dx + L) % L] = true;
            }
        }

        auto generate_random = [&]() -> Temperature {
            while (true) {
                Temperature temp(L);
                for (int y = 0; y < L; y++) {
                    for (int x = 0; x < L; x++) {
                        temp[y][x] = 500;
                    }
                }
                for (const Pos& p : landing_pos) {
                    for (auto [dy, dx] : neighborhood) {
                        int v = use_temp[rand() % use_temp.size()];
                        int y = (p.y + dy + L) % L;
                        int x = (p.x + dx + L) % L;
                        temp[y][x] = v;
                    }
                }

                if (is_unique(temp)) return temp;
            }
            exit(1);
        };

        // optional<Temperature> best_temp = nullopt;
        // while (timer.get_time() < 2.9) {
        //     Temperature temp = generate_random();
        //     if (!best_temp || temp.score() < best_temp.value().score()) {
        //         best_temp = temp;
        //     }
        // }

        Temperature best_temp = generate_random();

        vector<Pos> pro;
        for (int y = 0; y < L; y++) {
            for (int x = 0; x < L; x++) {
                if (protect[y][x]) {
                    pro.push_back({y, x});
                }
            }
        }

        while (timer.get_time() < 3.7) {
            int i = rand() % pro.size();
            int r = rand() % (use_temp.size() - 1);
            int p = best_temp[pro[i].y][pro[i].x];
            int v = (use_temp[r] == p ? use_temp[r + 1] : use_temp[r]);
            if (best_temp.change(pro[i].y, pro[i].x, v, false) <= 0) {
                best_temp.change(pro[i].y, pro[i].x, v, true);
                if (!is_unique(best_temp)) {
                    best_temp.change(pro[i].y, pro[i].x, p, true);
                }
            }
        }
        
        best_temp.smooth(protect);
        return best_temp;
    }

    vector<int> predict(const Temperature& temp) {
        auto query = [&](int i, int y, int x) -> int {
            int s = 0;
            for (int u = 0; u < query_cnt; u++) {
                s += judge.query(i, y, x);
            }
            return s / query_cnt;
        };

        vector<int> estimate(N);
        for (int i_in = 0; i_in < N; i_in++) {
            vector<int> measured_vals;
            for (const auto [dy, dx] : neighborhood) {
                measured_vals.push_back(query(i_in, dy, dx));
            }

            auto answer = [&]() -> int {
                vector<int> near;
                for (int i = 0; i < N; i++) {
                    bool add = true;
                    for (int j = 0; j < neighborhood.size(); j++) {
                        auto [dy, dx] = neighborhood[j];
                        int y = (landing_pos[i].y + dy + L) % L;
                        int x = (landing_pos[i].x + dx + L) % L;
                        if (abs(temp[y][x] - measured_vals[j]) > allow_error) {
                            add = false;
                            break;
                        }
                    }
                    if (add) {
                        near.push_back(i);
                    }
                }

                if (near.size() == 1) return near[0];

                int min_dist = 9999999;
                int res = 0;
                for (int i_out = 0; i_out < N; i_out++) {
                    int dist = 0;
                    for (int i = 0; i < neighborhood.size(); i++) {
                        auto [dy, dx] = neighborhood[i];
                        int y = (landing_pos[i_out].y + dy + L) % L;
                        int x = (landing_pos[i_out].x + dx + L) % L;
                        dist += abs(temp[y][x] - measured_vals[i]);
                    }
                    if (dist < min_dist) {
                        min_dist = dist;
                        res = i_out;
                    }
                }
                return res;
            };
            estimate[i_in] = answer();
        }

        return estimate;
    }



    void solve() {
        const Temperature temp = create_temperature();
        judge.set_temperature(temp);


        vector<vector<bool>> protect(L, vector<bool>(L, false));
        for (const Pos& p : landing_pos) {
            for (auto [dy, dx] : neighborhood) {
                protect[(p.y + dy + L) % L][(p.x + dx + L) % L] = true;
            }
        }
        for (auto &row : protect) {
            cout << "# ";
            for (int i = 0; i < row.size(); i++) {
                cout << (row[i] ? 'x' : '.');
            }
            cout << endl;
        }


        const vector<int> estimate = predict(temp);
        judge.answer(estimate);
    }
};


int main() {
    cin >> L >> N >> S;
    vector<Pos> landing_pos(N);
    for (int i = 0; i < N; i++) {
        int y, x;
        cin >> landing_pos[i].y >> landing_pos[i].x;
    }

    Solver solver(landing_pos);
    solver.solve();
}