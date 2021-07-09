/***************************************************************
	File name: y.cpp
	Author: ljfcnyali
	Create time: 2020年11月19日 星期四 11时01分00秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, d, Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int f[71][14][1 << 13], ans;

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

signed main()
{
    freopen("y.in", "r", stdin);
    freopen("y1.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &m, &d);
    REP(i, 1, m) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); add(u, v, w); add(v, u, w); }
    f[1][0][0] = 1;
    REP(i, 0, d - 1) REP(u, 1, n) for ( int o = Begin[u]; o; o = Next[o] ) 
    {
        int v = To[o];
        REP(j, 0, (1 << i) - 1) if ( f[u][i][j] ) 
            f[v][i + 1][j * 2 + W[o]] += f[u][i][j];
    }
    REP(i, 0, (1 << d) - 1) 
    {
        bool flag = false;
        REP(j, 1, n) if ( f[j][d][i] ) flag = true;
        ans += flag;
    }
    printf("%lld\n", ans);
    return 0;
}
