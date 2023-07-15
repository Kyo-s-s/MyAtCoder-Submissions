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
template<class T> bool chmax(T &a, const T &b) {
    if(a<b) {
        a=b;
        return 1;
    }
    return 0;
}
template<class T> bool chmin(T &a, const T &b) {
    if(b<a) {
        a=b;
        return 1;
    }
    return 0;
}
#define debug(x) cerr << #x << ":" << x << "\n";

/* REP macro */
#define reps(i, a, n) for(ll i = (a); i < (n); i++)
#define rep(i, n) reps(i, 0, (n))
#define rrep(i, n) reps(i, 1, (n + 1))
#define repd(i, n) for(ll i = (n - 1); i >= 0; i--)
#define rrepd(i, n) for(ll i = (n); i >= 1; i--)
#define fore(i, a) for(auto &i: a)

/* vector */
template<class T> T vmax(vector<T> &array) {
    T ret = array[0];
    for(T a: array) chmax(ret, a);
    return ret;
}
template<class T> T vmin(vector<T> &array) {
    T ret = array[0];
    for(T a: array) chmin(ret, a);
    return ret;
}
template<class T> T sum(vector<T> &array) {
    T ret = 0;
    for(T a:array) ret += a;
    return ret;
}
template<class T> void list_set(vector<T> &array) {
    sort(all(array));
    array.erase(unique(all(array)),array.end());
}
template<class T> int bisect_left(vector<T> &array, T key) {
    return lower_bound(all(array),key) - array.begin();
}
template<class T> int bisect_right(vector<T> &array, T key) {
    return upper_bound(all(array),key) - array.begin();
}

/* string */
ll string_to_ll(string n) {
    ll ret = 0, k = 1;
    while(n.length() > 0) {
        ret += k * (n.back() - '0');
        n.pop_back();
        k *= 10;
    }
    return ret;
}
string ll_to_string(ll n) {
    string ret = "";
    while(n > 0) {
        ret.pb((n % 10) + '0');
        n /= 10;
    }
    reverse(all(ret));
    return ret;
}

struct popopo {
    popopo() {
        cin.tie(0);
        ios::sync_with_stdio(0);
        cout << fixed << setprecision(15);
    };
} popopoppo;

// n = 1,...,N に対して、n % A < B を満たすものの数
ll Count_of_n_mod_A_less_than_B(ll N, ll A, ll B) {
    return N / A * min(A, B) + min(N % A, B - 1);
}

bool include(ll l, ll r, ll x) {
    return l <= x && x < r;
}

/* IN/OUT */
int scan() {
    return getchar();
}
void scan(int &a) {
    cin >> a;
}
void scan(long long &a) {
    cin >> a;
}
void scan(char &a) {
    cin >> a;
}
void scan(double &a) {
    cin >> a;
}
void scan(string &a) {
    cin >> a;
}
template <class T, class S> void scan(pair<T, S> &p) {
    scan(p.first), scan(p.second);
}
template <class T> void scan(vector<T> &);
template <class T> void scan(vector<T> &a) {
    for(auto &i : a) scan(i);
}

void IN() {}
template<class Head, class... Tail> void IN(Head& head, Tail &...tail) {
    scan(head);
    IN(tail...);
}

#define INT(...) int __VA_ARGS__; IN(__VA_ARGS__)
#define LL(...) ll __VA_ARGS__; IN(__VA_ARGS__)
#define STR(...) string __VA_ARGS__; IN(__VA_ARGS__)
#define VEC(type, name, size) vector<type> name(size); IN(name)
#define VECS(type, name, size) vector<type> name(size + 1); for(int i = 1; i <= size; i++) scan(name[i])

void OUT() {
    cout << "\n";
}
template<class T> void output(T a) {
    cout << a;
}
template<class T> void output(vector<T> v) {
    for(int i = 0; i < v.size(); i++) cout << v[i] << (i == v.size() - 1 ? "" : " ");
}
template<class Head, class... Tail> void OUT(const Head &head, const Tail &...tail) {
    output(head);
    if(sizeof...(tail)) cout << " ";
    OUT(tail...);
}

void FLASH() {
    cout << endl;
}
template<class Head, class... Tail> void FLASH(const Head  &head, const Tail &...tail) {
    output(head);
    if(sizeof...(tail)) cout << " ";
    FLASH(tail...);
}

