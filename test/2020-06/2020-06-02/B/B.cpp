/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年06月02日 星期二 14时17分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, Root, w[maxn], Begin[maxn], Next[maxn], To[maxn], e, val[maxn];
int p[maxn], tot, c[maxn], ans[maxn], size[maxn], pos[maxn];
struct node { int op, l, r; } Q[maxn];
vector<pii> a[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline int lowbit(int x) { return x & -x; }

inline void Modify(int pos, int val) { for ( int i = pos; i <= n; i += lowbit(i) ) c[i] += val; }

inline int Query(int pos) { int sum = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) sum += c[i]; return sum; }

inline void DFS1(int u, int fa)
{
    p[u] = ++ tot; size[u] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS1(v, u); size[u] += size[v];
    }
}

inline void DFS2(int u, int fa)
{
    w[u] = val[u];
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS2(v, u); w[u] += w[v];
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) { scanf("%lld", &w[i]); val[i] = w[i]; }
    REP(i, 1, n)
    {
        int u, v; scanf("%lld%lld", &u, &v);
        if ( u == 0 ) Root = v;
        else { add(u, v); add(v, u); }
    }
    DFS1(Root, 0);    
    REP(i, 1, m) 
    {
        scanf("%lld%lld%lld", &Q[i].op, &Q[i].l, &Q[i].r);
        if ( Q[i].op == 1 ) { int x = w[Q[i].l]; w[Q[i].l] = Q[i].r; Q[i].r -= x; }
        ans[i] = -1;
    }
    int block = sqrt(m * log2(m));
    REP(i, 1, m) pos[i] = (i - 1) / block;
    for ( int l = 1, r = block; l <= m; l += block, r = min(r + block, m) )
    {
        DFS2(Root, 0);
        REP(i, 1, n) w[i] += w[i - 1];
        REP(i, l, r) if ( Q[i].op == 2 ) ans[i] = w[Q[i].r] - w[Q[i].l - 1];
        REP(i, l, r) if ( Q[i].op == 1 ) val[Q[i].l] += Q[i].r; 
    }
    REP(i, 1, m) if ( Q[i].op == 2 ) 
    {
        a[Q[i].r].push_back(pii(i, 1));
        a[Q[i].l - 1].push_back(pii(i, -1));
    }
    REP(i, 1, n)
    {
        Modify(p[i], 1); Modify(p[i] + size[i], -1);
        for ( auto o : a[i] ) 
        {
            int l = pos[o.first] * block + 1, sum = 0;
            REP(j, l, o.first - 1) if ( Q[j].op == 1 ) sum += Query(p[Q[j].l]) * Q[j].r;
            ans[o.first] += o.second * sum;
        }
    }
    REP(i, 1, m) if ( ans[i] != -1 ) printf("%lld\n", ans[i]);
    return 0;
}
