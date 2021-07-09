/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年07月24日 星期五 19时07分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e6 + 10;

int n, a[maxn], Begin[maxn], Next[maxn], To[maxn], e, f[maxn];
vector<int> p, q;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u); a[u] -= a[v];
        if ( v < u ) { f[v] -= a[v]; f[u] += a[v]; }
        else { f[v] += a[v]; f[u] -= a[v]; }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    DFS(1, 0);
    REP(i, 1, n)
    {
        while ( f[i] > 0 ) { p.push_back(i); -- f[i]; }
        while ( f[i] < 0 ) { q.push_back(i); ++ f[i]; } 
    }
    sort(p.begin(), p.end()); sort(q.begin(), q.end());
    printf("%d\n", (int)p.size());
    for ( int i = 0; i < p.size(); ++ i ) printf("%d %d\n", q[i], p[i]);
    return 0;
}
