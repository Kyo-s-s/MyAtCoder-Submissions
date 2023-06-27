#include<bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, n) for (ll i = 0; i < (n); i++) 

int main() {

  ll N, K; cin >> N >> K; 
  vector<ll> A(K);
  rep(i, K) cin >> A[i];

  set<ll> S;
  for (auto a : A) S.insert(a);
  vector<vector<int>> v(K + 1);
  int addidx = 0;

  rep(u, N) {
    int a = u + 1;
    if (S.count(a)) continue;

    auto nxt = [&]() {
      if (addidx < K) {
        return A[addidx];
      } else {
        return 1LL << 58;
      }
    };
    while (!(a < nxt())) addidx++;
    v[addidx].push_back(a);
    if (addidx < K - 1) addidx++;
  } 

   rep(k, K) v[k].push_back(A[k]);
   swap(v[K - 1], v[K]);
   rep(k, K + 1) {
     reverse(v[k].begin(), v[k].end());
   }

  for (auto vv : v) {
    for (auto e : vv) {
      cout << e << " ";
    }
  }


}

