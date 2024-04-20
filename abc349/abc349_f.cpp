#ifdef INCLUDED_MAIN


// #line 2 "/Users/noya2/Desktop/Noya2_library/template/template.hpp"
// using namespace std;

// #include<bits/stdc++.h>
// #line 1 "/Users/noya2/Desktop/Noya2_library/template/inout_old.hpp"
// namespace noya2 {

// template <typename T, typename U>
// ostream &operator<<(ostream &os, const pair<T, U> &p){
//     os << p.first << " " << p.second;
//     return os;
// }
// template <typename T, typename U>
// istream &operator>>(istream &is, pair<T, U> &p){
//     is >> p.first >> p.second;
//     return is;
// }

// template <typename T>
// ostream &operator<<(ostream &os, const vector<T> &v){
//     int s = (int)v.size();
//     for (int i = 0; i < s; i++) os << (i ? " " : "") << v[i];
//     return os;
// }
// template <typename T>
// istream &operator>>(istream &is, vector<T> &v){
//     for (auto &x : v) is >> x;
//     return is;
// }

// void in() {}
// template <typename T, class... U>
// void in(T &t, U &...u){
//     cin >> t;
//     in(u...);
// }

// void out() { cout << "\n"; }
// template <typename T, class... U, char sep = ' '>
// void out(const T &t, const U &...u){
//     cout << t;
//     if (sizeof...(u)) cout << sep;
//     out(u...);
// }

// template<typename T>
// void out(const vector<vector<T>> &vv){
//     int s = (int)vv.size();
//     for (int i = 0; i < s; i++) out(vv[i]);
// }

// struct IoSetup {
//     IoSetup(){
//         cin.tie(nullptr);
//         ios::sync_with_stdio(false);
//         cout << fixed << setprecision(15);
//         cerr << fixed << setprecision(7);
//     }
// } iosetup_noya2;

// } // namespace noya2
// #line 1 "/Users/noya2/Desktop/Noya2_library/template/const.hpp"
// namespace noya2{

// const int iinf = 1'000'000'007;
// const long long linf = 2'000'000'000'000'000'000LL;
// const long long mod998 =  998244353;
// const long long mod107 = 1000000007;
// const long double pi = 3.14159265358979323;
// const vector<int> dx = {0,1,0,-1,1,1,-1,-1};
// const vector<int> dy = {1,0,-1,0,1,-1,-1,1};
// const string ALP = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
// const string alp = "abcdefghijklmnopqrstuvwxyz";
// const string NUM = "0123456789";

// void yes(){ cout << "Yes\n"; }
// void no(){ cout << "No\n"; }
// void YES(){ cout << "YES\n"; }
// void NO(){ cout << "NO\n"; }
// void yn(bool t){ t ? yes() : no(); }
// void YN(bool t){ t ? YES() : NO(); }

// } // namespace noya2
// #line 1 "/Users/noya2/Desktop/Noya2_library/template/utils.hpp"
// namespace noya2{

// unsigned long long inner_binary_gcd(unsigned long long a, unsigned long long b){
//     if (a == 0 || b == 0) return a + b;
//     int n = __builtin_ctzll(a); a >>= n;
//     int m = __builtin_ctzll(b); b >>= m;
//     while (a != b) {
//         int mm = __builtin_ctzll(a - b);
//         bool f = a > b;
//         unsigned long long c = f ? a : b;
//         b = f ? b : a;
//         a = (c - b) >> mm;
//     }
//     return a << min(n, m);
// }

// template<typename T> T gcd_fast(T a, T b){ return static_cast<T>(inner_binary_gcd(abs(a),abs(b))); }

// long long sqrt_fast(long long n) {
//     if (n <= 0) return 0;
//     long long x = sqrt(n);
//     while ((x + 1) * (x + 1) <= n) x++;
//     while (x * x > n) x--;
//     return x;
// }

