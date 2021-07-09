/***************************************************************
	File name: AGC023F.cpp
	Author: ljfcnyali
	Create time: 2021年01月14日 星期四 16时16分48秒
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

int n, fa[maxn], a[maxn], ans, g[maxn];
pii f[maxn];
struct node 
{
    int x, y, id;
    node ( int a = 0, int b = 0, int c = 0 ) { x = a; y = b; id = c; } 
    bool operator < (const node &a) const { return y * a.x > x * a.y; }
} ;
priority_queue<node> Q;

pii operator + (pii a, pii b) { return pii(a.first + b.first, a.second + b.second); } 

inline int find(int x) { return x == g[x] ? x : x = find(g[x]); }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 2, n) scanf("%lld", &fa[i]); 
    REP(i, 1, n) 
    {
        scanf("%lld", &a[i]);  
        if ( a[i] == 0 ) f[i] = pii(1, 0);
        else f[i] = pii(0, 1);
        Q.push(node(f[i].first, f[i].second, i));
        g[i] = i;
    }
    while ( !Q.empty() ) 
    {
        node x = Q.top(); Q.pop();
        if ( pii(x.x, x.y) != f[x.id] ) continue ; 
        if ( x.id == 1 ) continue ; 
        int u = x.id, v = find(fa[u]); g[u] = v;
        ans += f[v].second * f[u].first;
        f[v] = f[v] + f[u];
        Q.push(node(f[v].first, f[v].second, v));
    }
    printf("%lld\n", ans);
    return 0;
}
