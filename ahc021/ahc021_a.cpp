#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define SZ(x) ((int)(x).size())
template<class T> bool chmin(T &a, const T &b) {if(b<a){ a=b; return 1;} return 0;}


const int INF = 1 << 28;
// const vector<pair<int, int>> dxy = {{-1, -1}, {-1, 0}, {0, -1}, {0, 1}, {1, 0}, {1, 1}};
const vector<pair<int, int>> dxy = {{0, -1}, {0, 1}, {-1, -1}, {-1, 0}, {1, 0}, {1, 1}};

const int N = 30;

bool inc(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y <= x;
}

void my_swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

struct Timer {
    time_t start;
    Timer() { start = clock(); }
    double now() { return (double)(clock() - start) / CLOCKS_PER_SEC; }
} timer;

using Pyramid = array<array<int, N>, N>;

struct Preprocessing {
    // dist[x1][y1][x2][y2] := (x1, y1) から (x2, y2) までの最短距離
    array<array<Pyramid, N>, N> dist;
    Preprocessing() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j <= i; j++) {
                for (int k = 0; k < N; k++) {
                    for (int l = 0; l < N; l++) {
                        dist[i][j][k][l] = INF;
                    }
                }
                deque<pair<int, int>> que;
                que.push_back({i, j});
                dist[i][j][i][j] = 0;
                while (!que.empty()) {
                    auto [x, y] = que.front(); que.pop_front();
                    for (auto [dx, dy] : dxy) {
                        int nx = x + dx, ny = y + dy;
                        if (!inc(nx, ny)) continue;
                        if (dist[i][j][nx][ny] != INF) continue;
                        dist[i][j][nx][ny] = dist[i][j][x][y] + 1;
                        que.push_back({nx, ny});
                    }
                }
            }
        }
    }

    int get_dist(int x1, int y1, int x2, int y2) {
        return dist[x1][y1][x2][y2];
    }
} Pre;

struct op {
    int x, y, nx, ny;
};

struct State {
    Pyramid pyramid;
    vector<op> oper;

    State(Pyramid &input) {
        for (int x = 0; x < N; x++) {
            for (int y = 0; y <= x; y++) {
                pyramid[x][y] = input[x][y];
            }
        }
    }

    void apply(const op& o) {
        my_swap(pyramid[o.x][o.y], pyramid[o.nx][o.ny]);
        oper.push_back(o);
    }

    void output() {
        if (SZ(oper) > 10000) {
            vector<op> tmp;
            for (int i = 0; i < SZ(oper); i += 10000) {
                tmp.push_back(oper[i]);
            }
            oper = tmp;
        }
        cout << SZ(oper) << "\n";
        for (auto [x, y, nx, ny] : oper) {
            cout << x << " " << y << " " << nx << " " << ny << "\n";
        }
    }
};


struct Solver {
    Pyramid input;

    void init() {
        for (int x = 0; x < N; x++) {
            for (int y = 0; y <= x; y++) {
                cin >> input[x][y];
            }
        }
    }

    State to_goal(const Pyramid& goal) {
        State state(input);    
        // goal の一番上から
        for (int gx = 0; gx < N; gx++) {
            for (int gy = 0; gy <= gx; gy++) {
                // goal[gx][gy] のボールがある座標を state から探す
                auto p = [&]() {
                    for (int x = 0; x < N; x++) {
                        for (int y = 0; y <= x; y++) {
                            if (state.pyramid[x][y] == goal[gx][gy]) {
                                return make_pair(x, y);
                            }
                        }
                    }
                    exit(1);
                }();
                int sx = p.first, sy = p.second;
                // sx, sy を gx, gyに移動
                while (!(sx == gx && sy == gy)) {
                    // dxy の近傍のうち、goal に近い座標を探す
                    auto [dx, dy] = [&]() {
                        int rx, ry, d = INF;
                        for (auto [dx, dy] : dxy) {
                            int nx = sx + dx, ny = sy + dy;
                            if (!inc(nx, ny)) continue;
                            if (chmin(d, abs(nx - gx) + abs(ny - gy))) {
                                rx = dx, ry = dy;
                            }
                        }
                        return make_pair(rx, ry);
                    }();
                    int nx = sx + dx, ny = sy + dy;
                    state.apply({sx, sy, nx, ny});
                    sx = nx, sy = ny;
                }
            }
        }
        return state;
    }