namespace kyo {

long long bisect(long long ok, long long ng, function<bool(long long)> is_ok) {
    while (abs(ok - ng) > 1) {
        long long mid = ok + (ng - ok) / 2;
        (is_ok(mid) ? ok : ng) = mid;
    }
    return ok;
}

}

template<int m> struct StaticModint {
    using mint = StaticModint;
public:
    static constexpr int mod() {
        return m;
    } static mint raw(int v) {
        mint x;
        x._v = v;
        return x;
    } StaticModint() : _v(0) {} template <class T> StaticModint(T v) {
        long long x = (long long)(v % (long long)(umod()));
        if (x < 0) x += umod();
        _v = (unsigned int)(x);
    } unsigned int val() const {
        return _v;
    } mint& operator++() {
        _v++;
        if (_v == umod()) _v = 0;
        return *this;
    } mint& operator--() {
        if (_v == 0) _v = umod();
        _v--;
        return *this;
    } mint operator++(int) {
        mint result = *this;
        ++*this;
        return result;
    } mint operator--(int) {
        mint result = *this;
        --*this;
        return result;
    } mint& operator+=(const mint& rhs) {
        _v += rhs._v;
        if (_v >= umod()) _v -= umod();
        return *this;
    } mint& operator-=(const mint& rhs) {
        _v -= rhs._v;
        if (_v >= umod()) _v += umod();
        return *this;
    } mint& operator*=(const mint& rhs) {
        unsigned long long z = _v;
        z *= rhs._v;
        _v = (unsigned int)(z % umod());
        return *this;
    } mint& operator/=(const mint& rhs) {
        return *this = *this * rhs.inv();
    } mint operator+() const {
        return *this;
    } mint operator-() const {
        return mint() - *this;
    } mint pow(long long n) const {
        assert(0 <= n);
        mint x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    } mint inv() const {
        assert(_v);
        return pow(umod() - 2);
    } friend mint operator+(const mint& lhs, const mint& rhs) {
        return mint(lhs) += rhs;
    } friend mint operator-(const mint& lhs, const mint& rhs) {
        return mint(lhs) -= rhs;
    } friend mint operator*(const mint& lhs, const mint& rhs) {
        return mint(lhs) *= rhs;
    } friend mint operator/(const mint& lhs, const mint& rhs) {
        return mint(lhs) /= rhs;
    } friend bool operator==(const mint& lhs, const mint& rhs) {
        return lhs._v == rhs._v;
    } friend bool operator!=(const mint& lhs, const mint& rhs) {
        return lhs._v != rhs._v;
    } friend ostream &operator<<(ostream &os, mint x) {
        os << x.val();
        return (os);
    } private:
    unsigned int _v;
    static constexpr unsigned int umod() {
        return m;
    }
};
using Modint998244353 = StaticModint<998244353>;
using Modint1000000007 = StaticModint<1000000007>;
using Mint = Modint998244353;

template<class T> struct Enumeration {
public:
    Enumeration(int sz = 0) {
        update(sz);
    } T fact(int k) {
        update(k);
        return _fact[k];
    } T finv(int k) {
        update(k);
        return _finv[k];
    } T inv(int k) {
        update(k);
        return _inv[k];
    } T nPk(int n, int k) {
        if(k < 0 || n < k) return 0;
        return fact(n) * finv(n - k);
    } T nCk(int n, int k) {
        if(k < 0 || n < k) return 0;
        return fact(n) * finv(k) * finv(n - k);
    } T nHk(int n, int k) {
        if(n < 0 || k < 0) return 0;
        if(n == 0) return 1;
        else return nCk(n + k - 1, k);
    } T Catalan(int n) {
        return nCk(2*n, n) - nCk(2*n, n-1);
    } private:
    vector<T> _fact, _finv, _inv;
    void update(int sz) {
        if(_fact.size() < sz + 1) {
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

int main() {

    LL(N);
    STR(S);
    
    ll o = 0, l = 0;
    ll ans = 0;
    
    auto op = [&](int a, int b) {
        if (a == 1 && b == 1) return 0;
        return 1;
    };
    
    
    rep(i, N) {
        ll no = 0, nl = 0;
        int nxt = S[i] - '0';
        (op(0, nxt) == 0 ? no : nl) += o;
        (op(1, nxt) == 0 ? no : nl) += l;
        (nxt == 0 ? no : nl)++;
        ans += nl;
        o = no; l = nl;
    }
    OUT(ans);
}







    