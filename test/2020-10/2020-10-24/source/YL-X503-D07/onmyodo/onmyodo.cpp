#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1 << 18;
const int Mod = 1e9 + 9;

int n, m, k, ans, f[19][maxn], fac[maxn], inv[maxn], cnt[maxn];
vector<int> h;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

inline void FWT(int *f, int op)
{
    for ( int Mid = 1; Mid < m; Mid <<= 1 ) 
        for ( int i = 0; i < m; i += (Mid << 1) )
            for ( int j = 0; j < Mid; ++ j )
                f[i + j + Mid] += op * f[i + j];
    REP(i, 0, m - 1) f[i] %= Mod;
}

inline vector<int> operator *(vector<int> a, vector<int> b)
{
    vector<int> c; c.resize(19);
    REP(i, 0, 18) REP(j, 0, 18 - i) c[i + j] += a[i] * b[j];
    REP(i, 0, 18) c[i] %= Mod;
    return c;
}

inline vector<int> power(vector<int> a, int b)
{
    vector<int> r = a; -- b;
    while ( b ) 
    {
        if ( b & 1 ) r = r * a;
        a = a * a; b >>= 1; 
    }
    return r;
}

signed main()
{
    freopen("onmyodo.in", "r", stdin);
    freopen("onmyodo.out", "w", stdout);
    scanf("%lld%lld", &n, &k);
    m = 1 << 18;
    fac[0] = inv[0] = 1; REP(i, 1, m - 1) fac[i] = fac[i - 1] * i % Mod;
    inv[m - 1] = power(fac[m - 1], Mod - 2); for ( int i = m - 2; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;

    ans = power(k, n);
    if ( n % 2 == 0 ) 
    {
        REP(i, 0, m - 1) 
        {
            REP(j, 0, 17) if ( (i >> j) & 1 ) ++ cnt[i];
            f[cnt[i]][i] = inv[i];
        }
        REP(i, 0, 18) FWT(f[i], 1); 
        REP(i, 0, m - 1) 
        {
            h.resize(19);
            REP(j, 0, 18) h[j] = f[j][i];
            h = power(h, k);
            REP(j, 0, 18) f[j][i] = h[j];
        }
        FWT(f[cnt[n]], -1);
        ans = (ans - fac[n] * f[cnt[n]][n]) % Mod;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
