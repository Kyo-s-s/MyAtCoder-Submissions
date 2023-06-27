#include<bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, n) for (ll i = 0; i < (n); i++)

int main() {

  ll N, D; cin >> N >> D;  

  vector<pair<ll, ll>> LR;
  rep(i, N) {
    ll l, r; cin >> l >> r;
    LR.push_back({l, r});
  }

  sort(LR.begin(), LR.end(), [&](auto x, auto y) {
    ll xl = x.first;
    ll xr = x.second;
    ll yl = y.first;
    ll yr = y.second;
    if (xr == yr) {
      return xl < yl; 
    }
    return xr < yr;
  });

  ll p = -(1LL << 58);
  ll ans = 0;
  for (auto [l, r] : LR) {
    ll x = p, y = p + D - 1;
    if ([&](){
      if (l <= x && x <= r) return false;
      if (l <= y && y <= r) return false;
      if (x <= l && l <= y) return false;
      if (x <= r && r <= y) return false;
      return true;
    }()) {
      p = r;
      ans++;
    }
  }

  cout << ans << endl;


}
