#include<bits/stdc++.h>
using namespace std;
 
using ll = long long;
#define rep(i, n) for (ll i = 0; i < (n); i++)

int main() {

  ll N; cin >> N;
  vector<vector<ll>> F(N, vector<ll>(10));
  rep(i, N) rep(j, 10) cin >> F[i][j];
  vector<vector<ll>> P(N, vector<ll>(10));
  rep(i, N) rep(j, 11) cin >> P[i][j];

  
  ll ans = -1LL << 58;
  rep(S, 1 << 10) {
    if (S == 0) continue;
    ll s = 0;
    rep(i, N) {
      int c = 0;
      rep(j, 10) if (((S >> j) & 1) && F[i][j] == 1) c++;
      s += P[i][c];
    }
    ans = max(ans, s);
  }
  
  cout << ans << endl;
}

