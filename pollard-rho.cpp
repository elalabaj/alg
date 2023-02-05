#include <random>

typedef long long ll;
typedef __int128 i128;

i128 gcd(i128 a, i128 b) {
    return b ? gcd(b, a % b) : a;
}

ll rho(ll n) {
    if (n % 2 == 0) return 2;
    ll d;
    do {
        ll x = rand() % n;
        ll y = ((i128) x * x + 1) % n;
        do {
            d = gcd(std::abs(x - y), n);
            x = ((i128) x * x + 1) % n;
            y = ((i128) y * y + 1) % n;
            y = ((i128) y * y + 1) % n;
        } while (d == 1);
    } while (d == n);
    return d;
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

i128 rho(i128 n) {
    if (n % 2 == 0) return 2;
    i128 d;
    do {
        i128 x = rand() % n;
        i128 y = (mult(x, x, n) + 1) % n;
        do {
            d = gcd(x > y ? x-y : y-x, n);
            x = (mult(x, x, n) + 1) % n;
            y = (mult(y, y, n) + 1) % n;
            y = (mult(y, y, n) + 1) % n;
        } while (d == 1);
    } while (d == n);
    return d;
}
