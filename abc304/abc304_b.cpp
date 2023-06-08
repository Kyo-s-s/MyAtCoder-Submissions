#include<bits/stdc++.h>
using namespace std;

using ll = long long; 

int main() {
  

  ll N; cin >> N;
  ll cnt = 0;
  while (N > 999) {
    cnt++;
    N /= 10;
  }

  for (int i = 0; i < cnt; i++) {
    N *= 10;
  }

  cout << N << endl;

  
}
