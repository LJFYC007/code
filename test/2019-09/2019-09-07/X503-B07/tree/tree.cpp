/***************************************************************
	File name: tree.cpp
	Author: ljfcnyali
	Create time: 2019年09月07日 星期六 11时01分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 1010;
const int INF = 0x3f3f3f3f;

int n, d[maxn][maxn], l[maxn][maxn], r[maxn][maxn], dp[maxn][maxn], sum[maxn];
struct node
{
    int k, val;
    bool operator < (const node &a) const { return k < a.k; }
} a[maxn];

signed main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) scanf("%lld%lld", &a[i].k, &a[i].val); 
    sort(a + 1, a + n + 1);
    REP(i, 1, n - 1) REP(j, i + 1, n) if ( __gcd(a[i].k, a[j].k) != 1 ) d[i][j] = d[j][i] = 1;
    REP(i, 1, n) sum[i] = sum[i - 1] + a[i].val;
    REP(len, 1, n)
        REP(i, 1, n - len + 1)
        {
            int j = i + len - 1;
            dp[i][j] = l[i][j] = r[i][j] = -INF;
            REP(x, i, j)
            {
                int s = l[i][x - 1] + r[x + 1][j];
                if ( s >= 0 )
                {
                    s += sum[j] - sum[i - 1];
                    dp[i][j] = max(dp[i][j], s);
                    if ( d[i - 1][x] ) r[i][j] = max(r[i][j], s);
                    if ( d[x][j + 1] ) l[i][j] = max(l[i][j], s);
                }
            }
        }
    if ( dp[1][n] == -INF ) printf("-1\n");
    else printf("%lld\n", dp[1][n]);
    return 0;
}
