#include<bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  set<int> S;
  for (int i = 0; i < n; i++) {
    int d; cin >> d;
    S.insert(d);
  }
  cout << S.size() << endl;
}