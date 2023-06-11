#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define SZ(x) ((int)(x).size())

using PP = array<int, 100>;

struct Timer {
    time_t start;
    Timer() { start = clock(); }
    double now() { return (double)(clock() - start) / CLOCKS_PER_SEC; }
} timer;

struct UnionFind {
    int n, cnt;
    vector<int> parent;
    UnionFind() : n(0), cnt(0) {}
    UnionFind(int n) : n(n), cnt(n), parent(n, -1) {}

    int merge(int a, int b) {
        assert(0 <= a && a < n && 0 <= b && b < n);
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-parent[x] < -parent[y]) swap(x, y);
        parent[x] += parent[y];
        parent[y] = x;
        cnt--;
        return x;
    } 

    int leader(int a) {
        assert(0 <= a && a < n);
        if (parent[a] < 0) return a;
        return parent[a] = leader(parent[a]);
    }

    bool same(int a, int b) {
        assert(0 <= a && a < n && 0 <= b && b < n);
        return leader(a) == leader(b);
    }

    int size(int a) {
        assert(0 <= a && a < n);
        return -parent[leader(a)];
    }

    int count() { return cnt; }

    vector<vector<int>> groups() {
        vector<int> leader_buf(n), group_size(n);
        for (int i = 0; i < n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        vector<vector<int>> result(n);
        for (int i = 0; i < n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(
            remove_if(result.begin(), result.end(),
                      [&](const vector<int> &v) { return v.empty(); }),
            result.end());
        return result;
    }
};

int N, M, K;

struct Point {
    int x, y;
};
Point new_point(int x, int y) {
    Point p;
    p.x = x; p.y = y;
    return p;
}

ll dist(Point a, Point b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

struct Edge {
    int idx;
    int to;
    ll weight;
};
Edge new_edge(int _idx, int _to, ll _weight) {
    Edge e;
    e.idx = _idx; e.to = _to; e.weight = _weight;
    return e;
}

struct State {
    PP P;
    vector<int> B;
    State() {
        for (int i = 0; i < N; i++) P[i] = 0;
        B.resize(M, 0);
    }

    void output() {
        for (int i = 0; i < SZ(P); i++) {
            cout << P[i] << (i == SZ(P) - 1 ? "\n" : " ");
        }
        for (int i = 0; i < SZ(B); i++) {
            cout << B[i] << (i == SZ(B) - 1 ? "\n" : " ");
        }
    }
};




struct Solver {
    vector<Point> station;
    vector<vector<Edge>> G;
    vector<vector<Edge>> min_G;
    vector<tuple<int, int, int, int>> edges;
    vector<Point> people;

    ll score(const State& s) {
        // s についての0からの連結成分を探す
        UnionFind uf(N);
        ll S = 0;
        vector<bool> ch(N, false);

        for (int i = 0; i < SZ(s.B); i++) if (s.B[i] == 1) {
            auto [idx, u, v, w] = edges[i];
            uf.merge(u, v);
            S += w;
        }
        for (int i = 0; i < SZ(s.P); i++) if (uf.same(0, i)) {
            // 頂点 i からPower P[i] で放出している
            S += s.P[i] * s.P[i];
        }
        // 全ての人に行ける！！！と仮定 そうじゃないのは投げないで
        return (double)(1e6) * ((double)(1) + (double)(1e8)) / ((double)(S) + double(1e7));
    }

    void init() {
        cin >> N >> M >> K;
        for (int i = 0; i < N; i++) {
            int x, y; cin >> x >> y;
            station.push_back(new_point(x, y));
        }
        G.resize(N);
        for (int i = 0; i < M; i++) {
            int u, v; ll w; cin >> u >> v >> w;
            u--; v--;
            G[u].push_back(new_edge(i, v, w));
            G[v].push_back(new_edge(i, u, w));
            edges.push_back(tie(i, u, v, w));
        }
        for (int i = 0; i < K; i++) {
            int a, b; cin >> a >> b;
            people.push_back(new_point(a, b));
        }

        // build min_G
        min_G.resize(N);
        UnionFind uf(N);
        sort(edges.begin(), edges.end(), [&](const auto &a, const auto &b) {
            return get<3>(a) < get<3>(b);
        });
        for (auto [i, u, v, w] : edges) {
            if (!uf.same(u, v)) {
                uf.merge(u, v);
                min_G[u].push_back(new_edge(i, v, w));
                min_G[v].push_back(new_edge(i, u, w));
            }
        }

        sort(edges.begin(), edges.end(), [&](const auto &a, const auto &b) {
            return get<0>(a) < get<0>(b);
        });
    }

    State generate(bool random = false) {
        State result;
        // .B 構築
        for (auto es : min_G) for (auto e : es) {
            result.B[e.idx] = 1;
        }

        // P を構築 -> 最大 のは確定
        // 確定すると、それに対して考えなくてよい人が出てくる
        // -> 除外して構築しなおし

        set<int> ng;
        for (int i = 0; i < N; i++) ng.insert(i);
        vector<bool> pok(K, false);

        while (!ng.empty()) {
            vector<int> P(N, 0);
            for (int k = 0; k < K; k++) if (!pok[k]) {
                ll min_dist = 1e18;
                int min_idx = -1;
                for (auto n : ng) {
                    ll d = dist(people[k], station[n]);
                    if (d < min_dist) {
                        min_dist = d;
                        min_idx = n;
                    }                    
                }
                ll update = sqrt(min_dist) + 1;
                if (P[min_idx] < update) P[min_idx] = update;
            }
            
            // Pが最大の値は確定
            // ランダムに確定 -> ... 
            ll max_p = -1;
            int max_idx = -1;
            if (!random) {
                for (auto n : ng) {
                    if (max_p < P[n]) {
                        max_p = P[n];
                        max_idx = n;
                    }
                }
                result.P[max_idx] = max_p;
                ng.erase(max_idx);
            } else {
                // ng からランダムに一つ選ぶ
                int idx = rand() % SZ(ng);
                auto it = ng.begin();
                for (int i = 0; i < idx; i++) it++;
                max_idx = *it;
                max_p = P[max_idx];
                result.P[max_idx] = max_p;
                ng.erase(max_idx);
            }

            // pok を更新
            // max_idx から max_p 以内の人は確定
            for (int k = 0; k < K; k++) if (!pok[k]) {
                if (dist(people[k], station[max_idx]) <= max_p * max_p) {
                    pok[k] = true;
                }
            }
        }

        // result.output();


        // 一つを0にする -> ごにょごにょ...の山登り？o
        // それぞれの頂点について、何回かぶっているかを数える
        // 何かを一つ削ると、その値が変わる　0になってしまった頂点は他のところで回収
        // 先に、駅iに包まれている頂点を計算しておく

        // 更新は大したことなく行ける？
        // 距離 の計算を、すでに決定しているところとの差分でやる
        // が、大した数まわらなさそう

        vector<vector<int>> in(N);
        vector<int> pin(K, 0);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < K; j++) {
                if (dist(station[i], people[j]) <= result.P[i] * result.P[i]) {
                    in[i].push_back(j);
                    pin[j]++;
                }
            }
        }

       

        while (timer.now() < 1.95) {
            State tmp = result;

            // int erase_cnt = 1 + rand() % 3; // 1~3
            /*
total: 159946487
max: (1800855, '0069')
ave: 1599464.87
min: (1501202, '0075')
            */
        //    int erase_cnt = 1 + rand() % 4;
        /*
total: 160025894
max: (1787686, '0069')
ave: 1600258.94
min: (1489184, '0075')
        */
            // int erase_cnt = 1 + rand() % 5;
            /*
total: 160422232
max: (1799962, '0019')
ave: 1604222.32
min: (1495298, '0075')            
            */
        //    int erase_cnt = 1 + rand() % 6;
        /*
total: 160307438
max: (1779295, '0069')
ave: 1603074.38
min: (1500411, '0075')
*/
            // int erase_cnt = 1 + rand() % 10;
            /*
total: 160591991
max: (1786659, '0069')
ave: 1605919.91
min: (1501535, '0075')
            */

            int erase_cnt = 1 + rand() % 20;
/*
total: 160621456
max: (1780835, '0069')
ave: 1606214.56
min: (1489303, '0075')
kk*/

            // int erase_cnt = 1 + rand() % 25;
            /*
total: 160784675
max: (1787296, '0019')
ave: 1607846.75
min: (1502932, '0075')

            // int erase_cnt = 1 + rand() % 30;
            /*
total: 160650348
max: (1864423, '0069')
ave: 1606503.48
min: (1502363, '0067')  
            */

            // int erase_cnt = 1 + rand() % 40;
/*
total: 158917068
max: (1777644, '0069')
ave: 1589170.68
min: (0, '0090')
*/

            set<int> erase_idxes;
            for (int i = 0; i < erase_cnt; i++) {
                int erase_idx = rand() % N; // station
                erase_idxes.insert(erase_idx);
            }

            ll diff = 0;
            //  = -tmp.P[erase_idx] * tmp.P[erase_idx];
            for (auto idx : erase_idxes) {
                diff -= tmp.P[idx] * tmp.P[idx];
                tmp.P[idx] = 0;
            }

            vector<vector<int>> tmp_in = in;
            vector<int> tmp_pin = pin;
            bool ok = true;


            vector<int> erase_peoples;
            for (auto erase_idx : erase_idxes) {
                for (auto k : in[erase_idx]) {
                    tmp_pin[k]--;
                    if (tmp_pin[k] == 0) {
                        erase_peoples.push_back(k);
                    }
                }
                tmp_in[erase_idx].clear();
            }

            shuffle(erase_peoples.begin(), erase_peoples.end(), mt19937(0));
            for (auto k : erase_peoples) {
                if (tmp_pin[k] == 0) {
                    // people[k] := どこかの駅に包まれていない
                    // 全ての頂点のうち、一番消すコストが小さいやつを選ぶ
                    ll min_cost = 1e18;
                    int min_idx = -1;
                    for (int i = 0; i < N; i++) {
                        ll cost = dist(station[i], people[k]) - tmp.P[i] * tmp.P[i];
                        if (cost < min_cost) {
                            min_cost = cost;
                            min_idx = i;
                        }
                    }
                    diff += min_cost;
                    if (diff > 0) { ok = false; break; }
                    for (int j = 0; j < K; j++) {
                        if (dist(station[min_idx], people[j]) <= tmp.P[min_idx] * tmp.P[min_idx]) {
                            tmp_pin[j]--;
                        }
                    }
                    tmp.P[min_idx] = sqrt(dist(station[min_idx], people[k])) + 1;
                    tmp_in[min_idx].clear();
                    // min_idx から距離が min_cost 以内の人を追加
                    for (int j = 0; j < K; j++) {
                        if (dist(station[min_idx], people[j]) <= tmp.P[min_idx] * tmp.P[min_idx]) {
                            tmp_pin[j]++;
                            tmp_in[min_idx].push_back(j);
                        }
                    }
                }
            }

            if (ok) {
                result = tmp;
                in = tmp_in;
                pin = tmp_pin;
                // result.output();     
            }
        }

        erase_edge(result);
        return result;
    }

    State solve() {
        State res = generate();

        return res;
    }


    void erase_edge(State &s) {
        // s.P[i] が 0 かつそれが葉の時、そこから出る辺は不要
        set<int> zeroidx;
        for (int i = 1; i < N; i++) if (s.P[i] == 0) {
            zeroidx.insert(i);
        }

        vector<int> in(N, 0);
        for (int i = 0; i < N; i++) in[i] = SZ(min_G[i]);
        while (true) {
            bool update = false;
            for (auto i : zeroidx) if (in[i] == 1) {
                for (auto e : min_G[i]) {
                    in[e.to]--;
                    in[i]--;
                    s.B[e.idx] = 0;
                }
                update = true;
            }
            if (!update) return;
        }
    }
};



int main() {
    Solver solver;
    solver.init();
    State ans = solver.solve();
    ans.output();

    return 0;
}


/*
total: 136921583
max: (1440882, '0069')
ave: 1369215.83
min: (1316055, '0092')

*/