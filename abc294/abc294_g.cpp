#pragma region header
#include <bits/stdc++.h>
using namespace std;
// #include <atcoder/all>
// using namespace atcoder;

// clang-format off
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
#define reps(i, a, n) for(ll i = (a); i < (n); i++)
#define rep(i, n) reps(i, 0, (n))
#define rrep(i, n) reps(i, 1, (n + 1))
#define repd(i, n) for(ll i = (n - 1); i >= 0; i--)
#define rrepd(i, n) for(ll i = (n); i >= 1; i--)
#define fore(i, a) for(auto &i: a)

/* vector */
template<class T> T vmax(vector<T> &array){ T ret = array[0]; for(T a: array) chmax(ret, a); return ret; }
template<class T> T vmin(vector<T> &array){ T ret = array[0]; for(T a: array) chmin(ret, a); return ret; }
template<class T> T sum(vector<T> &array){ T ret = 0; for(T a:array) ret += a; return ret; }
template<class T> void list_set(vector<T> &array){ sort(all(array)); array.erase(unique(all(array)),array.end()); }
template<class T> int bisect_left(vector<T> &array, T key){ return lower_bound(all(array),key) - array.begin(); }
template<class T> int bisect_right(vector<T> &array, T key){ return upper_bound(all(array),key) - array.begin(); }

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
// clang-format on

