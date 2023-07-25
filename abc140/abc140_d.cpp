#include<bits/stdc++.h>
using namespace std;

int main() {


  int n, k; cin >> n >> k;
  string s; cin >> s;
  
  vector<pair<char, int>> st;
  for (auto c : s) {
    if (st.empty() || st.back().first != c) {
      st.push_back(make_pair(c, 1));
    } else {
      st.back().second++;
    }
  }
  
  int ans = n - st.size();
  ans += min((int)st.size() - 1, k * 2);
  cout << ans<< endl;


}