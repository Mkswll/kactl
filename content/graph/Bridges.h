/**
 * Author: Maxwell He
 * Date: 
 * License: 
 * Source: 
 * Description: 
 */
#pragma once

struct Bridges {
    int n, timer = 0;
    vector<vector<pair<int, int>>> adj;
    vector<pair<int, int>> edges;
    vector<int> tin, low, bridges;

    Bridges(int n) : n(n), adj(n), tin(n, -1), low(n) {}

    void addEdge(int u, int v) {
        int id = edges.size();
        edges.emplace_back(u, v);
        adj[u].emplace_back(v, id);
        adj[v].emplace_back(u, id);
    }

    void dfs(int u, int pe = -1) {
        tin[u] = low[u] = timer++;

        for (auto [v, id] : adj[u]) {
            if (id == pe) continue;

            if (tin[v] == -1) {
                dfs(v, id);
                low[u] = min(low[u], low[v]);

                if (low[v] > tin[u])
                    bridges.push_back(id);
            } else {
                low[u] = min(low[u], tin[v]);
            }
        }
    }

    void build() {
        for (int u = 0; u < n; ++u)
            if (tin[u] == -1) dfs(u);
    }
};
