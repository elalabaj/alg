#include <stack>

struct MinimumQueue {
    std::stack<std::pair<int, int>> s1, s2;

    bool empty() {
        return s1.empty() && s2.empty();
    }

    size_t size() {
        return s1.size() + s2.size();
    }

    int front() {
        if (s2.empty()) {
            while (!s1.empty()) {
                int elem = s1.top().first;
                s1.pop();
                int min_elem = s2.empty() ? elem : std::min(elem, s2.top().second);
                s2.push({elem, min_elem});
            }
        }
        return s2.top().first;
    }
    
    int minimum() {
        int min;
        if (s1.empty()) min = s2.top().second;
        else if (s2.empty()) min = s1.top().second;
        else min = std::min(s1.top().second, s2.top().second);
        return min;
    }
    
    void push(int new_elem) {
        int min_elem = s1.empty() ? new_elem : std::min(new_elem, s1.top().second);
        s1.push({new_elem, min_elem});
    }

    void pop() {
        front();
        s2.pop();
    }
};
