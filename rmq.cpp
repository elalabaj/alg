#include <vector>

struct RMQ {
    std::vector<std::vector<int>> sparse_table; 
    std::vector<int> lg;

    RMQ(std::vector<int>& vec) {
        int n = vec.size();
        lg.resize(n+1);
        lg[1] = 0;
        for (int i = 2; i <= n; i++) lg[i] = lg[i/2] + 1;
        sparse_table.resize(n);
        for (int i = 0; i < n; i++) sparse_table[i].resize(lg[n]+1);
        for (int i = 0; i < n; i++) sparse_table[i][0] = vec[i];
        for (int j = 1; j <= lg[n]; j++) {
            for (int i = 0; i < n; i++) {
                sparse_table[i][j] = sparse_table[i][j-1];
                int k = i + (1 << (j-1));
                if (k < n) sparse_table[i][j] = std::min(sparse_table[i][j], sparse_table[k][j-1]);
            }
        }
    }

    int minimum(int i, int j) {
        int l = lg[j - i + 1];
        return std::min(sparse_table[i][l], sparse_table[j - (1 << l) + 1][l]);
    }
};
