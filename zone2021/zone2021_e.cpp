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


int main(){

    ll R, C; cin >> R >> C;
    vvll A(R + 1, vll(C)); rrep(r, R) rrep(c, C-1) cin >> A[r][c];
    vvll B(R, vll(C + 1)); rrep(r, R-1) rrep(c, C) cin >> B[r][c];

    vvll dist(R + 1, vll(C + 1, INF));

    min_priority_queue<pair<ll, pii>> que;
    que.push({0, {1, 1}});

    while(!que.empty()){
        auto [dis, now] = que.top(); que.pop();
        auto [r, c] = now;

        if(dis > dist[r][c]) continue;
        dist[r][c] = dis;
        
        if(c < C){
            if(chmin(dist[r][c+1], dis + A[r][c])) que.push({dis + A[r][c], {r, c+1}});
        }

        if(c > 1){
            if(chmin(dist[r][c-1], dis + A[r][c-1])) que.push({dis + A[r][c-1], {r, c-1}});
        }

        if(r < R){
            if(chmin(dist[r+1][c], dis + B[r][c])) que.push({dis + B[r][c], {r + 1, c}});
        }

        for(int i = 1; i < r; i++){
            if(chmin(dist[r-i][c], dis + 1 + i)) que.push({dis + 1 + i, {r - i, c}});
        }

    }

    cout << dist[R][C] << endl;

}