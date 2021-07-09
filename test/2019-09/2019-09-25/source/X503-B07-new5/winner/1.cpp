/***************************************************************
	File name: winner.cpp
	Author: ljfcnyali
	Create time: 2019年09月25日 星期三 14时54分08秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 100010;

int n, m, a[maxn], ans, vis[maxn];
struct node
{
    int a, b, id;
    bool operator < (const node &x) const { return a < x.a; }
} p[maxn], B[maxn];
vector<node> choose;

inline int cmp(node a, node b) { return a.b - a.a > b.b - b.a; }

inline int cmp1(int x, int y) { return x > y; }

inline int cmp2(node a, node b) { return a.a > b.a; }

signed main()
{
    freopen("winner3.in", "r", stdin);
    freopen("winner.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) { scanf("%lld", &a[i]); choose.push_back((node){a[i], i}); }
    REP(i, 1, m) scanf("%lld%lld", &p[i].a, &p[i].b);
    sort(choose.begin(), choose.end());
    sort(p + 1, p + m + 1, cmp);
    REP(i, 1, m)
    {
        int pos = upper_bound(choose.begin(), choose.end(), (node){p[i].a, 0}) - choose.begin();
        if ( pos < choose.size() ) 
        { 
            vis[i] = choose[pos].b;
            choose.erase(choose.begin() + pos);
        }
    }
    int M = 0, now = 1; REP(i, 1, m) if ( vis[i] ) B[++ M] = p[i];
    sort(a + 1, a + n + 1, cmp1);
    sort(B + 1, B + M + 1, cmp);
    REP(i, 1, M) 
        if ( a[now] - B[i].a + B[i].b > 0 && now <= n ) { ans += a[now] - B[i].a + B[i].b; ++ now; }
    printf("%lld\n", ans);
    return 0;
}
