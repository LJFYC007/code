#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>

namespace IO {
    template <typename _T>
    inline bool read (_T& x) {
        x = 0;
        _T y = 1;
        char c = getchar();
        while ((c < '0' || '9' < c) && c != EOF) {
            if (c == '-') y = -1;
            c = getchar();
        }
        if (c == EOF) return false;
        while ('0' <= c && c <= '9') x = x * 10 + c - '0', c = getchar();
        x *= y;
        return true;
    }

    template <typename _T>
    inline _T input () {
        _T x = 0, y = 1;
        char c = getchar();
        while ((c < '0' || '9' < c) && c != EOF) {
            if (c == '-') y = -1;
            c = getchar();
        }
        if (c == EOF) return 0;
        while ('0' <= c && c <= '9') x = x * 10 + c - '0', c = getchar();
        x *= y;
        return x;
    }
};
using namespace IO;

#define reg register
#define MAX_N 207
#define MAX_L 750
#define MXN 200
#define MXL 736
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i, l, r) for(reg int i = l; i <= r; ++i)
#define lep(i, l, r) for(reg int i = l; i < r; ++i)
#define irep(i, r, l) for(int i = r; i >= l; --i)
#define ilep(i, r, l) for(int i = r; i > l; --i)
typedef long long ll;

int MOD;
int pw[MAX_L][MAX_N], fac[MAX_N], ifac[MAX_N], inv[MAX_L];
int f[MAX_N][MAX_L], pre[MAX_L][MAX_L], suf[MAX_L][MAX_L];

inline int add (int x, int y) { return (x += y) >= MOD ? x - MOD : x; }

inline void inc (int &x, int y) { (x += y) >= MOD ? x -= MOD : 0; }

inline int mul (int x, int y) { return 1LL * x * y % MOD; }

inline int qpow (int x, int y) {
    int ans = 1;
    for (; y; y >>= 1, x = mul(x, x)) if (y & 1) ans = mul(ans, x);
    return ans;
}

inline int C (int x, int y) {
    if (y < 0 || x < y) return 0;
    return mul(fac[x], mul(ifac[y], ifac[x - y]));
}

void init () {
    rep (i, 1, MXL) {
        rep (j, 1, MXN + 1)
            pw[i][j] = qpow(i, j);
    }
    fac[0] = ifac[0] = 1;
    rep (i, 1, MXN) fac[i] = mul(fac[i - 1], i);
    ifac[MXN] = qpow(fac[MXN], MOD - 2);
    irep (i, MXN - 1, 1) ifac[i] = mul(ifac[i + 1], i + 1);
    inv[0] = 1;
    rep (i, 1, MXL) inv[i] = qpow(i, MOD - 2);

    rep (i, 1, MXL) f[1][i] = i, f[0][i] = 1;
    int tmp, c, mn, bs;
    rep (i, 2, MXN) {
        rep (j, 0, i - 1 - j) {
            c = C(i - 1, j);
            mn = std::min(j, i - 1 - j) + 1;
            bs = (j * 2 == i - 1 ? 1 : 2);
            rep (k, 1, MXL) {
                tmp = mul(mul(f[j][k], f[i - 1 - j][k]), mul(bs, c));
                tmp = mul(tmp, pw[k][mn]);
                inc(f[i][k], tmp);
            }
        }
    }
    pre[0][0] = 1;
    rep (i, 1, MXL) {
        pre[i][0] = 1;
        rep (j, 1, i) {
            pre[i][j] = add(pre[i - 1][j], mul(pre[i - 1][j - 1], MOD - i));
        }
    }
    suf[MXL + 1][0] = 1;
    irep (i, MXL, 1) {
        suf[i][0] = 1;
        rep (j, 1, MXL - i + 1) {
            suf[i][j] = add(suf[i + 1][j], mul(suf[i + 1][j - 1], MOD - i));
        }
    }
}

inline int calc (int M, int p) {
    int ans = 0;
    rep (i, 0, M) inc(ans, mul(pre[p - 1][i], suf[p + 1][M - i]));
    return ans;
}

inline void solve (int N, int M) {
    if (M >= MXL) return puts("0"), void();
    int res = 0, ans = 0;

    // lagrange
    rep (i, 1, MXL) {
        ans = f[N][i];
        rep (j, 1, MXL) if (i != j) {
            if (i > j) ans = mul(ans, inv[i - j]);
            else ans = mul(ans, MOD - inv[j - i]);
        }
        inc(res, mul(ans, calc(MXL - M - 1, i)));
    }
    printf("%d\n", res);
}

int main() {
    freopen("s3mple.in", "r", stdin);
    freopen("s3mple.out", "w", stdout);
    read(MOD);
    init();
    int N, M;
    while (read(N) && read(M))
        solve(N, M);
    return 0;
}
