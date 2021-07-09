/***************************************************************
	File name: P5666.cpp
	Author: ljfcnyali
	Create time: 2019年11月27日 星期三 15时47分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 6e5 + 10;

int T, n, ans, size[maxn], Begin[maxn], Next[maxn], To[maxn], e, son[maxn][20], f[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int fa)
{
    size[u] = 1; int Max = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        f[v] = u; DFS1(v, u); 
        size[u] += size[v];
        if ( size[v] > Max ) { Max = size[v]; son[u][0] = v; }
    }
}

inline bool Check(int N, int u)
{
    if ( size[son[u][0]] <= N / 2 && N - size[u] <= N / 2 ) return true;
    return false;
}

inline int Get(int N, int u)
{
    int ret = 0;
    for ( int j = 18; j >= 0; -- j ) 
    {
        int x = son[u][j];
        if ( x && N - size[x] <= N / 2 ) u = x;
    }
    if ( Check(N, u) ) ret += u;
    if ( Check(N, f[u]) ) ret += f[u];
    if ( Check(N, son[u][0]) ) ret += son[u][0];
    return ret;
}

inline void DFS2(int u, int fa)
{
    int x = size[u], y = son[u][0], Max = 0, sonn = 0, s;
    if ( size[fa] > size[son[u][0]] ) son[u][0] = fa;
    s = son[u][0];
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == s ) continue ;
        if ( size[v] > Max ) { Max = size[v]; sonn = v; }
    }
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        size[u] = n - size[v]; 
        f[u] = f[v] = 0;
        if ( v == s ) son[u][0] = sonn; 
        else son[u][0] = s; 
        REP(j, 1, 18) son[u][j] = son[son[u][j - 1]][j - 1];
        ans += Get(size[v], v) + Get(n - size[v], u);
        f[u] = v; DFS2(v, u);
    }
    size[u] = x; son[u][0] = y; f[u] = fa;
    REP(j, 1, 18) son[u][j] = son[son[u][j - 1]][j - 1];
}

inline void read(int &x)
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &T);
    while ( T -- ) 
    {
        read(n);
        e = ans = 0; mem(Begin); mem(son);
        REP(i, 1, n - 1) { int u, v; read(u); read(v); add(u, v); add(v, u); }
        DFS1(1, 0);
        REP(i, 1, n) REP(j, 1, 18) son[i][j] = son[son[i][j - 1]][j - 1];
        DFS2(1, 0);
        printf("%d\n", ans);
    }
    return 0;
}
