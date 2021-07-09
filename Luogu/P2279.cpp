/***************************************************************
	File name: P2279.cpp
	Author: ljfcnyali
	Create time: 2019年07月30日 星期二 21时17分23秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 10010;

int Begin[maxn], Next[maxn], To[maxn], e, f[maxn], n, ans;
bool vis[maxn];

struct node
{
    int pos, dis;
    bool operator < (const node &a) const { return dis > a.dis; }
} a[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void Check(int u, int w)
{
    if ( u == 0 ) u = 1;
    vis[u] = true;
    if ( !w ) return ;
    for ( int i = Begin[u]; i; i = Next[i] ) Check(To[i], w - 1);
}

inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        f[v] = u;
        a[v].pos = v; a[v].dis = a[u].dis + 1;
        DFS(v, u);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    add(0, 1); add(1, 0);
    REP(i, 2, n) { int x; scanf("%d", &x); add(i, x); add(x, i); }
    a[1].pos = a[1].dis = 1;
    DFS(1, 0);
    sort(a + 1, a + n + 1);
    REP(i, 1, n) if ( !vis[a[i].pos] ) { Check(f[f[a[i].pos]], 2); ++ ans; }
    printf("%d\n", ans);
    return 0;
}
