#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#pragma region header
#include <bits/stdc++.h>
using namespace std;
// #include <atcoder/all>
// using namespace atcoder;

/* alias */
using ull = unsigned long long;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<long long>;
using vd = vector<double>;
using vs = vector<string>;
using vb = vector<bool>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<ll, ll>>;
using vvi = vector<vector<int>>;
using vvll = vector<vector<long long>>;
using vvd = vector<vector<double>>;
using vvs = vector<vector<string>>;
using vvb = vector<vector<bool>>;
template<typename T> using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

/* define */
#define MOD 998244353
// #define MOD 1000000007
#define INF (1LL << 60)
#define inf (1 << 28)
#define elif else if
#define pb push_back
#define pf push_front
#define fi first
#define se second
#define all(obj) (obj).begin(), (obj).end()
#define YESNO(bool) cout << (bool ? "YES\n" : "NO\n")
#define YesNo(bool) cout << (bool ? "Yes\n" : "No\n")
#define yesno(bool) cout << (bool ? "yes\n" : "no\n")
template<class T> bool chmax(T &a, const T &b) {if(a<b){ a=b; return 1;} return 0;}
template<class T> bool chmin(T &a, const T &b) {if(b<a){ a=b; return 1;} return 0;}
#define debug(x) cerr << #x << ":" << x << "\n";

/* REP macro */
#define reps(i, a, n) for(int i = (a); i < (n); i++)
#define rep(i, n) reps(i, 0, (n))
#define rrep(i, n) reps(i, 1, (n + 1))
#define repd(i, n) for(int i = (n - 1); i >= 0; i--)
#define rrepd(i, n) for(int i = (n); i >= 1; i--)
#define fore(i, a) for(auto &i: a)

/* vector */
template<class T> T vmax(vector<T> &array){ T ret = array[0]; for(T a: array) chmax(ret, a); return ret; }
template<class T> T vmin(vector<T> &array){ T ret = array[0]; for(T a: array) chmin(ret, a); return ret; }
template<class T> T sum(vector<T> &array){ T ret = 0; for(T a:array) ret += a; return ret; }
template<class T> void list_set(vector<T> &array){ sort(all(array)); array.erase(unique(all(array)),array.end()); }
template<class T> T bisect_left(vector<T> &array, T key){ return lower_bound(all(array),key) - array.begin(); }
template<class T> T bisect_right(vector<T> &array, T key){ return upper_bound(all(array),key) - array.begin(); }

/* string */
ll string_to_ll(string n){ ll ret = 0, k = 1; while(n.length() > 0){ ret += k * (n.back() - '0'); n.pop_back(); k *= 10; } return ret; }
string ll_to_string(ll n){ string ret = ""; while(n > 0){ ret.pb((n % 10) + '0'); n /= 10; } reverse(all(ret)); return ret; }

struct popopo{ popopo(){ cin.tie(0); ios::sync_with_stdio(0); cout << fixed << setprecision(15); }; } popopoppo;

// n = 1,...,N に対して、n % A < B を満たすものの数 
ll Count_of_n_mod_A_less_than_B(ll N, ll A, ll B){ return N / A * min(A, B) + min(N % A, B - 1); }


/* IN/OUT */
int scan() { return getchar(); }
void scan(int &a) { cin >> a; }
void scan(long long &a) { cin >> a; }
void scan(char &a) { cin >> a; }
void scan(double &a) { cin >> a; }
void scan(string &a) { cin >> a; }
template <class T, class S> void scan(pair<T, S> &p) { scan(p.first), scan(p.second); }
template <class T> void scan(vector<T> &);
template <class T> void scan(vector<T> &a) { for(auto &i : a) scan(i); }

void IN(){}
template<class Head, class... Tail> void IN(Head& head, Tail &...tail){ scan(head); IN(tail...); }

