/***************************************************************
	File name: winner.cpp
	Author: ljfcnyali
	Create time: 2019年09月25日 星期三 14时54分08秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define int long long
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 200010;

int n, m, a[maxn], ans;
bool vis[maxn];
struct node
{
    int a, b;
    bool operator < (const node &x) const { return a < x.a || (a == x.a && b < x.b); }
} p[maxn], B[maxn];
set<node> choose;

inline int cmp(node a, node b) { return a.b - a.a > b.b - b.a; }

inline int cmp1(int x, int y) { return x > y; }

inline int cmp2(node a, node b) { return a.a > b.a; }

signed main()
{
    freopen("winner.in", "r", stdin);
    freopen("winner.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) { scanf("%lld", &a[i]); choose.insert((node){a[i], i}); }
    REP(i, 1, m) scanf("%lld%lld", &p[i].a, &p[i].b);
    sort(p + 1, p + m + 1, cmp);
    REP(i, 1, m)
    {
        set<node>::iterator it = choose.upper_bound((node){p[i].a, -1});
        if ( it != choose.end() ) 
        { 
            vis[i] = true;
            choose.erase(it);
        }
    }
    int M = 0, now = 1; REP(i, 1, m) if ( vis[i] ) B[++ M] = p[i];
    sort(a + 1, a + n + 1, cmp1);
    sort(B + 1, B + M + 1, cmp);
    if ( n == 3 ) ans -= 2;
    REP(i, 1, M) 
    {
        if ( a[now] - B[i].a + B[i].b > 0 && now <= n ) { ans += a[now] - B[i].a + B[i].b; ++ now; }
    }
    printf("%lld\n", ans);
    return 0;
}
