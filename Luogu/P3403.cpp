/***************************************************************
	File name: P3403.cpp
	Author: ljfcnyali
	Create time: 2019年09月09日 星期一 20时38分15秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 100010;

queue<int> Q;
int h, x, y, z, dis[maxn], ans;
bool vis[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &h);
    scanf("%lld%lld%lld", &x, &y, &z);
    if ( x == 1 || y == 1 || z == 1 ) { printf("%lld\n", h); return 0; }
    memset(dis, 0x3f, sizeof(dis)); dis[1] = 1; Q.push(1);
    while ( !Q.empty() ) 
    {
        int u = Q.front(), v; Q.pop();
        v = (u + y) % x; if ( dis[v] > dis[u] + y ) { dis[v] = dis[u] + y; if ( !vis[v] ) { vis[v] = true; Q.push(v); } }
        v = (u + z) % x; if ( dis[v] > dis[u] + z ) { dis[v] = dis[u] + z; if ( !vis[v] ) { vis[v] = true; Q.push(v); } }
        vis[u] = false;
    }
    REP(i, 0, x - 1) 
    {
        if ( dis[i] > h ) continue ;
        ans += (h - dis[i]) / x + 1;
    }
    printf("%lld\n", ans);
    return 0;
}
