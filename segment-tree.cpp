#include <vector>

struct Value {};
struct Modifier {};
Value operator+(Value v1, Value v2) {}
Value operator+(Value v, Modifier m) {}
Modifier operator+(Modifier m1, Modifier m2) {}

//modify a point, get value from a range
struct PointRange {
    int base;
    std::vector<Value> values;

    PointRange(int n) {
        base = 1;
        while (base < n) base *= 2;
        values.resize(2*base);
        for (int i = 0; i < base; i++) values[i+base] = Value();
        init(1);
    }

    PointRange(std::vector<Value>& vec) {
        int n = vec.size();
        base = 1;
        while (base < n) base *= 2;
        values.resize(2*base);
        for (int i = 0; i < n; i++) values[base+i] = vec[i];
        for (int i = n; i < base; i++) values[base+i] = Value();
        init(1);
    }

    Value init(int v) {
        if (v >= base) return values[v];
        return values[v] = init(2*v) + init(2*v+1);
    }

    void update(int i, Modifier m) {
        i += base;
        values[i] = values[i] + m;
        i /= 2;
        while (i) {
            values[i] = values[2*i] + values[2*i+1];
            i /= 2;
        }
    }

    Value get(int i, int j) {
        i += base - 1;
        j += base + 1;
        Value res = Value();
        while (j - i > 1) {
            if (i % 2 == 0) res = res + values[i+1];
            if (j % 2 == 1) res = res + values[j-1];
            i /= 2;
            j /= 2;
        }
        return res;
    }
};

//modify a range, get value from a point
struct RangePoint {
    int base;
    std::vector<Value> values;

    RangePoint(int n) {
        base = 1;
        while (base < n) base *= 2;
        values.resize(2*base);
        for (int i = 0; i < base; i++) values[i+base] = Value();
        init(1);
    }

    RangePoint(std::vector<Value>& vec) {
        int n = vec.size();
        base = 1;
        while (base < n) base *= 2;
        values.resize(2*base);
        for (int i = 0; i < n; i++) values[base+i] = vec[i];
        for (int i = n; i < base; i++) values[base+i] = Value();
        init(1);
    }

    Value init(int v) {
        if (v >= base) return values[v];
        return values[v] = init(2*v) + init(2*v+1);
    }

    void update(int i, int j, Modifier m) {
        i += base - 1;
        j += base + 1;
        while (j - i > 1) {
            if (i % 2 == 0) values[i+1] = values[i+1] + m;
            if (j % 2 == 1) values[j-1] = values[j-1] + m;
            i /= 2;
            j /= 2;
        }
    }

    Value get(int i) {
        i += base;
        Value res = Value();
        while (i) {
            res = res + values[i];
            i /= 2;
        }
        return res;
    }
};

//modify and get value from a range
struct RangeRange {
    int base;
    std::vector<Value> values;
    std::vector<Modifier> modifiers;

    RangeRange(int n) {
        base = 1;
        while (base < n) base *= 2;
        values.resize(2*base);
        for (int i = 0; i < base; i++) values[i+base] = Value();
        modifiers.resize(2*base, Modifier());
        init(1);
    }

    RangeRange(std::vector<Value>& vec) {
        int n = vec.size();
        base = 1;
        while (base < n) base *= 2;
        values.resize(2*base);
        for (int i = 0; i < n; i++) values[i+base] = vec[i];
        for (int i = n; i < base; i++) values[i+base] = Value();
        modifiers.resize(2*base, Modifier());
        init(1);
    }

    Value init(int v) {
        if (v >= base) return values[v];
        return values[v] = init(2*v) + init(2*v+1);
    }

    void push(int v) {
        values[2*v] = values[2*v] + modifiers[v];
        values[2*v+1] = values[2*v+1] + modifiers[v];
        modifiers[2*v] = modifiers[2*v] + modifiers[v];
        modifiers[2*v+1] = modifiers[2*v+1] + modifiers[v];
        modifiers[v] = Modifier();
    }

    void update(int v, int a, int b, int i, int j, Modifier m) {
        if (a > j || b < i) return;
        if (a >= i && b <= j) {
            values[v] = values[v] + m;
            modifiers[v] = modifiers[v] + m;
        } else {
            push(v);
            update(2*v, a, (a+b)/2, i, j, m);
            update(2*v+1, (a+b)/2+1, b, i, j, m);
            values[v] = values[2*v] + values[2*v+1];
        }
    }

    Value get(int v, int a, int b, int i, int j) {
        if (a > j || b < i) return Value();
        if (a >= i && b <= j) return values[v];
        push(v);
        return get(2*v, a, (a+b)/2, i, j) + get(2*v+1, (a+b)/2+1, b, i, j);
    }

    void update(int i, int j, Modifier m) { update(1, 0, base-1, i, j, m); }
    
    Value get(int i, int j) { return get(1, 0, base-1, i, j); }
};
