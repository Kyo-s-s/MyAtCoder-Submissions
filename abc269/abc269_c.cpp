#include<bits/stdc++.h>
using namespace std;


using ll = long long;

int main() {
  ll N; cin >> N;
  vector<ll> ans;
  for (ll x = N; x >= 0; x = N & (x - 1)) {
    ans.push_back(x);
    if (x == 0) break;
  }
  sort(ans.begin(), ans.end());
  for (auto a : ans) cout << a << endl;
}