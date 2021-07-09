#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
typedef long long LL;
template<class T> int maxx(T a, T b) { return a > b ? a : b; }
template<class T> int minn(T a, T b) { return a < b ? a : b; }
template<class T> int abss(T a) { return a > 0 ? a : -a; }
#define max maxx
#define min minn
#define abs abss

const int maxn = 10010;

int dp[maxn], n, m, ans;

struct node
{
    int t, x, y;
} a[maxn];

inline int dis(int x1, int y1, int x2, int y2)
{
    return abs(x2 - x1) + abs(y2 - y1);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, m) dp[i] = 1;
    REP(i, 1, m)
    {
        scanf("%d%d%d", &a[i].t, &a[i].x, &a[i].y);
        REP(j, 1, i - 1)
        {
            int d = dis(a[i].x, a[i].y, a[j].x, a[j].y);
            if ( d <= a[i].t - a[j].t ) dp[i] = max(dp[i], dp[j] + 1);
        }
        ans = max(ans, dp[i]);
    }
    printf("%d\n", ans);
    return 0;
}
