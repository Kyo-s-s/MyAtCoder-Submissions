#include<bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
  
  ll N; cin >> N;
  string S; cin >> S;
  int Q; cin >> Q;
  while (Q--) {
    int k; cin >> k;

    ll ans = 0;
    ll D = 0;
    ll M = 0;
    ll add = 0;

    auto addchar = [&](char c) {
      if (c == 'D') {
        D++;
      }
      if (c == 'M') {
        M++;
        add += D;
      }
      if (c == 'C') {
        ans += add;
      }
    };

    auto erase = [&](char c) {
      if (c == 'D') {
        D--;
        add -= M;   
      }
      if (c == 'M') {
        M--;
      }
    };

    for (int i = 0; i < N; i++) {
      if (0 <= i - k) {
        erase(S[i - k]);
      }
      addchar(S[i]);
    }
    cout << ans << "\n";
  }
  

  
}
