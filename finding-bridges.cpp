#include <algorithm>
#include <iostream>
#include <vector>

void dfs(int v, int u, int& t, std::vector<std::vector<int>>& graph, std::vector<bool>& visited, 
        std::vector<int>& pre, std::vector<int>& low, std::vector<std::pair<int, int>>& bridges) {
    visited[v] = true;
    pre[v] = low[v] = t++;
    for (auto w : graph[v]) {
        if (w == u) continue;
        if (visited[w]) low[v] = std::min(low[v], pre[w]);
        else {
            dfs(w, v, t, graph, visited, pre, low, bridges);
            low[v] = std::min(low[v], low[w]);
            if (low[w] > pre[v]) bridges.push_back({std::min(v, w), std::max(w, v)});
        }
    }
}

std::vector<std::pair<int, int>> find_bridges(std::vector<std::vector<int>>& graph) {
    std::vector<std::pair<int, int>> bridges;
    int n = graph.size();
    std::vector<bool> visited(n);
    std::vector<int> pre(n);
    std::vector<int> low(n);

    int t = 0;
    for (int i = 0; i < n; i++) if (!visited[i]) dfs(i, i, t, graph, visited, pre, low, bridges);

    return bridges;
}
