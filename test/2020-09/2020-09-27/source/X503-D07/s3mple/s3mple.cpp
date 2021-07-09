/***************************************************************
	File name: s3mple.cpp
	Author: ljfcnyali
	Create time: 2020年09月27日 星期日 09时37分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 810;

int T, n, m, Mod, c[maxn][maxn], Inv[maxn], P[maxn][maxn];
vector<int> f[maxn], a, pre[maxn], suf[maxn], g[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline vector<int> operator * (vector<int> a, vector<int> b)
{
    REP(i, 0, 735) a[i] = a[i] * b[i] % Mod;
    return a;
}

inline vector<int> Mul(vector<int> a, vector<int> b)
{
    int n = a.size(), m = b.size(); vector<int> c; c.resize(n + m - 1);
    REP(i, 0, n - 1) REP(j, 0, m - 1) c[i + j] = (c[i + j] + a[i] * b[j]) % Mod;
    return c;
}

signed main()
{
    freopen("s3mple.in", "r", stdin);
    freopen("s3mple.out", "w", stdout);
    scanf("%lld", &Mod);
    n = maxn - 10; REP(i, 0, n) c[i][0] = 1;
    REP(i, 1, n) REP(j, 1, i) c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % Mod;

    REP(i, 0, 735) REP(j, 0, 200) P[i][j] = power(i, j);
    REP(i, 0, 736) Inv[i] = power(i, Mod - 2);
    n = 200;
    REP(i, 0, n) f[i].resize(736);
    REP(i, 0, 735) { f[1][i] = i; f[0][i] = 1; }
    REP(N, 2, n) REP(i, 1, N)
    {
        int x = i - 1, y = N - i, val = min(i, N - i + 1);
        a = f[x] * f[y];
        REP(j, 0, 735)
        {
            int num = a[j] * c[x + y][y] % Mod;
            f[N][j] = (f[N][j] + num * P[j][val]) % Mod;
        }
    }

    pre[0].resize(2); pre[0][1] = 1;         
    a.resize(2); a[1] = 1;
    REP(i, 1, 735) { a[0] = -i; pre[i] = Mul(pre[i - 1], a); }
    suf[736].resize(1); suf[736][0] = 1;
    for ( int i = 735; i >= 0; -- i ) { a[0] = -i; suf[i] = Mul(suf[i + 1], a); }

    while ( ~scanf("%lld%lld", &n, &m) ) 
    {
        if ( m >= n * 4 ) { puts("0"); continue ; }
        int ans = 0;
        REP(i, 0, 735)
        {
            int ret = 0;
            if ( i == 0 ) 
            {
                if ( m < suf[1].size() ) ret = suf[1][m];
            }
            else REP(j, 0, m) 
            {
                if ( j < pre[i - 1].size() && m - j < suf[i + 1].size() )
                    ret = (ret + pre[i - 1][j] * suf[i + 1][m - j]) % Mod;
            }
            REP(j, 0, 735) if ( j != i ) ret = ret * (i < j ? -Inv[j - i] : Inv[i - j]) % Mod;
            ret = ret * f[n][i] % Mod;
            ans = (ans + ret) % Mod;
        }
        printf("%lld\n", (ans + Mod) % Mod);
    }
    return 0;
}
