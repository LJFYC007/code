/***************************************************************
	File name: travel.cpp
	Author: ljfcnyali
	Create time: 2019年11月05日 星期二 16时26分13秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 400010;

int n, m, p, Begin[maxn], Next[maxn], To[maxn], e, L[maxn], R[maxn];
int dis[maxn], w[maxn], h[maxn];
bool vis[maxn];

inline void add(int u, int v, int l, int r) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; L[e] = l * 2; R[e] = r * 2; }

inline bool Check(int x)
{
    memset(dis, 0x3f, sizeof(dis));
    mem(w); mem(vis);
    int t = To[h[x]];
    dis[1] = 1; dis[t] = 0;
    REP(i, 1, x) { w[h[i]] = L[h[i]]; dis[t] += L[h[i]]; }
    priority_queue < pii, vector<pii>, greater<pii> > Q;
    Q.push(pii(1, 1)); Q.push(pii(dis[t], t));
    while ( !Q.empty() ) 
    {
        int u = Q.top().second, x = (Q.top().first & 1); Q.pop();
        if ( vis[u] ) continue ; vis[u] = true;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i];
            if ( !w[i] ) w[i] = x ? R[i] : L[i];
            if ( dis[v] > dis[u] + w[i] ) { dis[v] = dis[u] + w[i]; Q.push(pii(dis[v], v)); }
        }
    }
    return dis[2] & 1;
}

signed main()
{
    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &m, &p);
    REP(i, 1, m) { int u, v, l, r; scanf("%lld%lld%lld%lld", &u, &v, &l, &r); add(u, v, l, r); }
    REP(i, 1, p) scanf("%lld", &h[i]);
    int l = 1, r = p, ans = -1;
    while ( l <= r ) 
    {
        int Mid = l + r >> 1;
        if ( Check(Mid) ) { ans = h[Mid]; r = Mid - 1; }
        else l = Mid + 1;
    }
    if ( ans == -1 ) puts("No Response!");
    else printf("%lld\n", ans);
    return 0;
}
