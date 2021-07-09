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
int g[maxn], h[maxn], size[maxn], ans;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int fa)
{
    size[u] = 1; g[u] = h[u] = f[u] = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS1(v, u); size[u] += size[v];
        if ( f[v] == size[v] ) f[u] += f[v];
        else if ( f[v] > g[u] ) { h[u] = g[u]; g[u] = f[v]; }
        else if ( f[v] > h[u] ) h[u] = f[v];
    }
    if ( s[u] >= Mid ) f[u] = f[u] + g[u] + 1; 
    else f[u] = 0;
}

inline void DFS2(int u, int fa)
{
    int y = f[u];
    // if ( ans >= m ) return ;
    if ( s[u] >= Mid ) 
    {
        int sum = 1, Max = 0;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == fa ) continue ;
            if ( f[v] == size[v] ) sum += f[v];
            else Max = max(Max, f[v]);
        }
        if ( f[fa] == n - size[u] ) sum += f[fa];
        else Max = max(Max, f[fa]);
        ans = max(ans, sum + Max);
        printf("%d ", sum + Max);
    }
    else f[u] = 0;
    printf("%d\n", u);
    REP(i, 1, n) printf("%d ", f[i]); puts("");
    int x = f[u];
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        int Max = g[u];
        if ( f[v] == size[v] ) f[u] -= f[v];  
        else if ( f[v] == g[u] ) Max = h[u]; 
        f[u] -= Max;
        if ( f[fa] == n - size[u] ) f[u] += f[fa];
        else Max = max(Max, f[fa]);
        f[u] += Max;
        DFS2(v, u);
        f[u] = x;
    }
    f[u] = y;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d", &s[i]);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    int L = 0, R = 1000000, pos = 0;
    Mid = 2; DFS1(1, 0); 
    // REP(i, 1, n) printf("%d ", f[i]); puts("");
    // DFS2(1, 0);
    // return 0;
    while ( L <= R ) 
    {
        Mid = (L + R) >> 1;
        ans = 0;
        REP(i, 1, n) { DFS1(i, 0); ans = max(ans, f[i]); }
        // DFS1(1, 0); ans = 0; DFS2(1, 0);
        if ( ans >= m ) { L = Mid + 1; pos = Mid; }
        else R = Mid - 1;
    }
    printf("%d\n", pos);
    return 0;
}
