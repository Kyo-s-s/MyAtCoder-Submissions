#include<bits/stdc++.h>
using namespace std;


#define rep(i, n) for (int i = 0; i < (n); i++)


int main() {
  int N, M; cin >> N >> M;

  vector<pair<int, int>> A;
  rep(i, M) {
    int a, b; cin >> a >> b;
    a--; b--;
    A.push_back({a, b});
    A.push_back({b, a});
  }
  sort(A.begin(), A.end());

  vector<pair<int, int>> C;
  rep(i, M) {
    int a, b; cin >> a >> b;
    a--; b--;
    C.push_back({a, b});
    C.push_back({b, a}); 
  }

  vector<int> v;
  rep(i, N) v.push_back(i);

  do {
    vector<pair<int, int>> X;
    for (auto [x, y] : C) {
      X.push_back({v[x], v[y]});
    }
    sort(X.begin(), X.end());
    if (X == A) {
      cout << "Yes" << endl;
      exit(0);
    }

  } while (next_permutation(v.begin(), v.end()));

  cout << "No" << endl;


}   
