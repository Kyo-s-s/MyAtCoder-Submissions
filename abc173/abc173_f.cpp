#include<bits/stdc++.h>
using namespace std;

using ll = long long;




int main() {

  ll N; cin >> N;
  ll ans = N * (N * N + 3 * N + 2) / 6;

  for (int i = 0; i < N - 1; i++) {
    ll u, v; cin >> u >> v;
    if (u > v) swap(u, v);
    ans -= (u - 1 + 1) * (N - v + 1);
  }

  cout << ans << endl;
  
}
