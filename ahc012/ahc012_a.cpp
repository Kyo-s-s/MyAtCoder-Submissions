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


int N;
int K;
vi A;
int A_sum;
vpii berry;
time_t start;


// 1st -> 完全愚直の山登り　すぐ終わるので時間いっぱい繰り返す(割と回数できてる)
// 2nd -> 細かいの創るより大きいの分割したらポイント
// 3rd -> 16等分16等分してから焼きなまし

void input(){
    cin >> N >> K;
    berry.resize(N);
    A.resize(11);
    for(int i = 1; i <= 10; i++) cin >> A[i];
    A_sum = sum(A);
    rep(i, N){
        cin >> berry[i].fi >> berry[i].se;
    }
}


struct line {
    int px, py, qx, qy;
};

struct situation {

    vector<vector<int>> pieces;
    vector<line> lines;
    vector<int> count;
    ll score = -1;
    double point = 0;


    situation(){
        vi v(N);
        rep(i, N) v[i] = i;
        pieces.pb(v);
        count.resize(12, 0);    // 11 : else
    }


    // 返り値: 切ってしまったイチゴの数 -1 でerr , 10以上のグループを必要なものへ切断できた数
    tuple<bool, int, int> cut(int px, int py, int qx, int qy){

        if(px == qx && py == qy) return make_tuple(false, -1, -1);

        vvi new_pieces;
        int ret = 0;// 切ってしまったイチゴの数
        vi vecnum(11, 0);// 10以上のグループを必要なものへ切断できた数
        for(auto piece: pieces){
            vi left, right;
            for(int j: piece){
                int x = berry[j].fi, y = berry[j].se;
                ll side = (qx - px) * (y - py) - (qy - py) * (x - px);
                if(side > 0) left.pb(j);
                if(side < 0) right.pb(j);
                if(side == 0) ret++;
            }
            if(left.size() > 0) new_pieces.pb(left);
            if(right.size() > 0) new_pieces.pb(right);
            if(piece.size() > 10){
                if(0 < left.size() && left.size() <= 10) vecnum[left.size()]++;
                if(0 < right.size() && right.size() <= 10) vecnum[right.size()]++; 
            }
        }
        bool ch = (new_pieces != pieces);
        pieces = new_pieces;
        lines.pb({px, py, qx, qy});
        score = sco();
        point = pnt();
        int num = 0;
        for(int i = 1; i <= 10; i++){
            if(A[i] < count[i]) num -= vecnum[i];
            else num += vecnum[i] * 20; // 重み
        }
        return make_tuple(ch, ret, num);
    }

    ll sco() {
        if(lines.size() > K) return -1;
        for(auto &c: count) c = 0;
        for(auto piece: pieces){
            if(0 < piece.size() && piece.size() <= 10) count[piece.size()]++;
            if(piece.size() == 11) count[piece.size()]++;
        }
        double ret = 0;
        for(int i = 1; i <= 10; i++){
            ret += min(count[i], A[i]);
        }
        ret /= A_sum;
        ret *= 1000000;
        return (ll) ret;
    }

    // 評価関数 作りすぎていたら減点
    double pnt(){
        double ret = 0;
        for(int i = 1; i <= 10; i++){
            ret += A[i] - count[i];
        }
        return ret / 10000;
    }

    void output(){
        cout << lines.size() << "\n";
        for(auto l: lines){
            cout << l.px << " " << l.py << " " << l.qx << " " << l.qy << "\n";
        }
    }

};


struct Solver {

    void solve(){
        
        situation now_fir, ans;

        // vi cuti = {-8500, -6500, -5000, -3500, -2000, -1000, 0, 1000, 2000, 3500, 5000, 6500, 8500};
        // vi cuti = {-9000, -8000, -7000, -6000, -5000, -4000, -3000, -2000, -1000, 0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000};
        vi cuti = {-900, -1800, -2700, -3600, -4500, -5400, -6300, -7200, -8100, -9000, 0, 900, 1800, 2700, 3600, 4500, 5400, 6300, 7200, 8100, 9000};
        // vi cuti = {-800, -1600, -2400, -3200, -4000, -4800, -5600, -6400, -7200, -8000, -9000, 0, 800, 1600, 2400, 3200, 4000, 4800, 5600, 6400, 7200, 8000, 9000};
        for(auto c: cuti){

            {
                int ycut = -1, stv = 100000;
                for(int yc = c - 10; yc <= c + 10; yc++){
                    int cnt = 0;
                    for(auto [x, y]: berry){
                        if(yc == y) cnt++;
                    }
                    if(chmin(stv, cnt)) ycut = yc;
                }
                now_fir.cut(0, ycut, 1, ycut);
            }

            {
                int xcut = -1, stv = 100000;
                for(int xc = c - 10; xc <= c + 10; xc++){
                    int cnt = 0;
                    for(auto [x, y]: berry){
                        if(xc == x) cnt++;
                    }
                    if(chmin(stv, cnt)) xcut = xc;
                }
                now_fir.cut(xcut, 0, xcut, 1);
            }

            // now_fir.cut(0, x, 1, x);
            // now_fir.cut(x, 0, x, 1);
        }

        // now_fir.output();

        int cnt = 0;
        const int x = 20;
        // x手考える→その中で一番よいものを選出

        while((clock() - start) <= 2.6 * CLOCKS_PER_SEC){
        
            situation now = now_fir;

            ll empcnt = 0;

            while(now.lines.size() < K){
                if(empcnt >= 50) break;
                vector<situation> nexts(x);
                vector<double> cuts(x);
                rep(i, x){
                    nexts[i] = now;
                    int px = rand() % 20'000 - 10'000;
                    int py = rand() % 20'000 - 10'000;
                    int qx = rand() % 20'000 - 10'000;
                    int qy = rand() % 20'000 - 10'000;

                    
                    auto [ok, cutberry, cutgood] = nexts[i].cut(px, py, qx, qy);
                    cuts[i] = exp((double)(cutgood) / 300.0);
                    if(!ok || cutberry > 5){
                        nexts[i].score = 0;
                    }

                }

                int max_i = 0;
                for(int i = 1; i < x; i++){
                    if(nexts[i].score * cuts[i] > nexts[max_i].score * cuts[max_i]) max_i = i;
                }

                if(now.score < nexts[max_i].score) now = nexts[max_i];
                else empcnt++;


                // now.output();   // 消す！
            }
        

            if(now.score > ans.score){
                ans = now;
            }
            
        }


        ans.output();
        cerr << ans.score << "\n";

        return;
    }


};


int main(){

    start = clock();

    mt19937 rand(0);
    // 適当に切って良ければ(イチゴをちょうど切るようなものは減点)採用の焼きなまし

    input();

    Solver solver;
    solver.solve();


}