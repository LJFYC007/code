/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年06月12日 星期五 08时27分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4e5 + 10;

int n, m, s[maxn], Begin[maxn], Next[maxn], To[maxn], e, f[maxn], Mid;
int g[maxn], h[maxn], size[maxn], ans, dfn[maxn], tot, F[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS2(int u, int fa)
{
    int y = f[u], z = g[u], t = h[u];
    if ( s[u] >= Mid ) 
    {
        if ( f[fa] == n - size[u] ) f[u] += f[fa];
        else if ( f[fa] > g[u] ) { f[u] = f[u] - g[u] + f[fa]; h[u] = g[u]; g[u] = f[fa]; } 
        else if ( f[fa] > h[u] ) h[u] = f[fa];
        ans = max(ans, f[u]);
    }
    if ( ans >= m ) return ;
    int x = f[u];
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        if ( f[v] == size[v] ) f[u] -= f[v];  
        else if ( f[v] == g[u] ) f[u] = f[u] - f[v] + h[u]; 
        DFS2(v, u);
        f[u] = x;
    }
    f[u] = y; g[u] = z; h[u] = t;
}

inline void read(int &x)
{
    x = 0; char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

inline void DFS(int u, int fa)
{
    dfn[++ tot] = u; size[u] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u); size[u] += size[v]; F[v] = u;
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) read(s[i]);
    REP(i, 1, n - 1) { int u, v; read(u); read(v); add(u, v); add(v, u); }
    DFS(1, 0);
    int L = 0, R = 1000000, pos = 0, num = 0;
    while ( L <= R ) 
    {
        Mid = (L + R) >> 1;
        ans = num = 0; 
        REP(i, 1, n) g[i] = h[i] = f[i] = 0;
        for ( int j = n; j >= 1; -- j )
        {
            int u = dfn[j];
            if ( s[u] < Mid ) { f[u] = 0; continue ; }
            for ( int i = Begin[u]; i; i = Next[i] ) 
            {
                int v = To[i]; if ( v == F[u] ) continue ;
                if ( f[v] == size[v] ) f[u] += f[v];
                else if ( f[v] > g[u] ) { h[u] = g[u]; g[u] = f[v]; }
                else h[u] = max(h[u], f[v]);
            }
            f[u] = f[u] + g[u] + 1; 
            ++ num;
        }
        
        if ( num >= m ) DFS2(1, 0);
        if ( ans >= m ) { L = Mid + 1; pos = Mid; }
        else R = Mid - 1;
    }
    printf("%d\n", pos);
    return 0;
}
