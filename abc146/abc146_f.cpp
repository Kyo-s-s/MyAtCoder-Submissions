#include<bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, n) for (ll i = 0; i < (n); i++)

template<class M> struct Segtree {
  public:
    using S = typename M::T;

    Segtree() : Segtree(0) {}
    Segtree(int n) : Segtree(vector<S> (n, M::e())) {}
    Segtree(const vector<S> &v) : n(int(v.size())) { 
        while((1 << log) < n) log++;
        size = 1 << log;
        d = vector<S> (2 * size, M::e());
        for(int i = 0; i < n; i++) d[size + i] = v[i];
        for(int i = size- 1; i >= 1; i--) update(i);
    }

    void set(int p, S x){
        assert(0 <= p && p < n);
        p += size;
        d[p] = x;
        for(int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p){
        assert(0 <= p && p < n);
        return d[p + size];
    }

    S prod(int l, int r){
        assert(0 <= l && l <= r && r <= n);
        S sml = M::e(), smr = M::e();
        l += size; r += size;
        while(l < r){
            if(l & 1) sml = M::op(sml, d[l++]);
            if(r & 1) smr = M::op(d[--r], smr);
            l >>= 1; r >>= 1;
        }
        return M::op(sml, smr);
    }

    S all_prod(){ return d[1]; }


  private:
    int n, size, log = 0;
    vector<S> d;
    void update(int k){ d[k] = M::op(d[k * 2], d[k * 2 + 1]); }

};


const ll INF = 1LL << 58;
#define fi first
#define se second

struct Min {
  using T = ll;
  static T e() {
    return INF;
  }
  static T op(T x, T y) {
    return min(x, y);
  }
};

struct Min_idx {
  using T = pair<ll, ll>;
  static T e() {
    return make_pair(INF, INF);
  }
  static T op(T x, T y) {
    if (x.fi == y.fi) {
      return (x.se < y.se ? x : y);
    }
    return (x.fi < y.fi ? x : y);
  }
};

int main() {

  ll N, M; cin >> N >> M;
  string S; cin >> S;
  
  Segtree<Min> seg(N + 1);
  seg.set(0, 0);
  rep(i, N + 1) {
    if (i == 0) continue;
    if (S[i] == '1') continue;
    ll left = max(0LL, i - M);
    ll nxt = seg.prod(left, i);
    if (nxt != INF) nxt++;
    seg.set(i, nxt);
  }

  if (seg.get(N) == INF) {
    cout << -1 << endl;
    exit(0);
  }

  vector<Min_idx::T> v(N + 1);
  rep(i, N + 1) {
    v[i] = make_pair(seg.get(i), i);
  }

  Segtree<Min_idx> segi(v);
  
  vector<ll> now;
  now.push_back(N);

  while (now.back() != 0) {
    ll left = max(0LL, now.back() - M);
    auto nxt = segi.prod(left, now.back());
    now.push_back(nxt.se);
  }

  reverse(now.begin(), now.end());
  rep(i, (int)now.size() - 1) {
    cout << now[i + 1] - now[i] << " ";
  }
  cout << endl;

}
