#include <vector>

//change value on coordinates, get sum of an area
struct SegmentTree2D {
    int base_x, base_y;
    std::vector<std::vector<int>> values;

    SegmentTree2D(std::vector<std::vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        base_x = base_y = 1;
        while (base_x < n) base_x *= 2;
        while (base_y < m) base_y *= 2;
        values.resize(2*base_x, std::vector<int>(2*base_y));
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) values[base_x+i][base_y+j] = grid[i][j];
        init_x(1);
    }

    void init_x(int x) {
        if (x < base_x) {
            init_x(2*x);
            init_x(2*x+1);
        } 
        init_y(x, 1);
    }

    void init_y(int x, int y) {
        if (y >= base_y) {
            if (x < base_x) values[x][y] = values[2*x][y] + values[2*x+1][y];
        } else {
            init_y(x, 2*y);
            init_y(x, 2*y+1);
            values[x][y] = values[x][2*y] + values[x][2*y+1];
        }
    }

    void update(int x, int y, int val) {
        x += base_x;
        y += base_y;
        values[x][y] = val;
        update_y(x, y);
        x /= 2;
        while (x) {
            values[x][y] = values[2*x][y] + values[2*x+1][y];
            update_y(x, y);
            x /= 2;
        }
    }

    void update_y(int x, int y) {
        y /= 2;
        while (y) {
            values[x][y] = values[x][2*y] + values[x][2*y+1];
            y /= 2;
        }
    }

    int get(int x1, int x2, int y1, int y2) {
        int res = 0;
        x1 += base_x - 1;
        x2 += base_x + 1;
        while (x2 - x1 > 1) {
            if (x1 % 2 == 0) res += get_y(x1+1, y1, y2);
            if (x2 % 2 == 1) res += get_y(x2-1, y1, y2);
            x1 /= 2;
            x2 /= 2;
        }
        return res;
    }

    int get_y(int x, int y1, int y2) {
        int res = 0;
        y1 += base_y - 1;
        y2 += base_y + 1;
        while (y2 - y1 > 1) {
            if (y1 % 2 == 0) res += values[x][y1+1];
            if (y2 % 2 == 1) res += values[x][y2-1];
            y1 /= 2;
            y2 /= 2;
        }
        return res;
    }
};
