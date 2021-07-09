/***************************************************************
	File name: doubt.cpp
	Author: ljfcnyali
	Create time: 2019年10月29日 星期二 08时39分54秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define int long long
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 400010;
const int Mod = 998244353;
const int N = 1e8;

int n, a[maxn], Begin[maxn], Next[maxn], To[maxn], e, p[maxn][2], f[maxn][2], num[maxn][2];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    p[u][0] = f[u][0] = 1; p[u][1] = f[u][1] = a[u];
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u);
        if ( num[v][0] > num[v][1] || (num[v][0] == num[v][1] && f[v][0] > f[v][1]) ) 
        {
            f[u][0] = f[u][0] * f[v][0];
            p[u][0] = p[u][0] * p[v][0] % Mod;
            num[u][0] += num[v][0];
        }
        else 
        {
            f[u][0] = f[u][0] * f[v][1];
            p[u][0] = p[u][0] * p[v][1] % Mod;
            num[u][0] += num[v][1];
        }
        f[u][1] = f[u][1] * f[v][0];
        p[u][1] = p[u][1] * p[v][0] % Mod;
        num[u][1] += num[v][0];
        while ( f[u][1] > N ) { f[u][1] /= N; ++ num[u][1]; }
        while ( f[u][0] > N ) { f[u][0] /= N; ++ num[u][0]; }
    }
}

signed main()
{
    freopen("doubt2.in", "r", stdin);
    freopen("doubt.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
    DFS(1, 0);
    REP(i, 1, n) printf("%lld ", (LL)f[i][0]); puts("");
    REP(i, 1, n) printf("%lld ", (LL)f[i][1]); puts("");
    REP(i, 1, n) printf("%lld ", (LL)num[i][0]); puts("");
    REP(i, 1, n) printf("%lld ", (LL)num[i][1]); puts("");
    REP(i, 1, n) printf("%lld ", (LL)p[i][0]); puts("");
    REP(i, 1, n) printf("%lld ", (LL)p[i][1]); puts("");
    if ( f[1][0] > f[1][1] ) 
    // if ( num[1][0] > num[1][1] || (num[1][0] == num[1][1] && f[1][0] > f[1][1]) ) 
        printf("%lld\n", p[1][0]);
    else printf("%lld\n", p[1][1]);
    return 0;
}
