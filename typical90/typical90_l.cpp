#include<bits/stdc++.h>
using namespace std;

// UnionFind
struct DSU {
    int n;
    vector<int> parent;

    DSU(int n) : n(n) {
        parent.resize(n, -1);
    }

    int leader(int u) {
        if (parent[u] < 0) return u;
        parent[u] = leader(parent[u]);
        return parent[u];
    }

    int same(int a, int b) {
        return leader(a) == leader(b);
    }

    void merge(int a, int b) {
        int u = leader(a);
        int v = leader(b);
        if (u == v) return;
        if (size(u) < size(v)) swap(u, v);
        parent[u] += parent[v];
        parent[v] = u;
    }

    int size(int u) {
        return -parent[leader(u)];
    }

};


int main() {

    int H, W; cin >> H >> W;
    auto ch = [&](int x, int y) -> int {
        return 2020 * x + y;
    };
    vector board(H, vector<bool>(W, false));
    vector<pair<int, int>> dxy = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    DSU dsu(2020 * 2020);
    int Q; cin >> Q;
    while (Q--) {
        int t; cin >> t;

        if (t == 1) {
            int r, c; cin >> r >> c;
            r--; c--;
            board[r][c] = true;
            for (auto [dx, dy] : dxy) {
                int nx = r + dx, ny = c + dy;
                if (!(0 <= nx && nx < H && 0 <= ny && ny < W)) {
                    continue;
                }
                if (!board[nx][ny]) {
                    continue;
                }
                dsu.merge(ch(r, c), ch(nx, ny));
            }
        }

        if (t == 2) {
            int ra, ca, rb, cb; cin >> ra >> ca >> rb >> cb;
            ra--; ca--; rb--; cb--;
            if (board[ra][ca] && dsu.same(ch(ra, ca), ch(rb, cb))) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
    }

}