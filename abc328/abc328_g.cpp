#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;
template<class T> bool chmin(T &a, const T &b) {if(b<a){ a=b; return 1;} return 0;}
#define INF (1LL << 60)
#define rep(i, n) for (ll i = 0; i < (n); i++)

int main() {

    ll N, C; cin >> N >> C;
    vll A(N), B(N);
    for (auto &a : A) cin >> a;
    for (auto &b : B) cin >> b;

    vll dp(1 << N, INF);
    dp[0] = (N - 1) * C;

    rep(msk, (1 << N)) {
        ll cost = dp[msk];
        ll i = __builtin_popcountll(msk);
        vll mov;
        for (ll w = 1; w + i <= N; w++) {
            mov.push_back(A[i + w - 1]);
            ll wmsk = (1 << w) - 1;
            for (ll j = 0; j + w <= N; j++) {
                if ((msk | (wmsk << j)) == (msk + (wmsk << j))) {
                    ll nmsk = msk | (wmsk << j);
                    ll ncost = cost;
                    for (int k = 0; k < w; k++) {
                        ncost += abs(mov[k] - B[j + k]);
                    }
                    ncost -= (w - 1) * C;
                    chmin(dp[nmsk], ncost);
                }
            }
        }
    }

    cout << dp[(1 << N) - 1] << endl;
}