#ifdef INCLUDED_MAIN

template <class T> struct eraseble_priority_queue {
    priority_queue<T> q, e;

    void push(T x) { q.push(x); }

    void erase(T x) { e.push(x); }

    T top() {
        while (e.size() && q.top() == e.top()) {
            q.pop();
            e.pop();
        }
        return q.empty() ? 0 : q.top();
    }

    void pop() {
        top();
        q.pop();
    }
};

template<typename T> 
concept Monoid = requires {
    typename T::T;
    { T::op(std::declval<typename T::T>(), std::declval<typename T::T>()) } -> std::same_as<typename T::T>;
    { T::e() } -> std::same_as<typename T::T>;
};

template<class T>
struct MergeTree {
  public:

    MergeTree(int n, std::function<T(int, int)> f) : n(n) {
        while((1 << log) < n) log++;
        size = 1 << log;
        d = vector<T> (2 * size, T());
        auto init = [&](auto &&init, int l, int r, int k) -> void {
            d[k] = f(l, min(r, n));
            if((int)d.size() <= 2 * k) return;
            int m = (l + r) / 2;
            init(init, l, m, 2 * k);
            init(init, m, r, 2 * k + 1);
        };
        init(init, 0, size, 1);
    }

    void apply(int l, int r, std::function<void(T&)> g) {
        assert(0 <= l && l <= r && r <= n);
        l += size; r += size;
        while (l < r) {
            if (l & 1) g(d[l++]);
            if (r & 1) g(d[--r]);
            l >>= 1; r >>= 1;
        }
    }

    template<Monoid M> M::T get(int i, std::function<typename M::T(T&)> g) {
        assert(0 <= i && i < n);
        typename M::T res = M::e();
        i += size;
        while (i > 0) {
            res = M::op(res, g(d[i]));
            i >>= 1;
        }
        return res;
    }

    template<Monoid M> M::T prod(int l, int r, std::function<typename M::T(const T&)> g) {
        assert(0 <= l && l <= r && r <= n);
        typename M::T sml = M::e(), smr = M::e();
        l += size; r += size;
        while (l < r) {
            if (l & 1) sml = M::op(sml, g(d[l++]));
            if (r & 1) smr = M::op(g(d[--r]), smr);
            l >>= 1; r >>= 1;
        }
        return M::op(sml, smr);
    }

  private:
    int n, size, log = 0;
    vector<T> d;
};

struct Max_M {
    using T = ll;
    static T e() { return -INF; }
    static T op(T x, T y) { return max(x, y); }
};

int main() {

    LL(N);
    VEC(ll, A, N);

    MergeTree<eraseble_priority_queue<ll>> tree(N, [&](int l, int r) {
        eraseble_priority_queue<ll> ret;
        if (l + 1 == r) {
            ret.push(A[l]);
        }
        return ret;
    });

    LL(Q);
    vector<tuple<ll, ll, ll>> que(Q);

    rep(q, Q) {
        LL(t);

        if (t == 1) {
            LL(l, r, x); l--; r--;
            que[q] = {l, r, x};
            tree.apply(l, r + 1, [&](eraseble_priority_queue<ll> &q) {
                q.push(x);
            });
        }

        if (t == 2) {
            LL(i); i--;
            auto [l, r, x] = que[i];
            tree.apply(l, r + 1, [&](eraseble_priority_queue<ll> &q) {
                q.erase(x);
            });
        }

        if (t == 3) {
            LL(i); i--;
            ll ans = tree.get<Max_M>(i, [&](eraseble_priority_queue<ll> &q) -> ll {
                return q.top();
            });
            OUT(ans);
        }

    }

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
