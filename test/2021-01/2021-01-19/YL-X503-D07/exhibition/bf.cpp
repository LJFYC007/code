/***************************************************************
	File name: exhibition.cpp
	Author: ljfcnyali
	Create time: 2021年01月19日 星期二 09时57分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long 
#define x first
#define y second
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 1e18;

int n, dis[maxn], ans;
pii a[maxn];
bool vis[maxn];

inline int Get(int x, int y)
{
    pii A = a[x], B = a[y];
    if ( A.x > B.x ) swap(A, B);
    if ( A.y < B.x ) return INF;
    return min(A.y, B.y) - max(A.x, B.x) + 1;
}

signed main()
{
    freopen("exhibition.in", "r", stdin);
    freopen("exhibition.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) { scanf("%lld%lld", &a[i].x, &a[i].y); -- a[i].y; } 
    REP(i, 2, n) dis[i] = INF; dis[0] = INF;
    REP(o, 1, n)
    {
        int pos = 0;
        REP(i, 1, n) if ( !vis[i] && dis[i] < dis[pos] ) pos = i;
        if ( pos == 0 ) { puts("-1"); return 0; } 
        vis[pos] = true; ans += dis[pos];
        REP(i, 1, n) dis[i] = min(dis[i], Get(pos, i));
    }
    printf("%lld\n", ans);
    return 0;
}
