#include<bits/stdc++.h>
using namespace std;

using ll = long long;


int main() {

    int N, M; cin >> N >> M;
    vector<string> S(N);
    for (int i = 0; i < N; i++) {
        cin >> S[i];
    }

    sort(S.begin(), S.end());

    bool ans = false;

    do {
        bool ok = true;
        for (int i = 0; i < N - 1; i++) {
            int cnt = 0;
            for (int m = 0; m < M; m++) {
                if (S[i][m] != S[i + 1][m]) {
                    cnt++;
                }
            }
            if (cnt >= 2) {
                ok = false;
                break;
            }
        }

        if (ok) {
            ans = true;
            break;
        }
        
    } while (next_permutation(S.begin(), S.end()));
    

    cout << (ans ? "Yes" : "No") << endl;

}