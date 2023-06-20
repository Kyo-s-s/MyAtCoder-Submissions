#include<bits/stdc++.h>
using namespace std;

using ll = long long;

void drop(bool fl) {
  cout << (fl ? "YES" : "NO") << endl;
  exit(0);
}


int main() {

  ll N; cin >> N; 
  vector<ll> A(N); 
  for (int i = 0; i < N; i++) cin >> A[i];

  ll sum = 0;
  for (auto a : A) sum += a;
  ll dec = N * (N + 1) / 2;

  if (sum % dec != 0) {
    drop(false);
  }

  ll k = sum / dec;

  vector<ll> diff;
  for (int i = 0; i < N; i++) {
    diff.push_back(A[(i + 1) % N] - A[i] - k);   
  }

  drop(all_of(diff.begin(), diff.end(), [&](ll x) {
    return x <= 0 && x % N == 0; 
  }));

}
