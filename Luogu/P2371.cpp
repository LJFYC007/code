/***************************************************************
	File name: P2371.cpp
	Author: ljfcnyali
	Create time: 2019年09月08日 星期日 19时41分34秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 500010 * 12;

int n, m, l, r, dis[maxn], a[maxn], ans;
bool vis[maxn];

inline int calc(int x, int y)
{
    if ( x < y ) return 0;
    return (x - y) / a[1] + 1;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &l, &r);
    REP(i, 1, n) scanf("%lld", &a[i]);
    sort(a + 1, a + n + 1);
    // REP(i, 0, a[1] - 1) REP(j, 1, n) add(i, (i + a[j]) % a[1], a[j]);
    queue<int> Q; Q.push(0); 
    memset(dis, 0x3f, sizeof(dis)); dis[0] = 0;
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        REP(i, 1, n)
        {
            int v = (u + a[i]) % a[1];
            if ( dis[v] > dis[u] + a[i] )
            {
                dis[v] = dis[u] + a[i];
                if ( !vis[v] ) { vis[v] = true; Q.push(v); }
            }
        }
        vis[u] = false;
    }
    REP(i, 0, a[1] - 1) ans += calc(r, dis[i]) - calc(l - 1, dis[i]);
    printf("%lld\n", ans);
    return 0;
}
