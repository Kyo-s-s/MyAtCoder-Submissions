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

#pragma endregion header    

// https://atcoder.github.io/ac-library/document_ja/dsu.html 
struct dsu{
  public:
    dsu() : _n(0) {}
    dsu(int n):  _n(n), parent(n, -1) {}

    int merge(int a, int b){
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = leader(a), y = leader(b);
        if(x == y) return x;
        if(-parent[x] < -parent[y]) std::swap(x, y);
        parent[x] += parent[y];
        parent[y] = x;
        return x;
    }

    bool same(int a, int b){
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return leader(a) == leader(b);
    }

    int leader(int a){
        assert(0 <= a && a < _n);
        if(parent[a] < 0) return a;
        return parent[a] = leader(parent[a]);
    }

    int size(int a){
        assert(0 <= a && a < _n);
        return -parent[leader(a)];
    }

    std::vector<std::vector<int>> groups(){
        std::vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        std::vector<std::vector<int>> result(_n);
        for (int i = 0; i < _n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(
            std::remove_if(result.begin(), result.end(),
                           [&](const std::vector<int>& v) { return v.empty(); }),
            result.end());
        return result;
    }
    
  private:
    int _n;
    // root node: -1 * component size
    // otherwise: parent
    std::vector<int> parent;
};

// https://atcoder.github.io/ac-library/document_ja/segtree.html
template<class S, S (*op)(S, S), S (*e)()> struct Segtree {
  public:
    Segtree() : Segtree(0) {}
    Segtree(int n) : Segtree(vector<S> (n, e())) {}
    Segtree(const vector<S> &v) : n(int(v.size())) {
        while ((1 << log) < n) log++;
        size = 1 << log;
        d = vector<S> (2 * size, e());
        for (int i = 0; i < n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) update(i);
    }

    void set(int p, S x) {
        assert(0 <= p && p < n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
        assert(0 <= p && p < n);
        return d[p + size];
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        S sml = e(), smr = e();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    template <bool (*f)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F> int max_right(int l, F f) {
        assert(0 <= l && l <= n);
        assert(f(e()));
        if (l == n) return n;
        l += size;
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return n;
    }

    template <bool (*f)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F> int min_left(int r, F f) {
        assert(0 <= r && r <= n);
        assert(f(e()));
        if (r == 0) return 0;
        r += size;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int n, size, log = 0;
    vector<S> d;
    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }

};

long long RMQop(long long a, long long b) { return max(a, b); }
long long RMQe() { return -(1LL << 60); }
using RMQ = Segtree<long long, RMQop, RMQe>;

long long RmQop(long long a, long long b) { return min(a, b); }
long long RmQe() { return 1LL << 60; }
using RmQ = Segtree<long long, RmQop, RmQe>;

long long RSQop(long long a, long long b) { return a + b; }
long long RSQe() { return 0; }
using RSQ = Segtree<long long, RSQop, RSQe>;


struct MmS { long long min, max, sum; };
MmS MmSop(MmS a, MmS b){ return { min(a.min, b.min), max(a.max, b.max), a.sum + b.sum }; }
MmS MmSe(){ return {1LL << 60, -1ll << 60, 0 }; }

struct SegtreeMmS : Segtree<MmS, MmSop, MmSe> {
    using Segtree::Segtree;
    SegtreeMmS(int n){
        vector<MmS> sv(n, MmSe());
        (*this) = SegtreeMmS(sv);
    }
    SegtreeMmS(vector<long long> v) {
        int n = v.size();
        vector<MmS> sv(n);
        for(int i = 0; i < n; i++) sv[i] = {v[i], v[i], v[i]};
        (*this) = SegtreeMmS(sv);
    }
    void set(int p, long long x){
        Segtree::set(p, {x, x, x});
    }
    long long get(int p){
        return Segtree::get(p).sum;
    }
};




int main(){

    ll N, K; cin >> N >> K;
    vector<ll> P(N); for(int i = 0; i < N; i++) cin >> P[i];

    vll v(N+1, INF);
    RmQ seg(v);

    vll Ans(N+1, -1);

    dsu uf(N+1);

    map<ll, ll> an;

    rrep(i, N){
        ll p = P[i-1];
        ll u = seg.prod(p, N+1);

        if(u != INF){
            // u の上に乗せる
            uf.merge(p, u);
            seg.set(u, INF);
        }
        
        seg.set(p, p);

        if(uf.size(p) == K){
            an[uf.leader(p)] = i;
            seg.set(p, INF);
        }
    }

    auto G = uf.groups();

    for(auto g : G){
        ll l = uf.leader(g[0]);
        if(an[l] != 0){
            for(auto t: g) Ans[t] = an[l];
        }
    }


    rrep(i, N){
        cout << Ans[i] << "\n";
    }



}