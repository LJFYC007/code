/***************************************************************
	File name: fate.cpp
	Author: ljfcnyali-akioi
	Create time: 2020年11月29日 星期日 10时31分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2010;

int Mod, n, q, f[maxn][maxn], g[maxn][maxn], fac[maxn], Ans[maxn];
vector<int> F[maxn];

inline int sgn(int x) { return x & 1 ? -1 : 1; }

inline vector<int> operator * (vector<int> a, vector<int> b)
{
    int n = a.size(), m = b.size(); vector<int> c; c.resize(n + m - 1);
    REP(i, 0, n - 1) REP(j, 0, m - 1) c[i + j] = (c[i + j] + a[i] * b[j]) % Mod;
    return c;
}

inline vector<int> power(vector<int> a, int b)
{
    if ( !b ) { a.resize(1); a[0] = 1; return a; }
    vector<int> r = a; -- b;
    while ( b ) { if ( b & 1 ) r = r * a; a = a * a; b >>= 1; }
    return r;
}

signed main()
{
    freopen("fate.in", "r", stdin);
    freopen("fate.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &q, &Mod);
    fac[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    f[0][0] = 1;
    REP(j, 1, n) 
    {
        int sum = 0;
        REP(i, 0, j - 3) sum = (sum + f[i][j - 1]) % Mod;
        REP(i, j, n) 
        {
            if ( i >= 2 ) sum = (sum + f[i - 2][j - 1]) % Mod;
            f[i][j] = (f[i - 1][j - 1] + 2 * sum) % Mod;
        }
    }

    REP(i, 1, n) REP(j, 0, i) F[i].push_back(f[i][j]);
    REP(i, 1, n) Ans[i] = -1;
    while ( q -- ) 
    {
        int k; scanf("%lld", &k);
        if ( Ans[k] != -1 ) { printf("%lld\n", Ans[k]); continue ; }
        int p = n / k, a = n % k, b = k - a;
        vector<int> A = power(F[p + 1], a) * power(F[p], b);
        int ans = 0;
        REP(i, 1, n) ans = (ans + sgn(n - i) * fac[i] * A[i]) % Mod;
        Ans[k] = (ans + Mod) % Mod;
        printf("%lld\n", (ans + Mod) % Mod);
    }
    return 0;
}
