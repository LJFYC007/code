/***************************************************************
	File name: P1772.cpp
	Author: ljfcnyali
	Create time: 2019年07月15日 星期一 19时45分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 10010;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int n, m, k, p, d, f[maxn], dis[maxn];
bool vis[maxn], use[maxn], v[30][maxn];

struct node
{
    int l, r, id;
    bool operator < (const node &a) const { return l > a.l; }
} a[maxn];

inline void add(int u, int v, int w)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
    W[e] = w;
}

inline int SPFA()
{
    if ( use[1] == true ) return 0x3f3f3f3f;
    queue<int> Q; Q.push(1);
    memset(dis, 0x3f, sizeof(dis)); dis[1] = 0;
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( use[v] ) continue ;
            if ( dis[v] > dis[u] + W[i] ) 
            {
                dis[v] = dis[u] + W[i];
                if ( !vis[v] ) { vis[v] = true; Q.push(v); }
            }
        }
        vis[u] = false;
    }
    return dis[m];
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d%d", &n, &m, &k, &p);
    REP(i, 1, p) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, w); add(v, u, w); }    
    scanf("%d", &d);
    REP(i, 1, d) 
    {
        scanf("%d%d%d", &a[i].id, &a[i].l, &a[i].r);
        REP(j, a[i].l, a[i].r) v[a[i].id][j] = true;
    }
    memset(f, 0x3f, sizeof(f));
    f[0] = -k;
    REP(i, 1, n)
    {
        mem(use);
        for ( int j = i; j >= 1; -- j )
        {
            REP(k, 1, m) if ( v[k][j] ) use[k] = true;
            int x = SPFA(); if ( x == 0x3f3f3f3f ) continue ;
            f[i] = min(f[i], f[j - 1] + (i - j + 1) * x + k);
        }
    }
    printf("%d\n", f[n]);
    return 0;
}
