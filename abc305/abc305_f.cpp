#include<bits/stdc++.h>
using namespace std;

int main() {

  int N, M; cin >> N >> M;
  vector<bool> vis(N, false);
  
  auto dfs = [&](auto &&sf, int now, int prev) -> void {
    vis[now] = true;
    int k; cin >> k;
    vector<int> v(k);
    for (int i = 0; i < k; i++) {
      cin >> v[i];
      v[i]--;
    }
  
    for (auto e : v) if (!vis[e]) {
      cout << e + 1 << endl;
      if (e + 1 == N) {
        exit(0);
      }
      sf(sf, e, now);
      
      cout << now + 1 << endl;
      int kk; cin >> kk;
      vector<int> vv(kk);
      for (int i = 0; i < kk; i++) {
        cin >> vv[i];
        vv[i]--;
      }
    }

  };

  dfs(dfs, 0, 0);



}
