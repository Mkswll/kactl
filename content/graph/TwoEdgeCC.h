/**
 * Author: Maxwell He
 * Date: 
 * License: 
 * Source: 
 * Description: 
 */
#pragma once

struct TwoEdgeCC {
    int n, timer = 0, m = 0;
    vector<vector<pair<int, int>>> adj;
    vector<vector<int>> components;
    vector<int> tin, low, comp;
    vector<bool> isBridge;

    TwoEdgeCC(int n) : n(n), adj(n),
        tin(n, -1), low(n), comp(n, -1) {}

    void addEdge(int u, int v) {
        adj[u].emplace_back(v, m);
        adj[v].emplace_back(u, m);
        ++m;
    }

    void dfs(int u, int pe = -1) {
        tin[u] = low[u] = timer++;

        for (auto [v, id] : adj[u]) {
            if (id == pe) continue;

            if (tin[v] == -1) {
                dfs(v, id);
                low[u] = min(low[u], low[v]);

                if (low[v] > tin[u])
                    isBridge[id] = true;
            } else {
                low[u] = min(low[u], tin[v]);
            }
        }
    }

    void dfsComp(int u, int id) {
        comp[u] = id;
        components[id].push_back(u);

        for (auto [v, eid] : adj[u]) {
            if (!isBridge[eid] && comp[v] == -1)
                dfsComp(v, id);
        }
    }

    void build() {
        isBridge.assign(m, false);

        for (int u = 0; u < n; ++u)
            if (tin[u] == -1) dfs(u);

        for (int u = 0; u < n; ++u) {
            if (comp[u] == -1) {
                int id = components.size();
                components.emplace_back();
                dfsComp(u, id);
            }
        }
    }
};
