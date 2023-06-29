#include<bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, n) for (ll i = 0; i < (n); i++)


const ll INF = 1LL << 58;

int main() {

  ll N, M; cin >> N >> M;
  vector<ll> A(N);
  rep(i, N) cin >> A[i];

  vector<vector<ll>> G(N);
  rep(i, M) {
    ll x, y; cin >> x >> y; x--; y--; 
    G[x].push_back(y);
  }
  
  vector<ll> U(N, INF);

  ll ans = -INF;
  rep(i, N) {
    ans = max(ans, A[i] - U[i]);
    U[i] = min(U[i], A[i]); 
    for (auto e : G[i]) {
      U[e] = min(U[e], U[i]); 
    }
  }

  cout << ans << endl;


}