    State solve() {
        // pos[col] -> inputでの座標
        vector<pair<int, int>> pos(N * (N + 1) / 2);
        for (int x = 0; x < N; x++) {
            for (int y = 0; y <= x; y++) {
                pos[input[x][y]] = {x, y};
            }
        }
        Pyramid goal = input;
        while (true) {
            bool update = false;
            for (int x = 0; x < N - 1; x++) {
                for (int y = 0; y <= x; y++) {
                    int top = goal[x][y];
                    int left = goal[x + 1][y];
                    int right = goal[x + 1][y + 1];
                    if (top > left || top > right) {
                        if (left < right) {
                            my_swap(goal[x][y], goal[x + 1][y]);
                        } else {
                            my_swap(goal[x][y], goal[x + 1][y + 1]);
                        }
                        update = true;
                    }
                }
            }
            if (!update) break;
        } 

        State res = to_goal(goal);

        // 同じ行は好きに入れ替えてよい(前提)
        // 疑似解
        auto op_count = [&](const Pyramid& g) {
            int res = 0;
            for (int x = 0; x < N; x++) {
                for (int y = 0; y <= x; y++) {
                    auto [nx, ny] = pos[g[x][y]];
                    res += Pre.get_dist(x, y, nx, ny);
                }
            }
            return res;
        };

        vector<op> ops;
        auto generate_swap = [&](Pyramid& g) {
            if (SZ(ops) != 0) ops.clear();
            int loop = 1;
            auto get = [&](int x, int y, int nil) {
                if (!inc(x, y)) return nil;
                return g[x][y];
            };
            auto child = [&](int x, int y) {
                return make_pair(get(x + 1, y, INF), get(x + 1, y + 1, INF));
            };           
            auto parent = [&](int x, int y) {
                return make_pair(get(x - 1, y - 1, -INF), get(x - 1, y, -INF));
            };

            while (loop) {
                int x1 = rand() % N;
                int y1 = rand() % (x1 + 1);
                int x2 = rand() % N;
                // int x2 = x1;
                int y2 = rand() % (x2 + 1);
                auto [p1a, p1b] = parent(x1, y1);
                auto [c1a, c1b] = child(x1, y1);
                auto [p2a, p2b] = parent(x2, y2);
                auto [c2a, c2b] = child(x2, y2);
                int g1 = g[x1][y1], g2 = g[x2][y2];
                if (!(g2 < c1a && g2 < c1b && p1a < g2 && p1b < g2)) continue;
                if (!(g1 < c2a && g1 < c2b && p2a < g1 && p2b < g1)) continue;
                int bef_dist = Pre.get_dist(pos[g1].first, pos[g1].second, x1, y1)
                    + Pre.get_dist(pos[g2].first, pos[g2].second, x2, y2);
                int aft_dist = Pre.get_dist(pos[g2].first, pos[g2].second, x1, y1)
                    + Pre.get_dist(pos[g1].first, pos[g1].second, x2, y2);
                if (aft_dist > bef_dist) continue;
                loop--;
                ops.push_back({x1, y1, x2, y2});
                my_swap(g[x1][y1], g[x2][y2]);
            }
        };
        auto fix_swap = [&](Pyramid& g) {
            reverse(ops.begin(), ops.end());
            for (auto [x, y, nx, ny] : ops) {
                my_swap(g[x][y], g[nx][ny]);
            }
            ops.clear();
        };

        auto [solve1_lim, solve2_lim] = make_pair(0.6, 1.8);
        // auto [solve1_lim, solve2_lim] = make_pair(0.6, 20.0);


        int cnt1 = 0;
        int res_op_count = op_count(goal);
        while (timer.now() < solve1_lim) {
            cnt1++;
            vector<op> sw;
            generate_swap(goal);
            int tmp = op_count(goal);
            if (tmp < res_op_count) {
                res_op_count = tmp;
                res = to_goal(goal);
            } else {
                fix_swap(goal);
            }
        }

        // 正しい解
        int cnt2 = 0;
        while (timer.now() < solve2_lim) {
            cnt2++;
            generate_swap(goal);
            State tmp = to_goal(goal);
            if (SZ(tmp.oper) < SZ(res.oper)) {
                res = tmp;
            } else {
                fix_swap(goal);
            }
        }

        cerr << cnt1 << " " << cnt2 << endl;

        // for (int x = 0; x < N; x++) {
        //     for (int y = 0; y <= x; y++) {
        //         cout << goal[x][y] << " ";
        //     }
        //     cout << endl;
        // }
        
        return res;

    }
};


int main() {

    Solver solver;
    solver.init();

    State ans = solver.solve();

    ans.output();
}