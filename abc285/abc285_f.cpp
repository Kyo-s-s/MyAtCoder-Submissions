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
template<class M> struct Segtree {
  public:
    using S = typename M::T;

    Segtree() : Segtree(0) {}
    Segtree(int n) : Segtree(vector<S> (n, M::e())) {}
    Segtree(const vector<S> &v) : n(int(v.size())) { 
        while((1 << log) < n) log++;
        size = 1 << log;
        d = vector<S> (2 * size, M::e());
        for(int i = 0; i < n; i++) d[size + i] = v[i];
        for(int i = size- 1; i >= 1; i--) update(i);
    }

    void set(int p, S x){
        assert(0 <= p && p < n);
        p += size;
        d[p] = x;
        for(int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p){
        assert(0 <= p && p < n);
        return d[p + size];
    }

    S prod(int l, int r){
        assert(0 <= l && l <= r && r <= n);
        S sml = M::e(), smr = M::e();
        l += size; r += size;
        while(l < r){
            if(l & 1) sml = M::op(sml, d[l++]);
            if(r & 1) smr = M::op(d[--r], smr);
            l >>= 1; r >>= 1;
        }
        return M::op(sml, smr);
    }

    S all_prod(){ return d[1]; }


  private:
    int n, size, log = 0;
    vector<S> d;
    void update(int k){ d[k] = M::op(d[k * 2], d[k * 2 + 1]); }

};

struct R {
    bool ok;
    int l, r;
};

struct Monoid {
    // struct T {
    //     bool ok;
    //     int l, r;
    // };
    using T = R;

    static T op(T a, T b) {
        if (!a.ok || !b.ok) return {false, 0, 0};
        if (a.r <= b.l) return {true, a.l, b.r};
        return {false, 0, 0};
    };

    static T e() {
        return {true, 100, -100};
    }
};

int main() {

    LL(N);
    // 0 ~ 25 
    STR(S);
    vi A;
    for (auto s : S) {
        A.pb(s - 'a');
    }

    vector<R> v(N);
    for (int i = 0; i < N; i++) {
        v[i] = {true, A[i], A[i]};
    }

    Segtree<Monoid> seg(v);

    vector<set<int>> st(26);
    for (int i = 0; i < N; i++) {
        st[A[i]].insert(i);
    }


    LL(Q);
    while (Q--) {
        LL(t);
        if (t == 1) {
            ll x; cin >> x; x--;
            char c; cin >> c;
            seg.set(x, {true, c - 'a', c - 'a'});

            st[A[x]].erase(x);
            A[x] = c - 'a';
            st[A[x]].insert(x);

        } else {
            ll l, r; cin >> l >> r; l--;

            auto ch = [&](int l, int r) {
                int start = A[l];
                int end = A[r - 1];
                if (start == end) return true;
                for (int x = start + 1; x < end; x++) {
                    // st[x] のあたいがすべて l と r の間にあるか
                    // l <= st[x] の最小値 かつ st[x] の最大値 <= r ならok
                    if (st[x].empty()) continue;
                    if (*st[x].begin() < l || r <= *st[x].rbegin()) return false;
                }
                return true;
            };

            if (seg.prod(l, r).ok && ch(l, r)) {
                OUT("Yes");
            } else {
                OUT("No");
            }

        }
    } 


}