#include<bits/stdc++.h>
using namespace std;

template<typename T> 
concept Monoid = requires {
    typename T::T;
    { T::op(std::declval<typename T::T>(), std::declval<typename T::T>()) } -> std::same_as<typename T::T>;
    { T::e() } -> std::same_as<typename T::T>;
};

template<Monoid M> struct Rerooting {
  public:
    using E = typename M::T;
    Rerooting(int N) : N(N) {
        G.resize(N);
    }

    int add_edge(int from, int to) {
        assert(edge_count < N - 1);
        G[from].push_back(edge{to, edge_count});
        G[to].push_back(edge{from, edge_count});
        return edge_count++;
    }

    template<class V>
    vector<V> solve(function<E(V, int)> put_edge, function<V(E, int)> put_node) {
        return solve<V>(put_edge, put_node, put_node);
    }

    template<class V> 
    vector<V> solve(
        function<E(V, int)> put_edge, 
        function<V(E, int)> put_node,
        function<V(E, int)> solve_node
    ) {
        vector<vector<V>> dp(N);
        for (int i = 0; i < N; i++) dp[i].resize(G[i].size());
        auto dfs = [&](auto dfs, int now, int par) -> V {
            int deg = (int)G[now].size();
            E res = M::e();
            for (int i = 0; i < deg; i++) {
                auto [to, id] = G[now][i];
                if (to == par) continue;
                dp[now][i] = dfs(dfs, to, now);
                res = M::op(res, put_edge(dp[now][i], id));
            }
            return put_node(res, now);
        };
        dfs(dfs, 0, -1);
        vector<V> ans(N);
        auto reroot = [&](auto reroot, int now, int par, const optional<V> &v) -> void {
            int deg = (int)G[now].size();
            if (v) {
                for (int i = 0; i < deg; i++) if (G[now][i].to == par) {
                    dp[now][i] = v.value();
                    // dp[now][i] = v;
                }
            }
            vector<E> L(deg + 1, M::e()), R(deg + 1, M::e());
            // TODO: put_edge を複数回呼んでるのは無駄そう
            for (int i = 0; i < deg; i++) {
                L[i + 1] = M::op(L[i], put_edge(dp[now][i], G[now][i].id));
            }
            for (int i = deg - 1; i >= 0; i--) {
                R[i] = M::op(R[i + 1], put_edge(dp[now][i], G[now][i].id));
            }

            // ens[now] = put_node(L[deg], now);
            ans[now] = solve_node(L[deg], now);
            for (int i = 0; i < deg; i++) {
                int u = G[now][i].to;
                if (u == par) continue;
                reroot(reroot, u, now, put_node(M::op(L[i], R[i + 1]), now));
            }
        };
        reroot(reroot, 0, -1, nullopt);
        return ans;
    }

  private:
    int N;
    int edge_count = 0;
    struct edge {
        int to, id;
    };
    vector<vector<edge>> G;
};

struct M {
    using T = long long;
    static T op(T a, T b) { return max(a, b); }
    static T e() { return -1e18; }
};
int main() {

    int N; cin >> N;
    Rerooting<M> tree(N);
    vector<long long> C(N - 1);
    for (int i = 0; i < N - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        int id = tree.add_edge(a, b);
        cin >> C[id];
    }
    vector<long long> D(N);
    for (auto& d : D) cin >> d;

    using E = M::T;
    using V = long long;
    auto put_edge = [&](V v, int id) -> E {
        return v + C[id];
    };
    auto put_node = [&](E e, int v) -> V {
        return max(e, D[v]);
    };
    auto solve_node = [&](E e, int v) -> V {
        return e;
    };
    for (auto ans : tree.solve<V>(put_edge, put_node, solve_node)) {
        cout << ans << endl;
    }
}