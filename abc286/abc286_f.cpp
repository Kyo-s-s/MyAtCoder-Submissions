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

// struct popopo{ popopo(){ cin.tie(0); ios::sync_with_stdio(0); cout << fixed << setprecision(15); }; } popopoppo;

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


long long ext_gcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    long long x2, y2;
    long long d = ext_gcd(b, a%b, x2, y2);
    x = y2;
    y = x2 - (a / b)*y2;
    return d;
}

// m を法としたときの a のモジュラ逆数を計算
long long mod_inv(long long a, long long m) {
	long long x, y;
	long long d = ext_gcd(a, m, x, y);
	if (d != 1) {
		// モジュラ逆数が存在しない
		return -1;
	}
	x %= m;
	if (x < 0)x += m;  // 負の数の剰余を考慮
	return x;
}
long long garner(vector<long long> r, vector<long long> m) {
	int n = r.size();
	long long m_prod = 1;       // m_prod には m[i] の積を入れていく
	long long x = r[0] % m[0];  // 最初の条件を満たすような x の初期値
	for (int i = 1; i < n; i++) {
		m_prod *= m[i - 1];     // m の累積積を更新
		long long t = ((r[i] - x) * mod_inv(m_prod, m[i])) % m[i];
		if (t < 0)t += m[i];    // 負の数の剰余の対策
		x += t * m_prod;        // x を更新
	}
	return x;
}

vll primes = {4, 9, 5, 7, 11, 13, 17, 19, 23};

ll solve(vll A, vll B) {

    // 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 
    // 6469693230


    // 2, 3, 5, 7, 11, 13, 17, 19, 23, 29,  
    vll moood;
    ll st = 1;
    for (auto p : primes) {
        ll b = -1;
        rep (i, B.size()) {
            if (B[i] == st) {
                b = i + 1;
                break;
            }
        }

        ll sa = (10 * p - (b - st)) % p;
        moood.pb(sa);
        st += p;
    }
    // OUT(primes);
    // OUT(moood);
    ll ans = garner(moood, primes);
    return ans;

}

vll generate_A() {

    vll A;

    int value = 1;
    for (auto p : primes) {
        deque<int> tmp;
        rep (i, p) {
            tmp.pb(value);
            value++;
        }

        ll s = tmp.front(); tmp.pop_front();
        tmp.pb(s);

        for (auto t : tmp) A.pb(t);
    }
    
    return A;

}

vll fn(vll A, ll n) {

    vll B(A.size());
    rep (i, B.size()) B[i] = i + 1;

    rep(i, n) {
        vll C(A.size());
        rep (j, C.size()) {
            C[j] = B[A[j] - 1];
        }
        B = C;
    }

    return B;

}

int main() {

    // ll N = 10000;
    // vll A = generate_A();
    // vll B = fn(A, N);
    // ll an = solve(A, B);
    // YesNo(an == N);
    // OUT(an);



    vll A = generate_A();
    cout << A.size() << endl;
    rep (i, A.size()) {
        cout << A[i];
        if (i == A.size() - 1) cout << endl;
        else cout << " ";
    }
    VEC(ll, B, A.size());

    ll ans = solve(A, B);
    cout << ans << endl;

}