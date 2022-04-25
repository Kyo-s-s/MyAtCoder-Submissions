#pragma region header
#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;

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

// https://opt-cp.com/fps-implementation/
#define REP2(i, m, n) for (int i = (m); i < (n); ++i)
#define REP(i, n) REP2(i, 0, n)
#define DREP2(i, m, n) for (int i = (m)-1; i >= (n); --i)
#define DREP(i, n) DREP2(i, n, 0)

template<class T>
struct FormalPowerSeries : vector<T> {
    using vector<T>::vector;
    using vector<T>::operator=;
    using F = FormalPowerSeries;

    F operator-() const {
        F res(*this);
        for (auto &e : res) e = -e;
        return res;
    }
    F &operator*=(const T &g) {
        for (auto &e : *this) e *= g;
        return *this;
    }
    F &operator/=(const T &g) {
        assert(g != T(0));
        *this *= g.inv();
        return *this;
    }
    F &operator+=(const F &g) {
        int n = (*this).size(), m = g.size();
        REP(i, min(n, m)) (*this)[i] += g[i];
        return *this;
    }
    F &operator-=(const F &g) {
        int n = (*this).size(), m = g.size();
        REP(i, min(n, m)) (*this)[i] -= g[i];
        return *this;
    }
    F &operator<<=(const int d) {
        int n = (*this).size();
        (*this).insert((*this).begin(), d, 0);
        (*this).resize(n);
        return *this;
    }
    F &operator>>=(const int d) {
        int n = (*this).size();
        (*this).erase((*this).begin(), (*this).begin() + min(n, d));
        (*this).resize(n);
        return *this;
    }
    F inv(int d = -1) const {
        int n = (*this).size();
        assert(n != 0 && (*this)[0] != 0);
        if (d == -1) d = n;
        assert(d > 0);
        F res{(*this)[0].inv()};
        while (res.size() < d) {
            int m = size(res);
            F f(begin(*this), begin(*this) + min(n, 2*m));
            F r(res);
            f.resize(2*m), internal::butterfly(f);
            r.resize(2*m), internal::butterfly(r);
            REP(i, 2*m) f[i] *= r[i];
            internal::butterfly_inv(f);
            f.erase(f.begin(), f.begin() + m);
            f.resize(2*m), internal::butterfly(f);
            REP(i, 2*m) f[i] *= r[i];
            internal::butterfly_inv(f);
            T iz = T(2*m).inv(); iz *= -iz;
            REP(i, m) f[i] *= iz;
            res.insert(res.end(), f.begin(), f.begin() + m);
        }
        return {res.begin(), res.begin() + d};
    }

    // // fast: FMT-friendly modulus only
    // F &operator*=(const F &g) {
    //     int n = (*this).size();
    //     *this = convolution(*this, g);
    //     (*this).resize(n);
    //     return *this;
    // }
    // F &operator/=(const F &g) {
    //     int n = (*this).size();
    //     *this = convolution(*this, g.inv(n));
    //     (*this).resize(n);
    //     return *this;
    // }

    // // naive
    // F &operator*=(const F &g) {
    //     int n = (*this).size(), m = g.size();
    //     DREP(i, n) {
    //     (*this)[i] *= g[0];
    //     REP2(j, 1, min(i+1, m)) (*this)[i] += (*this)[i-j] * g[j];
    //     }
    //     return *this;
    // }
    // F &operator/=(const F &g) {
    //     assert(g[0] != T(0));
    //     T ig0 = g[0].inv();
    //     int n = (*this).size(), m = g.size();
    //     REP(i, n) {
    //     REP2(j, 1, min(i+1, m)) (*this)[i] -= (*this)[i-j] * g[j];
    //     (*this)[i] *= ig0;
    //     }
    //     return *this;
    // }

    // sparse
    F &operator*=(vector<pair<int, T>> g) {
        int n = (*this).size();
        auto [d, c] = g.front();
        if (d == 0) g.erase(g.begin());
        else c = 0;
        DREP(i, n) {
            (*this)[i] *= c;
            for (auto &[j, b] : g) {
                if (j > i) break;
                (*this)[i] += (*this)[i-j] * b;
            }
        }
        return *this;
    }
    F &operator/=(vector<pair<int, T>> g) {
        int n = (*this).size();
        auto [d, c] = g.front();
        assert(d == 0 && c != T(0));
        T ic = c.inv();
        g.erase(g.begin());
        REP(i, n) {
            for (auto &[j, b] : g) {
                if (j > i) break;
                (*this)[i] -= (*this)[i-j] * b;
            }
            (*this)[i] *= ic;
        }
        return *this;
    } 