#define INT(...) int __VA_ARGS__; IN(__VA_ARGS__)
#define LL(...) ll __VA_ARGS__; IN(__VA_ARGS__)
#define STR(...) string __VA_ARGS__; IN(__VA_ARGS__)
#define VEC(type, name, size) vector<type> name(size); IN(name)
#define VECS(type, name, size) vector<type> name(size + 1); for(int i = 1; i <= size; i++) scan(name[i])

void OUT(){ cout << "\n"; }
template<class T> void output(T a){ cout << a; }
template<class T> void output(vector<T> v){ for(int i = 0; i < v.size(); i++) cout << v[i] << (i == v.size() - 1 ? "" : " "); }
template<class Head, class... Tail> void OUT(const Head &head, const Tail &...tail) { output(head); if(sizeof...(tail)) cout << " "; OUT(tail...); }

void FLASH(){ cout << endl; }
template<class Head, class... Tail> void FLASH(const Head  &head, const Tail &...tail) { output(head); if(sizeof...(tail)) cout << " "; FLASH(tail...); }

#pragma endregion header    

struct UnionFind {
    map<pair<int, int>, pair<int, int>> parent;
    map<pair<int, int>, int> sz;
    UnionFind() : parent(), sz() {}

    pair<int, int> find(pair<int, int> x) {
        if (parent.find(x) == parent.end()) {
            parent[x] = x;
            return x;
        } else if (parent[x] == x) {
            return x;
        } else {
            parent[x] = find(parent[x]);
            return parent[x];
        }
    }

    void merge (pair<int, int> x, pair<int, int> y) {
        x = find(x);
        y = find(y);
        if (sz[x] == 0) sz[x] = 1;
        if (sz[y] == 0) sz[y] = 1;
        if (sz[x] > sz[y]) swap(x, y);
        if (x != y) {
            parent[x] = y;
            sz[y] += sz[x];
        }
    }

    bool same (pii x, pii y) {
        return find(x) == find(y);
    }

    int size (pii x) {
        return sz.find(find(x)) == sz.end() ? 1 : sz[find(x)];
    }
};


int _N, _K;
vs _C;
vi dx = {  0,  1,  0, -1};
vi dy = {  1,  0, -1,  0};
set<pair<int, int>> forcedConnectSet = {
    {15, 2}, {16, 2}, 
    {18, 3}, {19, 3}, {20, 3}, 
    {21, 4}, {22, 4}, {23, 4}, {24, 4}, 
    {24, 5}, {25, 5}, {26, 5}, {27, 5}, {28, 5},
};
const bool DEV = false;
random_device seed_gen;
mt19937 rnd(seed_gen());

vvi rndList = {
    {0, 1, 2, 3},
    {0, 1, 3, 2},
    {0, 2, 1, 3},
    {0, 2, 3, 1},
    {0, 3, 1, 2},
    {0, 3, 2, 1},
    {1, 0, 2, 3},
    {1, 0, 3, 2},
    {1, 2, 0, 3},
    {1, 2, 3, 0},
    {1, 3, 0, 2},
    {1, 3, 2, 0},
    {2, 0, 1, 3},
    {2, 0, 3, 1},
    {2, 1, 0, 3},
    {2, 1, 3, 0},
    {2, 3, 0, 1},
    {2, 3, 1, 0},
    {3, 0, 1, 2},
    {3, 0, 2, 1},
    {3, 1, 0, 2},
    {3, 1, 2, 0},
    {3, 2, 0, 1},
    {3, 2, 1, 0},
};


vi rnd4 () {
    return rndList[rnd() % 24];
}


struct Timer {
    clock_t st;
    double limit = 2.8;

    void start (double _limit) {
        limit = _limit;
        start();
    }
    void start () {
        st = clock();
    }

    bool end () {
        return (double(clock() - st) / CLOCKS_PER_SEC > limit);
    }

};
Timer timer;

bool boardIn(ll x) {
    return (0 <= x && x < _N);
}

bool boardIn(ll x, ll y) {
    return boardIn(x) && boardIn(y);
}

struct MoveAction {

    int bef_x, bef_y, aft_x, aft_y;

