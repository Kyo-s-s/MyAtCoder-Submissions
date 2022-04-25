#pragma region header
#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;

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

using S = ll;
S op(S a, S b){ return min(a, b); }
S e(){ return INF; }
using F = ll;
S mapping(F f, S x){ return f + x; }
F composition(F f, F g){ return f + g; }
F id(){ return 0; }


int main(){

    ll N, Q; cin >> N >> Q;
    string T; cin >> T;
    
    
    vector<ll> v = {0};

    for(auto s: T){
        v.pb(v.back() + (s == '(' ? 1 : -1));
    }

    // for(int i = 0; i < v.size(); i++){
    //     cout << v[i] << (i != v.size() - 1 ? ' ' : '\n');
    // }


    lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);

    while(Q--){
        ll t, l, r; cin >> t >> l >> r;
        if(t == 1){
            if(T[l-1] == '(' && T[r-1] == ')'){
                seg.apply(l, r, -2);
            }elif(T[l-1] == ')' && T[r-1] == '('){
                seg.apply(l, r, 2);
            }
            swap(T[l-1], T[r-1]);
        }else{
            bool same = seg.get(l - 1) == seg.get(r);
            bool mini = seg.prod(l - 1, r) >= seg.get(l - 1);
            YesNo(same && mini);
        }

        // rep(i, N + 1){
        //     cout << seg.get(i) << " \n"[i == N];
        // }

    }
    


    

}