    // multiply and divide (1 + cz^d)
    void multiply(const int d, const T c) { 
        int n = (*this).size();
        if (c == T(1)) DREP(i, n-d) (*this)[i+d] += (*this)[i];
        else if (c == T(-1)) DREP(i, n-d) (*this)[i+d] -= (*this)[i];
        else DREP(i, n-d) (*this)[i+d] += (*this)[i] * c;
    }
    void divide(const int d, const T c) {
        int n = (*this).size();
        if (c == T(1)) REP(i, n-d) (*this)[i+d] -= (*this)[i];
        else if (c == T(-1)) REP(i, n-d) (*this)[i+d] += (*this)[i];
        else REP(i, n-d) (*this)[i+d] -= (*this)[i] * c;
    }

    T eval(const T &a) const {
        T x(1), res(0);
        for (auto e : *this) res += e * x, x *= a;
        return res;
    }

    F operator*(const T &g) const { return F(*this) *= g; }
    F operator/(const T &g) const { return F(*this) /= g; }
    F operator+(const F &g) const { return F(*this) += g; }
    F operator-(const F &g) const { return F(*this) -= g; }
    F operator<<(const int d) const { return F(*this) <<= d; }
    F operator>>(const int d) const { return F(*this) >>= d; }
    F operator*(const F &g) const { return F(*this) *= g; }
    F operator/(const F &g) const { return F(*this) /= g; }
    F operator*(vector<pair<int, T>> g) const { return F(*this) *= g; }
    F operator/(vector<pair<int, T>> g) const { return F(*this) /= g; }
};

using mint = modint998244353;
using fps = FormalPowerSeries<mint>;
using sfps = vector<pair<int, mint>>;


// https://github.com/Kyo-s-s/Kyo_s_s_Library/blob/main/md/Enumeration.md
template<class T> struct Enumeration{
  public:
    Enumeration(int sz = 0) { update(sz); }

    T fact(int k) {
        update(k);
        return _fact[k];
    }

    T finv(int k) {
        update(k);
        return _finv[k];
    }

    T inv(int k) {
        update(k);
        return _inv[k];
    }

    T nPk(int n, int k) {
        if(k < 0 || n < k) return 0;
        return fact(n) * finv(n - k);
    }

    T nCk(int n, int k) {
        if(k < 0 || n < k) return 0;
        return fact(n) * finv(k) * finv(n - k);
    }

    T nHk(int n, int k) {
        if(n < 0 || k < 0) return 0;
        if(n == 0) return 1;
        else return nCk(n + k - 1, k);
    }

  private:
    vector<T> _fact, _finv, _inv;

    void update(int sz) {
        if(_fact.size() < sz + 1){
            int pre_sz = max(1, (int)_fact.size());
            _fact.resize(sz + 1, T(1));
            _finv.resize(sz + 1, T(1));
            _inv.resize(sz + 1, T(1));
            for(int i = pre_sz; i <= (int)sz; i++) {
                _fact[i] = _fact[i - 1] * T(i);
            }
            _finv[sz] = T(1) / _fact[sz];
            for(int i = (int)sz - 1; i >= pre_sz; i--) {
                _finv[i] = _finv[i + 1] * T(i + 1);
            }
            for(int i = pre_sz; i <= (int)sz; i++) {
                _inv[i] = _finv[i] * _fact[i - 1];
            }
        }
    }

};

int main(){

    ll N, M, K; cin >> N >> M >> K;

    Enumeration<mint> enu;
    
    vector<mint> A(K - N + 1, 0); //(1 - x^M)^N
    for(int r = 0; r <= N; r++){
        int k = M * r;
        mint a = enu.nCk(N, r) * (r % 2 == 1 ? -1 : 1);
        if(K - N + 1 > k) A[k] = a;
    }

    vector<mint> B(K - N + 1, 0); //(1 - x)^{-(N + 1)}
    int d = N + 1;
    for(int n = 0; n < K - N + 1; n++){
        B[n] = enu.nCk(n + d - 1, d - 1);
    }

    mint ans = 0;
    for(int i = 0; i <= K - N; i++){
        ans += A[i] * B[K - N - i];
    }

    cout << ans.val() << endl;
    
}