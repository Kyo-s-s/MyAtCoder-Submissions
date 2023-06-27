#include<bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, n) for (ll i = 0; i < (n); i++)



int main() {

  ll N, K; cin >> N >> K;  
  vector<int> A(K);
  rep(i, K) cin >> A[i];
  for (auto &a : A) a--;
  vector<pair<ll, ll>> XY;
  rep(i, N) {
    ll x, y; cin >> x >> y;
    XY.push_back({x, y});
  }


  ll dist = 0;
  rep(i, N) {
    auto [x, y] = XY[i];
    ll dim = (1LL << 58);
    for (auto a : A) {
      ll dx = abs(XY[a].first - x);
      ll dy = abs(XY[a].second - y);
      dim = min(dim, dx * dx + dy * dy);
    }
    dist = max(dist, dim);
  }   

  double ans = sqrt(dist);
  cout << fixed << setprecision(15); 
  cout << ans << endl;

}
