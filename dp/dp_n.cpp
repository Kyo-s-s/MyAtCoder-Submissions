#include<bits/stdc++.h>
using namespace std;

using ll = long long;

template<class T> struct CumulativeSum {
    int n;
    vector<T> data; 
    bool builded = false;
    CumulativeSum(int n) : n(n), data(n + 1) {}
    CumulativeSum(const vector<T> &v) : n(v.size()), data(n + 1) {
        for (int i = 0; i < n; i++) {
            data[i + 1] = v[i];
        }
    }

    void build() {
        for (int i = 0; i < n; i++) {
            data[i + 1] += data[i];
        }
        builded = true;
    }

    T sum(int r) {
        if (!builded) build();
        assert(0 <= r && r <= n);
        return data[r];
    }

    T sum(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        return sum(r) - sum(l);
    }

};

int main() {

  ll N; cin >> N;
  vector<ll> A(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }

  CumulativeSum<ll> cum(A);

  vector<vector<ll>> memo(N + 10, vector<ll>(N + 10, -1));

  auto dp = [&](auto &&sf, ll l, ll r) -> ll {
    if (l + 1 == r) {
      return 0;
    }
    
    if (memo[l][r] != -1) {
      return memo[l][r];
    }
    
   ll res = 1LL << 58;
    for (ll i = l + 1; i < r; i++) {
      res = min(res, sf(sf, l, i) + sf(sf, i, r) + cum.sum(l, r));
    }
    
    memo[l][r] = res;
    return res;
  };


  cout << dp(dp, 0, N) << endl;
  
}
