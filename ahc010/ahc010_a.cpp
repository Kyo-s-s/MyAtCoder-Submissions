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

unsigned int randxor(){
    static unsigned int x=123456789,y=362436069,z=521288629,w=88675123;
    unsigned int t;
    t=(x^(x<<11));x=y;y=z;z=w; return( w=(w^(w>>19))^(t^(t>>8)) );
}

int starttime;

int ne(int x){
    if(x == 0) return 1;
    if(x == 1) return 2;
    if(x == 2) return 3;
    if(x == 3) return 0;
    if(x == 4) return 5;
    if(x == 5) return 4;
    if(x == 6) return 7;
    if(x == 7) return 6;
    return -1;
}

vvi _ne = {
    {0, 1, 2, 3},
    {1, 2, 3, 0},
    {2, 3, 0, 1},
    {3, 0, 1, 2},
    {4, 5, 4, 5},
    {5, 4, 5, 4},
    {6, 7, 6, 7},
    {7, 6, 7, 6}
};

int next(int x, int r){
    // for(int i = 0; i < r; i++) x = ne(x);
    return _ne[x][r];
}

// vvi tiles(30, vi(30));
array<array<int, 30>, 30> tiles;
vi di = {0, -1, 0, 1};
vi dj = {-1, 0, 1, 0};

vvi to = {
    {1, 0, -1, -1},
    {3, -1, -1, 0},
    {-1, -1, 3, 2},
    {-1, 2, 1, -1},
    {1, 0, 3, 2},
    {3, 2, 1, 0},
    {2, -1, 0, -1},
    {-1, 3, -1, 1},
};

struct situation {

    // vvi rotate;
    array<array<int, 30>, 30> rotate;
    // vvb protect;
    array<array<bool, 30>, 30> protect;
    ll sco = -1;
    
    situation(){
        // rotate.resize(30, vi(30, 0));
        rep(i, 30) rep(j, 30){
            rotate[i][j] = 0;
            protect[i][j] = false;
        }
        // protect.resize(30, vb(30, false));
        
    }
    situation(vvi &v){
        // rotate = v;
        rep(i, 30) rep(j, 30){
            rotate[i][j] = v[i][j];
            protect[i][j] = false;    
        }
        // protect.resize(30, vb(30, false));
    }

    ll score(){
        if(sco != -1) return sco;
        vector vis(30, vector(30, vector(4, false)));
        vvi loop;
        rep(i, 4) loop.pb({0, 0, 0, 0});

        rep(si, 30) rep(sj, 30) rep(sd, 4) if(!vis[si][sj][sd]){
            int i = si, j = sj, d = sd;
            int length = 0;
            vis[i][j][d] = true;
            while(true){
                int d2 = to[next(tiles[i][j], rotate[i][j])][d];
                // int d2 = to[tiles[i][j]][d];
                if(d2 != -1) vis[i][j][d2] = true;
                if(d2 == -1) break;
                i += di[d2]; j += dj[d2];
                if(i < 0 || i >= 30 || j < 0 || j >= 30) break;
                d = (d2 + 2) % 4;
                length++;
                vis[i][j][d] = true;
                if(i == si && j == sj && d == sd){
                    loop.pb({length, i, j, d});
                    // debug(length);
                    // cout << length << " " << i << " " << j << " " << d << endl;
                    break;
                }
            }
        }

        sort(all(loop),[](auto a, auto b){ return a[0] > b[0]; });
        auto L1 = loop[0];
        auto L2 = loop[1];
        // cerr << L1 << " " << L2 << endl;

        rep(r, 1){
            int si = loop[r][1], sj = loop[r][2], sd = loop[r][3];
            int i = si, j = sj, d = sd;
            while(true){
                int d2 = to[next(tiles[i][j], rotate[i][j])][d];
                // int d2 = to[tiles[i][j]][d];
                // if(d2 != -1) vis[i][j][d2] = true;
                if(d2 == -1) break;
                i += di[d2]; j += dj[d2];
                if(i < 0 || i >= 30 || j < 0 || j >= 30) break;
                d = (d2 + 2) % 4;
                // vis[i][j][d] = true;
                protect[i][j] = true;
                if(i == si && j == sj && d == sd){
                    // debug(length);
                    // cout << length << " " << i << " " << j << " " << d << endl;
                    break;
                }
            }

        }
        return sco = L1[0] * L2[0];
    }

    void output(){

        rep(i, 30) rep(j, 30) cout << rotate[i][j];
        cout << "\n";

    }
};

bool operator<(const situation& a, const situation& b){
    // a.score(); b.score();
    if(a.sco == b.sco){
        return a.rotate < b.rotate;
    }
    return a.sco < b.sco;

}

bool operator>(const situation& a, const situation& b){
    // a.score(); b.score();
    if(a.sco == b.sco){
        return a.rotate > b.rotate;
    }
    return a.sco > b.sco;

}

void solve(){
    situation ans;
    ans.score();

    priority_queue<situation> que;
    que.push(ans);

    ll loopcnt = 0;

    min_priority_queue<situation> best;
    while(clock() - starttime <= 1960000){
        situation nxt;
        rep(i, 30) rep(j, 30){
            nxt.rotate[i][j] = randxor() % 4;
        }

        nxt.score();
        best.push(nxt);


        if(best.size() > 10) best.pop();
    }



    vector<situation> arr;
    while(!best.empty()){
        arr.emplace_back(best.top());
        best.pop();
    }

    ans = arr.back();

    rep(ix, arr.size()) rep(jx, arr.size()) if(ix != jx){
        situation add;
        bool ok = true;
        rep(i, 30) rep(j, 30){
            if(arr[ix].protect[i][j] && arr[jx].protect[i][j]){
                ok = false; break;
            }

            if(arr[ix].protect[i][j]) add.rotate[i][j] = arr[ix].rotate[i][j];
            else add.rotate[i][j] = arr[jx].rotate[i][j];
        }
        if(ok){
            if(ans.score() < add.score()) ans = add;
        }
    }

    ans.output();

}


int main(){
    starttime = clock();
    vector<string> T(30); for(int i = 0; i < 30; i++) cin >> T[i];

    rep(i, 30){
        rep(j, 30){
            tiles[i][j] = T[i][j] - '0';
        }
    }
    

    solve();    

}