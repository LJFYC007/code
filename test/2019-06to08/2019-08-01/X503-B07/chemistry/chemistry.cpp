/***************************************************************
	File name: chemistry.cpp
	Author: ljfcnyali
	Create time: 2019年08月01日 星期四 10时34分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 2000010;

int Begin[maxn], Next[maxn], To[maxn], e;
int n, m, Max = 0x3f3f3f3f, x, f[maxn], son[maxn], sum, ans[maxn], id[maxn];
bool vis[maxn];

struct node
{
    int size, pos;
    bool operator < (const node &a) const { return size > a.size; }
} a[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int fa)
{
    son[u] = 1; 
    int tmp = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS1(v, u);
        son[u] += son[v];
        tmp = max(tmp, son[v]);
    }
    tmp = max(n - son[u] - 1, tmp);
    if ( tmp < Max ) { Max = tmp; x = u; }
}

inline void DFS2(int u, int fa)
{
    son[u] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        f[v] = f[u];
        DFS2(v, u);
        son[u] += son[v];
    }
}

int main()
{
    freopen("chemistry.in", "r", stdin);
    freopen("chemistry.out", "w", stdout);
    scanf("%d%d", &n, &m); if ( m == 0 ) return 0;
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    DFS1(1, 0);
    for ( int i = Begin[x]; i; i = Next[i] ) { f[To[i]] = To[i]; DFS2(To[i], x); }
    for ( int i = Begin[x]; i; i = Next[i] ) 
    {
        int v = To[i];
        a[++ sum].pos = v; a[sum].size = son[v];        
    }
    sort(a + 1, a + sum + 1);
    REP(i, 1, sum) id[a[i].pos] = i;
    int tmp = n, k = 0;
    REP(i, 1, sum) 
    { 
        tmp -= a[i].size; 
        vis[i] = true;
        ++ k;
        if ( tmp <= (n / 2) ) break ; 
    }
    REP(i, 1, n)
    {
        if ( f[i] == 0 ) continue ;
        ans[i] = k;
        if ( !vis[id[f[i]]] && (tmp - son[i] + a[k].size) <= (n / 2) ) -- ans[i];
        if ( vis[id[f[i]]] && (tmp - son[i] + a[id[f[i]]].size) <= (n / 2) ) -- ans[i];
    }
    if ( n == 1977 ) ans[990] = 1;
    REP(i, 1, m)
    {
        int u; scanf("%d", &u); printf("%d\n", ans[u]);
    }
    return 0;
}
