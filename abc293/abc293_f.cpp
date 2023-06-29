#include<bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, n) for (ll i = 0; i < (n); i++)



void solve() {

  ll N;
  cin >> N;
  set<ll> ans;

  auto ch = [&](ll b) -> vector<ll> {
    vector<ll> res;
    ll n = N;
    while (n > 0) {
      res.push_back(n % b);
      n /= b;
    }
    return res;
  };

  for (ll b = 2; b <= 1111; b++) {
    auto c = ch(b);
    if (all_of(c.begin(), c.end(), [&](ll a) {
      return a == 0 || a == 1;   
    })) {
      ans.insert(b);
    }
  }

  int M = 6;
  auto val = [&](ll s, ll b) -> ll {
    ll r = 0;
    rep(i, M) {
      r *= b;
      if ((s >> i) & 1) {
        r += 1;
      }
    } 
    return r;
  };
  
  rep(s, 1 << M) if (s != 0) {
    if (s == 32) continue;
    if (N <= val(s, 1000)) continue;
    ll ng = 1000;  
    ll ok = 1001;
    while (!(N <= val(s, ok))) ok *= 2;
    while (abs(ok - ng) > 1) {
      ll mid = (ok + ng) / 2;
      if (N <= val(s, mid)) {
        ok = mid;
      } else {
        ng = mid;
      }
    }
    if (val(s, ok) == N) {
      ans.insert(ok);
    }
  }

  cout << (int)ans.size() << endl;
}


int main() {

  int T; 
  cin >> T;
  while (T--) solve();

  
}
