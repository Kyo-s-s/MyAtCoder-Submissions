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


// https://atcoder.github.io/ac-library/document_ja/lazysegtree.html
template <class S,
          S (*op)(S, S),
          S (*e)(),
          class F,
          S (*mapping)(F, S),
          F (*composition)(F, F),
          F (*id)()>
struct LazySegtree {
  public:
    LazySegtree() : LazySegtree(0) {}
    LazySegtree(int n) : LazySegtree(std::vector<S>(n, e())) {}
    LazySegtree(const std::vector<S>& v) : _n(int(v.size())) {
        int x = 0;
        while((1 << x) < _n) x++;
        log = x;
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        lz = std::vector<F>(size, id());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return e();

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push(r >> i);
        }

        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }

        return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    void apply(int p, F f) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }

        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template <bool (*g)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return g(x); });
    }
    template <class G> int max_right(int l, G g) {
        assert(0 <= l && l <= _n);
        assert(g(e()));
        if (l == _n) return _n;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < size) {
                    push(l);
                    l = (2 * l);
                    if (g(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*g)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return g(x); });
    }
    template <class G> int min_left(int r, G g) {
        assert(0 <= r && r <= _n);
        assert(g(e()));
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm))) {
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
    int _n, size, log;
    std::vector<S> d;
    std::vector<F> lz;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < size) lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};


struct ArithmeticS {
    long long min, max, sum;
    int l, r;
};
struct ArithmeticF {
    long long a, b;
};
ArithmeticS Arithmetic_op(ArithmeticS s, ArithmeticS t){
    return { min(s.min, t.min), max(s.max, t.max), s.sum + t.sum, min(s.l, t.l), max(s.r, t.r) };
}
ArithmeticS Arithmetic_e() { return {1LL << 60, -(1LL << 60), 0, 1 << 28, -(1 << 28)}; }
ArithmeticS Arithmetic_mapping(ArithmeticF f, ArithmeticS s) {
    if(f.a == (1LL << 60)) return s;
    return {
        min(f.a * s.l + f.b, f.a * (s.r - 1) + f.b), 
        max(f.a * s.l + f.b, f.a * (s.r - 1) + f.b), 
        (f.a * (s.l + s.r - 1) + f.b * 2) * (s.r - s.l) / 2, 
        s.l, 
        s.r
    };
}
ArithmeticF Arithmetic_composition(ArithmeticF f, ArithmeticF g) { return f.a == (1LL << 60) ? g : f; }
ArithmeticF Arithmetic_id() { return { 1LL << 60, 1LL << 60 }; }

struct ArithmeticLazySegtree : 
    LazySegtree<ArithmeticS, Arithmetic_op, Arithmetic_e, ArithmeticF, Arithmetic_mapping, Arithmetic_composition, Arithmetic_id> {
    using LazySegtree::LazySegtree;
    ArithmeticLazySegtree(int n){
        vector<ArithmeticS> sv(n);
        for(int i = 0; i < n; i++) sv[i] = {0, 0, 0, i, i+1};
        (*this) = ArithmeticLazySegtree(sv);
    }
    ArithmeticLazySegtree(vector<long long> v){
        int n = v.size();
        vector<ArithmeticS> sv(n);
        for(int i = 0; i < n; i++) sv[i] = {v[i], v[i], v[i], i, i+1};
        (*this) = ArithmeticLazySegtree(sv);
    }
    void apply(int l, int r, ArithmeticF f) {
        LazySegtree::apply(l, r, {f.a, f.b - f.a * get(l).l});
    }
    void apply(int p, ArithmeticF f) {
        LazySegtree::apply(p, {f.a, f.b - f.a * get(p).l});
    }
};


// https://github.com/Kyo-s-s/Kyo_s_s_Library/blob/main/md/Modint.md

