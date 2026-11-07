/**
 * Author: Maxwell He
 * Date: 
 * License: 
 * Source: 
 * Description: 
 */
#pragma once

struct ArticulationPoints {
    int n, timer = 0, m = 0;
    vector<vector<pair<int, int>>> adj;
    vector<int> tin, low;
    vector<bool> isArt;

    ArticulationPoints(int n) : n(n), adj(n),
        tin(n, -1), low(n), isArt(n, false) {}

    void addEdge(int u, int v) {
        adj[u].emplace_back(v, m);
        adj[v].emplace_back(u, m);
        ++m;
    }

    void dfs(int u, int pe = -1) {
        tin[u] = low[u] = timer++;
        int children = 0;

        for (auto [v, id] : adj[u]) {
            if (id == pe) continue;

            if (tin[v] == -1) {
                ++children;
                dfs(v, id);
                low[u] = min(low[u], low[v]);

                if (pe != -1 && low[v] >= tin[u])
                    isArt[u] = true;
            } else {
                low[u] = min(low[u], tin[v]);
            }
        }

        if (pe == -1 && children > 1)
            isArt[u] = true;
    }

    void build() {
        for (int u = 0; u < n; ++u)
            if (tin[u] == -1) dfs(u);
    }
};
