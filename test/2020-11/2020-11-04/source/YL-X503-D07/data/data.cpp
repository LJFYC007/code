/***************************************************************
	File name: data.cpp
	Author: ljfcnyali
	Create time: 2020年11月04日 星期三 08时50分33秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;
#define x first
#define y second

const int maxn = 3e5 + 10;

int n, f[maxn], ans, sum, belong[maxn];
pii a[maxn];
struct node 
{ 
    int x, y, id; 
    node ( int a = 0, int b = 0, int c = 0 ) { x = a; y = b; id = c; }
} ;
bool operator < (const node &a, const node &b) { return a.x * b.y > a.y * b.x; }
priority_queue<node> Q;
bool vis[maxn];

inline int find(int x) { return x == belong[x] ? x : belong[x] = find(belong[x]); }

signed main()
{
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 2, n) scanf("%lld", &f[i]);
    REP(i, 1, n) belong[i] = i;
    REP(i, 1, n) { scanf("%lld%lld", &a[i].x, &a[i].y); Q.push(node(a[i].x, a[i].y, i)); sum += a[i].x; }
    vis[0] = true;
    while ( !Q.empty() ) 
    {
        node x = Q.top(); Q.pop();
        if ( vis[find(x.id)] || x.id != find(x.id) || x.x != a[x.id].x || x.y != a[x.id].y ) continue ;
        int y = find(f[x.id]);
        if ( vis[y] ) { sum -= x.x; ans += x.y * sum; vis[x.id] = true; continue ; } 
        ans += a[y].y * x.x; vis[x.id] = true;
        a[y].x += x.x; a[y].y += x.y; belong[x.id] = y;
        Q.push(node(a[y].x, a[y].y, y));
    }
    printf("%lld\n", ans);
    return 0;
}