// template<typename T> T floor_div(const T n, const T d) {
//     assert(d != 0);
//     return n / d - static_cast<T>((n ^ d) < 0 && n % d != 0);
// }

// template<typename T> T ceil_div(const T n, const T d) {
//     assert(d != 0);
//     return n / d + static_cast<T>((n ^ d) >= 0 && n % d != 0);
// }

// template<typename T> void uniq(vector<T> &v){
//     sort(v.begin(),v.end());
//     v.erase(unique(v.begin(),v.end()),v.end());
// }

// template <typename T, typename U> inline bool chmin(T &x, U y) { return (y < x) ? (x = y, true) : false; }

// template <typename T, typename U> inline bool chmax(T &x, U y) { return (x < y) ? (x = y, true) : false; }

// template<typename T> inline bool range(T l, T x, T r){ return l <= x && x < r; }

// } // namespace noya2
// #line 8 "/Users/noya2/Desktop/Noya2_library/template/template.hpp"

// #define rep(i,n) for (int i = 0; i < (int)(n); i++)
// #define repp(i,m,n) for (int i = (m); i < (int)(n); i++)
// #define reb(i,n) for (int i = (int)(n-1); i >= 0; i--)
// #define all(v) (v).begin(),(v).end()

// using ll = long long;
// using ld = long double;
// using uint = unsigned int;
// using ull = unsigned long long;
// using pii = pair<int,int>;
// using pll = pair<ll,ll>;
// using pil = pair<int,ll>;
// using pli = pair<ll,int>;

// namespace noya2{

// /*　~ (. _________ . /)　*/

// }

// using namespace noya2;


// #line 2 "c.cpp"

// #line 2 "/Users/noya2/Desktop/Noya2_library/math/factorize.hpp"

// #line 6 "/Users/noya2/Desktop/Noya2_library/math/factorize.hpp"
// #include <initializer_list>
// #line 10 "/Users/noya2/Desktop/Noya2_library/math/factorize.hpp"

// namespace fast_factorize {

// /*
//     See : https://judge.yosupo.jp/submission/189742
// */

// // ---- gcd ----

// uint64_t gcd_stein_impl( uint64_t x, uint64_t y ) {
//     if( x == y ) { return x; }
//     const uint64_t a = y - x;
//     const uint64_t b = x - y;
//     const int n = __builtin_ctzll( b );
//     const uint64_t s = x < y ? a : b;
//     const uint64_t t = x < y ? x : y;
//     return gcd_stein_impl( s >> n, t );
// }

// uint64_t gcd_stein( uint64_t x, uint64_t y ) {
//     if( x == 0 ) { return y; }
//     if( y == 0 ) { return x; }
//     const int n = __builtin_ctzll( x );
//     const int m = __builtin_ctzll( y );
//     return gcd_stein_impl( x >> n, y >> m ) << ( n < m ? n : m );
// }

// // ---- is_prime ----

// uint64_t mod_pow( uint64_t x, uint64_t y, uint64_t mod ) {
//     uint64_t ret = 1;
//     uint64_t acc = x;
//     for( ; y; y >>= 1 ) {
//         if( y & 1 ) {
//             ret = __uint128_t(ret) * acc % mod;
//         }
//         acc = __uint128_t(acc) * acc % mod;
//     }
//     return ret;
// }

// bool miller_rabin( uint64_t n, const std::initializer_list<uint64_t>& as ) {
//     return std::all_of( as.begin(), as.end(), [n]( uint64_t a ) {
//         if( n <= a ) { return true; }

//         int e = __builtin_ctzll( n - 1 );
//         uint64_t z = mod_pow( a, ( n - 1 ) >> e, n );
//         if( z == 1 || z == n - 1 ) { return true; }

//         while( --e ) {
//             z = __uint128_t(z) * z % n;
//             if( z == 1 ) { return false; }
//             if( z == n - 1 ) { return true; }
//         }

//         return false;
//     });
// }

