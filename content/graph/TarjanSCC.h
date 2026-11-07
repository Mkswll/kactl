/**
 * Author: Maxwell He
 * Date: 
 * License: 
 * Source: 
 * Description: 
 */
#pragma once

struct TarjanSCC {
    int n, timer = 0;
    vector<vector<int>> adj, components;
    vector<int> tin, low, comp, st;
    vector<bool> inStack;

    TarjanSCC(int n) : n(n), adj(n), tin(n, -1),
        low(n), comp(n, -1), inStack(n, false) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void dfs(int u) {
        tin[u] = low[u] = timer++;
        st.push_back(u);
        inStack[u] = true;

        for (int v : adj[u]) {
            if (tin[v] == -1) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if (inStack[v]) {
                low[u] = min(low[u], tin[v]);
            }
        }

        if (low[u] == tin[u]) {
            int id = components.size();
            components.emplace_back();
            while (true) {
                int v = st.back();
                st.pop_back();
                inStack[v] = false;
                comp[v] = id;
                components.back().push_back(v);
                if (v == u) break;
            }
        }
    }

    void build() {
        for (int u = 0; u < n; ++u)
            if (tin[u] == -1) dfs(u);
    }
};
