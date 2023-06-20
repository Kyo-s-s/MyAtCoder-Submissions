#include<bits/stdc++.h>
using namespace std;


using ll = long long;


void solve() {

  ll N; cin >> N;  
  vector<ll> C(N);
  for (int i = 0; i < N; i++) cin >> C[i];

  vector<int> cnt(N + 1, 0);
  for (auto c : C) cnt[c]++;

  priority_queue<pair<int, int>> que;
  for (int i = 1; i <= N; i++) if (cnt[i] > 0) {
    que.push({cnt[i], i});
  }

  deque<ll> ans;
  auto dfs = [&](auto &&sf) -> void {
    if (que.empty()) return;
    auto [c, v] = que.top(); que.pop();
    for (int i = 0; i < c - 1; i++) {
      ans.push_back(v);
      sf(sf);
    }
    ans.push_back(v);
  };

  auto [c, v] = que.top(); que.pop();
  for (int i = 0; i < c; i++) {
    ans.push_back(v);
    dfs(dfs);
  }

  while (!que.empty()) {
    dfs(dfs);
  }

  for (int i = 0; i < ans.size(); i++) {
    cout << ans[i] << (i == ans.size() - 1 ? "\n" : " ");
  }

}

int main() {

  int T; cin >> T;
  while (T--) solve();

}
