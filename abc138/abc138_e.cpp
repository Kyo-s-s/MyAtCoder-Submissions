#include<bits/stdc++.h>
using namespace std; 
  
#define rep(i, n) for (int i = 0; i < (n); i++)

const int INF = 1 << 28;
using ll = long long;

int main() {

  string S, T; cin >> S >> T;
  int N = S.size();
    
  vector<vector<ll>> app;
  rep(i, 26) {
    vector<ll> ap(N, INF);
    for (int j = N - 1; j >= 0; j--) {
      if (j + 1 < N) ap[j] = ap[j + 1];
      if (S[j] == 'a' + i) {
        ap[j] = j;
      }
    }
    app.push_back(ap);
  }



  ll ans = -1;  
  for (auto t : T) {
    if (t == '\n') continue;
    ans++;
    ll nxt = [&]() {
      if (app[t - 'a'][ans % N] != INF) {
        return (ans / N) * N + app[t - 'a'][ans % N];
      }
      if (app[t - 'a'][0] != INF) {
        return (ans / N + 1) * N + app[t - 'a'][0];
      }
      cout << -1 << endl;
      exit(0);
    }();
    ans = nxt;
  }

  cout << ans + 1 << endl;


}
