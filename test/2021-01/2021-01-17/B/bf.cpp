/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2021年01月17日 星期日 10时23分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 998244353;

int n, s, val[maxn], Begin[maxn], Next[maxn], To[maxn], e, vis[maxn], ans;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

inline void DFS(int u, int x)
{
    ++ vis[u]; int deg = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
        if ( vis[To[i]] != 2 ) ++ deg;
    if ( !deg ) { ans = (ans + x * val[u]) % Mod; -- vis[u]; return ; } 
    deg = power(deg, Mod - 2);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( vis[v] == 2 ) continue ; 
        DFS(v, x * deg % Mod);
    }
    -- vis[u];
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &s);
    REP(i, 1, n) scanf("%lld", &val[i]);
    REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); } 
    DFS(s, 1);
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
