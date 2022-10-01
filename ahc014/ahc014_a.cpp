#pragma region header

#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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

unsigned int randxor() {
    static unsigned int x=123456789,y=362436069,z=521288629,w=88675123;
    unsigned int t;
    t=(x^(x<<11));x=y;y=z;z=w; return( w=(w^(w>>19))^(t^(t>>8)) );
}

int N, M, c, S, K;
mt19937 mt(randxor());

struct Timer {
    time_t _time;
    const double TL = 4.8;
    // const double TL = 99.0;
    const int loop = 200;
    double _now;
    int cnt;
    Timer() : _time(clock()) {}

    double now() {
        if (cnt++ % loop == 0) {
            _now = (double)(clock() - _time) / (CLOCKS_PER_SEC * TL);
        }
        return _now;
    }

    bool isTimeOut() {
        return now() >= 1.0;
    }

} timer;

struct Pos {
    int x, y;
    Pos(int x, int y) : x(x), y(y) {}
    int weight() const {
        int dx = x - c, dy = y - c;
        return dx * dx + dy * dy + 1;
    } 

    Pos add(int direction) const {
        switch (direction) {
            case 0: return Pos(x - 1, y    ); break;
            case 1: return Pos(x - 1, y + 1); break;
            case 2: return Pos(x    , y + 1); break;
            case 3: return Pos(x + 1, y + 1); break;
            case 4: return Pos(x + 1, y    ); break;
            case 5: return Pos(x + 1, y - 1); break;
            case 6: return Pos(x    , y - 1); break;
            case 7: return Pos(x - 1, y - 1); break;
        }
        return null;
    }

    bool in() const {
        return 0 <= x && x < N && 0 <= y && y < N;
    }

    bool operator<(const Pos &p) const {
        return x == p.x ? y < p.y : x < p.x;
    }

    bool operator==(const Pos &p) const {
        return x == p.x && y == p.y;
    }

    bool operator!=(const Pos &p) const {
        return x != p.x || y != p.y;
    }

    static const Pos null;
};
const Pos Pos::null = Pos(-1, -1);
vector<Pos> POINTS;
const array<Pos, 8> DXY = {
    Pos{-1,  0}, Pos{-1,  1}, Pos{ 0,  1}, Pos{ 1,  1},
    Pos{ 1,  0}, Pos{ 1, -1}, Pos{ 0, -1}, Pos{-1, -1}
};


// 64 * 64
template<class T> struct Array2D {
    // 4096 = 64 ^ 2
    array<T, 4096> data;
    T &operator[](Pos p) {
        return data[(p.x << 6) + p.y];
    }
    
    T &operator[](int k) {
        return data[k];
    }

    T &get(int x, int y) {
        return data[(x << 6) + y];
    }
};

template<class T> struct Array3D {
    array<T, 32768> data;
    T &get(Pos p, int d) {
        return data[(p.x << 9) + (p.y << 3) + d];
    }
    T &get(int x, int y, int d) {
        return data[(x << 9) + (y << 3) + d];
    }
    T &operator[](int k) {
        return data[k];
    }
};

using Query = array<Pos, 4>;
vector<Query> queries;

struct State {
    Array2D<bool> points;
    // Array2D<array<int, 8>> lines;
    Array3D<int> lines;
    set<int> Ans;
    int sum = 0;

    State() {
        rep(k, 4096) {
            points[k] = false;
            rep(i, 8) lines[(k << 3) + i]= -1;
        }
    }
    State(vector<Pos> ps) {
        rep(k, 4096) {
            points[k] = false;
            rep(i, 8) lines[(k << 3) + i] = -1;
        }
        for(auto p: ps) {
            points[p] = true;
            sum += p.weight();
        }
    }

    Pos nextPos(const Pos &p, int direction) {
        if (lines.get(p, direction) != -1) {
            return Pos::null;
        }
        Pos np = p.add(direction);
        while (np.in()) {
            if (points[np]) {
                return np;
            }
            np = np.add(direction);
        }
        return Pos::null;
    }

    int querySize(Query q) {
        int ret = 0;
        rep(i, 4) {
            int j = (i + 1) % 4;
            ret += max(abs(q[i].x - q[j].x), abs(q[i].y - q[j].y));
        }
        return ret;
    }

