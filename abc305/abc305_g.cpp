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

    friend mint operator+(const mint& lhs, const mint& rhs) { return mint(lhs) += rhs;}
    friend mint operator-(const mint& lhs, const mint& rhs) { return mint(lhs) -= rhs; }
    friend mint operator*(const mint& lhs, const mint& rhs) { return mint(lhs) *= rhs; }
    friend mint operator/(const mint& lhs, const mint& rhs) { return mint(lhs) /= rhs; }
    friend bool operator==(const mint& lhs, const mint& rhs) { return lhs._v == rhs._v; }
    friend bool operator!=(const mint& lhs, const mint& rhs) { return lhs._v != rhs._v; }

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

template<class T> struct Matrix {
    int n, m;
    vector<vector<T>> M;

    Matrix() : n(0), m(0) { init(); }
    Matrix(int _n, int _m) : n(_n), m(_m) { init(); }
    Matrix(int _n) : n(_n), m(_n) { init(); }

    void init() {
        M.resize(n, vector<T>(m));
    }

    inline const vector<T> &operator[](int k) const { return (M.at(k)); }
    inline vector<T> &operator[](int k) { return (M.at(k)); }

    static Matrix I(int n) {
        Matrix mat(n);
        for(int i = 0; i < n; i++) mat[i][i] = 1;
        return (mat);
    }

    Matrix operator+=(const Matrix &B) {
        assert(n == B.n && m == B.m);
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) (*this)[i][j] += B[i][j];
        return (*this);
    }

    Matrix operator-=(const Matrix &B) {
        assert(n == B.n && m == B.m);
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) (*this)[i][j] -= B[i][j];
        return (*this);
    }

    Matrix operator*=(const Matrix &B) {
        assert(m == B.n);
        m = B.m;
        vector<vector<T>> C(n, vector<T>(B.m, 0));
        for(int i = 0; i < n; i++) for(int j = 0; j < B.m; j++) for(int k = 0; k < B.n; k++) C[i][j] += (*this)[i][k] * B[k][j];
        M.swap(C);
        return (*this);
    }

    Matrix pow(long long k) {
        assert(n == m);
        Matrix B = Matrix::I(n);
        while(k > 0) {
            if(k & 1) B *= *this;
            *this *= *this;
            k >>= 1LL;
        }
        return B;
    }

    Matrix operator+(const Matrix &B) const { return (Matrix(*this) +=B); }
    Matrix operator-(const Matrix &B) const { return (Matrix(*this) -=B); }
    Matrix operator*(const Matrix &B) const { return (Matrix(*this) *=B); }

    friend ostream &operator<<(ostream &os, Matrix &p) {
        for(int i = 0; i < p.n; i++) {
            os << "[";
            for(int j = 0; j < p.m; j++){
                os << p[i][j] << (j == p.m - 1 ? "]\n" : ", ");
            }
        }
        return (os);
    }
};

int main() {

    LL(N, M);
    VEC(string, S, M);

    map<string, Mint> dp1;
    dp1[""] = 1;

    auto check = [&](string s) -> bool {
        reverse(all(s));
        for (auto t : S) if (s.size() >= t.size()) {
            reverse(all(t));
            bool ok = false;
            rep(i, t.size()) if (s[i] != t[i]) ok = true;
            if (!ok) return false;
        }
        return true;
    };

    ll loop = min(N, 6LL);
    rep(u, loop) {
        map<string, Mint> pd1;
        for (auto [s, val] : dp1) {
            {
                string t = s + 'a';
                if (check(t)) pd1[t] += val;
            }
            {
                string t = s + 'b';
                if (check(t)) pd1[t] += val;
            }
        }
        dp1 = pd1;
    }

    if (loop == N) {
        // 文字数がNと同じのの総和で終わり
        Mint ans = 0;
        for (auto [s, val] : dp1) {
            // OUT("dp1", s, val);
            if (s.size() == N) ans += val;
        }
        OUT(ans);
        exit(0);
    }

    // メイン
    Matrix<Mint> A((1<<6), (1<<6));
    // val -> string
    auto ch = [&](ll x) -> string {
        string s;
        rep(i, 6) {
            if (x & (1<<i)) s += 'a';
            else s += 'b';
        }
        return s;
    };
    rep(i, 1<<6) rep(j, 1<<6) {
        string sj = ch(j);
        // sj に 何かを足して si にできる？
        string si = ch(i);
        // sj に足すべきはsiの末尾
        string t = sj + si.back();
        
        bool ok = true;
        rep(k, 6) if (t[k + 1] != si[k]) ok = false;
        if (!ok) continue;

        if (check(t)) {
            A[i][j] += 1; 
        }
    }




    Matrix<Mint> B = A.pow(N - loop);
    Matrix<Mint> base((1<<6), 1);
    rep(i, 1<<6) base[i][0] = dp1[ch(i)];
    Matrix<Mint> C = B * base;

    Mint ans = 0;
    rep(i, 1<<6) ans += C[i][0];

    OUT(ans);



    
}