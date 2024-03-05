#ifdef INCLUDED_MAIN


// https://rsk0315.hatenablog.com/entry/2022/04/29/141726
// https://judge.yosupo.jp/submission/87787

template<class T>
struct ConvexHullTrick {
  public:
    // S \gets S \cup \{ (a, b) \}
    void add_line(T a, T b) {
        if (slope_to_intercept.empty()) {
            slope_to_intercept.insert({a, b});
            update_slope_and_right_limit(a, std::numeric_limits<T>::max());
            return;
        }
        if (unused(a, b)) {
            return;
        }
        remove_unused(a, b);
        insert(a, b);
    }

    // \min_{(a, b) \in S} ax + b
    T min(T x) {
        auto it = right_limit_to_slope.lower_bound(x);
        assert(it != right_limit_to_slope.end());
        return it->second * x + slope_to_intercept[it->second];
    }

  private:
    map<T, T> slope_to_intercept;
    map<T, T> slope_to_right_limit;
    map<T, T> right_limit_to_slope;
    
    bool unused(T a, T b) {
        auto itl = slope_to_intercept.lower_bound(a);
        if (itl == slope_to_intercept.end()) {
            return false;
        }
        auto [al, bl] = *itl;
        if (a == al) return bl <= b;
        if (itl == slope_to_intercept.begin()) {
            return false;
        }
        auto [ar, br] = *prev(itl);
        return f(al, bl, a, b) >= f(a, b, ar, br);
    }

    void erase_slope(T a) {
        slope_to_intercept.erase(a);
        right_limit_to_slope.erase(slope_to_right_limit[a]);
        slope_to_right_limit.erase(a);
    }

    void remove_unused(T a, T b) {
        erase_slope(a);
        vector<T> rm_slope;
        do {
            auto itl = slope_to_intercept.lower_bound(a);
            if (itl == slope_to_intercept.end()) {
                break;
            }
            auto itll = next(itl);
            while (itll != slope_to_intercept.end()) {
                auto [all, bll] = *itll;
                auto [al, bl] = *itl;
                if (f(all, bll, al, bl) >= f(al, bl, a, b)) {
                    rm_slope.push_back(al);
                } else {
                    break;
                }
                itl = itll++;
            }
        } while (false);
        do {
            auto itr = slope_to_intercept.lower_bound(a);
            if (itr == slope_to_intercept.begin()) {
                break;
            }
            auto itrr = prev(itr);
            while (itrr != slope_to_intercept.begin()) {
                itr = itrr--;
                auto [arr, brr] = *itrr;
                auto [ar, br] = *itr;
                if (f(a, b, ar, br) >= f(ar, br, arr, brr)) {
                    rm_slope.push_back(ar);
                } else {
                    break;
                }
            }
        } while (false);
        for (auto s : rm_slope) {
            erase_slope(s);
        }
    }

    void update_slope_and_right_limit(T slope, T right_limit) {
        if (auto it = slope_to_right_limit.find(slope); it != slope_to_right_limit.end() && it->first == slope) {
            T old = it->second;
            right_limit_to_slope.erase(old);
            it->second = right_limit;
        } else {
            slope_to_right_limit[slope] = right_limit;
        }
        if (auto it = right_limit_to_slope.find(right_limit); it != right_limit_to_slope.end() && it->first == right_limit) {
            T old = it->second;
            slope_to_right_limit.erase(old);
            it->second = slope;
        } else {
            right_limit_to_slope[right_limit] = slope;
        }
    }

    void insert(T a, T b) {
        auto it = slope_to_intercept.lower_bound(a);
        if (it != slope_to_intercept.end()) {
            auto [al, bl] = *it;
            update_slope_and_right_limit(al, f(al, bl, a, b));
        }
        if (it != slope_to_intercept.begin()) {
            auto [ar, br] = *std::prev(it);
            update_slope_and_right_limit(a, f(a, b, ar, br));
        } else {
            update_slope_and_right_limit(a, std::numeric_limits<T>::max());
        }
        slope_to_intercept.insert({a, b});
    }
  

    static T f(T a, T b, T ar, T br) {
        return div(br - b, a - ar);
    }

    static T div(T num, T den) {
        if (num % den == 0 || num >= 0) return num / den;
        return num / den + 1;
    }
};


template <typename L, typename R>
class bimap {
  std::map<L, R> M_ltor;
  std::map<R, L> M_rtol;

public:
  bimap() = default;

  void insert(L l, R r) {
    if (auto it = M_ltor.lower_bound(l); it != M_ltor.end() && it->first == l) {
      R old_r = it->second;
      M_rtol.erase(old_r);
      it->second = r;
    } else {
      M_ltor.emplace_hint(it, l, r);
    }
    if (auto it = M_rtol.lower_bound(r); it != M_rtol.end() && it->first == r) {
      L old_l = it->second;
      M_ltor.erase(old_l);
      it->second = l;
    } else {
      M_rtol.emplace_hint(it, r, l);
    }
  }

  void erase_left(L l) {
    if (auto it = M_ltor.find(l); it != M_ltor.end()) {
      auto r = it->second;
      M_rtol.erase(r);
      M_ltor.erase(it);
    }
  }