    MoveAction (int _bef_x, int _bef_y, int _aft_x, int _aft_y) : bef_x(_bef_x), bef_y(_bef_y), aft_x(_aft_x), aft_y(_aft_y) {}
    
    bool in () {
        return (boardIn(bef_x) && boardIn(bef_y) && boardIn(aft_x) && boardIn(aft_y));
    }

};

struct ConnectAction {

    int c1_x, c1_y, c2_x, c2_y;

    ConnectAction (int _c1_x, int _c1_y, int _c2_x, int _c2_y) : c1_x(_c1_x), c1_y(_c1_y), c2_x(_c2_x), c2_y(_c2_y) {}

    bool in () {
        return boardIn(c1_x) && boardIn(c1_y) && boardIn(c2_x) && boardIn(c2_y);
    }

};

struct Result {
    vector<MoveAction> move = {};
    vector<ConnectAction> connect = {};
    vs C = {}, block = {};    // C: 盤面 block: xは動かせない！ oは動かせる
    set<pii> ngList;
    UnionFind uf;
    Result () { 
        C = _C;
        string tmp = "";
        rep(i, _N) tmp += 'o';
        block = vs(_N, tmp);
    }
    Result (vector<MoveAction> _move, vector<ConnectAction> _connect) : move(_move), connect(_connect) {
        C = _C;
        string tmp = "";
        rep(i, _N) tmp += 'o';
        block = vs(_N, tmp);

        // ここではblockに値が入っている

        for (auto m: move) {
            swap(C[m.bef_x][m.bef_y], C[m.aft_x][m.aft_y]);
        }

        for (auto c: connect) {
            if (c.c1_x == c.c2_x) {
                for (int j = min(c.c1_y, c.c2_y); j <= max(c.c1_y, c.c2_y); j++) {
                    block[c.c1_x][j] = 'x';
                }
            } else {
                for (int i = min(c.c1_x, c.c2_x); i <= max(c.c1_x, c.c2_x); i++) {
                    block[i][c.c1_y] = 'x';
                }
            }
        }
    }

    // MoveAction m ができるかどうかの判定
    bool canAddMove (int x, int y, int nx, int ny) { return canAddMove(MoveAction(x, y, nx, ny)); }
    bool canAddMove (MoveAction m) {
        if (!m.in()) return false;
        if (abs(m.bef_x - m.aft_x) + abs(m.bef_y - m.aft_y) != 1) return false;
        if (block[m.bef_x][m.bef_y] != 'o') return false;
        if (block[m.aft_x][m.aft_y] != 'o') return false;
        if (C[m.bef_x][m.bef_y] == '0') return false;
        if (C[m.aft_x][m.aft_y] != '0') return false;
        if (move.size() + connect.size() >= _K * 100) return false;
        return true;
    }

    // MoveAction m を追加する
    bool addMove (int x, int y, int nx, int ny) { return addMove(MoveAction(x, y, nx, ny)); }
    bool addMove (MoveAction m) {
        if (!canAddMove(m)) return false;
        swap(C[m.bef_x][m.bef_y], C[m.aft_x][m.aft_y]);
        move.emplace_back(m);
        return true;
    }

    // (x, y) から i 方向に接続できるのがあるかの判定
    bool canAddConnect (int x, int y, int i) {
        if (!boardIn(x, y)) return false;
        if (C[x][y] == '0') return false;
        if (move.size() + connect.size() >= _K * 100) return false;
        int nx = x, ny = y;
        bool ret = false;
        while (true) {
            nx += dx[i]; ny += dy[i];
            if (!boardIn(nx, ny)) break;
            if (C[x][y] == C[nx][ny]) {
                ret = true;
                break;
            } elif (C[nx][ny] != '0' || block[nx][ny] != 'o') {
                break;
            }
        }

        if (ret) {
            for(auto c: connect) {
                if (c.c1_x == x && c.c1_y == y && c.c2_x == nx && c.c2_y == ny) {
                    return false;
                }
                if (c.c1_x == nx && c.c1_y == ny && c.c2_x == x && c.c2_y == y) {
                    return false;
                }
            }
            return true;
        }

        return false;
    }

