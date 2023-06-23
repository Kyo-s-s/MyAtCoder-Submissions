#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = (1LL << 58);

int main() {
  ll H, W; cin >> H >> W;
  vector<vector<ll>> A(H, vector<ll>(W, 0));
  for (int h = 0; h < H; h++) {
    for (int w = 0; w < W; w++) {
      cin >> A[h][w];
    }
  }

  vector<pair<ll, ll>> vp;
  for (int h = 0; h < H; h++) {
    ll ma = -INF, mi = INF;
    for (auto a : A[h]) if (a != 0) {
      ma = max(ma, a);
      mi = min(mi, a);
    }
    if (ma == -INF) continue;
    vp.push_back({mi, ma});
  }

  sort(vp.begin(), vp.end());
  vector<ll> vvv;
  for (auto [a, b] : vp) {
    vvv.push_back(a);
    vvv.push_back(b);
  }
  if ([&](){
    for (int i = 0; i < (int)vvv.size() - 1; i++) {
      if (vvv[i] > vvv[i + 1]) return true;
    }
    return false;
  }()) {
    cout << "No" << endl;
    exit(0);
  }

  deque<deque<int>> que;
  for (int i = 0; i < W; i++) {
    que.push_back({i});
  }

  auto sml = [&](int a, int b) {
    bool no = false;
    int res = 0; // 1 : <, 2 : >
    for (int h = 0; h < H; h++) {
      if (A[h][a] == 0 || A[h][b] == 0 || A[h][a] == A[h][b]) continue;
      if (A[h][a] < A[h][b]) {
        if (res == 2) no = true;
        res = 1;
      } else {
        if (res == 1) no = true;
        res = 2;
      }
    }
    if (no) {
      cout << "No" << endl;
      exit(0);
    }
    return res != 2; 
  };

  while (que.size() > 1) {
    auto l = que.front(); que.pop_front();
    auto r = que.front(); que.pop_front();
    deque<int> n;
    while (true) {
      if (l.empty()) break;
      if (r.empty()) break;
      auto a = l.front();
      auto b = r.front();
      if (sml(a, b)) {
        n.push_back(a);
        l.pop_front();
      } else {
        n.push_back(b);
        r.pop_front();
      }
    }
    while (!l.empty()) {
      auto a = l.front(); l.pop_front();
      n.push_back(a);
    }
    while (!r.empty()) {
      auto b = r.front(); r.pop_front();
      n.push_back(b);
    }
    que.push_back(n);
  }

  auto so = que.front();

  vector<vector<int>> ch(H);
  for (auto w : so) {
    for (int h = 0; h < H; h++) {
      ch[h].push_back(A[h][w]);
    }
  }

  if (all_of(ch.begin(), ch.end(), [&](auto& v) {
    for (int i = 0; i < (int)v.size() - 1; i++) {
      if (v[i] == 0 || v[i + 1] == 0) continue;
      if (v[i] > v[i + 1]) return false;
    }
    return true;
  })) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }


}
