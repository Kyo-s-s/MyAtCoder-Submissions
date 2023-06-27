#include<bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {

  ll N, A, B; cin >> N >> A >> B; 

  auto drop = []() {
    cout << -1 << endl;
    exit(0);
  };

  if (B == 1) {
    if (A == N) {
      vector<int> v;
      for (int i = 1; i <= N; i++) v.push_back(i);
      for (auto e : v) cout << e << " ";
      cout << endl;
      exit(0);
    } else {
      drop();
    }
  }

  ll mo = N - A;
  vector<int> cnt(B, 0);
  cnt[0] = A;
  while (mo > 0) {
    for (int i = 1; i < B; i++) {
      if (mo > 0) {
        cnt[i]++; mo--;
      } 
    }
  }

  if (!all_of(cnt.begin(), cnt.end(), [&](int v) {
    return 0 < v && v <= A;
  })) {
    drop();
  }
  
  vector<vector<int>> t;
  int add = 1;
  for (auto c : cnt) {
    t.push_back({});
    for (int i = 0; i < c; i++) {
      t.back().push_back(add); add++;
    }
  }

  reverse(t.begin(), t.end());
  vector<int> ans;
  for (auto s : t) {
    for (auto c : s) {
      ans.push_back(c);
    }
  }
  for (auto a : ans) cout << a << " ";



}
