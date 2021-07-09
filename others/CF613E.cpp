/***************************************************************
	File name: CF613E.cpp
	Author: ljfcnyali
	Create time: 2020年09月24日 星期四 19时49分10秒
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
const int Mod = 1e9 + 7;
const int seed = 107;

int f[3][maxn][maxn], pre[3][maxn], suf[3][maxn], n, m;
int p[maxn], inv[maxn], g[maxn], ans;
char s[3][maxn], t[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int Get(int op, int l, int r, bool dic)
{
    int ret;
    if ( dic == 0 )
    {
        ret = (pre[op][r] - pre[op][l - 1]) % Mod;
        ret = ret * inv[l - 1] % Mod;
    }
    else
    {
        ret = (suf[op][l] - suf[op][r + 1]) % Mod;
        ret = ret * inv[n - r] % Mod;
    }
    return (ret + Mod) % Mod;
}

inline void Solve()
{
    REP(i, 0, 2)
    {
        int N = i == 0 ? m : n;
        REP(j, 1, N) pre[i][j] = (pre[i][j - 1] + p[j] * (s[i][j] - 'a' + 1)) % Mod;
        for ( int j = N; j >= 1; -- j ) suf[i][j] = (suf[i][j + 1] + p[N - j + 1] * (s[i][j] - 'a' + 1)) % Mod;
    }
    mem(f);

    REP(i, 1, n) REP(op, 1, 2)
    {
        if ( s[0][1] == s[op][i] ) ++ f[op][i][1];
        REP(len, 1, min(m / 2, i))
        {
            int l = i - len + 1;
            if ( Get(0, 1, len, 0) != Get(op, l, i, 1) ) continue ;
            if ( Get(0, len + 1, len + len, 0) != Get(3 - op, l, i, 0) ) continue ;
            ++ f[3 - op][i][len * 2];
        }
    }

    REP(i, 1, n - 1) REP(op, 1, 2) REP(j, 1, m)
    {
        if ( s[op][i + 1] == s[0][j + 1] ) f[op][i + 1][j + 1] = (f[op][i + 1][j + 1] + f[op][i][j]) % Mod;
        if ( s[op][i + 1] == s[0][j + 1] && s[3 - op][i + 1] == s[0][j + 2] )
            f[3 - op][i + 1][j + 2] = (f[3 - op][i + 1][j + 2] + f[op][i][j]) % Mod;
    }

    REP(i, 1, n) REP(op, 1, 2)
    {
        ans = (ans + f[op][i][m]) % Mod;
        REP(j, 1, m - 3)
        {
            int len = (m - j) / 2;
            if ( (m - j) % 2 != 0 || i + len > n ) continue ;
            int l = i + 1, r = i + len;
            int L = m - len - len;
            if ( Get(0, L + 1, L + len, 0) != Get(op, l, r, 0) ) continue ;
            if ( Get(0, L + len + 1, L + len + len, 0) != Get(3 - op, l, r, 1) ) continue ;
            ans = (ans + f[op][i][j]) % Mod;
        }
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s[1] + 1); scanf("%s", s[2] + 1); n = str(s[1] + 1);
    scanf("%s", s[0] + 1); m = str(s[0] + 1);
    p[0] = inv[0] = 1; REP(i, 1, maxn - 10) { p[i] = p[i - 1] * seed % Mod; inv[i] = inv[i - 1] * power(seed, Mod - 2) % Mod; }

    Solve();
    reverse(s[1] + 1, s[1] + n + 1);
    reverse(s[2] + 1, s[2] + n + 1);
    if ( m != 1 ) Solve();
    if ( m == 2 )
    {
        REP(i, 1, n)
        {
            if ( s[1][i] == s[0][1] && s[2][i] == s[0][2] ) -- ans;
            if ( s[2][i] == s[0][1] && s[1][i] == s[0][2] ) -- ans;
        }
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
