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

//x座標、y座標、偏角メンバを持つ構造体
struct Point{
    double x,y,arg;
    int nouse = 0;
    //x, yの値をもとに偏角を計算する
    void calc_arg(){
        if(x == 0){
            //0除算を防ぐため、x=0の時argを10に設定する。
            arg = 10;
            //原点の場合11に設定する
            if(y == 0)arg++;
            return;
        }
        //通常argは-π/2からπ/2までの範囲
        arg = atan(y / x);
    }
    //原点からの距離の二乗を求める関数
    double dist(){
        return x * x + y * y;
    }
    static bool comp_x(Point &a, Point &b){
        //x座標が等しい場合、y座標を基準にする
        if(a.x == b.x)return a.y < b.y;
        return a.x < b.x;
    }
    static bool comp_arg(Point &a, Point &b){
        return a.arg < b.arg;
    }
    static bool comp_nouse(Point &a, Point &b){
        return a.nouse < b.nouse;
    }
};
//符号付き面積を求める関数
double area2(const Point a, const Point b, const Point c){
    return a.x*b.y + a.y*c.x + b.x*c.y - b.y*c.x - c.y*a.x - a.y*b.x;
}
//一直線上に点が並んでしまうような集合の場合を考慮して、原点から最も遠いものを残して削除する関数
void delete_samearg(vector<Point> &p, int &n){
    int recent = 0;
    int nouse = 0;
    rep(i,n){
        if(i==0)continue;
        if(p[recent].arg == p[i].arg){
            nouse++;
            if(p[recent].dist() < p[i].dist()){
                p[recent].nouse = 1;
                recent = i;
            }else{
                p[i].nouse = 1;
            }
        }else recent = i;
    }
    n -= nouse;
    sort(p.begin(), p.end(), Point::comp_nouse);
    p.resize(n);
    sort(p.begin(), p.end(), Point::comp_arg);
}

int main(){

    vector<Point> p(4);
    int n = 4;
    rep(i, 4) cin >> p[i].x >> p[i].y;

    iter_swap(min_element(p.begin(), p.end(), Point::comp_x), p.begin());
    Point p0 = p[0];
    //p[0]基準に原点を移動する
    rep(i,n){
        p[i].x -= p0.x;
        p[i].y -= p0.y;
        p[i].calc_arg();
    }
    //偏角順にソート
    sort(p.begin(), p.end(), Point::comp_arg);
    delete_samearg(p,n);
    vector<Point> sta;
    sta.push_back(p[n-1]);
    sta.push_back(p[0]);
    //print()を実行するとスタックの内容を出力するラムダ式を定義する
    auto print = [&](){
        cout << sta.size() << endl;
        rep(i,sta.size()){
            Point p = sta[i];
            printf("%8.7lf %7.7lf\n", p.x + p0.x, p.y + p0.y);
        }
    };
    //グラハムのアルゴリズム開始
    rep(i,n){
        if(i==0)continue;
        while(1){
            Point t = sta.back();
            sta.pop_back();
            Point s = sta.back();
            if(area2(s,t,p[i])> 0){
                sta.push_back(t);
                sta.push_back(p[i]);
                break;
            }
        }
    }
    sta.pop_back();
    //スタックの内容を出力
    YesNo(sta.size() == 4);
    

}