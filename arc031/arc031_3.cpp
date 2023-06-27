#include<bits/stdc++.h>
using namespace std;

using ll = long long;


template<class M> struct SegTree {
  public:
    using S = typename M::T;
    SegTree() : SegTree(0) {}
    SegTree(int n) : SegTree(vector<S> (n, M::e())) {}
    SegTree(const vector<S> &v) : n((int)v.size()) {
      while ((1 << log) < n) log++;
      size = 1 << log;
      d = vector<S> (2 * size, M::e());
      for (int i = 0; i < n; i++) d[size + i] = v[i];
      for (int i = size - 1; i >= 1; i--) update(i);
    }

    void set(int p, S x) {
      p += size;
      d[p] = x;
      for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
      return d[p + size];
    }

    S prod(int l, int r) {
      S sml = M::e(), smr = M::e();
      l += size; r += size;
      while (l < r) {
        if (l & 1) sml = M::op(sml, d[l++]);
        if (r & 1) smr = M::op(d[--r], smr);
        l >>= 1; r >>= 1;
      }
      return M::op(sml, smr);
    }

    S all_prod() {
      return d[1];
    }

  private:
    int n, size, log = 0;
    vector<S> d;
    void update(int k) {
      d[k] = M::op(d[k * 2], d[k * 2 + 1]);
    }
};

struct Add_M {
  using T = long long;
  static T op(T a, T b) {
    return a + b;
  }
  static T e() {
    return 0;
  }
};


int main() {

  int N; cin >> N;
  vector<int> B(N);
  for (int i = 0; i < N; i++) {
    cin >> B[i]; B[i]--;
  }

  vector<ll> v(N);
  for (int i = 0; i < N; i++) v[i] = 1;
  SegTree<Add_M> seg(v);

  vector<int> C(N);
  for (int i = 0; i < N; i++) {
    C[B[i]] = i;
  }

  ll ans = 0;
  for (int i = 0; i < N; i++) {
    int idx = C[i];
    seg.set(idx, 0);
    ll l = seg.prod(0, idx);
    ll r = seg.prod(idx, N);
    ans += min(l, r);
  }

  cout << ans << endl;

}