    // (x, y) から i 方向への接続を追加する 接続先を返す
    pii addConnect (int x, int y, int i) {
        if (!canAddConnect(x, y, i)) return {-1, -1};
        int nx = x, ny = y;
        char c = C[x][y];
        block[x][y] = 'x';
        while (true) {
            nx += dx[i]; ny += dy[i];
            block[nx][ny] = 'x';
            if (C[nx][ny] == c) break;
        }
        connect.emplace_back(ConnectAction(x, y, nx, ny));
        uf.merge({x, y}, {nx, ny});
        return {nx, ny};
    }

    // (x, y) -> (nx, ny) を接続する
    bool addConnect (int x, int y, int nx, int ny) {
        if (C[x][y] == '0' || C[nx][ny] == '0') return false;
        if (move.size() + connect.size() >= _K * 100) return false;
        for(auto c: connect) {
            if (c.c1_x == x && c.c1_y == y && c.c2_x == nx && c.c2_y == ny) {
                return false;
            }
            if (c.c1_x == nx && c.c1_y == ny && c.c2_x == x && c.c2_y == y) {
                return false;
            }
        }

        if (x == nx) {
            for (int j = min(y, ny); j <= max(y, ny); j++) {
                block[x][j] = 'x';
            }
        } else {
            for (int i = min(x, nx); i <= max(x, nx); i++) {
                block[i][y] = 'x';
            }
        }
        connect.emplace_back(ConnectAction(x, y, nx, ny));
        uf.merge({x, y}, {nx, ny});
        return true;
    }

    // (x, y) から i 方向へ
    //     不要なものがあったらどかす
    //     近くに同じのがあったら近づける
    // などをして接続する 返り値は接続したもののリスト
    // 意図しない挙動をしていそうなので fix/autoAddConnect で修正 したつもりだが壊れている...
    vector<pii> autoAddConnect (int x, int y, int i) {
        vector<pii> ret = {};
        if (C[x][y] == '0') return ret;
        if (ngList.find({x, y}) != ngList.end()) return ret;
        vector<MoveAction> addMoveQueue = {}; // きちんと接続できてからmoveへ追加する これに追加するときはaddMoveを確認
        vs D = C;
        int nx = x, ny = y;
        char n = C[x][y];

        while (true) {
            nx += dx[i], ny += dy[i];
            bool bre = false;
            if (!boardIn(nx, ny)) break;

            // どかす
            if (D[nx][ny] != '0' && D[nx][ny] != D[x][y]) {
                for (auto d: {-1, 1, 0}) {
                    if (canAddMove(nx, ny, nx + dx[(i + d) % 4], ny + dy[(i + d) % 4])) {
                        addMoveQueue.emplace_back(MoveAction(nx, ny, nx + dx[(i + d) % 4], ny + dy[(i + d) % 4]));
                        swap(D[nx][ny], D[nx + dx[(i + d) % 4]][ny + dy[(i + d) % 4]]);
                        break;
                    }
                }
            }
            
            // 近づける
            if (D[nx][ny] == '0') {
                for (auto d: {-1, 1}) {
                    if (!boardIn(nx + dx[(i + d) % 4], ny + dy[(i + d) % 4])) continue;
                    if (D[nx + dx[(i+d) % 4]][ny + dy[(i+d) % 4]] == D[x][y]) {

                        addMoveQueue.emplace_back(MoveAction(nx + dx[(i+d) % 4], ny + dy[(i+d) % 4], nx, ny));
                        swap(D[nx][ny], D[nx + dx[(i+d) % 4]][ny + dy[(i+d) % 4]]);
                    }
                }
            }

            // 接続先が見つかったら接続する
            if (D[nx][ny] == D[x][y]) {
                if (ngList.find({nx, ny}) != ngList.end()) break;
                for (auto m: addMoveQueue) addMove(m);
                addMoveQueue.clear();
                addConnect(x, y, i);
                x = nx; y = ny;
                ret.emplace_back(pii(nx, ny));
            } elif ((D[nx][ny] != '0' && D[nx][ny] != n) || block[nx][ny] == 'x') {
                break;
            }

        }

        return ret;

    } 