// bool is_prime( uint64_t n ) {
//     if( n == 2 ) { return true; }
//     if( n % 2 == 0 ) { return false; }
//     if( n < 4759123141 ) { return miller_rabin( n, { 2, 7, 61 } ); }
//     return miller_rabin( n, { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 } );
// }

// // ---- Montgomery ----

// class Montgomery {
//     uint64_t mod;
//     uint64_t R;
// public:
//     Montgomery( uint64_t n ) : mod(n), R(n) {
//        for( size_t i = 0; i < 5; ++i ) {
//           R *= 2 - mod * R;
//        }
//     }

//     uint64_t fma( uint64_t a, uint64_t b, uint64_t c ) const {
//         const __uint128_t d = __uint128_t(a) * b;
//         const uint64_t    e = c + mod + ( d >> 64 );
//         const uint64_t    f = uint64_t(d) * R;
//         const uint64_t    g = ( __uint128_t(f) * mod ) >> 64;
//         return e - g;
//     }

//     uint64_t mul( uint64_t a, uint64_t b ) const {
//         return fma( a, b, 0 );
//     }
// };

// // ---- Pollard's rho algorithm ----

// uint64_t pollard_rho( uint64_t n ) {
//     if( n % 2 == 0 ) { return 2; }
//     const Montgomery m( n );

//     constexpr uint64_t C1 = 1;
//     constexpr uint64_t C2 = 2;
//     constexpr uint64_t M = 512;

//     uint64_t Z1 = 1;
//     uint64_t Z2 = 2;
// retry:
//     uint64_t z1 = Z1;
//     uint64_t z2 = Z2;
//     for( size_t k = M; ; k *= 2 ) {
//         const uint64_t x1 = z1 + n;
//         const uint64_t x2 = z2 + n;
//         for( size_t j = 0; j < k; j += M ) {
//             const uint64_t y1 = z1;
//             const uint64_t y2 = z2;

//             uint64_t q1 = 1;
//             uint64_t q2 = 2;
//             z1 = m.fma( z1, z1, C1 );
//             z2 = m.fma( z2, z2, C2 );
//             for( size_t i = 0; i < M; ++i ) {
//                 const uint64_t t1 = x1 - z1;
//                 const uint64_t t2 = x2 - z2;
//                 z1 = m.fma( z1, z1, C1 );
//                 z2 = m.fma( z2, z2, C2 );
//                 q1 = m.mul( q1, t1 );
//                 q2 = m.mul( q2, t2 );
//             }
//             q1 = m.mul( q1, x1 - z1 );
//             q2 = m.mul( q2, x2 - z2 );

//             const uint64_t q3 = m.mul( q1, q2 );
//             const uint64_t g3 = gcd_stein( n, q3 );
//             if( g3 == 1 ) { continue; }
//             if( g3 != n ) { return g3; }

//             const uint64_t g1 = gcd_stein( n, q1 );
//             const uint64_t g2 = gcd_stein( n, q2 );

//             const uint64_t C = g1 != 1 ? C1 : C2;
//             const uint64_t x = g1 != 1 ? x1 : x2;
//             uint64_t       z = g1 != 1 ? y1 : y2;
//             uint64_t       g = g1 != 1 ? g1 : g2;

//             if( g == n ) {
//                 do {
//                     z = m.fma( z, z, C );
//                     g = gcd_stein( n, x - z );
//                 } while( g == 1 );
//             }
//             if( g != n ) {
//                 return g;
//             }

//             Z1 += 2;
//             Z2 += 2;
//             goto retry;
//         }
//     }
// }

// void factorize_impl( uint64_t n, std::vector<uint64_t>& ret ) {
//     if( n <= 1 ) { return; }
//     if( is_prime( n ) ) { ret.push_back( n ); return; }

//     const uint64_t p = pollard_rho( n );

//     factorize_impl( p, ret );
//     factorize_impl( n / p, ret );
// }

