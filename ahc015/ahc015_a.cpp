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

vi dxy = {1, -1, 10, -10};
string FBLR = "FBLR";
mt19937 rnd(1145141919);

struct Board {
    array<int, 100> g;
    Board() {
        g.fill(0);
    }
    void build(array<int, 100> _g) {
        g = _g;
    }

    int operator[](int i) {
        return g[i];
    }

    void set(int i, int v) {
        g[i] = v;
    }

    Board move(char c) {
        Board ret;
        switch (c) {
            case 'F':
                for (int i = 0; i < 10; i++) {
                    int pos = i;
                    for (int x = i; x < 100; x+=10) {
                        if (g[x] != 0) {
                            ret.g[pos] = g[x];
                            pos += 10;
                        }
                    }
                }
                break;
            case 'B':
                for (int i = 0; i < 10; i++) {
                    int pos = i + 90;
                    for (int x = i + 90; x >= 0; x-=10) {
                        if (g[x] != 0) {
                            ret.g[pos] = g[x];
                            pos -= 10;
                        }
                    }
                }
                break;
            case 'L':
                for (int i = 0; i < 100; i+=10) {
                    int pos = i;
                    for (int x = i; x < i + 10; x++) {
                        if (g[x] != 0) {
                            ret.g[pos] = g[x];
                            pos++;
                        }
                    }
                }
                break;
            case 'R':
                for (int i = 0; i < 100; i+=10) {
                    int pos = i + 9;
                    for (int x = i + 9; x >= i; x--) {
                        if (g[x] != 0) {
                            ret.g[pos] = g[x];
                            pos--;
                        }
                    }
                }
                break;
        }

        return ret;
    }

    array<Board, 4> neighbothood() {
        array<Board, 4> ret;
        for (int i = 0; i < 4; i++) {
            ret[i] = move(FBLR[i]);
        }
        return ret;
    }



    int score() {
        array<bool, 100> used;
        used.fill(false);
        int sum = 0;
        for (int i = 0; i < 100; i++) {
            if (used[i] == true || g[i] == 0) continue;
            int find = g[i];
            deque<int> q; q.emplace_back(i);
            used[i] = true;
            int cnt = 0;
            while (!q.empty()) {
                int now = q.front(); q.pop_front();
                for (auto d: dxy) {
                    int nxt = now + d;
                    if (nxt < 0 || nxt >= 100) continue;
                    if (used[nxt] == true) continue;
                    if (g[nxt] != find) continue;
                    used[nxt] = true;
                    q.emplace_back(nxt);
                    cnt++;
                }
            }
            sum += cnt * cnt;
        }
        return sum;
    }
    
};


struct Solver {
    array<int, 100> f;
    Board board;

    Solver() {
        rep(i, 100) cin >> f[i];
        int x = 0, y = 0, z = 0;
        for (auto i: f) {
            if (i == 1) x++;
            if (i == 2) y++;
            if (i == 3) z++;
        }
    }

    void solve() {
        rep(i, 99) {
            loop(f[i], i);
        }
    }


    void loop(int candyType, int turn) {
        
        INT(inp);
        int pos = inpToPos(inp, board);

        board.set(pos, candyType);

        array<Board, 4> nextBoards = board.neighbothood();

        const int tryCnt = 35;
        const int trydepth = 2;
        array<int, 4> assignCount; assignCount.fill(0);

        if (turn == 98) {
            assignCount[estimate1(nextBoards, turn, {1}).first]++;
        } elif (turn == 97) {
            assignCount[estimate2(nextBoards, turn, {2, 1}).first]++;
            assignCount[estimate2(nextBoards, turn, {1, 1}).first]++;
        } else {
            rep(i, tryCnt) {
                array<int, 3> inp;
                inp[0] = rnd() % (100 - turn - 1) + 1;
                inp[1] = rnd() % (100 - turn - 2) + 1;
                inp[2] = rnd() % (100 - turn - 3) + 1;
                assignCount[estimate3(nextBoards, turn, inp).first]++;
            }
        }

        int maxIdx = 0;
        rep(i, 4) if (assignCount[i] > assignCount[maxIdx]) maxIdx = i;

        board = nextBoards[maxIdx];
        cout << FBLR[maxIdx] << endl;


    }

    pair<int, int> estimate3(array<Board, 4> &neighbothood, int turn, array<int, 3> inp) {
        array<int, 4> score; score.fill(0);
        array<int, 2> p = {inp[1], inp[2]};
        rep(j, 4) {
            int nextPos = inpToPos(inp[0], neighbothood[j]);
            Board nextBoard = neighbothood[j];
            nextBoard.set(nextPos, f[turn + 1]);
            array<Board, 4> nextBoards = nextBoard.neighbothood();
            score[j] += estimate2(nextBoards, turn + 1, p).second;
        }
        int maxIdx = 0;
        rep(i, 4) if (score[i] > score[maxIdx]) maxIdx = i;
        return {maxIdx, score[maxIdx]};
    }

    pair<int, int> estimate2(array<Board, 4> &neighbothood, int turn, array<int, 2> inp) {
        array<int, 4> score; score.fill(0);
        array<int, 1> p = {inp[1]};
        rep(j, 4) {
            int nextPos = inpToPos(inp[0], neighbothood[j]);
            Board nextBoard = neighbothood[j];
            nextBoard.set(nextPos, f[turn + 1]);
            array<Board, 4> nextNeighbothood = nextBoard.neighbothood();
            score[j] = estimate1(nextNeighbothood, turn + 1, p).second;
        }
        int maxIdx = 0;
        rep(i, 4) if (score[i] > score[maxIdx]) maxIdx = i;
        return {maxIdx, score[maxIdx]};
    }

    pair<int, int> estimate1(array<Board, 4> &neighbothood, int turn, array<int, 1> inp) {
        array<int, 4> scores; scores.fill(-1);
        rep(j, 4) {
            int nxtPos = inpToPos(inp[0], neighbothood[j]);
            Board nxtBoard = neighbothood[j];
            nxtBoard.set(nxtPos, f[turn + 1]);
            array<Board, 4> nextNextBoards = nxtBoard.neighbothood();
            rep(k, 4) chmax(scores[j], nextNextBoards[k].score());
        }
        int maxIdx = 0;
        rep(j, 4) if (scores[j] > scores[maxIdx]) maxIdx = j;
        return {maxIdx, scores[maxIdx]};
    }

    int inpToPos(int inp, Board &b) {
        int pos = 0, cnt = 0;
        rep(i, 100) {
            if (b[i] == 0) cnt++;
            if (cnt == inp) return i;
        }
        return 1000000;
    }

};


int main() {

    Solver solver;

    solver.solve();

}