#include <vector>

void dfs(int v, int u, int& t, std::vector<std::vector<int>>& graph, std::vector<bool>& visited,
        std::vector<int>& pre, std::vector<int>& low, std::vector<bool>& is_articulation_point) {
    visited[v] = true;
    pre[v] = low[v] = t++;
    int children = 0;
    for (auto w : graph[v]) {
        if (w == u) continue;
        if (visited[w]) low[v] = std::min(low[v], pre[w]);
        else {
            children++;
            dfs(w, v, t, graph, visited, pre, low, is_articulation_point);
            low[v] = std::min(low[v], low[w]);
            if (low[w] >= pre[v] && v != u) is_articulation_point[v] = true;
        }
    }
    if (v == u && children > 1) is_articulation_point[v] = true;
}

std::vector<int> find_articulation_points(std::vector<std::vector<int>>& graph) {
    std::vector<int> articulation_points; 
    int n = graph.size();
    std::vector<bool> visited(n);
    std::vector<int> pre(n);
    std::vector<int> low(n);
    std::vector<bool> is_articulation_point(n);

    int t = 0;
    for (int i = 0; i < n; i++) if (!visited[i]) dfs(i, i, t, graph, visited, pre, low, is_articulation_point);

    for (int i = 0; i < n; i++) if (is_articulation_point[i]) articulation_points.push_back(i);

    return articulation_points;
}