    int score () {
        // UnionFind uf_score;
        // for (auto c: connect) {
        //     uf_score.merge({c.c1_x, c.c1_y}, {c.c2_x, c.c2_y});
        // }

        vector<pair<int, int>> computers;
        for (int i = 0; i < _N; i++) {
            for (int j = 0; j < _N; j++) {
                if (C[i][j] != '0') {
                    computers.emplace_back(i, j);
                }
            }
        }

        int score = 0;
        for (int i = 0; i < (int)computers.size(); i++) {
            for (int j = i+1; j < (int)computers.size(); j++) {
                auto c1 = computers[i];
                auto c2 = computers[j];
                if (uf.find(c1) == uf.find(c2)) {
                    score += (C[c1.first][c1.second] == C[c2.first][c2.second]) ? 1 : -1;
                }
            }
        }

        return score;
    }

    void out () {

        if (DEV) {

            rep (i, move.size()) {
                OUT(i);
                rep (j, i) {
                    auto m = move[j];
                    OUT(m.bef_x, m.bef_y, m.aft_x, m.aft_y);
                }
                OUT(0);
            }

            rep (i, connect.size()) {
                OUT(move.size());
                for (auto m: move) OUT(m.bef_x, m.bef_y, m.aft_x, m.aft_y);
                OUT(i);
                rep (j, i) {
                    auto c = connect[j];
                    OUT(c.c1_x, c.c1_y, c.c2_x, c.c2_y);
                }
            }

        } else {
            OUT(move.size());
            for(auto m: move) OUT(m.bef_x, m.bef_y, m.aft_x, m.aft_y);
            OUT(connect.size());
            for(auto c: connect) OUT(c.c1_x, c.c1_y, c.c2_x, c.c2_y);
        }
    }
};

struct Solver {

    int N, K;
    vs C;

    Solver (int n, int k, vs c) : N(n), K(k), C(c) {}

    void solve () {

        Result ans;
        int ans_score = ans.score();
        int cnt = 0;
        while (!timer.end()) {
            loop(ans, ans_score);
            cnt++;
        }
        debug(cnt);
        ans.out();
        debug(ans_score);
    }

    void maximizeF (Result &now, char F) {
        vvb vis(N, vb(N, false));
        int vis_cnt = 0;
        // 終了条件
        while (vis_cnt < 70) {
            int x = rnd() % N, y = rnd() % N;
            if (now.C[x][y] != F) continue;
            if (vis[x][y]) continue;

            deque<pii> que; que.pb({x, y});

            while (!que.empty()) {
                auto [x, y] = que.front(); que.pop_front();
                if (vis[x][y]) continue;
                // if (now.C[x][y] != F) continue;
                vis[x][y] = true;
                vis_cnt++;
                for (int i: rnd4()) {
                    auto v = now.autoAddConnect(x, y, i);
                    for (auto m: v) que.pb(m);
                }
            }
        }
        vis = vvb(N, vb(N, false));
        // 残りは全部見る
        rep (i, N) rep(j, N) if (!vis[i][j] && now.C[i][j] == F) {
            deque<pii> que; que.pb({i, j});
            while (!que.empty()) {
                auto [x, y] = que.front(); que.pop_front();
                if (vis[x][y]) continue;
                vis[x][y] = true;
                for (int i: rnd4()) {
                    auto v = now.autoAddConnect(x, y, i);
                    for (auto m: v) que.pb(m);
                }
            }
        }
    }

    void autoRandom (Result &now, int L = 100) {
        vvb vis(N, vb(N, false));
        rep (o, L) {
            int x = rnd() % N, y = rnd() % N;
            if (now.C[x][y] == '0') continue;
            if (vis[x][y]) continue;

            deque<pii> que; que.pb({x, y});
            while (!que.empty()) {
                auto [x, y] = que.front(); que.pop_front();
                if (vis[x][y]) continue;
                vis[x][y] = true;
                for (int i: rnd4()) {
                    auto v = now.autoAddConnect(x, y, i);
                    for (auto m: v) que.pb(m);
                }
            }
        }
    }

