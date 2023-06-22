#include<bits/stdc++.h>
using namespace std;

int main() {
  
  vector<vector<int>> memo(2000, vector<int>(3000, -1));

  auto grundy = [&](auto&& g, int w, int b) -> int {
    if (memo[w][b] != -1) {
      return memo[w][b];
    }
    if (w == 0 && b <= 1) {
      return 0;
    }
    set<int> st;

    if (w >= 1) {
      st.insert(g(g, w - 1, b + w));
    }
    if (b >= 2) {
      for (int k = 1; k <= b / 2; k++) {
        st.insert(g(g, w, b - k));
      }
    }

    int res = 0;
    while (st.count(res)) res++;
    memo[w][b] = res;
    return res;
  };

  int N; cin >> N;
  vector<int> W(N), B(N);
  for (int i = 0; i < N; i++) cin >> W[i];
  for (int i = 0; i < N; i++) cin >> B[i];

  int g = 0;
  for (int i = 0; i < N; i++) {
    int w = W[i], b = B[i];
    g ^= grundy(grundy, w, b);
  }

  if (g != 0) {
    cout << "First" << endl;
  } else {
    cout << "Second" << endl;
  }

}
