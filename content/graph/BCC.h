/**
 * Author: Maxwell He
 * Date: 
 * License: 
 * Source: 
 * Description: 
 */
#pragma once

struct BiconnectedComponents {
    int n, timer = 0;
    vector<vector<pair<int, int>>> adj;
    vector<pair<int, int>> edges;
    vector<vector<int>> components;
    vector<int> tin, low, st, seen;
    vector<bool> isArt, covered;

    BiconnectedComponents(int n) : n(n), adj(n),
        tin(n, -1), low(n), seen(n, -1),
        isArt(n, false), covered(n, false) {}

    void addEdge(int u, int v) {
        int id = edges.size();
        edges.emplace_back(u, v);
        adj[u].emplace_back(v, id);
        adj[v].emplace_back(u, id);
    }

    void extract(int last) {
        int id = components.size();
        components.emplace_back();

        while (true) {
            int e = st.back();
            st.pop_back();
            auto [u, v] = edges[e];

            if (seen[u] != id) {
                seen[u] = id;
                covered[u] = true;
                components.back().push_back(u);
            }
            if (seen[v] != id) {
                seen[v] = id;
                covered[v] = true;
                components.back().push_back(v);
            }

            if (e == last) break;
        }
    }

    void dfs(int u, int pe = -1) {
        tin[u] = low[u] = timer++;
        int children = 0;

        for (auto [v, id] : adj[u]) {
            if (id == pe) continue;

            if (tin[v] == -1) {
                ++children;
                st.push_back(id);
                dfs(v, id);
                low[u] = min(low[u], low[v]);

                if (low[v] >= tin[u]) {
                    if (pe != -1) isArt[u] = true;
                    extract(id);
                }
            } else if (tin[v] < tin[u]) {
                st.push_back(id);
                low[u] = min(low[u], tin[v]);
            }
        }

        if (pe == -1 && children > 1)
            isArt[u] = true;
    }

    void build() {
        for (int u = 0; u < n; ++u)
            if (tin[u] == -1) dfs(u);

        for (int u = 0; u < n; ++u)
            if (!covered[u])
                components.push_back({u});
    }
};
