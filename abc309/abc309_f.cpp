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

;
template<class M> class DynamicSegtree {
  public:
    using S = typename M::T;

    DynamicSegtree() : DynamicSegtree(LONG_LONG_MAX / 2) {}
    DynamicSegtree(long long limit) : limit(limit), root(nullptr) {}

    void set(long long p, S x) {
        set(root, 0, limit, p, x);
    }

    S get(long long p) const {
        return get(root, 0, limit, p);
    }

    S prod(long long l, long long r) const {
        assert(l <= r);
        return prod(root, 0, limit, l, r);
    }

    S all_prod() const { return root ? root->product : M::e(); }

    void reset(long long l, long long r) {
        assert(l <= r);
        return reset(root, 0, limit, l, r);
    }

  private:
    struct node;
    using node_ptr = std::unique_ptr<node>;

    struct node {
        long long index;
        S value, product;
        node_ptr left, right;

        node(long long index, S value)
            : index(index),
              value(value),
              product(value),
              left(nullptr),
              right(nullptr) {}

        void update() {
            product = M::op(M::op(left ? left->product : M::e(), value),
                         right ? right->product : M::e());
        }
    };

    long long limit = LONG_LONG_MAX / 2;
    node_ptr root;

    void set(node_ptr& t, long long a, long long b, long long p, S x) const {
        if (!t) {
            t = std::make_unique<node>(p, x);
            return;
        }
        if (t->index == p) {
            t->value = x;
            t->update();
            return;
        }
        long long c = (a + b) >> 1;
        if (p < c) {
            if (t->index < p) std::swap(t->index, p), std::swap(t->value, x);
            set(t->left, a, c, p, x);
        } else {
            if (p < t->index) std::swap(p, t->index), std::swap(x, t->value);
            set(t->right, c, b, p, x);
        }
        t->update();
    }

    S get(const node_ptr& t, long long a, long long b, long long p) const {
        if (!t) return M::e();
        if (t->index == p) return t->value;
        long long c = (a + b) >> 1;
        if (p < c) return get(t->left, a, c, p);
        else return get(t->right, c, b, p);
    }

    S prod(const node_ptr& t, long long a, long long b, long long l, long long r) const {
        if (!t || b <= l || r <= a) return M::e();
        if (l <= a && b <= r) return t->product;
        long long c = (a + b) >> 1;
        S result = prod(t->left, a, c, l, r);
        if (l <= t->index && t->index < r) result = M::op(result, t->value);
        return M::op(result, prod(t->right, c, b, l, r));
    }

    void reset(node_ptr& t, long long a, long long b, long long l, long long r) const {
        if (!t || b <= l || r <= a) return;
        if (l <= a && b <= r) {
            t.reset();
            return;
        }
        long long c = (a + b) >> 1;
        reset(t->left, a, c, l, r);
        reset(t->right, c, b, l, r);
        t->update();
    }
};

struct M {
    using T = ll;
    static T op(T a, T b) { return min(a, b); }
    static T e() { return INF; }
};

int main() {
    
    LL(N);
    map<ll, vector<vector<ll>>> mp;
    rep(i, N) {
        VEC(ll, d, 3);
        sort(all(d));
        reverse(all(d));
        mp[d[0]].pb(d);
    }

    DynamicSegtree<M> seg(1000000000LL);

    bool ok = false;
    for (auto [e, v] : mp) {
        for (auto d : v) {
            ll a = d[0], b = d[1], c = d[2];
            ll x = seg.prod(0, b);
            if (x < c) {
                ok = true;
            }
        }
        for (auto d : v) {
            ll a = d[0], b = d[1], c = d[2];
            seg.set(b, min(seg.get(b), c));
        }
    }

    YesNo(ok);
}