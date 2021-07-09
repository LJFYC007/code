/***************************************************************
	File name: CF674D.cpp
	Author: ljfcnyali
	Create time: 2021年01月21日 星期四 19时29分36秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 1e18;

int n, q, t[maxn], f[maxn], deg[maxn], a[maxn];
vector<int> son[maxn];
multiset<pii> Set[maxn];

pii operator + (pii a, int b) { return pii(a.first + b, a.second); }

inline void Maintain(int i)
{
    if ( Set[i].empty() ) return ;
    auto it = Set[i].begin();
    Set[0].insert(*it + t[i] / (deg[i] + 2));
    it = -- Set[i].end();
    Set[0].insert(*it + t[i] / (deg[i] + 2));
}

inline void Erase(int i)
{
    if ( Set[i].empty() ) return ;
    auto it = Set[i].begin();
    Set[0].erase(*it + t[i] / (deg[i] + 2));
    it = -- Set[i].end();
    Set[0].erase(*it + t[i] / (deg[i] + 2));
}

inline void Link(int u, int v)
{
    Erase(u); a[u] += t[v] / (deg[v] + 2); Set[u].insert(pii(a[v], v));
    a[u] -= t[u] - t[u] / (deg[u] + 2) * (deg[u] + 1);
    ++ deg[u];
    a[u] += t[u] - t[u] / (deg[u] + 2) * (deg[u] + 1);
    Maintain(u);
}

inline void Cut(int u, int v)
{
    Erase(u); a[u] -= t[v] / (deg[v] + 2); Set[u].erase(pii(a[v], v));
    a[u] -= t[u] - t[u] / (deg[u] + 2) * (deg[u] + 1);
    -- deg[u];
    a[u] += t[u] - t[u] / (deg[u] + 2) * (deg[u] + 1);
    Maintain(u);
}

inline void Insert(int u, int v) { Erase(u); Set[u].insert(pii(a[v], v)); Maintain(u); }
inline void Delete(int u, int v) { Erase(u); Set[u].erase(pii(a[v], v)); Maintain(u); }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &q);
    REP(i, 1, n) scanf("%lld", &t[i]); REP(i, 1, n) { scanf("%lld", &f[i]); son[f[i]].push_back(i); ++ deg[f[i]]; } 
    REP(i, 1, n)
    {
        a[i] = t[i] - t[i] / (deg[i] + 2) * (deg[i] + 1); 
        for ( auto it : son[i] ) a[i] += t[it] / (deg[it] + 2);
    }
    REP(i, 1, n)
    {
        for ( auto it : son[i] ) Set[i].insert(pii(a[it], it)); 
        Maintain(i);
    }
    while ( q -- ) 
    {
        int op, x, y; scanf("%lld", &op);
        if ( op == 1 ) 
        {
            scanf("%lld%lld", &x, &y);
            int u = f[x], v = f[u]; Delete(f[v], v); Cut(v, u); Cut(u, x); Link(v, u); Insert(f[v], v);
            u = y; v = f[u]; Delete(f[v], v); Cut(v, u); Link(u, x); Link(v, u); Insert(f[v], v);
            f[x] = y;
        }
        if ( op == 2 ) 
        {
            scanf("%lld", &x);
            printf("%lld\n", a[x] + t[f[x]] / (deg[f[x]] + 2));
        }
        if ( op == 3 ) printf("%lld %lld\n", (*Set[0].begin()).first, (*(-- Set[0].end())).first);
    }
    return 0;
}
