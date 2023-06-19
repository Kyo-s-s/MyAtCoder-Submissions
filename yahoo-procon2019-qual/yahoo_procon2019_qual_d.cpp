#include<bits/stdc++.h>
using namespace std;

using ll = long long;

template<class T> bool chmin(T &a, const T &b) {if(b<a){ a=b; return 1;} return 0;}

int main() {

  int L; cin >> L;

  vector<ll> dp(5, 1LL << 58);
  dp[0] = 0;

  auto even = [&](ll a) -> ll {
    if (a == 0)  return 2;
    return a % 2;
  };

  auto odd = [&](ll a) -> ll {
    if (a == 0)  return 1;
    return (a + 1) % 2;
  };

  for (int l = 0; l < L; l++) {
    ll a; cin >> a;
    vector<ll> pd(5, 1LL << 58);

    chmin(pd[0], dp[0] + a);
    
    chmin(pd[1], dp[0] + even(a)); 
    chmin(pd[1], dp[1] + even(a));
      
    chmin(pd[2], dp[0] + odd(a));
    chmin(pd[2], dp[1] + odd(a));
    chmin(pd[2], dp[2] + odd(a));

    chmin(pd[3], dp[0] + even(a));
    chmin(pd[3], dp[1] + even(a));
    chmin(pd[3], dp[2] + even(a));
    chmin(pd[3], dp[3] + even(a));

    chmin(pd[4], dp[0] + a);
    chmin(pd[4], dp[1] + a);
    chmin(pd[4], dp[2] + a);
    chmin(pd[4], dp[3] + a);
    chmin(pd[4], dp[4] + a);

    dp = pd;

  }
  
  ll ans = (1LL << 58);
  for (auto d : dp) chmin(ans, d);

  cout << ans << endl;
  
}