#pragma endregion header
template<class M> struct Segtree {
  public:
    using S = typename M::T;

    Segtree() : Segtree(0) {}
    Segtree(int n) : Segtree(vector<S> (n, M::e())) {}
    Segtree(const vector<S> &v) : n(int(v.size())) { 
        while((1 << log) < n) log++;
        size = 1 << log;
        d = vector<S> (2 * size, M::e());
        for(int i = 0; i < n; i++) d[size + i] = v[i];
        for(int i = size- 1; i >= 1; i--) update(i);
    }

    void set(int p, S x){
        assert(0 <= p && p < n);
        p += size;
        d[p] = x;
        for(int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p){
        assert(0 <= p && p < n);
        return d[p + size];
    }

    S prod(int l, int r){
        assert(0 <= l && l <= r && r <= n);
        S sml = M::e(), smr = M::e();
        l += size; r += size;
        while(l < r){
            if(l & 1) sml = M::op(sml, d[l++]);
            if(r & 1) smr = M::op(d[--r], smr);
            l >>= 1; r >>= 1;
        }
        return M::op(sml, smr);
    }

    S all_prod(){ return d[1]; }


  private:
    int n, size, log = 0;
    vector<S> d;
    void update(int k){ d[k] = M::op(d[k * 2], d[k * 2 + 1]); }

};

struct Add_M {    
    using T = long long;
    static T e() { return 0; }
    static T op(T x, T y) { return x + y; }
};

template<class T = int> struct Tree {
    struct edge{ int to; T cost; };
    vector<vector<edge>> G;
    vector<vector<int>> parent;
    vector<int> unweighted_dist;
    vector<T> weighted_dist;

    Tree(int n) : G(n) {}

    void add_edge(int u, int v) { add_edge(u, v, T(1)); }
    void add_edge(int u, int v, T w) {
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }

    vector<T> calc_dist(int root = 0) {
        vector<T> dist(G.size(), -1); dist[root] = 0;
        queue<int> que; que.push(root);
        while (!que.empty()) {
            int v = que.front(); que.pop();
            for (auto e: G[v]) {
                if (dist[e.to] != -1) continue;
                dist[e.to] = dist[v] + e.cost;
                que.push(e.to);
            }
        }
        return dist;
    }

    tuple<T, int, int> diameter() {
        vector<T> dist = calc_dist();
        int v = max_element(dist.begin(), dist.end()) - dist.begin();
        dist = calc_dist(v);
        int u = max_element(dist.begin(), dist.end()) - dist.begin();
        return { dist[u], u, v };
    }

    void lca_build(int root = 0) {
        int V = G.size();
        int K = 1;
        while ((1 << K) < V) K++;
        parent.assign(K, vector<int>(V, -1));
        unweighted_dist.assign(V, -1);

        auto unweighted_dfs = [this](auto&& self, int v, int p, int d) -> void {
            parent[0][v] = p;
            unweighted_dist[v] = d;
            for (auto e: G[v]) {
                if (e.to == p) continue;
                self(self, e.to, v, d + 1);
            }
        };

        unweighted_dfs(unweighted_dfs, root, -1, 0);
        for (int k = 0; k + 1 < K; k++) {
            for (int v = 0; v < V; v++) {
                if (parent[k][v] < 0) parent[k + 1][v] = -1;
                else parent[k + 1][v] = parent[k][parent[k][v]];
            }
        }

        weighted_dist.assign(V, -1); weighted_dist[root] = 0;
        queue<int> que; que.push(root);
        while (!que.empty()) {
            int v = que.front(); que.pop();
            for (auto e: G[v]) {
                if (weighted_dist[e.to] == -1 || weighted_dist[e.to] > weighted_dist[v] + e.cost) {
                    weighted_dist[e.to] = weighted_dist[v] + e.cost;
                    que.push(e.to);
                }
            }
        }
    }

    int lca(int u, int v) {
        if (parent.size() == 0) lca_build();
        if (unweighted_dist[u] < unweighted_dist[v]) swap(u, v);
        int K = parent.size();
        for (int k = 0; k < K; k++) {
            if ((unweighted_dist[u] - unweighted_dist[v]) >> k & 1) {
                u = parent[k][u];
            }
        }
        if (u == v) return u;
        for (int k = K - 1; k >= 0; k--) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }

    T dist(int u, int v) {
        if (weighted_dist.size() == 0) lca_build();
        return weighted_dist[u] + weighted_dist[v] - 2 * weighted_dist[lca(u, v)];
    }
};

struct Solver {
    struct edge {
        int to; 
        int id;
        ll cost;
    };

    int n;
    vector<vector<edge>> G;
    vector<vector<pair<int, int>>> need_change;
    vector<int> in;
    Segtree<Add_M> seg;

    Solver(int _n) : n(_n) {
        G.resize(n);
        // 辺の本数 Nで抑えられるはず
        need_change.resize(n); // N - 1 だけど
        in.resize(n);
    }

    void add_edge(int u, int v, ll cost, int id) {
        G[u].push_back({v, id, cost});
        G[v].push_back({u, id, cost});
    }

    void build() {

        // id, cost
        vector<pair<int, ll>> euler;

        dfs(0, -1, -1, euler);

        vll v;
        for (int i = 0; i < euler.size(); i++) {
            need_change[euler[i].first].push_back({i, euler[i].second > 0 ? 1 : -1});
            v.push_back(euler[i].second);
        }

        seg = Segtree<Add_M>(v);
    }

    void dfs (int now, int bef, int id, vector<pair<int, ll>> &euler) {
        in[now] = euler.size();
        for (auto e : G[now]) {
            if (e.to != bef) {
                euler.push_back({e.id, e.cost});
                dfs(e.to, now, e.id, euler);
                euler.push_back({e.id, -e.cost});
            }
        }
    }

    void change(int id, ll w) {
        for (auto p : need_change[id]) {
            seg.set(p.first, p.second * w);
        }
    }

    ll query(int u, int v, int lca) {
        return dist(u) + dist(v) - 2 * dist(lca);
    }

    ll dist(int d) {
        return seg.prod(0, in[d]);
    }

};

int main() {

    LL(N);
    Solver solver(N);
    Tree tree(N);
    rep(i, N - 1) {
        LL(u, v, w);
        u--; v--;
        solver.add_edge(u, v, w, i);
        tree.add_edge(u, v);
    }

    solver.build();
    LL(Q);
    while (Q--) {
        LL(t);
        if (t == 1) {
            LL(i, w); i--;
            solver.change(i, w);
        } else {
            LL(u, v); u--; v--;
            OUT(solver.query(u, v, tree.lca(u, v)));
        }
    }

}