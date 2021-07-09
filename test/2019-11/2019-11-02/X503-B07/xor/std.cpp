/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2019年11月02日 星期六 15时42分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long 
typedef long long LL;

const int maxn = 2000010;
const int Mod = 1e9 + 7;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], dis[maxn], b[70], ans, s, t;
bool vis[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void Modify(int x)
{
    for ( int i = 60; i >= 0; -- i )
    {
        if ( !(x & (1ll << i)) ) continue ;
        if ( b[i] ) x ^= b[i];
        else { b[i] = x; break ; }
    }
}

inline void DFS(int u)
{
    vis[u] = true;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; 
        if ( vis[v] ) Modify(dis[v] ^ dis[u] ^ W[i]);
        else { dis[v] = dis[u] ^ W[i]; DFS(v); }
    }
}

signed main()
{
    freopen("xor.in", "r", stdin);
    freopen("xor.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, m) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); add(u, v, w); add(v, u, w); }
    scanf("%lld%lld", &s, &t);
    DFS(s);
    if ( !vis[t] ) { puts("0"); return 0; }
    int ret = 0; REP(i, 0, 60) if ( b[i] ) ++ ret;
    REP(i, 0, 60)
    {
        int sum1 = 0, sum2 = 1ll << ret;
        REP(j, 0, 60)
            if ( b[j] & (1ll << i) ) { sum1 = sum2 = 1ll << ret - 1; break ; }
        sum1 %= Mod; sum2 %= Mod;
        int x = (1ll << i) % Mod;
        if ( dis[t] & (1ll << i) ) ans = (ans + sum2 * x) % Mod;
        else ans = (ans + sum1 * x) % Mod;
    }
    printf("%lld\n", ans);
    return 0;
}
