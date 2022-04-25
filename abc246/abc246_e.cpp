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



int main(){

    ll N; cin >> N;
    ll ax, ay; cin >> ax >> ay;
    ll bx, by; cin >> bx >> by;
    ax--; ay--; bx--; by--;

    vector<string> S(N); for(int i = 0; i < N; i++) cin >> S[i];
    map<int, pll> delta = {{0, {1, 1}}, {1, {1, -1}}, {2, {-1, 1}}, {3, {-1, -1}}};
    
    vector<vvll> dist(N, vvll(N, vll(4, INF)));
    rep(i, 4) dist[ax][ay][i] = 1;

    deque<tuple<ll, ll, int>> que;
    rep(i, 4) que.pb({ax, ay, i});

    while(!que.empty()){
        auto [nx, ny, d] = que.front(); que.pop_front();

        rep(i, 4){
            ll gx = nx + delta[i].fi, gy = ny + delta[i].se;
            if(!(0 <= gx && gx < N && 0 <= gy && gy < N)) continue;
            if(S[gx][gy] == '#') continue;
            if(i == d){
                if(dist[gx][gy][i] > dist[nx][ny][d]){
                    dist[gx][gy][i] = dist[nx][ny][d];
                    que.push_front({gx, gy, i});
                }
            }else{
                if(dist[gx][gy][i] > dist[nx][ny][d] + 1){
                    dist[gx][gy][i] = dist[nx][ny][d] + 1;
                    que.push_back({gx, gy, i});
                }
            }
        }

    }

    ll ans = INF;
    rep(i, 4) chmin(ans, dist[bx][by][i]);
    if(ans == INF) ans = -1;
    cout << ans << '\n';

} 