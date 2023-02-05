#include <random>

typedef long long ll;
typedef __int128 i128;

ll pw(ll a, ll b, ll m) {
    ll res = 1;
    while (b) {
        if (b&1) res = (i128) res * a % m;
        a = (i128) a * a % m;
        b /= 2;
    }
    return res;
}

i128 mult(i128 a, i128 b, i128 m) {
    i128 res = 0;
    while (b) {
        if (b&1) res = (res + a) % m;
        a = (a + a) % m;
        b /= 2;
    }
    return res;
}

i128 pw(i128 a, i128 b, i128 m) {
    i128 res = 1;
    while (b) {
        if (b&1) res = mult(res, a, m);
        a = mult(a, a, m);
        b /= 2;
    }
    return res;
}

bool passes_mr(ll n, int a, ll d, int s) {
    ll x = pw(a, d, n);
    if (x == 1 || x == n - 1) return true;
    for (int i = 1; i < s; i++) {
        x = (i128) x * x % n;
        if (x == n - 1) return true;
    }
    return false;
}

bool passes_mr(i128 n, int a, i128 d, int s) {
    i128 x = pw(a, d, n);
    if (x == 1 || x == n - 1) return true;
    for (int i = 1; i < s; i++) {
        x = mult(x, x, n);
        if (x == n - 1) return true;
    }
    return false;
}

bool is_prime(ll n) {
    if (n < 2) return false;

    ll d = n - 1;
    int s = 1;
    while (d % 2 == 0) {
        s++;
        d /= 2;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a) return true;
        if (!passes_mr(n, a, d, s)) return false;
    }
    return true;
}

bool is_probably_prime(ll n, int tries) {
    if (n < 2) return false;
    if (n == 2) return true;

    ll d = n - 1;
    int s = 1;
    while (d % 2 == 0) {
        s++;
        d /= 2;
    }

    for (int i = 0; i < tries; i++) {
        ll a = rand() % (n-2) + 2;
        if (!passes_mr(n, a, d, s)) return false;
    }
    return true;
}

bool is_probably_prime(i128 n, int tries) {
    if (n < 2) return false;
    if (n == 2) return true;

    i128 d = n - 1;
    int s = 1;
    while (d % 2 == 0) {
        s++;
        d /= 2;
    }

    for (int i = 0; i < tries; i++) {
        int a = rand() % (n-2) + 2;
        if (!passes_mr(n, a, d, s)) return false;
    }
    return true;
}
