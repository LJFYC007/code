/***************************************************************
	File name: plan.cpp
	Author: ljfcnyali
	Create time: 2020年11月03日 星期二 09时33分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;
#define int long long

const int maxn = 5010;
const int INF = 1e18;

int n, L, R, f[maxn][maxn], g[maxn][maxn], a[maxn], ans = INF;

inline void print(int i, int j)
{
    if ( i > 1 ) print(i - 1, g[i][j]);
    printf("%lld ", a[i] + j);
}

signed main()
{
    freopen("plan.in", "r", stdin);
    freopen("plan.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &L, &R);
    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 0, n) REP(j, 0, L) f[i][j] = INF;
    REP(i, 0, L) f[1][i] = i;
    REP(i, 2, n) for ( int j = L; j >= 0; -- j )
    {
        if ( f[i - 1][j] == INF ) continue ;
        int y = a[i - 1] + j + a[i];
        REP(k, max(0ll, L - y), min(L, R - y))
        {
            int x = y + k;
            if ( f[i - 1][j] + k < f[i][k] ) { f[i][k] = f[i - 1][j] + k; g[i][k] = j; }
        }
    }
    int pos;
    REP(i, 0, L) if ( f[n][i] < ans ) { ans = f[n][i]; pos = i; } 
    if ( ans == INF ) { puts("-1"); return 0; } 
    printf("%lld\n", ans);
    print(n, pos); puts("");
    return 0;
}
