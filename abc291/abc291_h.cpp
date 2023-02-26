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
// clang-format on

#pragma endregion header    

template< typename T >
struct edge {
  int src, to;
  T cost;

  edge(int to, T cost) : src(-1), to(to), cost(cost) {}

  edge(int src, int to, T cost) : src(src), to(to), cost(cost) {}

  edge &operator=(const int &x) {
    to = x;
    return *this;
  }

  operator int() const { return to; }
};


template< typename T >
using Edges = vector< edge< T > >;
template< typename T >
using WeightedGraph = vector< Edges< T > >;
using UnWeightedGraph = vector< vector< int > >;
template< typename T >
using Matrix = vector< vector< T > >;
template< typename G >
struct CentroidDecomposition {
  const G &g;
  vector< int > sub;
  vector< vector< int > > belong;
  vector< bool > v;

  CentroidDecomposition(const G &g) : g(g), sub(g.size()), v(g.size()), belong(g.size()) {}

  inline int build_dfs(int idx, int par) {
    sub[idx] = 1;
    for(auto &to : g[idx]) {
      if(to == par || v[to]) continue;
      sub[idx] += build_dfs(to, idx);
    }
    return sub[idx];
  }

  inline int search_centroid(int idx, int par, const int mid) {
    for(auto &to : g[idx]) {
      if(to == par || v[to]) continue;
      if(sub[to] > mid) return search_centroid(to, idx, mid);
    }
    return idx;
  }

  inline void belong_dfs(int idx, int par, int centroid) {
    belong[idx].emplace_back(centroid);
    for(auto &to : g[idx]) {
      if(to == par || v[to]) continue;
      belong_dfs(to, idx, centroid);
    }
  }

  inline int build(UnWeightedGraph &t, int idx) {
    int centroid = search_centroid(idx, -1, build_dfs(idx, -1) / 2);
    v[centroid] = true;
    belong_dfs(centroid, -1, centroid);
    for(auto &to : g[centroid]) {
      if(!v[to]) t[centroid].emplace_back(build(t, to));
    }
    v[centroid] = false;
    return centroid;
  }

  inline int build(UnWeightedGraph &t) {
    t.resize(g.size());
    return build(t, 0);
  }
};

int main() {
    LL(N);
    UnWeightedGraph g(N);
    rep(i, N - 1) {
        LL(a, b);
        a--, b--;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }

    CentroidDecomposition< UnWeightedGraph > cd(g);
    UnWeightedGraph t;
    int root = cd.build(t);

    vll ans(N, -1);

    rep(p, N) {
        for (auto u : t[p]) {
            ans[u] = p + 1;
        }
    }

    OUT(ans);
}