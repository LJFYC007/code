/***************************************************************
	File name: CF908G.cpp
	Author: ljfcnyali
	Create time: 2021年01月05日 星期二 15时45分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define x first
#define y second
typedef long long LL;

const int maxn = 710;
const int Mod = 1e9 + 7;

int n, a[maxn], f[maxn][10][maxn], g[maxn][10][maxn], fac[maxn];
char s[maxn];

inline pii Solve(int x, int j, int k, bool op)
{
    if ( k > n - x + 1 || k < 0 ) return pii(0, 0);
    if ( x == n + 1 ) return pii(0, 1);
    if ( !op && g[x][j][k] != -1 ) return pii(f[x][j][k], g[x][j][k]);
    int tmp = op ? a[x] : 9, ret1 = 0, ret2 = 0; 
    REP(i, 0, tmp)
    {
        pii val = Solve(x + 1, j, k - (i <= j), op & (i == tmp));
        if ( val.y == 0 ) continue ; 
        ret2 = (ret2 + val.y) % Mod;
        int sum = 0;
        if ( i < j ) sum = val.x;
        if ( i == j ) sum = (val.x * 10 + fac[n - x + 1 - k] * val.y) % Mod;
        if ( i > j ) sum = val.x * 10 % Mod;
        ret1 = (ret1 + sum) % Mod;
    }
    if ( !op ) { f[x][j][k] = ret1; g[x][j][k] = ret2; } 
    return pii(ret1, ret2);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s + 1); n = str(s + 1);
    fac[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * 10 % Mod;
    REP(i, 1, n) a[i] = s[i] - '0'; 
    memset(f, -1, sizeof(f)); memset(g, -1, sizeof(g));
    int ans = 0;
    REP(i, 1, 9) REP(j, 1, n) 
    {
        int x = Solve(1, i, j, 1).x;
        if ( x != -1 ) ans = (ans + i * x) % Mod;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
