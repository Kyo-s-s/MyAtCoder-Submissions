#ifdef INCLUDED_MAIN

struct mp {
    vi a, b;
    mp(ll n) {
        a = vector(n, -1);
        b = vector(n, -1);
    }

    void set(int i, int x) {
        a[i] = x;
        b[x] = i;
    }

    int apply(int x) {
        return a[x];
    }

    int rev(int x) {
        return b[x];
    }
};

int main() {

    LL(N, Q);


    // boxes[i] := 箱 i に入っているボールの番号
    vector<set<ll>> boxes(N);

    // 箱 -> 箱
    // vector<ll> sw(N);
    mp sw(N);
    // idx[i] := ボール i が入っている箱の番号
    vector<ll> idx(N + Q);
    rep(i, N) {
        sw.set(i, i);
        idx[i] = i;
        boxes[sw.apply(i)].insert(i);
    }

    ll nxt = N; 

    while (Q--) {

        // cout << "==============" << endl;
        // rep(i, N) {
        //     cout << "| [" + to_string(i + 1) + "]: ";
        //     for (auto x : boxes[i]) {
        //         cout << x + 1 << " ";
        //     }
        // }
        // cout << endl;
        // rep(i, N) {
        //     cout << "| " << i + 1 << " -> " << sw[i] + 1 << ", ";
        // }
        // cout << endl;


        LL(t);

        if (t == 1) {
            LL(X, Y); X--; Y--;

            bool swa = boxes[sw.apply(X)].size() < boxes[sw.apply(Y)].size();
            if (swa) {
                swap(X, Y);
            }
            
            for (auto y : boxes[sw.apply(Y)]) {
                idx[y] = sw.apply(X);
                boxes[sw.apply(X)].insert(y);
            }
            boxes[sw.apply(Y)].clear();

            if (swa) {
                ll rx = sw.apply(X);
                ll ry = sw.apply(Y);
                sw.set(X, ry);
                sw.set(Y, rx);
            }

        } else if (t == 2) {
            LL(X); X--;

            idx[nxt] = sw.apply(X);   
            boxes[sw.apply(X)].insert(nxt);
            nxt++;
        } else {
            LL(X); X--;

            OUT(sw.rev(idx[X]) + 1);
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
