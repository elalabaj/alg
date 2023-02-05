#include <vector>

struct DSU {
    std::vector<int> parent;
    std::vector<int> size;

    DSU(int n) {
        parent.resize(n+1);
        for (int i = 0; i <= n; i++) parent[i] = i;
        size.resize(n+1, 1);
    }

    int find_set(int a) {
        if (parent[a] == a) return a;
        return parent[a] = find_set(parent[a]);
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (size[a] < size[b]) std::swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }
};
