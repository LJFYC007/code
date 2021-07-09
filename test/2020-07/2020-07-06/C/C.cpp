/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年07月06日 星期一 21时17分06秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e3 + 10;
const int INF = 1e18;

int n, ans = INF;
pii t[maxn];
struct Node { int x, y, a, b, w; } a[maxn];
map<int, int> Map[2];
map<int, bool> vis[2], Vis[2];
queue<pii> Q;

inline pii Merge(pii a, pii b)
{
    if ( a.second == 0 && b.second == 0 ) return pii(__gcd(a.first, b.first), 0);
    if ( a.second == 1 && b.second == 1 ) return pii(__gcd(a.first, b.first), 1);
    if ( b.second == 0 ) swap(a, b);
    int g = __gcd(a.first, 2 * b.first);
    if ( g % 2 == 0 && b.first % g == g / 2 ) return pii(g / 2, 1);
    return pii(g, 0);
}

inline bool Check(int x, pii t)
{
    int X = abs(a[x].x - a[1].x), Y = abs(a[x].y - a[1].y);
    if ( X % t.first != 0 || Y % t.first != 0 ) return false;
    if ( t.second == 0 ) return true;
    return (X / t.first) % 2 == (Y / t.first) % 2;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n) 
    {
        scanf("%lld%lld%lld%lld%lld", &a[i].x, &a[i].y, &a[i].a, &a[i].b, &a[i].w);
        int g = __gcd(a[i].a, a[i].b);
        if ( (a[i].a / g) % 2 != (a[i].b / g) % 2 ) t[i] = pii(g, 0);
        else t[i] = pii(g, 1);
    }
    if ( a[1].x == 0 && a[1].y == 0 ) { puts("0"); return 0; }
    REP(i, 1, n)
    {
        if ( a[i].x != a[1].x || a[i].y != a[1].y ) continue ;
        if ( vis[t[i].second][t[i].first] ) 
        {
            Map[t[i].second][t[i].first] = min(Map[t[i].second][t[i].first], a[i].w);
            continue ; 
        }
        Map[t[i].second][t[i].first] = a[i].w;
        Vis[t[i].second][t[i].first] = vis[t[i].second][t[i].first] = true;
        Q.push(t[i]);
    }
    while ( !Q.empty() ) 
    {
        pii x = Q.front(); Q.pop();
        int w = Map[x.second][x.first];
        if ( w >= ans ) continue ;
        if ( Check(0, x) ) ans = w;
        REP(j, 1, n)
        {
            if ( !Check(j, x) ) continue ;
            pii y = Merge(x, t[j]);
            if ( !vis[y.second][y.first] || Map[y.second][y.first] > w + a[j].w )
            {
                vis[y.second][y.first] = true;
                Map[y.second][y.first] = w + a[j].w;
                if ( !Vis[y.second][y.first] )
                {
                    Vis[y.second][y.first] = true;
                    Q.push(y);
                }
            }
        }
        Vis[x.second][x.first] = false;
    }
    printf("%lld\n", ans == INF ? -1 : ans);
    return 0;
}
