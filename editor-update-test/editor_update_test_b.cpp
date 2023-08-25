#include<bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
  int N; cin >> N;
  vector<vector<ll>> G(N);
  for (int i = 1; i < N; i++) {
    int p; cin >> p; p--;
    G[i].push_back(p);
    G[p].push_back(i);
  }
  
  vector<int> ans(N, -1);
  
  auto dfs = [&](auto&& self, int now, int par) -> void {
    if (ans[now] != -1) return;
    ans[now] = 1;
    for (auto e : G[now]) if (e != par) {
      self(self, e, now);
      ans[now] += ans[e]; 
    }
  };
  
  dfs(dfs, 0, -1);
  for (int i = 0; i < N; i++) {
    cout << ans[i] << '\n';
  }
  
}