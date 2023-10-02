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

template <class M, class O, auto fn> struct LazySegtree {
    using S = typename M::T;
    using F = typename O::T;
    static_assert(is_convertible_v<decltype(fn), std::function<S(F, S)>>);

  public:
    LazySegtree() : LazySegtree(0) {}
    LazySegtree(int n) : LazySegtree(std::vector<S>(n, M::e())) {}
    LazySegtree(const std::vector<S>& v) : n(int(v.size())) {
        while ((1 << log) < n) log++;
        size = 1 << log;
        d = vector<S>(2 * size, M::e());
        lz = vector<F>(size, O::e());
        for (int i = 0; i < n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) update(i);
    }

    void set(int p, S x) {
        assert(0 <= p && p < n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
        assert(0 <= p && p < n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return M::e();
        l += size; r += size;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push(r >> i);
        }
        S sml = M::e(), smr = M::e();
        while (l < r) {
            if (l & 1) sml = M::op(sml, d[l++]);
            if (r & 1) smr = M::op(d[--r], smr);
            l >>= 1; r >>= 1;
        }
        return M::op(sml, smr);
    }

    S all_prod() { return d[1]; }

    void apply(int p, F f) {
        assert(0 <= p && p < n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = fn(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return;
        l += size; r += size;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1; r >>= 1;
            }
            l = l2; r = r2;
        }
        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

  private:
    int n, size, log = 0;
    vector<S> d;
    vector<F> lz;

    void update(int k) { d[k] = M::op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = fn(f, d[k]);
        if (k < size) lz[k] = O::op(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = O::e();
    }
};

struct Hand {
    int left, right, cl, cr, ma;

    bool operator==(const Hand &h) const {
        return left == h.left && right == h.right && cl == h.cl && cr == h.cr && ma == h.ma;
    }

    bool connect() {
        return right - left == ma;
    }

    static optional<Hand> marge(optional<Hand> an, optional<Hand> bn) {
        if (!an) return bn;
        if (!bn) return an;
        Hand a = an.value();
        Hand b = bn.value();
        if (a.connect() && b.connect()) {
            return Hand{a.left, b.right, a.cl + b.cl, a.cr + b.cr, a.ma + b.ma};
        }
        if (a.connect()) {
            int cl = a.cl + b.cl;
            int cr = b.cr;
            int ma = max(max(a.ma, b.ma), max(cl, cr));
            return Hand{a.left, b.right, cl, cr, ma};
        }
        if (b.connect()) {
            int cl = a.cl;
            int cr = a.cr + b.cr;
            int ma = max(max(a.ma, b.ma), max(cl, cr));
            return Hand{a.left, b.right, cl, cr, ma};
        }
        int cl = a.cl;
        int cr = b.cr;
        int ma = max(max(max(a.ma, b.ma), max(cl, cr)), a.cr + b.cl);
        return Hand{a.left, b.right, cl, cr, ma};
    }
};

struct M {
    struct T {
        optional<Hand> o, i; 
    };

    static T op(T a, T b) {
        return T{Hand::marge(a.o, b.o), Hand::marge(a.i, b.i)};
    }

    static T e() {
        // return T{Hand{0, 0, 0, 0, 0}, Hand{0, 0, 0, 0, 0}};
        return T{nullopt, nullopt};
    }
};

struct O {
    using T = bool;
    static T op(T a, T b) {
        return a ^ b;
    }
    static T e() {
        return false;
    }
};

M::T fn(O::T f, M::T x) {
    if (f) {
        return M::T{x.i, x.o};
    }
    return x;
}


int main() {

    LL(N, Q);
    STR(S);

    vector<M::T> v(N);
    for (int i = 0; i < N; i++) {
        if (S[i] == '0') {
            v[i] = M::T{Hand{i, i + 1, 1, 1, 1}, Hand{i, i + 1, 0, 0, 0}};
        } else {
            v[i] = M::T{Hand{i, i + 1, 0, 0, 0}, Hand{i, i + 1, 1, 1, 1}};
        }
    }

    LazySegtree<M, O, fn> seg(v);

    while (Q--) {
        INT(c, l, r);
        l--; r--;
        if (c == 1) {
            seg.apply(l, r + 1, true);
        } else {
            M::T res = seg.prod(l, r + 1);
            if (!res.i) {
                return 1;
            }
            OUT(res.i.value().ma);
        }
    }
    
}


/*
C: あ、あの　実装ミスってWAです
D: ピースの構造体を作るなどするとよいですね
E: なんだこれ　DPやるだけ
F: 連続する'x'の長さの最大値、左から連続する'x'の個数、右から連続する'x'の個数 などを持つとモノイドになるので遅延セグ木に乗せます


何か今日パフォしょっぱくない？最強コンあったから？

*/