  L right_ge(R r) {
    auto it = M_rtol.lower_bound(r);
    assert(it != M_rtol.end());
    return it->second;
  }
};

template <typename I>
class CHT {
  std::map<I, I> M_f;
  bimap<I, I> M_range;
  
public:
  CHT() = default;

  void push(I a, I b) {
    if (M_f.empty()) {
      auto max = std::numeric_limits<I>::max();
      M_f.insert({a, b});
      M_range.insert(a, max);
      return;
    }
    if (M_unused(a, b)) {
      return;
    }
    M_remove_unused(a, b);
    M_insert(a, b);
  }

  I min(I x) {
    I a = M_range.right_ge(x);
    I b = M_f[a];
    return a * x + b;
  }

private:
  bool M_unused(I a, I b) {
    auto itl = M_f.lower_bound(a);
    if (itl == M_f.end()) return false;
    auto [al, bl] = *itl;
    if (a == al) return bl <= b;
    if (itl == M_f.begin()) return false;
    auto itr = std::prev(itl);
    auto [ar, br] = *itr;
    return S_right(al, bl, a, b) >= S_right(a, b, ar, br);
  }

  void M_remove_unused(I a, I b) {
    M_f.erase(a);
    M_range.erase_left(a);

    std::vector<I> rm;
    do {
      auto itl = M_f.lower_bound(a);
      if (itl == M_f.end()) break;
      auto itll = std::next(itl);
      while (itll != M_f.end()) {
        auto [all, bll] = *itll;
        auto [al, bl] = *itl;
        if (S_right(all, bll, al, bl) >= S_right(al, bl, a, b)) {
          rm.push_back(al);
        } else {
          break;
        }
        itl = itll++;
      }
    } while (false);
    do {
      auto itr = M_f.lower_bound(a);
      if (itr == M_f.begin()) break;
      auto itrr = std::prev(itr);
      while (itrr != M_f.begin()) {
        itr = itrr--;
        auto [arr, brr] = *itrr;
        auto [ar, br] = *itr;
        if (S_right(a, b, ar, br) >= S_right(ar, br, arr, brr)) {
          rm.push_back(ar);
        } else {
          break;
        }
      }
    } while (false);
    for (auto ar: rm) {
      M_f.erase(ar);
      M_range.erase_left(ar);
    }
  }

  void M_insert(I a, I b) {
    auto it = M_f.lower_bound(a);
    if (it != M_f.end()) {
      auto [al, bl] = *it;
      M_range.insert(al, S_right(al, bl, a, b));
    }
    if (it != M_f.begin()) {
      auto [ar, br] = *std::prev(it);
      M_range.insert(a, S_right(a, b, ar, br));
    } else {
      M_range.insert(a, std::numeric_limits<I>::max());
    }
    M_f.insert({a, b});
  }

  static I S_right(I a, I b, I ar, I br) {
    return S_div_euclid(br - b, a - ar);
  }

  static I S_div_euclid(I num, I den) {
    if (num % den == 0 || num >= 0) return num / den;
    return num / den + 1;
  }
};


int main() {

    // LL(N, Q);
    // ConvexHullTrick<ll> cht;
    // rep(i, N) {
    //     LL(a, b);
    //     cht.add_line(a, b);
    // }

    // while (Q--) {
    //     LL(t);
    //     if (t == 0) {
    //         LL(a, b);
    //         cht.add_line(a, b);
    //     } else {
    //         LL(p);
    //         OUT(cht.min(p));
    //     }
    // }


    LL(N, M);   
    VEC(ll, B, N);
    VEC(ll, C, M);

    sort(all(B));
    reverse(all(B));

    // ConvexHullTrick<ll> cht;
    CHT<ll> cht;

    rep(i, N) {
        cht.push(-(i + 1), - B[i] * (i + 1));
    }

    vll ans;
    fore(c, C) {
        ans.pb(-cht.min(c));
    }

    OUT(ans);
  
}

#else

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
template<class T> int bisect_left(vector<T> &array, T key){ return lower_bound(all(array),key) - array.begin(); }
template<class T> int bisect_right(vector<T> &array, T key){ return upper_bound(all(array),key) - array.begin(); }

/* string */
ll string_to_ll(string n){ ll ret = 0, k = 1; while(n.length() > 0){ ret += k * (n.back() - '0'); n.pop_back(); k *= 10; } return ret; }
string ll_to_string(ll n){ string ret = ""; while(n > 0){ ret.pb((n % 10) + '0'); n /= 10; } reverse(all(ret)); return ret; }

struct popopo{ popopo(){ cin.tie(0); ios::sync_with_stdio(0); cout << fixed << setprecision(15); }; } popopoppo;

// n = 1,...,N に対して、n % A < B を満たすものの数 
ll Count_of_n_mod_A_less_than_B(ll N, ll A, ll B){ return N / A * min(A, B) + min(N % A, B - 1); }

bool include(ll l, ll r, ll x) { return l <= x && x < r; }

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

namespace kyo {

long long bisect(long long ok, long long ng, function<bool(long long)> is_ok) { while (abs(ok - ng) > 1) { long long mid = ok + (ng - ok) / 2; (is_ok(mid) ? ok : ng) = mid; } return ok; }

}

#define INCLUDED_MAIN
#include __FILE__ // Codeforces で壊れるらしい

#endif
