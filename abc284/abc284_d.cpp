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

vll primes;

struct Eratos{
  public:
    
    Eratos(int _Eramax = 1e6){
        Eramax = _Eramax;
        E.resize(Eramax + 1);
        for(int i = 0; i < Eramax + 1; i++) E[i] = i;
        for(int i = 2; i < Eramax + 1; i++) if(E[i] == i){
            for(int j = 2 * i; j < Eramax + 1; j += i) E[j] = i;
        }
        E[1] = -1;
    }

    vector<int> factorize(int n){
        assert(n <= Eramax);
        vector<int> ret;
        while(n != 1){
            ret.push_back(E[n]);
            n /= E[n];
        }
        return ret;
    }

    vector<int> divisor(int n){
        assert(n <= Eramax);
        vector<int> fact = factorize(n);
        map<int, int> cnt;
        vector<int> list;
        for(auto x: fact) cnt[x]++;
        for(auto [k, v]: cnt) list.push_back(k);
        vector<int> ret;

        auto dfs = [&](auto&& self, int n, int x) -> void {
            if(n == list.size()){
                ret.pb(x); return;
            }
            for(int u = 0; u <= cnt[list[n]]; u++){
                self(self, n + 1, x * pow(list[n], u));
            }
        };
        dfs(dfs, 0, 1);
        return ret;
    }

    bool is_prime(int x){
        assert(x <= Eramax);
        return x == E[x];
    }

  private:
    vector<int> E;
    int Eramax;
    int pow(int a, int n){
        int ret = 1;
        while(n > 0){
            if(n & 1) ret = ret * a;
            a *= a;
            n >>= 1;
        }
        return ret;
    }

};

void solve() {

    LL(N);

    ll x;
    fore(p, primes) {
        if (N % p == 0) {
            x = p;
            break;
        }
    }

    if ((N / x) % x == 0) {
        ll y = (N / x) / x;
        OUT(x, y);
    } else {

        ll ok = 1, ng = 1;
        while (ng * ng <= N / x) ng *= 2;
        while (abs(ok - ng) > 1) {
            ll mid = (ok + ng) / 2;
            if (mid * mid <= N / x) ok = mid;
            else ng = mid;
        }

        OUT(ok, x);

    }

}



int main() {

    Eratos era(3000100);
    for (ll x = 2; x <= 3000010; x++) {
        if (era.is_prime(x)) primes.pb(x);
    }

    LL(T);
    while (T--) {
        solve();
    }

}