#include<bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, n) for (ll i = 0; i < (n); i++)

int main() {
  int H, W; cin >> H >> W;
  vector<string> S(H);
  rep(i, H) {
    cin >> S[i];
  }

  vector<pair<ll, ll>> dxy = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0},
    {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
  };

  auto in = [&](ll h, ll w) -> bool {
    return 0 <= h && h < H && 0 <= w && w < W;
  };

  rep(h, H) rep(w, W) for (auto [dx, dy] : dxy) {
    vector<pair<int, int>> v;
    string s;
    ll nh = h, nw = w;
    rep(i, 5) {
      if (!in(nh, nw)) continue;      
      v.push_back({nh + 1, nw + 1});
      s += S[nh][nw];
      nh += dx, nw += dy;
    }

    if (v.size() != 5) continue;
    if (s != "snuke") continue;
    for (auto [x, y] : v) {
      cout << x << " " << y << endl;
    }
    exit(0);
  }



}

