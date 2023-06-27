#include<bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, n) for (ll i = 0; i < (n); i++)

struct pos {
  ll x, y;
  pos(ll x, ll y) : x(x), y(y) {}
};


int main() {
  int N; cin >> N;

  vector<pair<pos, pos>> V;
  rep(i, N) {
    ll x, y; cin >> x >> y;
    V.push_back({
        pos(x - 1, y),
        pos(x, y - 1)
    });
  }

  auto is_big = [&](pos a, pos b) {
    if (a.y * b.x == a.x * b.y) {
      return a.x > b.x;
    }
    return a.y * b.x > a.x * b.y;
  };

  auto is_big_ = [&](pos a, pos b) {
    if (a.y * b.x == a.x * b.y) {
      return true;
    }
    return a.y * b.x > a.x * b.y;
  };

  sort(V.begin(), V.end(), [&](auto a, auto b) {
    pos A = a.second;
    pos B = b.second;
    return is_big(A, B);
  });

  pos now(0, 1);
  ll ans = 0;
  for (auto v : V) {
    pos e = v.first;
    if (is_big_(now, e)) {
      now = v.second;
      ans++;
    }     
  }

  cout << ans << endl;

}
