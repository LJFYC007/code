/***************************************************************
	File name: U95383.cpp
	Author: ljfcnyali
	Create time: 2019年11月13日 星期三 14时15分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, q, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], f[maxn], p[maxn];

inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; 
        if ( v ^ fa )
        {
            p[v] = p[u] ^ W[i];
            DFS(v, u);
        }
    }
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
    scanf("%d%d%d", &n, &m, &q);
    REP(i, 1, n) f[i] = i;
    REP(i, 1, m) 
    { 
        int u, v, w, fx, fy; read(u); read(v); read(w); 
        fx = find(u); fy = find(v);
        if ( fx != fy ) { add(u, v, w); add(v, u, w); f[fx] = fy; }
    }
    DFS(1, 0);
    REP(i, 1, q)
    {
        int x, y; read(x); read(y);
        printf("%d\n", p[x] ^ p[y]);
    }
    return 0;
}