    int usePosGenerateQuery(const Pos p, int sz = -1) {
        if (!points[p]) return -1;

        array<Pos, 8> next = {Pos::null, Pos::null, Pos::null, Pos::null, Pos::null, Pos::null, Pos::null, Pos::null};
        for(int i = 0; i < 8; i++) {
            next[i] = nextPos(p, i);
        }

        vector<Query> ret;

        // 自分の隣に追加するパターン
        for (int d: {-2, 2}) {
            rep(i, 8) if (next[i] != Pos::null) {
                int j = (i + d + 8) % 8;
                Pos nextNextJ = nextPos(next[i], j);
                if (nextNextJ == Pos::null) continue;
                int dx = nextNextJ.x - next[i].x, dy = nextNextJ.y - next[i].y;
                Pos np = Pos(p.x + dx, p.y + dy);
                if (!np.in()) continue;
                if (points[np]) continue;
                if (canAddLine(p, np, j) && canAddLine(nextNextJ, np, (i + 4) % 8)) {
                    Query add = {np, p, next[i], nextNextJ};
                    if (sz == -1 || querySize(add) < sz) {
                        ret.emplace_back(add);
                    }
                }
            }
        }

        // 自分の対角線に新たに追加するパターン
        rep(i, 8) {
            int j = (i + 2) % 8;
            if (next[i] == Pos::null || next[j] == Pos::null) continue;
            // p, next[i], next[j], 
            int dx = next[i].x - p.x, dy = next[i].y - p.y;
            Pos np = Pos(next[j].x + dx, next[j].y + dy);
            if (!np.in()) continue;
            if (points[np]) continue;
            if (canAddLine(next[i], np, j) && canAddLine(next[j], np, i)) {
                Query add = {np, next[i], p, next[j]};
                if (sz == -1 || querySize(add) < sz) {
                    ret.emplace_back(add);
                }
            }
        }

        // return
        if (ret.size() == 0) return -1;
        Query addQ = ret[randxor() % ret.size()];
        int id = queries.size();
        queries.emplace_back(addQ);
        return id;
    }

    bool canAddLine(Pos st, Pos gl) { return canAddLine(st, gl, direct(st, gl)); }
    bool canAddLine(Pos st, Pos gl, int direction) { 
        if (lines.get(st, direction) != -1) return false;
        Pos np = st.add(direction);
        while (np != gl) {
            if (points[np]) return false;
            np = np.add(direction);
        }
        return true;
    }

    int generateQuery(Pos p) {
        if (points[p]) return -1;
        
        array<Pos, 8> next = {Pos::null, Pos::null, Pos::null, Pos::null, Pos::null, Pos::null, Pos::null, Pos::null};
        for(int i = 0; i < 8; i++) {
            next[i] = nextPos(p, i);
        }

        vector<Query> ret;
        rep(i, 8) {
            int j = (i + 2) % 8;
            if (next[i] == Pos::null || next[j] == Pos::null) continue;
            Pos p1 = nextPos(next[i], j); 
            if (p1 == Pos::null) continue;
            Pos p2 = nextPos(next[j], i);
            if (p2 == Pos::null) continue;
            if (p1 == p2) {
                ret.pb({p, next[i], p1, next[j]});
            }
        }

        if (ret.size() == 0) return -1;
        Query add = ret[randxor() % ret.size()];
        int id = queries.size();
        queries.pb(add);
        return id;
    }

    int sign(int val) {
        if (val == 0) return 0;
        return val > 0 ? 1 : -1;
    }

    int direct(const Pos p1, const Pos p2) {
        int dx = sign(p2.x - p1.x), dy = sign(p2.y - p1.y);
        rep(i, 8) {
            if (DXY[i].x == dx && DXY[i].y == dy) return i;
        }
        return -1;
    }

    void addLineDirection(Pos p1, Pos p2, int id) {
        int d = direct(p1, p2);
        if (d == -1) return;
        Pos now = p1;
        while (now != p2) {
            lines.get(now, d) = id;
            now = now.add(d);
        }
    }

    void addLine(int id) {
        Query q = queries[id];
        points[q[0]] = true;

        rep(i, 4) {
            int j = (i + 1) % 4;
            addLineDirection(q[i], q[j], id);
            addLineDirection(q[j], q[i], id);
        }
        sum += q[0].weight();
        Ans.insert(id);
    }

    void greedy(int sz = -1) {
        vector<Pos> addPos = POINTS;
        for (int id: Ans) {
            addPos.emplace_back(queries[id][0]);
        }
        
        while (true) {
            vector<Pos> nxtAddPos;
            bool update = false;
            shuffle(all(addPos), mt);
            for (auto p: addPos) {
                int id = usePosGenerateQuery(p, sz);
                if (id != -1) {
                    addLine(id);
                    update = true;
                    nxtAddPos.pb(queries[id][0]);
                }
                // 追加できなかったのは他で追加されるため、nxtPosには入れない
            }
            if (!update) break;
            addPos = nxtAddPos;
        }
    }

    void _greedy() {
        vector<Pos> addPos;
        rep(i, N) rep(j, N) if (!points.get(i, j)) addPos.pb(Pos(i, j));
        shuffle(all(addPos), mt);
        while (true) { // ここのwhile がやばい
            bool limFlag = true;
            for (Pos p: addPos) {
                int id = generateQuery(p);
                if (id == -1) continue;
                addLine(id);
                limFlag = false;
            }
            if (limFlag) break;
        }
    }

    int querySize(int &id) {
        int ret = 0;
        rep(i, 4) {
            int j = (i + 1) % 4;
            ret += max(abs(queries[id][i].x - queries[id][j].x), abs(queries[id][i].y - queries[id][j].y));
        }
        return ret;
    }

