#include<bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, n) for (ll i = 0; i < (n); i++)

struct UnionFind {
    int n, cnt;
    vector<int> parent;
    UnionFind() : n(0), cnt(0) {}
    UnionFind(int n) : n(n), cnt(n), parent(n, -1) {}

    int merge(int a, int b) {
        assert(0 <= a && a < n && 0 <= b && b < n);
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-parent[x] < -parent[y]) swap(x, y);
        parent[x] += parent[y];
        parent[y] = x;
        cnt--;
        return x;
    } 

    int leader(int a) {
        assert(0 <= a && a < n);
        if (parent[a] < 0) return a;
        return parent[a] = leader(parent[a]);
    }

    bool same(int a, int b) {
        assert(0 <= a && a < n && 0 <= b && b < n);
        return leader(a) == leader(b);
    }

    int size(int a) {
        assert(0 <= a && a < n);
        return -parent[leader(a)];
    }

    int count() { return cnt; }

    vector<vector<int>> groups() {
        vector<int> leader_buf(n), group_size(n);
        for (int i = 0; i < n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        vector<vector<int>> result(n);
        for (int i = 0; i < n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(
            remove_if(result.begin(), result.end(),
                      [&](const vector<int> &v) { return v.empty(); }),
            result.end());
        return result;
    }
};

int main() {

  ll N, M; cin >> N >> M;
  vector<ll> D(N);
  rep(i, N) cin >> D[i];
  bool ok = true;
  vector<vector<ll>> G(N);
  {
    ll sum = 0;
    for (auto e : D) sum += e;
    if (2 * (N - 1) != sum) {
      ok = false;
    }
  }

  UnionFind uf(N);
  rep(i, M) {
    ll a, b; cin >> a >> b; a--; b--; 
    if (uf.same(a, b)) ok = false; 
    D[a]--;
    D[b]--;
    uf.merge(a, b);
    G[a].push_back(b);
    G[b].push_back(a);
  }

  auto drop = []() {
    cout << -1 << endl;
    exit(0);
  };

  if (!ok) {
    drop();
  }

  auto g = uf.groups();
  vector<vector<int>> U, sz1;
  for (auto v : g) {
    vector<int> u;
    for (auto e : v) {
      rep(j, D[e]) u.push_back(e);
    }
    if ((int)u.size() == 0) {
      drop();   
    }
    if ((int)u.size() == 1) {
      sz1.push_back(u);
    } else {
      U.push_back(u);
    }
  }

  vector<pair<ll, ll>> ans;
  while (sz1.size() > 0) {
    ll a = sz1.back()[0]; sz1.pop_back();
    if (U.empty()) {
      if (sz1.size() == 1) {
        ll b = sz1.back()[0];
        uf.merge(a, b);
        ans.push_back({a, b});
        break;
      } 
      drop();
    }
    ll b = U.back().back(); U.back().pop_back();
    uf.merge(a, b);
    ans.push_back({a, b});
    if (U.back().size() == 1) {
      sz1.push_back(U.back());
      U.pop_back();
    }
  }
  
  if (uf.count() != 1) {
    cout << "a" << endl;
    drop();
  }

  for (auto [x, y] : ans) {
    cout << x + 1 << " " << y + 1 << endl;
  }
}
