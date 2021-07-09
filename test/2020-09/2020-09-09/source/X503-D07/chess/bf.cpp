/***************************************************************
	File name: chess.cpp
	Author: ljfcnyali
	Create time: 2020年09月09日 星期三 19时04分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;

int T, n, q, sumx[maxn], sumy[maxn];
struct node 
{ 
    int x, y; 
    node (int a = 0, int b = 0) { x = a; y = b; }
    bool operator < (const node &a) const { return x - y < a.x - a.y; }
} a[maxn];

signed main()
{
    freopen("chess.in", "r", stdin);
    freopen("chess1.out", "w", stdout);
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld%lld", &n, &q);
        REP(i, 1, n) scanf("%lld%lld", &a[i].x, &a[i].y); 
        REP(i, 1, q)
        {
            node t; scanf("%lld%lld", &t.x, &t.y);
            int ans = 0;
            REP(j, 1, n) ans += max(abs(a[j].x - t.x), abs(a[j].y - t.y));
            printf("%lld\n", ans);
        }
        /*
        sort(a + 1, a + n + 1);
        REP(i, 1, n) { sumx[i] = sumx[i - 1] + a[i].x; sumy[i] = sumy[i - 1] + a[i].y; }
        REP(i, 1, q)
        {
            node t; scanf("%lld%lld", &t.x, &t.y);
            int pos = lower_bound(a + 1, a + n + 1, t) - a;
            int ans = sumy[pos] - t.y * pos + sumx[n] - sumx[pos] - t.x * (n - pos);
            printf("%lld\n", ans);
        }
        */
    }
    return 0;
}
