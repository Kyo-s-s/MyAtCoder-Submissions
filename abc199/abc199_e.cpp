#include<bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, n) for (ll i = 0; i < (n); i++)

int main() {

  ll N, M; cin >> N >> M;
  vector<ll> X(M), Y(M), Z(M);
  rep(i, M) {
    cin >> X[i] >> Y[i] >> Z[i];
  }

  vector<ll> dp(1 << N, 0);
  dp[0] = 1;

  auto bit = [](ll s) -> ll {
    ll c = 0;
    while (s > 0) {
      c += s % 2;
      s /= 2;
    }
    return c;
  };

  auto check = [&](ll s) -> bool {
    ll b = bit(s);   
    rep(i, M) if (X[i] == b) {
      // Y[i] 以下の数
      ll c = 0;
      rep(j, Y[i]) {
        if ((s >> j) & 1) c++;
      }
      if (c > Z[i]) return false;
    }
    return true;
  };

  rep(S, 1 << N) {
    rep(i, N) if (!((S >> i) & 1)) {
      if (check(S | (1 << i))) {
        dp[S | (1 << i)] += dp[S];
      }     
    }
  }
  
  cout << dp[(1 << N) - 1] << endl;
  
}
