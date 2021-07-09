/***************************************************************
    File name: tearssp.cpp
    Author: ljfcnyali
    Create time: 2021年04月02日 星期五 10时17分40秒
***************************************************************/
#include<bits/stdc++.h>
   
#define lg(x) (31-__builtin_clz(x))
   
using namespace std;
   
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;
   
const int maxn = 4e5 + 10;
const LL INF = 1e18;
   
int n, m, k, root, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], ccc[maxn], f[maxn];
int dep[maxn], anc[18][maxn], belong[maxn], a[maxn], cnt[maxn], num, b[670][maxn / 2], len[maxn];
LL dis[maxn], Min[maxn];
pii p[maxn];
bool vis[670][maxn / 2];
   
inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; } 
   
inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ; 
        dep[v] = dep[u] + 1; dis[v] = dis[u] + W[i];
        anc[0][v] = u; f[v] = u; DFS(v, u); 
    }
}
   
// inline int lowbit(int x) { return x & -x; } 
#define lowbit(x) (x & -x)
inline int Get(int x, int len)
{
    for ( register int i = len; i > 0; i -= lowbit(i) ) x = anc[x][ccc[lowbit(i)]];
    return x;
}
   
inline void ReBuild(int x, int l = 1, int r = 0)
{
    if ( cnt[x] ) 
	{ 
		for ( register int i = cnt[x]; i > 0; i -= lowbit(i) )
		{
			const int t = ccc[lowbit(i)];
			REP(i, p[x].first, p[x].second) a[i] = anc[t][a[i]];
		}
		cnt[x] = 0;
	}
    REP(i, l, r) if ( !vis[x][a[i]] ) 
    {
        vis[x][a[i]] = true; Min[x] = min(Min[x], dis[a[i]]);
        b[x][++ len[x]] = a[i];
    }
}
   
inline void Move(int x)
{
    ++ cnt[x]; if ( Min[x] == 0 ) return ; 
    for ( int i = 1; i <= len[x]; ++ i ) 
    {
        b[x][i] = f[b[x][i]];
        if ( vis[x][b[x][i]] ) { b[x][i] = b[x][len[x]]; -- i; -- len[x]; }
        else { vis[x][b[x][i]] = true; Min[x] = min(Min[x], dis[b[x][i]]); }
    }
}
  
inline void read(int &x)
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); } 
}
   
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("tearssp.in", "r", stdin);
    freopen("tearssp.out", "w", stdout);
#endif
    read(n); read(m); read(root);
    REP(i, 1, n - 1) { int u, v, w; read(u); read(v); read(w); add(u, v, w); add(v, u, w); } 
    dep[root] = 1; DFS(root, 0); REP(j, 1, 17) REP(i, 1, n) anc[j][i] = anc[j - 1][anc[j - 1][i]];
    int B = 400;
    for ( int l = 1, r = B; l <= n; l += B, r = min(n, r + B) )  { p[++ k] = pii(l, r); REP(i, l, r) belong[i] = k; }
    REP(i, 1, n) read(a[i]);
    REP(i, 0, 17) ccc[1 << i] = i; 
    REP(i, 1, k) { Min[i] = INF; ReBuild(i, p[i].first, p[i].second); }
   
    while ( m -- ) 
    {
        int t, l, r; read(t); read(l); read(r);
        if ( t == 1 ) 
        {
            if ( belong[l] + 1 >= belong[r] ) 
            {
                REP(i, l, r) a[i] = f[a[i]];
                if ( belong[l] == belong[r] ) ReBuild(belong[l], l, r);
                else ReBuild(belong[l], l, p[belong[l]].second), ReBuild(belong[r], p[belong[r]].first, r);
                continue ; 
            }
            REP(i, belong[l] + 1, belong[r] - 1) Move(i);
            REP(i, l, p[belong[l]].second) a[i] = f[a[i]];
            REP(i, p[belong[r]].first, r) a[i] = f[a[i]];
            ReBuild(belong[l], l, p[belong[l]].second); ReBuild(belong[r], p[belong[r]].first, r);
        }
        else
        {
            LL ans = INF;
            if ( belong[l] + 1 >= belong[r] )
            {
                ReBuild(belong[l]); if ( belong[l] != belong[r] ) ReBuild(belong[r]);
                REP(i, l, r) ans = min(ans, dis[a[i]]);
            }
            else
            {
                REP(i, belong[l] + 1, belong[r] - 1) ans = min(ans, Min[i]);
                ReBuild(belong[l]); ReBuild(belong[r]);
                REP(i, l, p[belong[l]].second) ans = min(ans, dis[a[i]]);
                REP(i, p[belong[r]].first, r) ans = min(ans, dis[a[i]]);
            }
            printf("%lld\n", ans);
        }
    }
    return 0;
}
