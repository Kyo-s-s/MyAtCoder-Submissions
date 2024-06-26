#include<bits/stdc++.h>
using namespace std; 

using ll = long long;

const ll INF = 1LL << 58;

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

struct Max_M {    
    using T = long long;
    static T e() { return -INF; }
    static T op(T x, T y) { return max(x, y); }
};


int main() {

  ll N; cin >> N;  
  vector<ll> H(N), A(N);
  for (int i = 0; i < N; i++) cin >> H[i];
  for (int i = 0; i < N; i++) cin >> A[i];

  Segtree<Max_M> seg(N);

  for (int i = 0; i < N; i++) {
    ll h = H[i] - 1, a = A[i];

    ll m = max(0LL, seg.prod(0, h));

    seg.set(h, m + a);
  }


  cout << seg.all_prod() << endl;

}
