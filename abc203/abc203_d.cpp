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

#pragma endregion header    

// struct syakutori {

//     void solve(int N, function<bool(int)> check, function<void(int)> add, function<void(int)> erase, function<void(int, int)> look){
//         int l = 0, r = 0;
//         while(r < N){
//             if(check(r)){
//                 add(r);
//                 r++;
//             }else if(l == r){
//                 r++; l++;
//             }else{
//                 erase(l);
//                 l++;
//             }
//             look(l, r);
//         }
//     }

// };

// int main(){

//     ll N; cin >> N;
//     vector<ll> A(N); for(int i = 0; i < N; i++) cin >> A[i];

    
//     vb use(100010, false);
//     int ans = 0;

//     auto check = [&](int i) -> bool {
//         return !use[A[i]];
//     };

//     auto add = [&](int i) -> void {
//         use[A[i]] = true;
//     };

//     auto erase = [&](int i) -> void {
//         use[A[i]] = false;
//     };

//     auto look = [&](int l, int r) -> void {
//         chmax(ans, r - l);
//     };

//     syakutori sy;
//     sy.solve(N, check, add, erase, look);

//     cout << ans << '\n';

// }

template< class T >
struct CumulativeSum2D {
  vector< vector< T > > data;

  CumulativeSum2D(int W, int H) : data(W + 1, vector< T >(H + 1, 0)) {}

  void add(int x, int y, T z) {
    ++x, ++y;
    if(x >= data.size() || y >= data[0].size()) return;
    data[x][y] += z;
  }

  void build() {
    for(int i = 1; i < data.size(); i++) {
      for(int j = 1; j < data[i].size(); j++) {
        data[i][j] += data[i][j - 1] + data[i - 1][j] - data[i - 1][j - 1];
      }
    }
  }

  T query(int sx, int sy, int gx, int gy) const {
    return (data[gx][gy] - data[sx][gy] - data[gx][sy] + data[sx][sy]);
  }
};

int main(){

    ll N, K; cin >> N >> K;
    vvll A(N, vll(N));
    rep(i, N) rep(j, N) cin >> A[i][j];

    auto solve = [&](ll x) -> bool {

        CumulativeSum2D<ll> cum(N, N);
        rep(i, N) rep(j, N) cum.add(i, j, (A[i][j] <= x) ? 1 : 0);
        cum.build();
        rep(i, N - K + 1) rep(j, N - K + 1){
            if(cum.query(i, j, i + K, j + K) >= (K * K + 1) / 2) return true;
        }
        return false;
        // rep(i, N - K + 1){
        //     ll su = 0;
        //     rep(j, N - K + 1){
        //         if(j == 0){
        //             rep(di, K) rep(dj, K){
        //                 su += (A[i + di][j + dj] <= x);
        //             }
        //         }else{
        //             rep(di, K){
        //                 su -= (A[i + di][j - 1] <= x);
        //                 su += (A[i + di][j + K - 1] <= x);
        //             }
        //         }

        //         // cout << x << " " << i << " " << j << " " << su  << endl;

        //         if(su >= (K * K + 1) / 2){
        //             return true;
        //         }
        //     }
        // }
        // return false;
    };
    
    // ll ok = 0, ng = 10000000000, mid;
    ll ok = 10000000000, ng = -1, mid;
    while(abs(ok - ng) > 1){
        mid = (ok + ng) / 2;
        if(solve(mid)) ok = mid;
        else ng = mid;
    }

    cout << ok << '\n';

}