    void limGreedy(int lim) {
        vector<Pos> addPos;
        rep(i, N) rep(j, N) if (!points.get(i, j)) addPos.emplace_back(Pos(i, j));
        while (true) {
            shuffle(all(addPos), mt);
            bool limFlag = true;

            for (Pos p: addPos) {
                int id = generateQuery(p);
                if (id == -1) continue;
                int sz = querySize(id);
                if (sz <= lim) {
                    addLine(id);
                    limFlag = false;
                }
            }

            if (limFlag) break;
        }
    }

    void initSolve() {
        limGreedy(  4);
        limGreedy(  8);
        limGreedy( 16);
        limGreedy( 32);
        greedy();
    }

    set<int> delIdUponQuery(int id) {
        set<Pos> delPoints;
        delPoints.insert(queries[id][0]);
        set<int>  ret;
        for (int i: Ans) {
            Query q = queries[i];
            for (Pos p: q) if (delPoints.find(p) != delPoints.end()) {
                ret.insert(i);
                delPoints.insert(q[0]);
            }
        }
        return ret;
    }

    void deleteLineDirection(Pos &p1, Pos &p2) {
        int direction = direct(p1, p2);
        Pos now = p1;
        while (now != p2) {
            lines.get(now, direction) = -1;
            now = now.add(direction);
        }
    }

    // 削除したクエリの数を返す
    int deleteQuery(int id) {
        Query delQuery = queries[id];
        set<int> delQueryId = delIdUponQuery(id);

        for (int i: delQueryId) {
            Query delQ = queries[i];
            rep(i, 4) {
                int j = (i + 1) % 4;
                deleteLineDirection(delQ[i], delQ[j]);
                deleteLineDirection(delQ[j], delQ[i]);
            }
            Ans.erase(i);
        }

        for (auto i: delQueryId) {
            Pos p = queries[i][0];
            points[p] = false;
            sum -= p.weight();
        }

        return delQueryId.size();
    }

    void destruction() {
        if (Ans.size() == 0) return;

        vi vAns;
        for (int i: Ans) vAns.emplace_back(i);
        double time = timer.now();
        int delCntBase;
        if (time < 0.2) {
            delCntBase = 6;
        } else if (time < 0.4) {
            delCntBase = 5;
        } else if (time < 0.6) {
            delCntBase = 4;
        } else if (time < 0.8) {
            delCntBase = 3;
        } else {
            delCntBase = 2;
        }

        int delCnt = randxor() % delCntBase;
        Pos randPos = queries[vAns[randxor() % vAns.size()]][0];
        const int boarder = 25;
        int cnt = 0;
        for (int i = -delCnt; i <= delCnt; i++) for (int j = -delCnt; j <= delCnt; j++) {
            int nx = randPos.x + i, ny = randPos.y + j;
            Pos np(randPos.x + i, randPos.y + j);
            if (!np.in()) continue;
            rep(k, 8) {
                int id = lines.get(np, k);
                if (id != -1) cnt += deleteQuery(id);
                if (cnt >= boarder) {
                    return;
                }
            }
        }

    }

    void solve() {
        initSolve();
        // 破壊パート : 実はやるだけ
        // Pos(x, y)を使ってクエリが追加できるか？を作る
        // -> それに追加したのを投げるのを繰り返すとよい！

        const double startTemp = 500.0, endTemp = 10.0;
        int cnt = 0;

        while (!timer.isTimeOut()) {
            cnt++;

            State next = (*this);

            next.destruction();
            next.greedy();

            double temp = startTemp + (endTemp - startTemp) * timer.now();
            double prob = exp((double)(next.calcScore() - calcScore()) / temp);

            if (prob > (randxor() % 10000) / 10000.0) {
                *this = next;
            }
        }
        // debug(cnt);
    }

    int calcScore(int add = 0) {
        // double ret = 1000000.0 * (double)N * (double)N * (double)(sum + add) / (double)S / (double)M;
        return K * (sum + add);
    }

    void output() {
        cout << Ans.size() << "\n";
        for (auto id: Ans) {
            Query q = queries[id];
            cout << q[0].x << " " << q[0].y << " "
                 << q[1].x << " " << q[1].y << " " 
                 << q[2].x << " " << q[2].y << " " 
                 << q[3].x << " " << q[3].y << "\n";
        }
    }

};



int main() {

    queries.reserve(1000000);

    // input
    cin >> N >> M;
    rep(i, M) {
        INT(x, y);
        POINTS.emplace_back(Pos(x, y));
    }

    // preprocessing
    c = N / 2;
    S = 0;
    rep(x, N) rep(y, N) S += Pos(x, y).weight();
    K = 1000000.0 * (double)N * (double)N / (double)S / (double)M;


    // solve
    State state(POINTS);
    state.solve();

    // output
    state.output();

}