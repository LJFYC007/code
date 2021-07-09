/***************************************************************
	File name: P6097.cpp
	Author: ljfcnyali
	Create time: 2020年05月25日 星期一 21时08分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = (1 << 20) + 10;
const int Mod = 1e9 + 9;

int n, a[21][maxn], b[21][maxn], num[maxn], c[21][maxn];

inline void FWT(int *f, int n, int op)
{
    for ( int Mid = 1; Mid < n; Mid <<= 1 ) 
        for ( int i = 0; i < n; i += (Mid << 1) )
            REP(j, 0, Mid - 1)
                f[i + Mid + j] = (f[i + Mid + j] + f[i + j] * op) % Mod;
}

inline void read(int &x)
{
    x = 0; char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 0, (1 << n) - 1) REP(j, 1, n) if ( (i >> j - 1) & 1 ) ++ num[i];
    REP(i, 0, (1 << n) - 1) read(a[num[i]][i]);
    REP(i, 0, (1 << n) - 1) read(b[num[i]][i]);
    REP(i, 0, n) { FWT(a[i], 1 << n, 1); FWT(b[i], 1 << n, 1); }
    REP(i, 0, n) REP(j, 0, n) if ( i + j <= n ) REP(k, 0, (1 << n) - 1) c[i + j][k] = (c[i + j][k] + ((LL)(a[i][k]) * b[j][k] % Mod)) % Mod;
    REP(i, 0, n) FWT(c[i], 1 << n, -1);
    REP(i, 0, (1 << n) - 1) printf("%d ", (c[num[i]][i] + Mod) % Mod); puts("");
    return 0;
}
