#include<bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, n) for (ll i = 0; i < (n); i++)

int main() {

  ll N, X; cin >> N >> X;
  string S; cin >> S;

  string T;
  for (auto s : S) {
    if (!T.empty() && T.back() != 'U' && s == 'U') {
      T.pop_back();
    } else {
      T.push_back(s);
    }
  }

  for (auto t : T) {
    if (t == 'U') X /= 2;
    if (t == 'L') X = X * 2;
    if (t == 'R') X = X * 2 + 1;
  }

  cout << X << endl;
}
