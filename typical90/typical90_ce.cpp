#include<bits/stdc++.h>
using namespace std;

using ll = long long;


int main() {

  ll N, M; cin >> N >> M;
  vector<vector<int>> G(N);
  for (int i = 0; i < M; i++) {
    ll a, b; cin >> a >> b;
    a--; b--;
    G[a].push_back(b);
    G[b].push_back(a);
  }

  vector<bool> is_big(N, false);
  for (int i = 0; i < N; i++) {
    ll sz = G[i].size();
    if (sz * sz > M) {
      is_big[i] = true;
    }
  }
  vector<vector<int>> big_G(N);
  for (int a = 0; a < N; a++) {
    for (int b : G[a]) {
      if (is_big[b]) {
        big_G[a].push_back(b);
      }
    }
  }

  vector<ll> color(N, 1);
  vector<pair<ll, ll>> update(N, {-1, 1});

  int Q; cin >> Q;
  vector<ll> ans;
  vector<tuple<int, int, ll>> query;
  for (int i = 0; i < Q; i++) {
    int x; ll y; cin >> x >> y;
    x--;

    if (is_big[x]) {
      // ans.push_back(color[x]); 
      cout << color[x] << "\n";
    } else {
      ll mt = update[x].first, v = update[x].second;
      for (auto e : G[x]) {
        if (update[e].first > mt) {
          mt = update[e].first;
          v = update[e].second;
        }
      }
      // ans.push_back(v);
      cout << v << "\n";
    }

    color[x] = y;
    for (int e : big_G[x]) {
      color[e] = y;
    }

    update[x] = {i, y};
  }

}
