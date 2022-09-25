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

#pragma endregion header    

#include <bits/stdc++.h>
using namespace std;

// https://atcoder.github.io/ac-library/document_ja/dsu.html 

struct dsu{
  public:
    dsu() : _n(0) {}
    dsu(int n):  _n(n), parent(n, -1) {}

    int marge(int a, int b){
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


struct Q {
    int type; // 0 -> x, 1 -> y, 2 -> z
    int i;
    int a, b;
    ll cost;
};

Q generateX(int i, ll cost) {
    return Q{0, i, 0, 0, cost};
}

Q generateY(int i, ll cost) {
    return Q{1, i, 0, 0, cost};
}

Q generateZ(int a, int b, ll cost) {
    return Q{2, 0, a, b, cost};
}

int main() {

    LL(N, M);
    vector<Q> queries;

    rep(i, N) {
        LL(x);
        queries.pb(generateX(i, x));
    }

    rep(i, N) {
        LL(y);
        queries.pb(generateY(i, y));
    }

    rep(i, M) {
        LL(a, b, z);
        queries.pb(generateZ(a - 1, b - 1, z));
    }

    sort(all(queries), [](Q a, Q b) {
        return a.cost < b.cost;
    });

    dsu uf00(N), uf01(N+1), uf10(N+1), uf11(N+2);
    ll ans00 = 0, ans01 = 0, ans10 = 0, ans11 = 0;


    for (auto q: queries) {

        if (q.type == 0) {  // 空港
            // uf00 none
            // uf01 none
            // uf10 
            if (!uf10.same(q.i, N)) {
                ans10 += q.cost;
                uf10.marge(q.i, N);
            }
            // uf11
            if (!uf11.same(q.i, N)) {
                ans11 += q.cost;
                uf11.marge(q.i, N);
            }
        } elif (q.type == 1) { // 港
            // uf00 none
            // uf01
            if (!uf01.same(q.i, N)) {
                ans01 += q.cost;
                uf01.marge(q.i, N);
            }
            // uf10 none
            // uf11
            if (!uf11.same(q.i, N + 1)) {
                ans11 += q.cost;
                uf11.marge(q.i, N + 1);
            }
        } else { // 道路
            // uf00
            if (!uf00.same(q.a, q.b)) {
                ans00 += q.cost;
                uf00.marge(q.a, q.b);
            }
            // uf01
            if (!uf01.same(q.a, q.b)) {
                ans01 += q.cost;
                uf01.marge(q.a, q.b);
            }
            // uf10
            if (!uf10.same(q.a, q.b)) {
                ans10 += q.cost;
                uf10.marge(q.a, q.b);
            }
            // uf11
            if (!uf11.same(q.a, q.b)) {
                ans11 += q.cost;
                uf11.marge(q.a, q.b);
            }
        }

    }

    ll ans = INF;
    if (uf00.size(0) == N) chmin(ans, ans00);
    if (uf01.size(0) == N + 1) chmin(ans, ans01);
    if (uf10.size(0) == N + 1) chmin(ans, ans10);
    if (uf11.size(0) == N + 2) chmin(ans, ans11);

    OUT(ans);

}