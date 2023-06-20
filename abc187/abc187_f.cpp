#include<bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {

  ll N, M; cin >> N >> M;
  vector<vector<bool>> edge(N, vector<bool>(N, false));
  for (int i = 0; i < M; i++) {
    int a, b; cin >> a >> b;
    a--; b--;
    edge[a][b] = true;
    edge[b][a] = true;
  }

  for (int i = 0; i < N; i++) edge[i][i] = true;

  vector<bool> complete(1 << N, false);

  for (int s = 0; s < (1 << N); s++) {
    complete[s] = [&]() {
      for (int i = 0; i < N; i++) if ((s >> i) & 1) {
        for (int j = 0; j < N; j++) if ((s >> j) & 1) {
          if (!edge[i][j]) return false;
        }
      }
      return true;
    }();
  }

  vector<ll> dp(1 << N, 1LL << 58);
  for (int s = 0; s < (1 << N); s++) if (complete[s]) {
    dp[s] = 1;
  }

  for (int s = 0; s < (1 << N); s++) {
    for (int t = s; --t &= s; ) {
      dp[s] = min(dp[s], dp[t] + dp[s ^ t]);
    }
  }

  cout << dp[(1 << N) - 1] << endl;

}
