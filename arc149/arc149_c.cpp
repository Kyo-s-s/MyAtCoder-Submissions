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

void solve_gu(int N) {

    vvll A(N, vll(N, -1));

    vll gu0, gu1, gu2, ki0, ki1, ki2;
    rrep(i, N * N) {
        if (i <= 2) {
            if (i == 1) ki0.pb(i);
            if (i == 2) gu0.pb(i);
            continue;
        }
        if (i % 2 == 0) {
            if (i % 3 == 0) {
                gu0.pb(i);
            } elif (i % 3 == 1) {
                gu1.pb(i);
            } else {
                gu2.pb(i);
            }
        } else {
            if (i % 3 == 0) {
                ki0.pb(i);
            } elif (i % 3 == 1) {
                ki1.pb(i);
            } else {
                ki2.pb(i);
            }
        }
    } 



    rep(i, N) {
        if (gu1.size() > 0 && ki2.size() > 0) {
            A[N / 2 - 1][i] = gu1.back(); gu1.pop_back();
            A[N / 2][i] = ki2.back(); ki2.pop_back();
        } else {
            A[N / 2 - 1][i] = gu2.back(); gu2.pop_back();
            A[N / 2][i] = ki1.back(); ki1.pop_back();
        }
    }

    for (auto g: gu1) gu0.pb(g);
    for (auto g: gu2) gu0.pb(g);
    for (auto k: ki1) ki0.pb(k);
    for (auto k: ki2) ki0.pb(k);

    rep(i, N) rep(j, N) if (A[i][j] == -1) {
        if (i < N / 2) {
            A[i][j] = gu0.back(); gu0.pop_back();
        } else {
            A[i][j] = ki0.back(); ki0.pop_back();
        }
    }

    for (auto a: A) {
        OUT(a);
    }

}

void solve_ki(int N) {

    vvll A(N, vll(N, -1));

    vll gu0, gu1, gu2, ki0, ki1, ki2;
    rrep(i, N * N) {
        if (i % 2 == 0) {
            if (i % 3 == 0) {
                gu0.pb(i);
            } elif (i % 3 == 1) {
                gu1.pb(i);
            } else {
                gu2.pb(i);
            }
        } else {
            if (i % 3 == 0) {
                ki0.pb(i);
            } elif (i % 3 == 1) {
                ki1.pb(i);
            } else {
                ki2.pb(i);
            }
        }
    } 
    reverse(all(ki1));

    // 上：gu
    int p = N / 2;

    rep(i, N) {
        if (i == N / 2) p--;

        if (gu2.size() > 0 && ki1.size() > 0) {
            A[p][i] = gu2.back(); gu2.pop_back();
            A[p + 1][i] = ki1.back(); ki1.pop_back();
        } else {
            A[p][i] = gu1.back(); gu1.pop_back();
            A[p + 1][i] = ki2.back(); ki2.pop_back();
        }
    }

    for (auto g: gu1) gu0.pb(g);
    for (auto g: gu2) gu0.pb(g);
    for (auto k: ki1) ki0.pb(k);
    for (auto k: ki2) ki0.pb(k);

    rep(i, N) rep(j, N) if (A[i][j] == -1) {
        if (gu0.size() > 0) {
            A[i][j] = gu0.back(); gu0.pop_back();
        } else {
            A[i][j] = ki0.back(); ki0.pop_back();
        }
    }

    for (auto a: A) {
        OUT(a);
    }

}


int main() {

    LL(N);

    if ((N * N) % 2 == 0) {
        solve_gu(N);
    } else {
        solve_ki(N);
    }


}