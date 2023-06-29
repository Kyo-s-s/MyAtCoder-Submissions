#include<bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, n) for (ll i = 0; i < (n); i++)




int main() {

  vector<pair<ll, ll>> dxy = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0},
    {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
  };

  ll N; cin >> N;
  vector<string> A(N);
  rep(i, N) cin >> A[i];

  ll ans = 0;
  auto ch = [&](string s) -> ll {
    ll res = 0;
    rep(i, (int)s.size()) {
      res *= 10;
      res += (s[i] - '0');
    }
    return res;
  };

  rep(x, N) rep(y, N) for (auto [dx, dy] : dxy) {
    string t = ""; 
    ll nx = x, ny = y;
    rep(i, N) {
      t += A[nx][ny];
      nx = (nx + dx + N) % N;
      ny = (ny + dy + N) % N;
    }
    ll a = ch(t);
    ans = max(ans, a);
  }

  cout << ans << endl;

}