// std::vector<uint64_t> factorize( uint64_t n ) {
//     std::vector<uint64_t> ret;
//     factorize_impl( n, ret );
//     std::sort( ret.begin(), ret.end() );
//     return ret;
// }

// } // namespace fast_factorize

// namespace noya2 {

// std::vector<std::pair<long long, int>> factorize(long long n){
//     std::vector<std::pair<long long, int>> ans;
//     auto ps = fast_factorize::factorize(n);
//     int sz = ps.size();
//     for (int l = 0, r = 0; l < sz; l = r){
//         while (r < sz && ps[l] == ps[r]) r++;
//         ans.emplace_back(ps[l], r-l);
//     }
//     return ans;
// }

// std::vector<long long> divisors(long long n){
//     auto ps = fast_factorize::factorize(n);
//     int sz = ps.size();
//     std::vector<long long> ans = {1};
//     for (int l = 0, r = 0; l < sz; l = r){
//         while (r < sz && ps[l] == ps[r]) r++;
//         int e = r - l;
//         int len = ans.size();
//         ans.reserve(len*(e+1));
//         long long mul = ps[l];
//         while (true){
//             for (int i = 0; i < len; i++){
//                 ans.emplace_back(ans[i]*mul);
//             }
//             if (--e == 0) break;
//             mul *= ps[l];
//         }
//     }
//     return ans;
// }

// std::vector<long long> divisors(const std::vector<std::pair<long long, int>> &pes){
//     std::vector<long long> ans = {1};
//     for (auto [p, e] : pes){
//         int len = ans.size();
//         ans.reserve(len*(e+1));
//         long long mul = p;
//         while (true){
//             for (int i = 0; i < len; i++){
//                 ans.emplace_back(ans[i]*mul);
//             }
//             if (--e == 0) break;
//             mul *= p;
//         }
//     }
//     return ans;
// }

// } // namespace noya2

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


vector<pair<ll, int>> factorize(ll n) {
    vector<pair<ll, int>> ans;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int cnt = 0;
            while (n % i == 0) {
                n /= i;
                cnt++;
            }
            ans.emplace_back(i, cnt);
        }
    }
    if (n != 1) ans.emplace_back(n, 1);
    return ans;
}

int main() {

    LL(N, M);
    VEC(ll, A, N);


    if (M == 1) {
        ll oc = 0;
        fore(a, A) if (a == 1) oc += 1;
        OUT(Mint(2).pow(oc) - 1);
        exit(0);
    }

    // auto fac = noya2::factorize(M);
    auto fac = factorize(M);

    ll m = fac.size();

    map<ll, ll> cnt;
    for (auto a : A) {
        ll bs = 0;
        bool ok = true;
        for(auto [p, c] : fac) {
            bs *= 2;
            if ([&]() {
                rep(u, c) {
                    if (a % p == 0) {
                        a /= p;
                    } else {
                        return false;
                    }
                }
                if (a % p == 0) {
                    ok = false; return false;
                }
                return true;
            }()) {
                bs++;
            }
        }

        if (ok && a == 1) {
            cnt[bs]++;
        }
    }

    vector<Mint> dp(1 << m, 0);
    dp[0] = 1;

    for (auto [b, c] : cnt) {
        if (c == 0) continue;
        vector<Mint> pd = dp;
        // 一つ以上選ぶ
        Mint k = Mint(2).pow(c) - Mint(1);
        for (int state = 0; state < (1 << m); state++) {
            pd[state | b] += dp[state] * k;
        }
        swap(dp, pd);
    }

    OUT(dp[(1 << m) - 1]);

}

/*

D: 再帰セグ木
E: やる
F: M = 1 のときをやめてください！ 普通にバカなWAを何度か投げてしまった
   こんなの難しくて通されないだろ～と思って油断していた
   https://mofecoder.com/contests/cyan_or_less_01/tasks/cyan_or_less_01_h を思い出した(？)

*/

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
