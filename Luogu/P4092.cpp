/***************************************************************
	File name: P4092.cpp
	Author: ljfcnyali
	Create time: 2019年08月19日 星期一 19时10分08秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 200010;

int f[maxn], Begin[maxn], Next[maxn], To[maxn], e, cnt[maxn];
int n, m, F[maxn], ans[maxn];

struct node
{
    int opt, x; 
} a[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa, int top)
{
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i]; if ( v == fa ) continue ;
        if ( cnt[v] ) f[v] = v;
        else f[v] = top; 
        F[v] = u;
        if ( cnt[v] ) DFS(v, u, v);
        else DFS(v, u, top);
    }
}

inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    REP(i, 1, m) 
    { 
        char s[3]; scanf("%s", s); 
        scanf("%d", &a[i].x); 
        if ( s[0] == 'Q' ) a[i].opt = 1; 
        else ++ cnt[a[i].x];
    }
    ++ cnt[1]; f[1] = 1; DFS(1, 0, 1);
    for ( int i = m; i >= 1; -- i )
    {
        if ( a[i].opt == 1 ) { ans[i] = find(a[i].x); continue ; }
        -- cnt[a[i].x];
        if ( !cnt[a[i].x] ) f[a[i].x] = F[a[i].x];
    }
    REP(i, 1, m) if ( a[i].opt == 1 ) printf("%d\n", ans[i]);
    return 0;
}