template<int m> struct StaticModint{
    using mint = StaticModint;
  public:
    static constexpr int mod() { return m; }
    static mint raw(int v) {
        mint x;
        x._v = v;
        return x;
    }

    StaticModint() : _v(0) {}
    template <class T>
    StaticModint(T v) {
        long long x = (long long)(v % (long long)(umod()));
        if (x < 0) x += umod();
        _v = (unsigned int)(x);
    }

    unsigned int val() const { return _v; }

    mint& operator++() {
        _v++;
        if (_v == umod()) _v = 0;
        return *this;
    }
    mint& operator--() {
        if (_v == 0) _v = umod();
        _v--;
        return *this;
    }
    mint operator++(int) {
        mint result = *this;
        ++*this;
        return result;
    }
    mint operator--(int) {
        mint result = *this;
        --*this;
        return result;
    }

    mint& operator+=(const mint& rhs) {
        _v += rhs._v;
        if (_v >= umod()) _v -= umod();
        return *this;
    }
    mint& operator-=(const mint& rhs) {
        _v -= rhs._v;
        if (_v >= umod()) _v += umod();
        return *this;
    }
    mint& operator*=(const mint& rhs) {
        unsigned long long z = _v;
        z *= rhs._v;
        _v = (unsigned int)(z % umod());
        return *this;
    }
    mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }

    mint operator+() const { return *this; }
    mint operator-() const { return mint() - *this; }

    mint pow(long long n) const {
        assert(0 <= n);
        mint x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    mint inv() const {
        assert(_v);
        return pow(umod() - 2);
    }

    friend mint operator+(const mint& lhs, const mint& rhs) {
        return mint(lhs) += rhs;
    }
    friend mint operator-(const mint& lhs, const mint& rhs) {
        return mint(lhs) -= rhs;
    }
    friend mint operator*(const mint& lhs, const mint& rhs) {
        return mint(lhs) *= rhs;
    }
    friend mint operator/(const mint& lhs, const mint& rhs) {
        return mint(lhs) /= rhs;
    }
    friend bool operator==(const mint& lhs, const mint& rhs) {
        return lhs._v == rhs._v;
    }
    friend bool operator!=(const mint& lhs, const mint& rhs) {
        return lhs._v != rhs._v;
    }

    friend ostream &operator<<(ostream &os, mint x) {
        os << x.val();
        return (os);
    }

  private:
    unsigned int _v;
    static constexpr unsigned int umod() { return m; }

};

using Modint998244353 = StaticModint<998244353>;
using Modint1000000007 = StaticModint<1000000007>;

using Mint = Modint998244353;


Mint inv2;
struct ArithmeticAddS {
    // long long sum;  
    Mint sum;
    int l, r;
};
struct ArithmeticAddF {
    // long long a, b;
    Mint a, b;
};
ArithmeticAddS ArithmeticAdd_op(ArithmeticAddS s, ArithmeticAddS t) { return {s.sum + t.sum, min(s.l, t.l), max(s.r, t.r)}; }
ArithmeticAddS ArithmeticAdd_e() { return {0, 1 << 28, -(1 << 28)}; }
ArithmeticAddS ArithmeticAdd_mapping(ArithmeticAddF f, ArithmeticAddS s) {
    // return { s.sum + (f.a * (s.l + s.r - 1) + f.b * 2) * (s.r - s.l) / 2, s.l, s.r };
    return { s.sum + (f.a * (s.l + s.r - 1) + f.b * 2) * (s.r - s.l) * inv2, s.l, s.r };
}
ArithmeticAddF ArithmeticAdd_composition(ArithmeticAddF f, ArithmeticAddF g) { return {f.a + g.a, f.b + g.b}; }
ArithmeticAddF ArithmeticAdd_id() { return {0, 0}; }

struct ArithmeticAddLazySegtree : 
    LazySegtree<ArithmeticAddS, ArithmeticAdd_op, ArithmeticAdd_e, ArithmeticAddF, ArithmeticAdd_mapping, ArithmeticAdd_composition, ArithmeticAdd_id> {
    using LazySegtree::LazySegtree;
    ArithmeticAddLazySegtree(int n){
        inv2 = Mint(1) / 2;
        vector<ArithmeticAddS> sv(n);
        for(int i = 0; i < n; i++) sv[i] = {0, i, i+1};
        (*this) = ArithmeticAddLazySegtree(sv);      
    }
    ArithmeticAddLazySegtree(vector<Mint> v){
        inv2 = Mint(1) / 2;
        int n = v.size();
        vector<ArithmeticAddS> sv(n);
        for(int i = 0; i < n; i++) sv[i] = {v[i], i, i+1};
        (*this) = ArithmeticAddLazySegtree(sv);
    }
    void apply(int l, int r, ArithmeticAddF f){
        LazySegtree::apply(l, r, {f.a, f.b - f.a * get(l).l});
    }
    void apply(int p, ArithmeticAddF f){
        LazySegtree::apply(p, {f.a, f.b - f.a * get(p).l});
    }
};

int main(){

    int N, Q; cin >> N >> Q;
 
 
    vector<ll> A(N);
    rep(i, N) cin >> A[i];
 
    vector<Mint> B(N); B[0] = A[0];
    rrep(i, N-1) B[i] = B[i-1] + A[i];
 
    vector<Mint> C(N); C[0] = B[0];
    rrep(i, N-1) C[i] = C[i-1] + B[i];
 

    ArithmeticAddLazySegtree seg(C);
 
    while(Q--){
        
        // cout << "! ";
        // rep(i, N) cout << seg.get(i).sum << " ";
        // cout << endl;
 
 
        int t; cin >> t;
        if(t == 1){
            int x;
            ll v; 
            cin >> x >> v; x--;
            seg.apply(x, N, {v - A[x], v - A[x]});
            A[x] = v;
        }else{
            ll x; cin >> x;
            cout << seg.prod(0, x).sum << "\n";
        }
 
 
    }
 
}