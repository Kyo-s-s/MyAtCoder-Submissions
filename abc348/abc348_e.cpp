#ifdef INCLUDED_MAIN

template<typename T> 
concept Monoid = requires {
    typename T::T;
    { T::op(std::declval<typename T::T>(), std::declval<typename T::T>()) } -> std::same_as<typename T::T>;
    { T::e() } -> std::same_as<typename T::T>;
};

template<Monoid M> struct Rerooting {
  public:
    using E = typename M::T;
    Rerooting(int N) : N(N) {
        G.resize(N);
    }

    int add_edge(int from, int to) {
        assert(edge_count < N - 1);
        G[from].push_back(edge{to, edge_count});
        G[to].push_back(edge{from, edge_count});
        return edge_count++;
    }

    template<class V>
    vector<V> solve(function<E(V, int)> put_edge, function<V(E, int)> put_node) {
        return solve<V>(put_edge, put_node, put_node);
    }

    template<class V> 
    vector<V> solve(
        function<E(V, int)> put_edge, 
        function<V(E, int)> put_node,
        function<V(E, int)> solve_node
    ) {
        vector<vector<V>> dp(N);
        for (int i = 0; i < N; i++) dp[i].resize(G[i].size());
        auto dfs = [&](auto dfs, int now, int par) -> V {
            int deg = (int)G[now].size();
            E res = M::e();
            for (int i = 0; i < deg; i++) {
                auto [to, id] = G[now][i];
                if (to == par) continue;
                dp[now][i] = dfs(dfs, to, now);
                res = M::op(res, put_edge(dp[now][i], id));
            }
            return put_node(res, now);
        };
        dfs(dfs, 0, -1);
        vector<V> ans(N);
        auto reroot = [&](auto reroot, int now, int par, const optional<V> &v) -> void {
            int deg = (int)G[now].size();
            if (v.has_value()) {
                for (int i = 0; i < deg; i++) if (G[now][i].to == par) {
                    dp[now][i] = v.value();
                }
            }
            vector<E> L(deg + 1, M::e()), R(deg + 1, M::e());
            for (int i = 0; i < deg; i++) {
                L[i + 1] = M::op(L[i], put_edge(dp[now][i], G[now][i].id));
            }
            for (int i = deg - 1; i >= 0; i--) {
                R[i] = M::op(R[i + 1], put_edge(dp[now][i], G[now][i].id));
            }

            ans[now] = solve_node(L[deg], now);
            for (int i = 0; i < deg; i++) {
                int u = G[now][i].to;
                if (u == par) continue;
                reroot(reroot, u, now, put_node(M::op(L[i], R[i + 1]), now));
            }
        };
        reroot(reroot, 0, -1, nullopt);
        return ans;
    }

  private:
    int N;
    int edge_count = 0;
    struct edge {
        int to, id;
    };
    vector<vector<edge>> G;
};

struct Mono {
    struct T {
        ll dec;
        ll sum;
    };
    static T op(T a, T b) {
        return T{a.dec + b.dec, a.sum + b.sum};
    }
    static T e() {
        return T{0, 0};
    }
};

int main() {

    LL(N);
    Rerooting<Mono> tree(N);
    rep(i, N - 1) {
        LL(a, b); a--; b--;
        tree.add_edge(a, b);
    }
    VEC(ll, C, N);

    using E = typename Mono::T;
    using V = typename Mono::T;

    auto put_edge = [&](V v, int id) -> E {
        return E{v.dec, v.sum + v.dec};
    };
    auto put_node = [&](E e, int node) -> V {
        return V{e.dec + C[node], e.sum};
    };

    auto dist = tree.solve<V>(put_edge, put_node);
    ll ans = -1;
    rep(i, N) {
        if (ans == -1 || dist[i].sum < ans) {
            ans = dist[i].sum;
        }
    }
    OUT(ans);

}

#else

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

bool include(ll l, ll r, ll x) { return l <= x && x < r; }

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

namespace kyo {

long long bisect(long long ok, long long ng, function<bool(long long)> is_ok) { while (abs(ok - ng) > 1) { long long mid = ok + (ng - ok) / 2; (is_ok(mid) ? ok : ng) = mid; } return ok; }

}

#define INCLUDED_MAIN
#include __FILE__ // Codeforces で壊れるらしい

#endif
