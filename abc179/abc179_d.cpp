#include<bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, n) for (ll i = 0; i < (n); i++)

template<int m> struct StaticModint{
    using mint = StaticModint;
  public:
    static constexpr int mod() { return m; }
    static mint raw(int v) {
        mint x;
        x._v = v;
        return x;
    }

    StaticModint() : _v(0) {}
    template <class T>
    StaticModint(T v) {
        long long x = (long long)(v % (long long)(umod()));
        if (x < 0) x += umod();
        _v = (unsigned int)(x);
    }

    unsigned int val() const { return _v; }

    mint& operator++() {
        _v++;
        if (_v == umod()) _v = 0;
        return *this;
    }
    mint& operator--() {
        if (_v == 0) _v = umod();
        _v--;
        return *this;
    }
    mint operator++(int) {
        mint result = *this;
        ++*this;
        return result;
    }
    mint operator--(int) {
        mint result = *this;
        --*this;
        return result;
    }

    mint& operator+=(const mint& rhs) {
        _v += rhs._v;
        if (_v >= umod()) _v -= umod();
        return *this;
    }
    mint& operator-=(const mint& rhs) {
        _v -= rhs._v;
        if (_v >= umod()) _v += umod();
        return *this;
    }
    mint& operator*=(const mint& rhs) {
        unsigned long long z = _v;
        z *= rhs._v;
        _v = (unsigned int)(z % umod());
        return *this;
    }
    mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }

    mint operator+() const { return *this; }
    mint operator-() const { return mint() - *this; }

    mint pow(long long n) const {
        assert(0 <= n);
        mint x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    mint inv() const {
        assert(_v);
        return pow(umod() - 2);
    }

    friend mint operator+(const mint& lhs, const mint& rhs) { return mint(lhs) += rhs;}
    friend mint operator-(const mint& lhs, const mint& rhs) { return mint(lhs) -= rhs; }
    friend mint operator*(const mint& lhs, const mint& rhs) { return mint(lhs) *= rhs; }
    friend mint operator/(const mint& lhs, const mint& rhs) { return mint(lhs) /= rhs; }
    friend bool operator==(const mint& lhs, const mint& rhs) { return lhs._v == rhs._v; }
    friend bool operator!=(const mint& lhs, const mint& rhs) { return lhs._v != rhs._v; }

    friend ostream &operator<<(ostream &os, mint x) {
        os << x.val();
        return (os);
    }

  private:
    unsigned int _v;
    static constexpr unsigned int umod() { return m; }

};

using Modint998244353 = StaticModint<998244353>;
using Modint1000000007 = StaticModint<1000000007>;

using Mint = Modint998244353;

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

struct Add_M {    
    using T = Mint;
    static T e() { return Mint(0); }
    static T op(T x, T y) { return x + y; }
};


int main() {

  ll N, K; cin >> N >> K;
  vector<pair<ll, ll>> LR;  
  rep(i, K) {
    ll l, r; cin >> l >> r;
    LR.push_back({l, r});
  }

  Segtree<Add_M> seg(N);
  seg.set(0, Mint(1));

  auto update = [&](int i) {
    Mint u(0);
    for (auto [l, r] : LR) {
      ll nl = max(0LL, i - r);
      ll nr = max(0LL, i - l + 1);
      u += seg.prod(nl, nr);
    }      
    seg.set(i, u);
  };

  for (int i = 1; i < N; i++) {
    update(i);
  }
  
  cout << seg.get(N - 1) << endl;


}
