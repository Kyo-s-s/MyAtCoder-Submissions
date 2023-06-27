#include<bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, n) for (ll i = 0; i < (n); i++) 


int main() {

  ll N, M; cin >> N >> M; 
  vector<vector<int>> G(N);
  rep(i, M) {
    int a, b; cin >> a >> b;
    a--; b--;
    G[a].push_back(b);
    G[b].push_back(a);
  }

  vector<bool> even(N, false), odd(N, false);
  deque<pair<int, bool>> que;
  que.push_back({0, true});
  even[0] = true;

  while (!que.empty()) {
    auto [idx, is_even] = que.front(); que.pop_front();
    for (auto e : G[idx]) {
      if ((is_even ? odd : even)[e]) continue;
      (is_even ? odd : even)[e] = true;
      que.push_back({e, !is_even});
    }
  }

  ll ev = 0, od = 0;
  rep(i, N) {
    if (even[i]) ev++;
    if (odd[i]) od++;
  }

  ll ans = 0;
  rep(i, N) {
    if (even[i]) {
      ll dec = 0;
      for (auto e : G[i]) if (odd[e]) dec++;
      if (odd[i]) dec++;
      ans += od - dec; 
    } else {
      ll dec = 0;
      for (auto e : G[i]) if (even[e]) dec++;
      if (even[i]) dec++;
      ans += ev - dec;
    }
  }
  ans /= 2;

  cout << ans << endl;
}
