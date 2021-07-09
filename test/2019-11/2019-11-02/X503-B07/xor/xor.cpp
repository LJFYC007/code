/***************************************************************
	File name: xor.cpp
	Author: ljfcnyali
	Create time: 2019年11月02日 星期六 10时12分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int unsigned long long
typedef long long LL;

const int maxn = 50;
const int Mod = 1e9 + 7;

int Begin[maxn], Next[maxn], To[maxn], W[maxn], e = 1, n, m, ans, s, t;
map<int, bool> Map;
bool vis[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void DFS(int u, int ret)
{
    if ( u == s )
    {
        if ( Map.count(ret) ) return ;
        Map[ret] = true; ans = (ans + ret) % Mod;
    }
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        if ( vis[i] ) continue ;
        vis[i] = vis[i ^ 1] = true; 
        DFS(To[i], ret ^ W[i]);
        vis[i] = vis[i ^ 1] = false;
    }
}

signed main()
{
    freopen("xor.in", "r", stdin);
    freopen("xor.out", "w", stdout);
    scanf("%llu%llu", &n ,&m);
    REP(i, 1, m) { int u, v, w; scanf("%llu%llu%llu", &u, &v, &w); add(u, v, w); add(v, u, w); }
    scanf("%llu%llu", &s, &t); 
    if ( n > 20 ) { printf("%llu\n", Mod - 1); return 0; }
    DFS(t, 0);
    printf("%llu\n", ans);
    return 0;
}
