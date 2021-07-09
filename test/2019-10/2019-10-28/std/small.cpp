#include <bits/stdc++.h>
using namespace std;

#define TASKNAME "smaLL"

typedef long long LL;
const LL mod = 19491001;

void add(LL &x, LL val) {
    x += val;
    if (x >= mod) x -= mod;
}

struct Matrix {
    LL a[2][2];

    Matrix() {
        memset(this, 0, sizeof *this);
    }

    Matrix(const int b[2][2]) {
        a[0][0] = b[0][0];
        a[0][1] = b[0][1];
        a[1][0] = b[1][0];
        a[1][1] = b[1][1];
    }

    Matrix operator * (const Matrix &m) {
        Matrix ret;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    add(ret.a[i][j], a[i][k] * m.a[k][j] % mod);
                }
            }
        }
        return ret;
    }
};

const int arr_b[2][2] = {{0, 1}, {1, 1}};
const int arr_i[2][2] = {{1, 0}, {0, 1}};

LL solve(LL x) {
    Matrix base = arr_b, ans = arr_i;
    for (; x; x >>= 1) {
        if (x & 1) ans = ans * base;
        base = base * base;
    }
    LL ret = ans.a[1][0];
    add(ret, ans.a[1][1]);
    add(ret, mod - 1);
    return ret;
}

int main() {
    freopen(TASKNAME ".in",  "r", stdin);
    freopen(TASKNAME ".out", "w", stdout);
    LL n; scanf("%lld", &n);
    if (n == 1) return puts("0"), 0;
    printf("%lld\n", solve(n - 1));
    return 0;
}