    void loop (Result &ans, int &ans_score) {
        Result now;

        char F = '1' + (rnd() % K);  // Fを作ろうとする！
        maximizeF(now, F);

        int now_score = now.score();
        if (ans_score < now_score) {
            ans = now;
            ans_score = now_score;
        }

        autoRandom(now);

        now_score = now.score();
        if (ans_score < now_score) {
            ans = now;
            ans_score = now_score;
        }
    }


    void autoForcedConnect (Result &now, int &now_score, char F) {
        UnionFind uf;
        for (auto c: now.connect) {
            uf.merge({c.c1_x, c.c1_y}, {c.c2_x, c.c2_y});
        }

        priority_queue<pair<int, pii>> que;
        rep (i, N) rep(j, N) if (now.C[i][j] == F) {
            que.push({uf.size({i, j}), {i, j}});
        }

        while (!que.empty()) {  // やる順序は適当でいいので、queは更新しない
            auto [sz, p] = que.top(); que.pop(); 
            auto [x, y] = p;

            // x, yから一番近いFは？ただし... 
            //  0 なら来た方向にしか進めない
            //  else ならcost+1
            //  01dfs
            //  経路復元しないといけなくない？ダル...
            vector dist(N, vector(N, vector(4, inf)));
            for (int i: rnd4()) dist[x][y][i] = 0;
            deque<pair<int, vpii>> que; // 向き、今までの経路 今の位置は.back()
            for (int i: rnd4()) que.pb({i, {{x, y}}}); // 向き, pos
            vpii route;
            while (!que.empty()) {

                auto [i, u] = que.front(); que.pop_front();
                auto [s, t] = u.back();
                if (now.C[s][t] == F && !uf.same({x, y}, {s, t})) {
                    route = u;
                    break;
                }

                // s+, t+ がboardInか？の判定
                if (now.C[s][t] == '0' && now.block[s][t] != 'x' && boardIn(s + dx[i], t + dy[i])) {
                    if (chmin(dist[s + dx[i]][t + dy[i]][i], dist[s][t][i])) {
                        que.pf({i, u});
                    }
                } elif (now.C[s][t] != '0') {
                    rep (j, 4) if (j != (i + 2) % 2 && boardIn(s + dx[j], t + dy[j])) {
                        if (chmin(dist[s + dx[j]][t + dy[j]][j], dist[s][t][i] + 1)) {
                            u.emplace_back(pii(s + dx[j], t + dy[j]));
                            que.pb({j, u});
                            u.pop_back();
                        }
                    }
                }
            }

            if (route.size() == 0) continue;
            if (route.size() > 3) continue;

            // nxtでそれをもとに接続
            Result nxt = now;
            ll nx = x, ny = y;
            for (auto [s, t]: route) {
                if (nx == s && ny == t) continue;
                nxt.addConnect(nx, ny, s, t);
                nx = s; ny = t;
            }

            // 点数が上がったら採用
            ll nxt_score = nxt.score();
            if (now_score < nxt_score) {
                now = nxt;
                for (int i = 1; i < route.size() - 1; i++) {
                    now.ngList.insert({route[i].fi, route[i].se});
                }
                now_score = nxt_score;
                uf.merge({x, y}, {nx, ny});
            }

        }

    }   

    void autoForcedConnect2 (Result &now, int &now_score, char F) {
        priority_queue<pair<int, pii>> que;
        rep (i, N) rep(j, N) if (now.C[i][j] == F) {
            que.push({now.uf.size({i, j}), {i, j}});
        }

        while (!que.empty()) { 
            auto [sz, p] = que.top(); que.pop(); 
            auto [x, y] = p;
            if (now.uf.size(p) < 3) continue;
            // 1つ接続して3以上同士の!sameがあれば接続する
            vector<vpii> route = {};

            auto dfs = [&](auto&& self, vpii v, int lim) -> void {
                if (lim + 1 <= v.size()) {
                    if (now.C[v.back().fi][v.back().se] == F) {
                        route.emplace_back(v);
                    }
                } else {
                    for (int i: rnd4()) {
                        pii c = firstConflict(v.back().fi, v.back().se, i, now);
                        if (c.fi != -1) {
                            if (now.uf.same(p, c)) continue;
                            v.emplace_back(c);
                            self(self, v, lim);
                            v.pop_back();
                        } 
                    }
                }
                
            };

            dfs(dfs, vpii({{x, y}}), 2);
            

            // debug(route.size());
            for (auto rt: route) {

                // cerr << rt[0].fi << " " << rt[0].se << " " << rt[1].fi << " " << rt[1].se << " " << rt[2].fi << " " << rt[2].se << endl; 

                if (now.uf.same({x, y}, rt.back())) continue;
                // if (now.uf.size(rt.back()) < 3) continue;
                if (now.uf.size(rt.back()) < 2) continue;   // WolframAlpha に聞くと3, 2をコスト1で接続してもプラスになる
                int s = -1, t = -1;
                for (auto [nx, ny]: rt) {
                    if (now.C[nx][ny] != F) {
                        now.ngList.insert({nx, ny});
                    }
                    if (s != -1) {
                        now.addConnect(s, t, nx, ny);
                    }
                    s = nx; t = ny;
                }
                // 違う数 -> v.size() - 2
                // しかし一度connectしたのはあれなのでよい？

            }

            if (now.uf.size(p) < 5) continue;
            route.clear();
            dfs(dfs, vpii({{x, y}}), 3);    // 5と4はコスト2払ってつなげてもよい
            for (auto rt: route) {
                if (now.uf.same({x, y}, rt.back())) continue;
                if (now.uf.size(rt.back()) < 4) continue;
                int s = -1, t = -1;
                for (auto [nx, ny]: rt) {
                    if (now.C[nx][ny] != F) {
                        now.ngList.insert({nx, ny});
                    }
                    if (s != -1) {
                        now.addConnect(s, t, nx, ny);
                    }
                    s = nx; t = ny;
                }
            }

        }

    }

    // Resultがuf持てばよくない？それで採点できる

    // ないなら-1, -1
    pii firstConflict(int x, int y, int i, Result &now) {
        int nx = x, ny = y;
        while (true) {
            nx += dx[i]; ny += dy[i];
            if (!boardIn(nx, ny)) return {-1, -1};
            if (now.C[nx][ny] != '0') { 
                if (now.uf.same({x, y}, {nx, ny})) return {-1, -1};
                return {nx, ny};
            }
            if (now.block[nx][ny] == 'x') return {-1, -1};
        }        
        return {-1, -1};
    }

    void solve2 () {

        Result ans;
        int ans_score = ans.score();

        int cnt = 0;
        while (!timer.end()) {
            loop2(ans, ans_score);
            cnt++;
        }
        debug(cnt);

        ans.out();
        debug(ans_score);
    }

    void loop2 (Result &ans, int &ans_score) {
        Result now;
        
        char F = '1' + (rnd() % K);  // Fを作ろうとする！
        maximizeF(now, F);
        int now_score = now.score();

        autoForcedConnect2(now, now_score, F);

        autoRandom(now, 200);

        now_score = now.score();

        if (ans_score < now_score) {
            ans = now;
            ans_score = now_score;
        }

    }
};



int main(){

    timer.start();

    cin >> _N >> _K;
    _C.resize(_N);
    rep(i, _N) cin >> _C[i];

    Solver solver(_N, _K, _C);

    // if (forcedConnectSet.find({_N, _K}) == forcedConnectSet.end()) {
    //     cerr << 1 << endl;
    //     solver.solve2();
    // } else {
    //     cerr << 2 << endl;
    //     solver.solve2();
    // }

    solver.solve2();

}
